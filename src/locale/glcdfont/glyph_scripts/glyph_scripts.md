# Developer Scripts

This project includes two helper utilities (Python 3) for working with the
5x7 `glcdfont` font used by ehRadio.  They are primarily intended for
maintainers who need to inspect or tweak individual glyphs or compare
variant fonts.

Both tools are GUI applications built on `tkinter` but also have minimal CLI
fallbacks so they can be imported/inspected in headless environments.

---

## glyph_creator_gui.py

A simple 5x7 glyph editor for a single font file.

**Features**

* Load an existing `glcdfont` C source file and parse the `font[]` array.
* Display a 5×7 grid for the currently selected glyph; click cells to toggle
  pixels on/off.
* Show the selected glyph's hex and binary bytes.
* Navigate glyphs by index with prev/next or jump-to controls.
* Copy the current glyph to an internal clipboard or paste from the clipboard.
* Save modifications back to the original file (creates a timestamped backup).
* Export the byte sequence to clipboard or external file.

Usage:

```sh
python scripts/glyph_creator_gui.py
```

If `tkinter` is not available, the script can still be imported without
error, but the GUI will not be functional.

---

## glyph_compare_gui.py

Side‑by‑side comparison tool for two `glcdfont` files.

**Features**

* Load two font files (`left`/`right` panes).  Defaults point at the
  Latin/Cyrillic builds under `src/locale/glcdfont`.
* Render any glyph index from 0–255 in both panes.
* Overview grid showing all 256 glyphs; differing cells are highlighted.
* Click a cell to select that glyph for closer inspection.
* Copy a glyph from one side to the other and save the target file.
* Export a list of differing indices (useful for generating change logs).

Usage:

```sh
python scripts/glyph_compare_gui.py
```

Requires `tkinter`.  The script will still parse fonts in a non‑GUI
environment but cannot display windows.

---

Both scripts are licensed GPL‑3.0‑only (see headers) and were written by
Aivaras Kasperaitis (@kasperaitis) as part of the ehRadio toolchain.
