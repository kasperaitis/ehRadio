// Shared station preview/play functionality for search and playlist editor
// Sends station to device for playback

function sendStationAction(name, url, addtoplaylist) {
  if (!name || !url) {
    console.error('Invalid station data:', { name, url });
    return;
  }
  
  const label = addtoplaylist ? "Added to playlist: " : "Preview: ";
  const formData = new URLSearchParams();
  formData.append('name', name);
  formData.append('url', url);
  formData.append('addtoplaylist', addtoplaylist);
  
  fetch('/search', {
    method: 'POST',
    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
    body: formData
  })
  .then(response => {
    if (!response.ok) throw new Error('Action failed');
    return response.text();
  })
  .then(responseText => {
    console.log(label + name, 'Response:', responseText);
  })
  .catch(error => console.error('Error sending station action:', error));
}
