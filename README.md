# Reverse-Audio-Files

## Description

This program takes a sound file and reverses it with the help of Sound eXchange (SOX). It allows users to convert audio format (.wav and .ogg) to data (.dat) files. The program will read the audio file and create a new data file. Sox is then used to convert the data file back into standard audio file. The audio file can then be played in music players. 

## Notes

Test files are included in the assets directory.

## Requirements

sox is required to run the program.

Windows Operating System:

[Download Sox Here](https://sourceforge.net/projects/sox/files/sox/14.4.2/sox-14.4.2-win32.zip/download)

**Linux/MacOS Operating System:**
```bash
$ sudo apt install sox #debian based distribution
$ sudo dnf install sox #fedora based distribution
$ brew install sox #macOS
$ play <sound file> #using sox from the terminal
```
## Running The Program

```bash 
$ make
$ sox assets/file1.ogg assets/file1.dat # convert audio file to data file
$ ./reverse assets/file1.dat assets/file1-reverse.dat # reverse data file
$ sox assets/file1-reverse.dat assets/file1-reverse.ogg # convert data file to audio file
$ play assets/file1-reverse.ogg # or use an audio player
```