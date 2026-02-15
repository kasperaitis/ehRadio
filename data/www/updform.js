// Online update checker functionality for update.html

function initOnlineUpdateChecker() {
  if (onlineUpdCapable) {
    getId('check_online_update').classList.remove('hidden');
    getId('check_online_update').value = "Check for Online Update";
    getId('check_online_update').disabled = false;
    getId("update_url").href = "/update.html";
    console.log("Online Update is available");
  } else {
    getId('check_online_update').classList.add('hidden');
    getId("update_url").href = updateUrl;
    console.log("Online Update not available");
  }
}

function checkOnlineUpdate(button) {
  if (button.value === "Check for Online Update") {
    console.log("Checking for online update");
    button.value = "Checking...";
    button.disabled = true;
    fetch('/onlineupdatecheck')
      .then(response => response.text())
      .then(data => {
        console.log("Check update response:", data);
        // The server will send WebSocket messages with the actual results so just wait
      })
      .catch(error => {
        console.error("Error checking for updates:", error);
        button.value = "Check for Online Update";
        button.disabled = false;
      });
  } else if (button.value.startsWith("Update to")) {
    console.log("Starting online update via HTTP");
    // Show and reset progress bar
    const bar = getId('updateprogress');
    if (bar) { bar.hidden = false; bar.value = 0; }

    button.disabled = true;
    fetch('/onlineupdatestart')
      .then(response => response.text())
      .then(data => {
        console.log("Start update response:", data);
        // Prepare UI: hide form, show status and progress bar
        getId('updateform').attr('class','hidden');
        const status = getId('uploadstatus');
        
        if(status) status.innerHTML = getId('check_online_update').value;

        getId("uploadstatus").innerHTML = "Starting online update...";
        getId('updateform').classList.add('hidden');
        getId("updateprogress").value = 0;
        getId('updateprogress').hidden=false;
        getId('update_cancel_button').hidden=true;
        getId('check_online_update').classList.add('hidden');
        // WebSocket messages will drive progress
      })
      .catch(error => {
        console.error("Error starting update:", error);
        button.value = "Check for Online Update";
        button.disabled = false;
        getId("uploadstatus").innerHTML = "Error starting online update";
        getId('updateform').classList.remove('hidden');
        getId('updateprogress').hidden=true;
        getId("updateprogress").value = 0;
        getId('update_cancel_button').hidden=false;
        getId('check_online_update').classList.remove('hidden');
      });
  }
}
