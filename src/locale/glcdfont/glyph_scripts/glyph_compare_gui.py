#!/usr/bin/env python3
# Copyright (c) 2026 Aivaras Kasperaitis (@kasperaitis)
# SPDX-License-Identifier: GPL-3.0-only

"""Glyph Compare GUI

Features:
- Load two glcdfont C files (left/right)
- Side-by-side 5x7 rendered view for selected index
- Prev/Next and Jump to index
- Copy glyph from one side to the other (and save target file)
- Grid overview of all 256 glyphs with quick diff markers and click-to-select
- Export diff list

Usage: python scripts/glyph_compare_gui.py
"""

import tkinter as tk
from tkinter import filedialog, messagebox, ttk
import re
from pathlib import Path
from datetime import datetime
import os
import math

DEFAULT_LEFT  = Path(__file__).parent.parent / 'glcdfont_Latin.c'
DEFAULT_RIGHT = Path(__file__).parent.parent / 'glcdfont_Cyrillic.c'

ARRAY_RE = re.compile(r"static const unsigned char font\[\] PROGMEM = \{([\s\S]*?)\};")

# ── Light clean theme ────────────────────────────────────────────────────────
BG           = '#f0f0f0'   # window / frame background
SEC          = '#ffffff'   # secondary / panel fill
BORDER       = '#c0c0c0'   # generic border
FG           = '#1a1a1a'   # primary text
FG_DIM       = '#555555'   # secondary / muted text
ACCENT       = '#1565c0'   # accent (section titles, selection)
GREEN_SEL    = '#2e7d32'   # independent / local selection ring
DIFF_BORDER  = '#c62828'   # cell border when glyphs differ
CANVAS_BG    = '#ffffff'   # glyph canvas background
GRID_LINE    = '#999999'   # cell grid lines (matches glyph_creator)
PIXEL_ON     = '#000000'   # lit pixel fill (inset rect, like glyph_creator)
PIXEL_DIFF   = '#c62828'   # differing pixel fill in diff canvas

# ── Fonts ────────────────────────────────────────────────────────────────────
HEX_FONT    = ('Courier New', 10)
INFO_FONT   = ('Segoe UI', 9)
HEADER_FONT = ('Segoe UI', 10, 'bold')
STATUS_FONT = ('Segoe UI', 9)

# ── Glyph pixel scale (px per dot in the 5x7 grid) ──────────────────────────
SCALE = 24


def parse_font(fp: Path):
    txt = fp.read_text(encoding='utf-8')
    m = ARRAY_RE.search(txt)
    if not m:
        raise ValueError(f'No font array found in {fp}')
    # Remove comments so hex values appearing in comments (e.g. "0x80" in labels)
    # do not get mistaken for actual font bytes which would shift glyph indices.
    block = m.group(1)
    block = re.sub(r'/\*[\s\S]*?\*/', '', block)  # strip /* ... */ comments
    block = re.sub(r'//.*', '', block)               # strip // ... comments
    nums = re.findall(r'0x[0-9A-Fa-f]{1,2}', block)
    vals = [int(x, 16) for x in nums]
    if len(vals) != 256 * 5:
        # Some variants may omit trailing bytes; pad with zeros
        vals = (vals + [0] * (256 * 5))[:256 * 5]
    return vals


def format_font_array(vals):
    lines = []
    for i in range(0, len(vals), 16):
        slicev = vals[i:i+16]
        lines.append('  ' + ', '.join(f'0x{x:02X}' for x in slicev) + ',')
    return '\n'.join(lines)


