# Dolphin - A GameCube / Wii / Triforce Emulator

[Homepage](https://dolphin-emu.org/) | [Project Site](https://github.com/dolphin-emu/dolphin) | [Forums](https://forums.dolphin-emu.org/) | [Wiki](https://wiki.dolphin-emu.org/) | [Issue Tracker](https://bugs.dolphin-emu.org/projects/emulator/issues) | [Coding Style](https://github.com/dolphin-emu/dolphin/blob/master/Contributing.md) | [Transifex Page](https://www.transifex.com/projects/p/dolphin-emu/)

Dolphin is an emulator for running GameCube, Wii, and Triforce games on
Windows, Linux, OS X, and recent Android devices. It's licensed under
the terms of the GNU General Public License, version 2 or later (GPLv2+).

Please read the [FAQ](https://dolphin-emu.org/docs/faq/) before using Dolphin.

### BreadCrumb

To see if a particular function is called, BreadCrumbs can be used by including `Common/BreadCrumb.h` and dropping `BREADCRUMB` statements. Whenever the line line is reached in code, the file, function name and line will be highlighted and printed to standard out.

```c
#include "Common/BreadCrumb.h"
...
BREADCRUMB();
```


## System Requirements
### Desktop
* OS
    * Windows (7 SP1 or higher is officially supported, but Vista SP2 might also work).
    * Linux.
    * OS X (10.9 Mavericks or higher).
    * Unix-like systems other than Linux are not officially supported but might work.
* Processor
    * A CPU with SSE2 support.
    * A modern CPU (3 GHz and Dual Core, not older than 2008) is highly recommended.
* Graphics
    * A reasonably modern graphics card (Direct3D 10.0 / OpenGL 3.0).
    * A graphics card that supports Direct3D 11 / OpenGL 4.4 is recommended.


Dolphin can only be installed on devices that satisfy the above requirements. Attempting to install on an unsupported device will fail and display an error message.

## Building for Windows
Use the solution file `Source/dolphin-emu.sln` to build Dolphin on Windows.
Visual Studio 2015 is a hard requirement. Other compilers might be able to
build Dolphin on Windows but have not been tested and are not recommended to
be used.

An installer can be created by using the `Installer_win32.nsi` and
`Installer_x64.nsi` scripts in the Installer directory. This will require the
Nullsoft Scriptable Install System (NSIS) to be installed. Creating an
installer is not necessary to run Dolphin since the Build directory contains
a working Dolphin distribution.

## Building for Linux and OS X
Dolphin requires [CMake](http://www.cmake.org/) for systems other than Windows. Many libraries are
bundled with Dolphin and used if they're not installed on your system. CMake
will inform you if a bundled library is used or if you need to install any
missing packages yourself.

### Build Steps:
1. `mkdir Build`
2. `cd Build`
3. `cmake ..`
4. `make`

On OS X, an application bundle will be created in `./Binaries`.

On Linux, it's strongly recommended to perform a global installation via `sudo make install`.


## Uninstalling
When Dolphin has been installed with the NSIS installer, you can uninstall
Dolphin like any other Windows application.

Linux users can run `cat install_manifest.txt | xargs -d '\n' rm` as root from the build directory
to uninstall Dolphin from their system.

OS X users can simply delete Dolphin.app to uninstall it.

Additionally, you'll want to remove the global user directory (see below to
see where it's stored) if you don't plan to reinstall Dolphin.

## Command Line Usage
`Usage: Dolphin [-h] [-d] [-l] [-e <str>] [-b] [-V <str>] [-A <str>]`  

* -h, --help Show this help message  
* -d, --debugger Opens the debugger  
* -l, --logger Opens the logger  
* -e, --exec=<str> Loads the specified file (DOL,ELF,WAD,GCM,ISO)  
* -b, --batch Exit Dolphin with emulator  
* -V, --video_backend=<str> Specify a video backend  
* -A, --audio_emulation=<str> Low level (LLE) or high level (HLE) audio  

Available DSP emulation engines are HLE (High Level Emulation) and
LLE (Low Level Emulation). HLE is fast but often less accurate while LLE is
slow but close to perfect. Note that LLE has two submodes (Interpreter and
Recompiler), which cannot be selected from the command line.

Available video backends are "D3D" (only available on Windows) and
"OGL". There's also "Software Renderer", which uses the CPU for rendering and
is intended for debugging purposes only.

## Sys Files
* `totaldb.dsy`: Database of symbols (for devs only)
* `GC/font_ansi.bin`: font dumps
* `GC/font_sjis.bin`: font dumps
* `GC/dsp_coef.bin`: DSP dumps
* `GC/dsp_rom.bin`: DSP dumps
* `Wii/clientca.pem`: Wii network certificate
* `Wii/clientcacakey.pem`: Wii network certificate
* `Wii/rootca.pem`: Wii network certificate

The DSP dumps included with Dolphin have been written from scratch and do not
contain any copyrighted material. They should work for most purposes, however
some games implement copy protection by checksumming the dumps. You will need
to dump the DSP files from a console and replace the default dumps if you want
to fix those issues.

Wii network certificates must be extracted from a Wii IOS. A guide for that can be found [here](https://wiki.dolphin-emu.org/index.php?title=Wii_Network_Guide).

## Folder Structure
These folders are installed read-only and should not be changed:

* `GameSettings`: per-game default settings database
* `GC`: DSP and font dumps
* `Maps`: symbol tables (dev only)
* `Shaders`: post-processing shaders
* `Themes`: icon themes for GUI
* `Resources`: icons that are theme-agnostic
* `Wii`: default Wii NAND contents

## User Folder Structure
A number of user writeable directories are created for caching purposes or for
allowing the user to edit their contents. On OS X and Linux these folders are
stored in `~/Library/Application Support/Dolphin/` and `~/.dolphin-emu`
respectively. On Windows the user directory is stored in the `My Documents`
folder by default, but there are various way to override this behavior:

* Creating a file called `portable.txt` next to the Dolphin executable will
  store the user directory in a local directory called "User" next to the
  Dolphin executable.
* If the registry string value `LocalUserConfig` exists in
  `HKEY_CURRENT_USER/Software/Dolphin Emulator` and has the value **1**,
  Dolphin will always start in portable mode.
* If the registry string value `UserConfigPath` exists in
  `HKEY_CURRENT_USER/Software/Dolphin Emulator`, the user folders will be
  stored in the directory given by that string. The other two methods will be
  prioritized over this setting.


List of user folders:

* `Cache`: used to cache the ISO list
* `Config`: configuration files
* `Dump`: anything dumped from Dolphin
* `GameConfig`: additional settings to be applied per-game
* `GC`: memory cards and system BIOS
* `Load`: custom textures
* `Logs`: logs, if enabled
* `ScreenShots`: screenshots taken via Dolphin
* `StateSaves`: save states
* `Wii`: Wii NAND contents
