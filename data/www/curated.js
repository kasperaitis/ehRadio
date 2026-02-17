const gateway = `ws://${window.location.hostname}/ws`;
let websocket;
let indexData = [];
let currentPlaylistData = null;
let currentPlaylistFile = '';

window.addEventListener('load', onCuratedLoad);

function onCuratedLoad(event) {
  // Set curated source info if available
  if (typeof curatedName !== 'undefined' && curatedName) {
    document.getElementById('curatedSource').textContent = curatedName;
    document.getElementById('curatedBy').innerHTML = `<a target="_blank" href="${curatedLink || '#'}">${curatedName}</a>`;
  }

  // Event listeners
  document.getElementById('loadListsBtn').addEventListener('click', loadCuratedIndex);
  document.getElementById('replaceBtn').addEventListener('click', () => importPlaylist('replace'));
  document.getElementById('mergeBtn').addEventListener('click', () => importPlaylist('merge'));
  document.getElementById('backToIndexBtn').addEventListener('click', backToIndex);
  document.getElementById('curateddone').addEventListener('click', () => { window.location.href = '/'; });

  // Initialize WebSocket
  initCuratedWebSocket();
}

function initCuratedWebSocket() {
  console.log('[Curated] Opening WebSocket connection...');
  websocket = new WebSocket(gateway);
  websocket.onopen = onCuratedWSOpen;
  websocket.onclose = onCuratedWSClose;
  websocket.onmessage = onCuratedWSMessage;
}

function onCuratedWSOpen(event) {
  console.log('[Curated] WebSocket connection opened');
}

function onCuratedWSClose(event) {
  console.log('[Curated] WebSocket connection closed');
  setTimeout(initCuratedWebSocket, 2000);
}

function onCuratedWSMessage(event) {
  try {
    const data = JSON.parse(event.data);
    
    if (data.curated_index_done) {
      console.log('[Curated] Index download complete, fetching index...');
      fetchIndex();
    } else if (data.curated_playlist_done) {
      console.log('[Curated] Playlist download complete, fetching playlist...');
      fetchPlaylist();
    } else if (data.curated_failed) {
      console.error('[Curated] Download failed');
      showLoadStatus('Failed to download. Check network connection.', true);
      enableLoadButton();
    } else if (data.curated_ready) {
      console.log('[Curated] Playlist ready for review, mode:', data.mode);
      // Store the mode for the editor
      sessionStorage.setItem('pl_import_mode', data.mode);
      sessionStorage.setItem('pl_import_review', 'true');
      // Redirect to player to open editor
      window.location.replace('/');
    } else if (data.curated_import_failed) {
      console.error('[Curated] Import failed');
      alert('Failed to prepare playlist. Please try again.');
    }
  } catch (e) {
    console.error('[Curated] Error parsing WebSocket message:', e);
  }
}

function loadCuratedIndex() {
  console.log('[Curated] Requesting index download...');
  console.log('[Curated] WebSocket ready state:', websocket.readyState);
  showLoadStatus('Downloading curated lists...', false);
  disableLoadButton();
  
  // Send WebSocket command to trigger download
  console.log('[Curated] Sending command: loadindex=');
  websocket.send('loadindex=');
  console.log('[Curated] Command sent');
}

function fetchIndex() {
  fetch('curated.json?t=' + Date.now())
    .then(response => {
      if (!response.ok) throw new Error('Failed to fetch index');
      return response.json();
    })
    .then(data => {
      indexData = data || [];
      displayIndex();
      showLoadStatus('', false);
    })
    .catch(error => {
      console.error('[Curated] Error fetching index:', error);
      showLoadStatus('Error loading index file', true);
    })
    .finally(() => {
      enableLoadButton();
    });
}

function displayIndex() {
  const indexTable = document.getElementById('indexTable');
  indexTable.innerHTML = '';
  
  if (!indexData || indexData.length === 0) {
    indexTable.innerHTML = '<tr><td colspan="3" class="importantmessage">No playlists available</td></tr>';
    document.getElementById('indexView').classList.remove('hidden');
    return;
  }
  
  indexData.forEach((playlist, idx) => {
    const row = document.createElement('tr');
    row.innerHTML = `
      <td class="station-name">${escapeHtml(playlist.name || 'Unnamed')}</td>
      <td class="station-genre">${escapeHtml(playlist.total ? playlist.total + ' stations' : '')}</td>
      <td class="station-actions">
        <button class="searchbutton" data-index="${idx}" data-action="load">Load</button>
      </td>
    `;
    indexTable.appendChild(row);
  });
  
  // Add click handler for Load buttons
  indexTable.addEventListener('click', (event) => {
    const button = event.target.closest('button[data-action="load"]');
    if (button) {
      const index = parseInt(button.dataset.index);
      loadPlaylist(indexData[index]);
    }
  });
  
  document.getElementById('indexView').classList.remove('hidden');
}

