## Overview
- Game Boy Dev :) 

## Design Decisions
- Game boy SDK for C: 
    - Docs: 
        - http://gbdk.sourceforge.net/doc/html/c0504.html
        - https://gbdev.gg8.se/wiki/articles/GBDK_Sprite_Tutorial
        - https://gbdev.gg8.se/wiki/articles/Main_Page
        - https://www.youtube.com/watch?v=Ltyi-Ljd5-g&list=PLeEj4c2zF7PaFv5MPYhNAkBGrkx4iPGJo&index=4
    - https://github.com/gbdk-2020/gbdk-2020
- Frameworks: 
    - Advanaced collision detection and such
    - https://bitbucket.org/HellSuffering/retr0-gb/src/master/
    - https://zalods.blogspot.com/2017/01/zgb-little-engine-for-game-boy.html
- Gameboy Color games: 
    - GBA is not supported as well for development
    - GBC has colors and is better than the regular gameboy
- Emulators:
    - Linux:
        - https://github.com/mgba-emu/mgba
        - https://emulicious.net/: 
            - Source level debugging with memory editor!
    - MacOS:
        - https://bgb.bircd.org/ (Wine)
        - https://github.com/LIJI32/SameBoy
- Tile/Sprite designer: 
    - Installing Wine: https://dl.winehq.org/wine-builds/macosx/download.html
    - Gameboy Only: 
        - https://spkelly.net/tilegen/
    - https://gbdev.io/list.html#graphics-utilities
- Music and sounds: 
    - https://gbdev.io/list.html#tools

## General Game Design 
- Falldown game!
    - Ball rolls to the end, until the ball hits the top of the screen
    - Randomly generate WHERE the lines will go for the game
    - Starts slow but SPEEDS up
- The ball is a sprite
- Add ons are also sprites (speedups and such) 
- Lines are the background for the game
- Collision detection for sprites, specials and lines
- Layers: 
    - Background: The course that we are trying to get through
    - Sprites: The character and specials are sprites
    - Screen: The score
- Tiles: 
    - A 'tile' is 8 by 8 pixels
    - Essentially a GROUPING of graphics on the screen
    - Only 4 colors per tile
- Specials: 
    - Speedup
    - Stop time
    - Multiple balls on screen
    - Add points
    - Break wall
- Steps to creation: 
    - Create walls & Character
    - Add walls to background
    - Add scrolling for the background (randomly generated levels)
    - Add character + gravity
    - Add collision between walls and character
    - Extras: 
        - Sound effects
        - Specials
        - Menu... 
        - Pointers
        - etc.

## Gameboy Progamming
- Tips for optmizations: 
    - 8-bit are MUCH better because of the architecture.
    - Global and static variables are better because of non-stack based architecture
    - Use CONST for read-only arrays, structs and variables for faster loading
    - Multiplication, modulo and division with non-powers of two are NOT made in the software... Mimize these where possible. 
    - No recursive functions
    - https://gbdk-2020.github.io/gbdk-2020/docs/api/docs_coding_guidelines.html
- wait_vbl_done: 
    - Wait for the next frame in order to do something. Uses HALT to put CPU into lower power state. 

## TAS
- EmuHawk has a specific TAS configuration
    - Edit inputs frame by frame

## Pwnable?
- Corruption Ideas: 
    - Too many balls on screen causing global buffer overflow
    - High score integer underflow
    - Too much speed breaks logic
    - Pause buffering does not render game logic properly
    - Screen mechanics for 'items' 
- Inputs: 
    - Username (for score keeping) 
    - Item information
    - Score
    - Controller inputs
- Flow idea: 
    - Use too many balls on screen to corrupt 'item box' buffer logic
    - Use/Move items around with broken item box logic: 
    - Overwrite function pointer to point to our 'username' code
    - Print the flag!

## Resources
- AwesomeList of GB links:
    - https://gbdev.io/list.html#documentation