def save_font(fp: Path, vals):
    """Save updated font bytes to file.

    This performs minimal in-place edits: only the changed hex tokens inside the
    font array are replaced. Comments and surrounding formatting are preserved.
    A backup of the original file is created and returned.
    """
    txt = fp.read_text(encoding='utf-8')
    m = ARRAY_RE.search(txt)
    if not m:
        raise ValueError('font array not found')
    block_start = m.start(1)
    block_end = m.end(1)
    block = txt[block_start:block_end]

    # Find hex tokens while skipping /* */ and // comments so we don't pick up tokens inside comments
    token_matches = []  # list of (start, end, text)
    i = 0
    L = len(block)
    while i < L:
        if block.startswith('/*', i):
            j = block.find('*/', i+2)
            if j == -1:
                break
            i = j + 2
            continue
        if block.startswith('//', i):
            j = block.find('\n', i+2)
            if j == -1:
                break
            i = j + 1
            continue
        mhex = re.match(r'0x[0-9A-Fa-f]{1,2}', block[i:])
        if mhex:
            s = mhex.group(0)
            start = i
            end = i + len(s)
            token_matches.append((start, end, s))
            i = end
            continue
        i += 1

    orig_vals = [int(t[2], 16) for t in token_matches] if token_matches else []
    # pad if original file omits trailing bytes
    if len(orig_vals) < 256 * 5:
        orig_vals = (orig_vals + [0] * (256 * 5))[:256 * 5]

    # Ensure provided vals length and compare
    if len(vals) < 256 * 5:
        vals = (vals + [0] * (256 * 5))[:256 * 5]

    changed = [i for i in range(256 * 5) if i < len(orig_vals) and vals[i] != orig_vals[i]]
    if not changed:
        return None

    # Perform replacements from end -> start so indices remain valid while editing
    block2 = block
    for idx in sorted(changed, reverse=True):
        if idx >= len(token_matches):
            # no token in file for this position; skip
            continue
        start, end, orig_text = token_matches[idx]
        new_val = vals[idx]
        hex_digits = orig_text[2:]
        width = len(hex_digits)
        has_lower = any(c.islower() for c in hex_digits if c.isalpha())
        fmt = 'x' if has_lower else 'X'
        if width == 1:
            # preserve single-digit formatting where possible
            new_hex = format(new_val, fmt)
            new_text = '0x' + new_hex
        else:
            new_text = '0x' + format(new_val, '02' + fmt)
        block2 = block2[:start] + new_text + block2[end:]

    newtxt = txt[:block_start] + block2 + txt[block_end:]

    # backup original then write
    bak = fp.with_suffix(fp.suffix + '.bak.' + datetime.utcnow().strftime('%Y%m%d%H%M%S'))
    Path(fp).rename(bak)
    fp.write_text(newtxt, encoding='utf-8')
    return bak


def apply_theme(root: tk.Tk):
    style = ttk.Style(root)
    style.theme_use('clam')
    style.configure('.', background=BG, foreground=FG, troughcolor='#d0d0d0',
                    bordercolor=BORDER, focuscolor=ACCENT, font=INFO_FONT)
    style.configure('TFrame',      background=BG)
    style.configure('TLabel',      background=BG, foreground=FG)
    style.configure('TSeparator',  background=BORDER)
    style.configure('TLabelframe', background=BG, bordercolor=BORDER)
    style.configure('TLabelframe.Label', background=BG, foreground=ACCENT,
                    font=('Segoe UI', 9, 'bold'))
    style.configure('TButton', background='#e0e0e0', foreground=FG,
                    bordercolor=BORDER, relief='flat', padding=(6, 3))
    style.map('TButton',
              background=[('active', ACCENT), ('pressed', ACCENT)],
              foreground=[('active', '#ffffff'), ('pressed', '#ffffff')])
    style.configure('TCheckbutton', background=BG, foreground=FG)
    style.map('TCheckbutton', background=[('active', BG)],
              indicatorcolor=[('selected', ACCENT)])
    style.configure('TEntry', fieldbackground='#ffffff', foreground=FG,
                    insertcolor=FG, bordercolor=BORDER)
    style.configure('TScrollbar', background='#d0d0d0', troughcolor='#e8e8e8',
                    bordercolor=BORDER, arrowcolor=FG)


