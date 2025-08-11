# How to Sync Config Files in VS Code

This folder contains contributor-specific configuration files that are automatically synced from the root directory

## What Gets Synced
  - platformio.ini in root
  - .h files in root directory

## Setup

### Create your builds folder
  - Create a subfolder in builds with your Github username

### Install File Watcher Extension (by Appulate)
1. Open VS Code Extensions (Ctrl+Shift+X)
2. Search for: appulate.filewatcher
3. Install "File Watcher" by appulate


### Edit .vscode/settings.json
  - Add a section that looks like (edit username):
   ```json
	"filewatcher.commands": [
		{
			"match": "platformio.ini",
			"cmd": "copy \"${file}\" \"${workspaceRoot}\\builds\\username\\platformio.ini\"", 
			"event": "onFileChange"
		},
		{
			"match": "\\.h",
			"cmd": "copy \"${file}\" \"${workspaceRoot}\\builds\\username\\\"",
			"event": "onFileChange"
		}
	]
   ```
  - don't forget it's JSON so brackets and commas are important!
  - see the `settings.json` for an example

### Done!

All important files that are ignored by .gitignore will now be backed-up and shared and Github workflow will build your firmwares automatically!