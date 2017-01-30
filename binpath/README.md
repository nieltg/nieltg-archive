# binpath

binpath is a tool that simplifies the way you access apps in bin directories
by creating shortcuts to them.

This tool works by placing shortcuts in places which will be added to `$PATH`,
so you can just type the name of shortcuts you've created. This tool is usable
for people who like to keep programs somewhere in their home directory, so
they can access them easily.

## Installation

To install binpath to `$HOME`, you can `cd` to the project directory then type:

```
./install.sh
```

**WARNING:** The installer is EXPERIMENTAL. So if it fails, you must clean up
things by yourself. You can read uninstallation guide below to help you do it.

## Uninstallation

There isn't any ways to uninstall it automatically (at least for now), so you
must do it manually.

The installer works in `$HOME`. It copies `.bashrc` to `.bashrc~`, edits
`.bashrc`, then places binpath on `.binpath`. So if the installation fails and
you want to clean up things or uninstall, you can type:

```
cd $HOME
mv .bashrc~ .bashrc
```

To finish uninstallation process and keep shortcuts you've created, you can
leave `.binpath/sto` & its content, then delete other files in `.binpath`. To
clean up or finish installation without keeping shortcuts, just delete whole
`.binpath` directory.

## Usage

For example, you want to access `emulator-x86` easily from freshly downloaded
Android SDK you've placed in `$HOME/Documents/Android/Tools/SDK` (the binary
itself is placed under `tools` subdirectory). To create the shortcut, you can
type:

```
binpath register android_tools $HOME/Documents/Android/Tools/SDK/tools
```

To use `emulator-x86` with `-avd API19-Tablet` as its arguments, you can type:

```
android_tools emulator-x86 -avd API19-Tablet
```

To remove the shortcut, you can type:

```
binpath unregister android_tools
```