class GlyphCompareApp:
    def __init__(self, root: tk.Tk):
        self.root = root
        root.title('Glyph Compare Tool — glcdfont')
        root.configure(bg=BG)
        apply_theme(root)

        self.left_fp    = DEFAULT_LEFT
        self.right_fp   = DEFAULT_RIGHT
        self.left_vals  = parse_font(self.left_fp)  if self.left_fp.exists()  else [0] * 1280
        self.right_vals = parse_font(self.right_fp) if self.right_fp.exists() else [0] * 1280
        self.index = 65

        # ── Font Files section ──────────────────────────────────────────────
        files_lf = ttk.LabelFrame(root, text=' Font Files ', padding=(10, 6))
        files_lf.pack(fill=tk.X, padx=10, pady=(10, 4))

        ttk.Label(files_lf, text='Left:', font=HEADER_FONT).grid(
            row=0, column=0, sticky='w')
        self.left_label = ttk.Label(files_lf, text=str(self.left_fp),
                                    foreground=FG_DIM, font=HEX_FONT)
        self.left_label.grid(row=0, column=1, sticky='w', padx=(6, 12))
        ttk.Button(files_lf, text='Load Left …', command=self.load_left, width=12).grid(
            row=0, column=2, padx=4)

        ttk.Label(files_lf, text='Right:', font=HEADER_FONT).grid(
            row=1, column=0, sticky='w', pady=(6, 0))
        self.right_label = ttk.Label(files_lf, text=str(self.right_fp),
                                     foreground=FG_DIM, font=HEX_FONT)
        self.right_label.grid(row=1, column=1, sticky='w', padx=(6, 12), pady=(6, 0))
        ttk.Button(files_lf, text='Load Right …', command=self.load_right, width=12).grid(
            row=1, column=2, padx=4, pady=(6, 0))

        # ── Glyph Preview section ───────────────────────────────────────────
        preview_lf = ttk.LabelFrame(root, text=' Glyph Preview ', padding=(10, 6))
        preview_lf.pack(fill=tk.X, padx=10, pady=4)

        def _glyph_panel(parent, title):
            f = ttk.Frame(parent)
            ttk.Label(f, text=title, font=HEADER_FONT, foreground=ACCENT).pack(pady=(0, 4))
            c = tk.Canvas(f, width=5 * SCALE, height=7 * SCALE,
                          bg=CANVAS_BG, highlightthickness=1, highlightbackground=BORDER)
            c.pack()
            lbl = ttk.Label(f, text='', font=HEX_FONT, foreground=FG_DIM)
            lbl.pack(pady=(4, 0))
            return f, c, lbl

        left_panel,  self.left_canvas,  self.left_hex  = _glyph_panel(preview_lf, 'Left')
        left_panel.pack(side=tk.LEFT, padx=16, pady=4)
        diff_panel,  self.diff_canvas,  self.diff_lbl  = _glyph_panel(preview_lf, 'Diff')
        diff_panel.pack(side=tk.LEFT, padx=16, pady=4)
        right_panel, self.right_canvas, self.right_hex = _glyph_panel(preview_lf, 'Right')
        right_panel.pack(side=tk.LEFT, padx=16, pady=4)

        # ── Navigation section ──────────────────────────────────────────────
        nav_lf = ttk.LabelFrame(root, text=' Navigation ', padding=(10, 6))
        nav_lf.pack(fill=tk.X, padx=10, pady=4)

        row1 = ttk.Frame(nav_lf)
        row1.pack(fill=tk.X, pady=(0, 6))
        ttk.Button(row1, text='◀ Prev',     command=self.prev,             width=8).pack(side=tk.LEFT, padx=(0, 3))
        ttk.Button(row1, text='Next ▶',     command=self.next,             width=8).pack(side=tk.LEFT, padx=3)
        ttk.Separator(row1, orient=tk.VERTICAL).pack(side=tk.LEFT, fill=tk.Y, padx=10)
        ttk.Button(row1, text='Left Grid',  command=self.open_left_grid,  width=11).pack(side=tk.LEFT, padx=3)
        ttk.Button(row1, text='Right Grid', command=self.open_right_grid, width=11).pack(side=tk.LEFT, padx=3)
        ttk.Separator(row1, orient=tk.VERTICAL).pack(side=tk.LEFT, fill=tk.Y, padx=10)
        ttk.Button(row1, text='Export Diff List', command=self.export_diffs, width=16).pack(side=tk.LEFT, padx=3)

        row2 = ttk.Frame(nav_lf)
        row2.pack(fill=tk.X)
        self.sync_var = tk.BooleanVar(value=True)
        ttk.Checkbutton(row2, text='Sync selection',
                        variable=self.sync_var, command=self._on_sync_toggle).pack(side=tk.LEFT, padx=(0, 4))
        ttk.Separator(row2, orient=tk.VERTICAL).pack(side=tk.LEFT, fill=tk.Y, padx=10)
        ttk.Label(row2, text='Index:').pack(side=tk.LEFT, padx=(4, 4))
        self.index_entry = ttk.Entry(row2, width=7, font=HEX_FONT)
        self.index_entry.pack(side=tk.LEFT)
        self.index_entry.insert(0, str(self.index))
        ttk.Button(row2, text='Go', command=self.goto, width=5).pack(side=tk.LEFT, padx=(4, 0))

        # ── Copy / Save section ─────────────────────────────────────────────
        copy_lf = ttk.LabelFrame(root, text=' Copy / Save ', padding=(10, 6))
        copy_lf.pack(fill=tk.X, padx=10, pady=(4, 6))
        ttk.Button(copy_lf, text='⟵  Copy Right → Left',
                   command=self.copy_r2l, width=22).pack(side=tk.LEFT, padx=(0, 4))
        ttk.Button(copy_lf, text='Copy Left → Right  ⟶',
                   command=self.copy_l2r, width=22).pack(side=tk.LEFT, padx=4)
        ttk.Separator(copy_lf, orient=tk.VERTICAL).pack(side=tk.LEFT, fill=tk.Y, padx=14)
        ttk.Button(copy_lf, text='💾  Save Left File',
                   command=self.save_left, width=18).pack(side=tk.LEFT, padx=(0, 4))
        ttk.Button(copy_lf, text='💾  Save Right File',
                   command=self.save_right, width=18).pack(side=tk.LEFT, padx=4)

        # ── Status bar ──────────────────────────────────────────────────────
        self.status = ttk.Label(root, text='', anchor='w',
                                font=STATUS_FONT, foreground=FG_DIM)
        self.status.pack(fill=tk.X, padx=10, pady=(0, 8))

        self.grid_windows = []
        self.left_grid  = GridWindow(self.root, self.left_vals, self.right_vals, self, side='left')
        self.right_grid = GridWindow(self.root, self.left_vals, self.right_vals, self, side='right')

        self.draw()

    def load_left(self):
        p = filedialog.askopenfilename(title='Select left glcdfont C file', filetypes=[('C files', '*.c'), ('All','*.*')])
        if not p: return
        self.left_fp = Path(p)
        self.left_label.config(text=str(self.left_fp))
        self.left_vals = parse_font(self.left_fp)
        if hasattr(self, 'left_grid'):
            self.left_grid.update_vals(self.left_vals, self.right_vals)
        if hasattr(self, 'right_grid'):
            self.right_grid.update_vals(self.left_vals, self.right_vals)
        self.draw()

    def load_right(self):
        p = filedialog.askopenfilename(title='Select right glcdfont C file', filetypes=[('C files', '*.c'), ('All','*.*')])
        if not p: return
        self.right_fp = Path(p)
        self.right_label.config(text=str(self.right_fp))
        self.right_vals = parse_font(self.right_fp)
        if hasattr(self, 'left_grid'):
            self.left_grid.update_vals(self.left_vals, self.right_vals)
        if hasattr(self, 'right_grid'):
            self.right_grid.update_vals(self.left_vals, self.right_vals)
        self.draw()

    def glyph_bytes(self, vals, idx):
        base = idx*5
        return vals[base:base+5]

    def render_glyph(self, canvas, bytesv, scale=SCALE, highlight=None):
        """Render a 5×7 glyph like glyph_creator: white bg, #999 grid lines,
        inset filled rect for lit pixels. highlight is a 5-element diff-mask."""
        canvas.delete('all')
        pad = max(2, scale // 8)
        for c in range(5):
            for r in range(7):
                x0 = c * scale
                y0 = r * scale
                x1 = x0 + scale
                y1 = y0 + scale
                # draw cell outline
                canvas.create_rectangle(x0, y0, x1, y1,
                                        outline=GRID_LINE, fill=CANVAS_BG)
                on = (bytesv[c] >> r) & 1
                is_diff = highlight and bool(highlight[c] & (1 << r))
                if is_diff:
                    # show differing pixel (lit or unlit) with red inset rect
                    canvas.create_rectangle(x0 + pad, y0 + pad,
                                            x1 - pad, y1 - pad,
                                            fill=PIXEL_DIFF, outline='')
                elif on:
                    canvas.create_rectangle(x0 + pad, y0 + pad,
                                            x1 - pad, y1 - pad,
                                            fill=PIXEL_ON, outline='')

    def draw(self):
        # When sync is ON, both previews show global index; when OFF, each preview shows its grid's local selection if present
        global_idx = self.index
        left_idx = global_idx
        right_idx = global_idx
        if not self.sync_var.get():
            if hasattr(self, 'left_grid') and hasattr(self.left_grid, 'local_index'):
                left_idx = self.left_grid.local_index
            if hasattr(self, 'right_grid') and hasattr(self.right_grid, 'local_index'):
                right_idx = self.right_grid.local_index

        self.index_entry.delete(0, tk.END)
        self.index_entry.insert(0, str(global_idx))

        lb = self.glyph_bytes(self.left_vals, left_idx)
        rb = self.glyph_bytes(self.right_vals, right_idx)
        self.render_glyph(self.left_canvas, lb)
        self.render_glyph(self.right_canvas, rb)
        diffmask = [lb[c] ^ rb[c] for c in range(5)]
        self.render_glyph(self.diff_canvas, [0]*5, highlight=diffmask)
        self.left_hex.config(text=' '.join(f'0x{x:02X}' for x in lb))
        self.right_hex.config(text=' '.join(f'0x{x:02X}' for x in rb))
        diffs = sum(1 for x in diffmask if x != 0)
        self.diff_lbl.config(text=f'{diffs} col{"s" if diffs != 1 else ""} differ')
        self.status.config(
            text=f'Index {global_idx} (0x{global_idx:02X})   '
                 f'Left[{left_idx}]  Right[{right_idx}]   '
                 f'{self.left_fp.name}  ↔  {self.right_fp.name}')

        # Refresh grid windows and ensure visibility depending on sync state
        for g in (getattr(self, 'left_grid', None), getattr(self, 'right_grid', None)):
            if g is None:
                continue
            g.update_vals(self.left_vals, self.right_vals)
            if self.sync_var.get():
                g.ensure_visible(global_idx)
            else:
                if hasattr(g, 'local_index'):
                    g.ensure_visible(g.local_index)

    def prev(self):
        if self.index>0:
            self.index -= 1
            self.draw()

    def next(self):
        if self.index<255:
            self.index += 1
            self.draw()

    def goto(self):
        try:
            v = int(self.index_entry.get(), 0)
            if 0 <= v <= 255:
                self.index = v
                self.draw()
        except Exception:
            messagebox.showerror('Error','Invalid index')

    def _side_selected_index(self, side):
        # Return the effective selected index for a side ('left'|'right').
        grid = getattr(self, f'{side}_grid', None)
        # If app-level sync is OFF and the grid has a local selection, use that; otherwise fall back to the global selection.
        if not self.sync_var.get():
            if grid and hasattr(grid, 'local_index'):
                return grid.local_index
        return self.index

    def copy_l2r(self):
        src = self._side_selected_index('left')
        dst = self._side_selected_index('right')
        lb = self.glyph_bytes(self.left_vals, src)
        self._set_bytes(self.right_vals, dst, lb)
        if hasattr(self, 'left_grid'):  self.left_grid.update_vals(self.left_vals, self.right_vals)
        if hasattr(self, 'right_grid'): self.right_grid.update_vals(self.left_vals, self.right_vals)
        self.draw()
        self.status.config(text=f'Copied  Left[{src}]  →  Right[{dst}]')

    def copy_r2l(self):
        src = self._side_selected_index('right')
        dst = self._side_selected_index('left')
        rb = self.glyph_bytes(self.right_vals, src)
        self._set_bytes(self.left_vals, dst, rb)
        if hasattr(self, 'left_grid'):  self.left_grid.update_vals(self.left_vals, self.right_vals)
        if hasattr(self, 'right_grid'): self.right_grid.update_vals(self.left_vals, self.right_vals)
        self.draw()
        self.status.config(text=f'Copied  Right[{src}]  →  Left[{dst}]')



    def _set_bytes(self, vals, idx, bytesv):
        base = idx*5
        for i in range(5):
            vals[base+i] = bytesv[i]

    def save_left(self):
        try:
            bak = save_font(self.left_fp, self.left_vals)
            if not bak:
                messagebox.showinfo('Saved', 'No changes detected — file not modified.')
            else:
                messagebox.showinfo('Saved', f'Saved:  {self.left_fp}\nBackup: {bak}')
        except Exception as e:
            messagebox.showerror('Error', str(e))

    def save_right(self):
        try:
            bak = save_font(self.right_fp, self.right_vals)
            if not bak:
                messagebox.showinfo('Saved', 'No changes detected — file not modified.')
            else:
                messagebox.showinfo('Saved', f'Saved:  {self.right_fp}\nBackup: {bak}')
        except Exception as e:
            messagebox.showerror('Error', str(e))

    def export_diffs(self):
        diffs = []
        for idx in range(256):
            if any(self.left_vals[idx*5 + i] != self.right_vals[idx*5 + i] for i in range(5)):
                diffs.append(idx)
        if not diffs:
            messagebox.showinfo('Diffs', 'No differences found')
            return
        p = filedialog.asksaveasfilename(defaultextension='.txt', filetypes=[('Text','*.txt')], title='Save diff list')
        if not p: return
        with open(p, 'w', encoding='utf-8') as fh:
            for idx in diffs:
                fh.write(f'0x{idx:02X}\n')
        messagebox.showinfo('Saved', f'Wrote {len(diffs)} entries to {p}')

    def _on_sync_toggle(self):
        # When switching sync ON, remove per-grid local selections and show global index everywhere.
        if self.sync_var.get():
            for g in (getattr(self, 'left_grid', None), getattr(self, 'right_grid', None)):
                if g is None:
                    continue
                if hasattr(g, 'local_index'):
                    try:
                        del g.local_index
                    except Exception:
                        pass
                g.ensure_visible(self.index)
        else:
            # When switching sync OFF, initialize each grid's local selection from the current global index
            for g in (getattr(self, 'left_grid', None), getattr(self, 'right_grid', None)):
                if g is None:
                    continue
                g.local_index = self.index
                g.ensure_visible(g.local_index)
        self.draw()
    def open_grid(self):
        # kept for compatibility - focus left & right grids
        self.open_left_grid()
        self.open_right_grid()

    def open_left_grid(self):
        if not hasattr(self, 'left_grid') or self.left_grid is None:
            self.left_grid = GridWindow(self.root, self.left_vals, self.right_vals, self, side='left')
        else:
            try:
                self.left_grid.deiconify()
                self.left_grid.lift()
            except Exception:
                self.left_grid = GridWindow(self.root, self.left_vals, self.right_vals, self, side='left')

    def open_right_grid(self):
        if not hasattr(self, 'right_grid') or self.right_grid is None:
            self.right_grid = GridWindow(self.root, self.left_vals, self.right_vals, self, side='right')
        else:
            try:
                self.right_grid.deiconify()
                self.right_grid.lift()
            except Exception:
                self.right_grid = GridWindow(self.root, self.left_vals, self.right_vals, self, side='right')

    def focus_grid(self):
        if hasattr(self, 'grid_canvas'):
            self.grid_canvas.focus_set()




class GridWindow(tk.Toplevel):
    # 256-glyph overview: one tk.Canvas per glyph, responsive reflowing columns

    CELL_PAD = 1   # padx/pady passed to .grid()
    CELL_CS  = 8   # pixel scale

    def __init__(self, parent, left_vals, right_vals, app, side='left'):
        super().__init__(parent)
        self.side       = side
        self.app        = app
        self.left_vals  = left_vals
        self.right_vals = right_vals
        self.cellsize   = self.CELL_CS
        self.cols       = 20          # updated dynamically
        self._syncing   = False
        self._cell_canvases = {}      # idx -> tk.Canvas
        self._built_cols    = None    # last cols used in _rebuild_cells

        self.configure(bg=BG)
        self.title(f'Glyph Grid \u2014 {side.capitalize()} Side')
        self.resizable(True, True)

        if not hasattr(self.app, 'grid_windows'):
            self.app.grid_windows = []
        self.app.grid_windows.append(self)

        # Control bar
        ctrl = ttk.Frame(self, padding=(6, 4))
        ctrl.pack(side=tk.TOP, fill=tk.X)
        side_label = 'Left' if side == 'left' else 'Right'
        ttk.Label(ctrl, text=f'{side_label} Grid', font=HEADER_FONT,
                  foreground=ACCENT).pack(side=tk.LEFT, padx=(0, 10))
        ttk.Button(ctrl, text='Select \u2192 Main',
                   command=self._apply_local_to_main).pack(side=tk.LEFT, padx=4)

        ttk.Separator(self, orient=tk.HORIZONTAL).pack(fill=tk.X)

        # Legend
        legend = ttk.Frame(self, padding=(6, 3))
        legend.pack(fill=tk.X)
        def _dot(parent, color, text):
            c = tk.Canvas(parent, width=12, height=12, bg=BG, highlightthickness=0)
            c.pack(side=tk.LEFT)
            c.create_rectangle(1, 1, 11, 11, outline=color, width=2)
            ttk.Label(parent, text=text, font=STATUS_FONT,
                      foreground=FG_DIM).pack(side=tk.LEFT, padx=(2, 10))
        _dot(legend, DIFF_BORDER, 'Differs')
        _dot(legend, ACCENT,      'Synced sel.')
        _dot(legend, GREEN_SEL,   'Local sel.')

        ttk.Separator(self, orient=tk.HORIZONTAL).pack(fill=tk.X)

        # Scrollable area
        outer = ttk.Frame(self)
        outer.pack(fill=tk.BOTH, expand=True)

        self.canvas = tk.Canvas(outer, bg=BG, highlightthickness=0)
        self.vs = ttk.Scrollbar(outer, orient=tk.VERTICAL, command=self._on_vscroll)
        self.canvas.configure(yscrollcommand=self._on_yscroll)
        self.vs.pack(side=tk.RIGHT, fill=tk.Y)
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        self._container = tk.Frame(self.canvas, bg=BG)
        self._cwin_id = self.canvas.create_window((0, 0), window=self._container, anchor='nw')
        self._inner = tk.Frame(self._container, bg=BG)
        self._inner.place(relx=0.5, y=0, anchor='n')
        self._inner.bind('<Configure>', self._on_inner_configure)

        self.canvas.bind_all('<MouseWheel>', self.on_mousewheel)

        # Bind canvas resize -> reflow columns
        self.canvas.bind('<Configure>', self._on_canvas_configure)

        # Initial size: 20 cols, 10 rows visible
        cs = self.cellsize
        slot_w = self._cell_slot()
        slot_h = cs * 7 + 2 + 18    # canvas + border + label row at 8pt
        scr_w  = self.winfo_screenwidth()
        scr_h  = self.winfo_screenheight()
        win_w  = min(20 * slot_w + 22, scr_w - 40)   # +22 for scrollbar
        win_h  = min(10 * slot_h + 100, scr_h - 80)  # +100 for header/legend
        self.geometry(f'{win_w}x{win_h}')
        self.minsize(slot_w * 2 + 24, slot_h * 2 + 100)

    # ── helpers ───────────────────────────────────────────────────────────────

    def _cell_slot(self):
        """Total pixel width/height consumed per grid column."""
        cs = self.cellsize
        p  = self.CELL_PAD
        return cs * 5 + 2 + p * 2   # canvas_w + 2*highlightthick + 2*padx

    def _compute_cols(self, available_w):
        return max(1, available_w // self._cell_slot())

    # ── cell (re-)building ────────────────────────────────────────────────────

    def _rebuild_cells(self, cols):
        if cols == self._built_cols:
            return
        self._built_cols    = cols
        self.cols           = cols
        self._cell_canvases = {}

        for widget in self._inner.winfo_children():
            widget.destroy()

        cs = self.cellsize
        p  = self.CELL_PAD
        for idx in range(256):
            r = idx // cols
            c = idx % cols
            cc = tk.Canvas(self._inner, width=cs * 5, height=cs * 7,
                           bg='white', highlightthickness=1,
                           highlightbackground='#cccccc')
            cc.grid(row=r * 2, column=c, padx=p, pady=p)
            self._cell_canvases[idx] = cc
            cc.bind('<Button-1>',        lambda e, i=idx: self._on_cell_click(i))
            cc.bind('<Double-Button-1>', lambda e, i=idx: self._on_cell_dbl(i))
            # show decimal index for clarity
            tk.Label(self._inner, text=str(idx), anchor='center',
                     font=('Courier New', 8), foreground=FG_DIM, bg=BG
                     ).grid(row=r * 2 + 1, column=c)

        self._inner.update_idletasks()
        self.after_idle(self._update_scrollregion)
        self.draw_grid()

    def _on_inner_configure(self, event):
        self.after_idle(self._update_scrollregion)

    def _on_canvas_configure(self, event):
        if event.width < 10:
            return
        self._last_canvas_w = event.width
        self.canvas.itemconfigure(self._cwin_id, width=event.width)
        new_cols = self._compute_cols(event.width)
        self._rebuild_cells(new_cols)
        self.after_idle(self._update_scrollregion)

    def _update_scrollregion(self):
        w = getattr(self, '_last_canvas_w', 0) or self.canvas.winfo_width()
        if w < 10:
            return
        h = self._inner.winfo_reqheight()
        if h < 1:
            return
        self._container.configure(height=h)
        self.canvas.configure(scrollregion=(0, 0, w, h))

    # keep alias so any other callers still work
    def _recentre(self):
        self._update_scrollregion()

    # ── data helpers ──────────────────────────────────────────────────────────

    def destroy(self):
        try:
            self.app.grid_windows.remove(self)
        except Exception:
            pass
        super().destroy()

    def update_vals(self, left_vals, right_vals):
        self.left_vals  = left_vals
        self.right_vals = right_vals
        self.draw_grid()

    def vals_for(self, idx):
        if self.side == 'left':
            return self.left_vals[idx * 5:idx * 5 + 5]
        return self.right_vals[idx * 5:idx * 5 + 5]

    def other_vals_for(self, idx):
        if self.side == 'left':
            return self.right_vals[idx * 5:idx * 5 + 5]
        return self.left_vals[idx * 5:idx * 5 + 5]

    def glyph_diff(self, idx):
        a = self.vals_for(idx)
        b = self.other_vals_for(idx)
        return any(a[i] != b[i] for i in range(5))

    # ── drawing ───────────────────────────────────────────────────────────────

    def draw_grid(self):
        cs         = self.cellsize
        sel_global = self.app.index
        sel_local  = getattr(self, 'local_index', None)
        sync_on    = getattr(self.app, 'sync_var', None) and self.app.sync_var.get()

        for idx in range(256):
            cc = self._cell_canvases.get(idx)
            if cc is None:
                continue

            is_diff = self.glyph_diff(idx)
            vals    = self.vals_for(idx)

            cc.configure(background='#ffe8e8' if is_diff else 'white')
            cc.delete('all')

            for col in range(5):
                for row in range(7):
                    if (vals[col] >> row) & 1:
                        x0 = col * cs
                        y0 = row * cs
                        # draw full‑size square so left and right edges both touch
                        cc.create_rectangle(x0, y0, x0 + cs, y0 + cs,
                                            fill='black', outline='')

            if sync_on:
                if idx == sel_global:
                    cc.configure(highlightthickness=2, highlightbackground=ACCENT)
                else:
                    cc.configure(highlightthickness=1,
                                 highlightbackground=DIFF_BORDER if is_diff else '#cccccc')
            else:
                if idx == sel_local:
                    cc.configure(highlightthickness=2, highlightbackground=GREEN_SEL)
                elif idx == sel_global and sel_global != sel_local:
                    cc.configure(highlightthickness=2, highlightbackground=ACCENT)
                else:
                    cc.configure(highlightthickness=1,
                                 highlightbackground=DIFF_BORDER if is_diff else '#cccccc')

    # ── interaction ───────────────────────────────────────────────────────────

    def _on_cell_click(self, idx):
        if getattr(self.app, 'sync_var', None) and self.app.sync_var.get():
            self.app.index = idx
            self.app.draw()
        else:
            self.local_index = idx
            self.draw_grid()
            self.ensure_visible(idx)
            try:
                self.app.draw()
            except Exception:
                pass

    def _on_cell_dbl(self, idx):
        self.app.index = idx
        self.app.draw()

    def _on_vscroll(self, *args):
        self.canvas.yview(*args)
        frac = self.canvas.yview()[0]
        if self._syncing:
            return
        try:
            self._syncing = True
            for gw in getattr(self.app, 'grid_windows', []):
                if gw is not self:
                    gw.canvas.yview_moveto(frac)
        finally:
            self._syncing = False

    def _on_yscroll(self, first, last):
        self.vs.set(first, last)
        if self._syncing:
            return
        frac = float(first)
        try:
            self._syncing = True
            for gw in getattr(self.app, 'grid_windows', []):
                if gw is not self:
                    gw.canvas.yview_moveto(frac)
        finally:
            self._syncing = False

    def on_mousewheel(self, event):
        delta = -1 * (event.delta // 120)
        self.canvas.yview_scroll(delta, 'units')
        frac = self.canvas.yview()[0]
        try:
            self._syncing = True
            for gw in getattr(self.app, 'grid_windows', []):
                if gw is not self:
                    gw.canvas.yview_moveto(frac)
        finally:
            self._syncing = False

    def _apply_local_to_main(self):
        if hasattr(self, 'local_index'):
            self.app.index = self.local_index
            self.app.draw()

    def ensure_visible(self, idx):
        self.canvas.update_idletasks()
        bbox = self.canvas.bbox('all')
        if not bbox:
            return
        total_h = bbox[3] - bbox[1]
        view_h  = self.canvas.winfo_height()
        if view_h <= 1 or total_h <= view_h:
            return
        cs     = self.cellsize
        p      = self.CELL_PAD
        cell_h = cs * 7 + 2 + p * 2 + 18
        row    = idx // max(1, self.cols)
        y      = row * cell_h
        max_scroll = max(1, total_h - view_h)
        frac   = min(max(0.0, (y - view_h / 2) / max_scroll), 1.0)
        self.canvas.yview_moveto(frac)


if __name__ == '__main__':
    root = tk.Tk()
    app  = GlyphCompareApp(root)
    root.mainloop()
