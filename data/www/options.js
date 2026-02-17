// Options/Settings page specific functions

const localTZjson = 'timezones.json';
let timezoneData = null;

// Load timezones on DOM ready
document.addEventListener('DOMContentLoaded', () => { loadTimezones(); });

/** TIMEZONES **/
async function loadTimezones() {
  try {
    const response = await fetch(localTZjson);
    if (!response.ok) {
      throw new Error(`HTTP ${response.status}: ${response.statusText}`);
    }
    timezoneData = await response.json();
    populateTZDropdown(timezoneData);
  } catch (err) {
    console.error("Failed to load local timezones:", err);
  }
}

function populateTZDropdown(zones) {
  const select = getId('tz_name');
  const input = getId('tzposix');
  if (!select || !input) {
    return;
  }
  select.innerHTML = '';
  input.readOnly = true;
  Object.entries(zones).forEach(([zone, posix]) => {
    const option = document.createElement('option');
    option.value = posix;
    option.textContent = zone.length > 60 ? zone.substring(0, 57) + '...' : zone;
    select.appendChild(option);
  });
  // Handle dropdown changes
  select.addEventListener('change', () => {
    input.value = select.value;
  });
}

function applyTZ(){
  websocket.send("tz_name="+getId("tz_name").selectedOptions[0].text);
  websocket.send("tzposix="+getId("tzposix").value);
  websocket.send("sntp2="+getId("sntp2").value);
  websocket.send("sntp1="+getId("sntp1").value);
}

/** MQTT **/
function applyMQTT(){
  websocket.send("mqttenable="+getId("mqttenable").value);
  websocket.send("mqtthost="+getId("mqtthost").value);
  websocket.send("mqttport="+getId("mqttport").value);
  websocket.send("mqttuser="+getId("mqttuser").value);
  websocket.send("mqttpass="+getId("mqttpass").value);
  websocket.send("mqtttopic="+getId("mqtttopic").value);
}

/** WEATHER **/
function applyWeather(){
  let key=getId("wkey").value;
  if(key!=""){
    websocket.send("lat="+getId("wlat").value);
    websocket.send("lon="+getId("wlon").value);
    websocket.send("key="+key);
  }
}

/** WIFI **/
function handleWiFiData(fileData) {
  if (!fileData) return;
  var lines = fileData.split('\n');
  for(var i = 0;i < lines.length;i++){
    let line = lines[i].split('\t');
    if(line.length==2){
      getId("ssid"+i).value=line[0].trim();
      getId("pass"+i).attr('data-pass', line[1].trim());
    }
  }
}

function getWiFi(path){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (xhr.readyState == 4) {
      if (xhr.status == 200) {
        handleWiFiData(xhr.responseText);
      } else {
        handleWiFiData(null);
      }
    }
  };
  xhr.open("GET", path);
  xhr.send(null);
}

function submitWiFi(){
  var output="";
  var items=document.getElementsByClassName("credential");
  for (var i = 0; i <= items.length - 1; i++) {
    inputs=items[i].getElementsByTagName("input");
    if(inputs[0].value == "") continue;
    let ps=inputs[1].value==""?inputs[1].dataset.pass:inputs[1].value;
    output+=inputs[0].value+"\t"+ps+"\n";
  }
  if(output!=""){ // Well, let's say, quack.
    let file = new File([output], "tempwifi.csv",{type:"text/plain;charset=utf-8", lastModified:new Date().getTime()});
    let container = new DataTransfer();
    container.items.add(file);
    let fileuploadinput=getId("file-upload");
    fileuploadinput.files = container.files;
    var formData = new FormData();
    formData.append("wifile", fileuploadinput.files[0]);
    var xhr = new XMLHttpRequest();
    xhr.open("POST",`http://${hostname}/upload`,true);
    xhr.send(formData);
    fileuploadinput.value = '';
    getId("settingscontent").innerHTML="<h2>Settings saved. Rebooting...</h2>";
    getId("settingsdone").classList.add("hidden");
    getId("navigation").classList.add("hidden");
    setTimeout(function(){ window.location.href=`http://${hostname}/`; }, 10000);
  }
}

/** SYSTEM **/
function rebootSystem(info){
  getId("settingscontent").innerHTML=`<h2>${info}</h2>`;
  getId("settingsdone").classList.add("hidden");
  getId("navigation").classList.add("hidden");
  setTimeout(function(){ window.location.href=`http://${hostname}/`; }, 5000);
}

/** TOOLS AKA DANGERZONE **/
function showDangerConfirm(buttonId) {
  hideDangerConfirm();
  const btn = getId(buttonId);
  if(btn) btn.classList.remove('hidden');
}

function hideDangerConfirm() {
  const btns = ['dz_reboot', 'dz_format', 'dz_reset'];
  btns.forEach(id => {
    const btn = getId(id);
    if(btn) btn.classList.add('hidden');
  });
}

function checkDangerZone() {
  const sw1 = getId('dangerzone_sw1');
  const sw2 = getId('dangerzone_sw2');
  const sw3 = getId('dangerzone_sw3');
  if(!sw1 || !sw2 || !sw3) return;
  
  const allChecked = sw1.classList.contains('checked') && 
                     sw2.classList.contains('checked') && 
                     sw3.classList.contains('checked');
  
  const dangerzone = getId('dangerzone');
  const txt = getId('dangerzone_txt');
  
  if(allChecked) {
    if(dangerzone) dangerzone.classList.remove('hidden');
    if(txt) {
      const replacement = txt.getAttribute('replacement');
      if(replacement) txt.textContent = replacement;
    }
  } else {
    if(dangerzone) dangerzone.classList.add('hidden');
    if(txt) txt.textContent = 'Turn on all switches to unlock';
  }
}

function toggleDangerZoneSwitch(switchId) {
  const sw = getId(switchId);
  if(!sw) return;
  sw.classList.toggle('checked');
  hideDangerConfirm();
  checkDangerZone();
}

function initDangerZone() {
  const switches = ['dangerzone_sw1', 'dangerzone_sw2', 'dangerzone_sw3'];
  switches.forEach(id => {
    const sw = getId(id);
    if(sw) sw.classList.remove('checked');
  });
  
  const txt = getId('dangerzone_txt');
  if(txt) txt.textContent = 'Turn on all switches to unlock';
  
  const dangerzone = getId('dangerzone');
  if(dangerzone) dangerzone.classList.add('hidden');
  
  hideDangerConfirm();
}
