# change_brightness

Description: A small FLTK-based GUI and CLI tool to change the brightness of a connected monitor on Linux (X11) using xrandr.

## Overview

change_brightness allows you to adjust your monitor’s brightness either:
1. Via a simple GUI slider, or
2. From the command line, using a numeric value between 0.0 and 1.0

This tool was created to avoid repeatedly typing commands like:
- xrandr --output HDMI-A-1 --brightness 0.5
- and to make brightness adjustment easier and more accessible for everyday use.

## Motivation
I’m new to Linux (Arch Linux + XFCE), and I wanted:
- A quick and simple way to adjust monitor brightness
- A GUI option so that non-technical users (e.g. family members) can use the PC comfortably

A small personal project to learn more about C++, FLTK, and Linux system tools

This project was written on 24–25 December 2025.

## Usage
### GUI mode
Simply run:
./change_brightness
A window will appear with a slider to control brightness.

### Command-line mode
If you are in the same directory as change_brightness, you can also set the brightness directly:
./change_brightness <value>
Where <value> is a number between 0.0 and 1.0.
Example:
./change_brightness 0.5

## Requirements:
- Linux with X11
- xrandr
- FLTK runtime libraries

On Arch Linux:
sudo pacman -S fltk xorg-xrandr

## Notes

This tool currently detects and adjusts the active connected monitor
Wayland is not supported (X11 only)
Brightness values outside 0.2 – 1.0 are clamped because I sometimes set brightness to 0 accidentally and that's annoying

Author:
Mikhail s/o Mahamood
