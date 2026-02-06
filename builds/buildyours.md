# Building Your Own Web Flasher

Read the howtosync.md first!

## Preparation

Inside your builds folder must be `platformio.ini`, `myoptions.h`, and optionally `mytheme.h`.

There must also be a `firmware.txt` file.
This contains information that is used by the workflows use to build the `.json` manifests for your particular build:
```
board_esp32_s3_n16r8|ESP32-S3|esp32_s3_trip5_st7735_pcm_1button|Trip5 Color Screen with 1-Button
```
There are 4 fields here, separated by a `|`:
  - board name (the bare-board environment used to extract bootloader and partition file)
  - the chip name to determine offsets, etc for the online esp-tool flasher (ie. `ESP32`,`ESP32-S3`)
  - the environment name of the firmware build (corresponds to the `.bin` file)
  - the "friendly name" of the firmware build (which will appear in the flasher's dropdown menu)

Also, you should edit the `releases.md` file to match your filenames, etc.  This file will be the note in the Releases, and it is linked from the `firmware.html` flasher page.

Probably too you should make sure `myoptions.h` has the source url override set with `#define GITHUBURL "https://github.com/trip5/ehradio"` (replace `trip5` with your Github username)...
Unless, of course, you don't mind that Trip5's repository is responsible for your firmware builds when a device wants to do an OTA update.

### Github Settings

#### Pages

Build and deployment: Source: Github Actions

#### Environments

Environments / github-pages: Deployment branches and tags: 1 branch and 0 tags allowed: ehradio (or whatever your main branch is called)

## Building

After everything is ready, the following should trigger your own Firmware build:
```
$tag="2026.02.06"; git tag -d "$tag"; git tag -a "$tag" -m "$tag"; git push origin "$tag" --force
```

This should trigger the `Build and Release Firmware` workflow on Github which builds the firmware `.bin` files for a Release.
It will also build the manifests `.json` files, used by the online flashing tool, which are then comitted into your `builds` folder.

With every commit, the `Build and Deploy GitHub Page` is run, making sure your online flasher `firmware.html` is up-to-date.

Both of these workflows are dynamic according to your Github username, repo name, and branch.
The only thing that will link back to Trip5's original repository when it is done will be on the bottom of `firmware.html`.

### Other Workflows

The workflow `Update JSON Files Automatically` keeps two .json files up-to-date, checking on every commit whether or not
`rb_srvrs.json` (the last of radio-browser servers) and `timezones.json.gz` need updating.
