# Overview

A small X program which provides a modal keyboard driven interface for cursor
manipulation. The program was originally inspired by the mousekeys feature of
Kaleidoscope, the firmware for the Keyboardio.

# Demo

## Hint Mode

<p align="center">
<img src="demo/hints.gif" height="400px"/>
</p>

## Grid Mode

<p align="center">
<img src="demo/warp.gif" height="400px"/>
</p>

## Normal Mode

<p align="center">
<img src="demo/discrete.gif" height="400px"/>
<img src="demo/discrete2.gif" height="400px" width="711px"/>
</p>


# Dependencies

## Linux:

The usual array of X libraries:

 - libxi
 - libxinerama
 - libxft
 - libxfixes
 - libxtst
 - libx11

## MacOS:

 - The standard Xcode command line developer tools.


# Installation

Make sure you have the appropriate dependencies for your system:

E.G 

debian/ubuntu:

```
sudo apt-get install \
	libxi-dev \
	libxinerama-dev \
	libxft-dev \
	libxfixes-dev \
	libxtst-dev \
	libx11-dev
```


macos:

```
xcode-select --install
```

Then simply do:

```
make && sudo make install
```

# Quickstart

1. Run `warpd` 

## Hint Mode
2. Press `A-M-x` to generate a list of hints
3. Enter the key sequence associated with the desired target to warp the pointer to that location and enter normal mode.
4. Use the normal mode movement keys to select the final desination (see Normal Mode). 

## Grid Mode
2. Press `A-M-g` (meta is the command key) to activate the warping process.
3. Use `u`,`i`,`j`,`k` to repeatedly navigate to different quadrants.
4. Press `m` to left click, `,` to middle click or `.` to right click. 
5. See Normal Mode

## Normal Mode
2. Press `A-M-c` to activate normal mode.
3. Use the normal movement keys (default `hjkl`) to adjust the cursor.
4. Press `m` to left click, `,` to middle click or `.` to right click. 
5. Press `escape` to quit.

A drag movement can be simulated from any of the above modes by focusing on the
source and then pressing the `drag_key` (default `v`) which will cause normal
mode to be activated for selection of the drag target.

A more comprehensive description can be found in the man page (along with a list of options).

# Packages:

`warpd` is currently available on the following distributions:

## Arch

Available as an [AUR](https://aur.archlinux.org/packages/warpd-git/) package (maintained by Matheus Fillipe).

If you are interesting in adding warpd to your distribution's repository please contact me.

# Limitations/Bugs

- No multi monitor support (it may still work by treating the entire display as
  one giant screen, I haven't tried this). If you use this program and desire
  this feature feel free to harass me via email or file an issue.

- Programs which use Xinput and or Xtest for keyboard may not work correctly
  (e.g synergy). If a specific program which you feel should be working does
  not please file an [issue](https://github.com/rvaiya/warpd/issue).

- This was a small one off c file that ballooned into a small project, I did
  not originally plan to publish it. Consequently the code is ugly/will eat
  your face. You have been warned.


# Contributions

A special thanks to

 - Pete Fein - For encouragement and early adoption.
 - Matheus Fillipe - For the original border radius patch as well as numerous bug reports and feature requests.
 - The Kaleidoscope/Vimperator projects - For inspiration.