function loadPlaylist(playlist) {
  if (!playlist || !playlist.json) {
    console.error('[Curated] Invalid playlist data');
    return;
  }
  
  currentPlaylistFile = playlist.json;
  console.log('[Curated] Requesting playlist download:', currentPlaylistFile);
  
  // Hide index, show loading in playlist view
  document.getElementById('indexView').classList.add('hidden');
  document.getElementById('playlistView').classList.remove('hidden');
  document.getElementById('playlistTitle').textContent = 'Loading...';
  document.getElementById('playlistDescription').textContent = '';
  document.getElementById('playlistTable').innerHTML = '<tr><td class="importantmessage" colspan="4">Downloading playlist...</td></tr>';
  
  // Send WebSocket command to trigger download
  websocket.send('loadplaylist=' + playlist.json);
}

function fetchPlaylist() {
  fetch('pl_import.json?t=' + Date.now())
    .then(response => {
      if (!response.ok) throw new Error('Failed to fetch playlist');
      return response.text();
    })
    .then(text => {
      // Parse JSONL format (JSON Lines)
      const lines = text.trim().split('\n');
      const stations = [];
      
      for (const line of lines) {
        const trimmed = line.trim();
        if (trimmed.length === 0) continue;
        
        try {
          const station = JSON.parse(trimmed);
          if (station.name && station.url) {
            stations.push(station);
          }
        } catch (e) {
          console.error('[Curated] Error parsing line:', trimmed, e);
        }
      }
      
      // Find the playlist name from indexData
      const playlist = indexData.find(p => p.json === currentPlaylistFile);
      const playlistName = playlist ? playlist.name : 'Playlist';
      
      currentPlaylistData = {
        name: playlistName,
        stations: stations
      };
      
      displayPlaylist(currentPlaylistData);
    })
    .catch(error => {
      console.error('[Curated] Error fetching playlist:', error);
      document.getElementById('playlistTable').innerHTML = '<tr><td class="importantmessage" colspan="4">Error loading playlist file</td></tr>';
    });
}

function displayPlaylist(data) {
  document.getElementById('playlistTitle').textContent = data.name || 'Playlist';
  document.getElementById('playlistDescription').innerHTML = data.description ? `<p>${escapeHtml(data.description)}</p>` : '';
  
  const playlistTable = document.getElementById('playlistTable');
  playlistTable.innerHTML = '';
  
  const stations = data.stations || [];
  if (stations.length === 0) {
    playlistTable.innerHTML = '<tr><td colspan="4" class="importantmessage">No stations in this playlist</td></tr>';
    return;
  }
  
  stations.forEach((station, idx) => {
    const row = document.createElement('tr');
    row.innerHTML = `
      <td class="station-name">${escapeHtml(station.name || station.url)}</td>
      <td class="station-url">${escapeHtml(station.url)}</td>
      <td class="station-actions">
        <button class="searchbutton" data-index="${idx}" data-action="preview" title="Preview">▶</button>
      </td>
    `;
    playlistTable.appendChild(row);
  });
  
  // Add click handler for Preview buttons
  playlistTable.addEventListener('click', (event) => {
    const button = event.target.closest('button[data-action="preview"]');
    if (button) {
      const index = parseInt(button.dataset.index);
      const station = stations[index];
      if (station && station.url) {
        // Use playStation function from playstation.js
        if (typeof playStation === 'function') {
          playStation(station.url, station.name || station.url, false);
        } else {
          console.error('[Curated] playStation function not available');
        }
      }
    }
  });
}

function importPlaylist(mode) {
  if (mode !== 'replace' && mode !== 'merge') {
    console.error('[Curated] Invalid import mode:', mode);
    return;
  }
  
  // Verify that a playlist was actually loaded
  if (!currentPlaylistFile || !currentPlaylistData) {
    console.error('[Curated] No playlist loaded');
    alert('Please load a playlist first by clicking on one from the list.');
    return;
  }
  
  console.log('[Curated] Importing playlist with mode:', mode);
  
  // Send WebSocket command to import the playlist
  websocket.send('curated_import=' + mode);
}

function backToIndex() {
  document.getElementById('playlistView').classList.add('hidden');
  document.getElementById('indexView').classList.remove('hidden');
  currentPlaylistData = null;
  currentPlaylistFile = '';
}

function showLoadStatus(message, isError) {
  const statusEl = document.getElementById('loadStatus');
  if (message) {
    statusEl.textContent = message;
    statusEl.classList.remove('hidden');
    if (isError) {
      statusEl.style.color = 'red';
    } else {
      statusEl.style.color = '';
    }
  } else {
    statusEl.classList.add('hidden');
  }
}

function disableLoadButton() {
  const btn = document.getElementById('loadListsBtn');
  btn.disabled = true;
  btn.style.opacity = '0.5';
}

function enableLoadButton() {
  const btn = document.getElementById('loadListsBtn');
  btn.disabled = false;
  btn.style.opacity = '1';
}

function escapeHtml(text) {
  const div = document.createElement('div');
  div.textContent = text;
  return div.innerHTML;
}
