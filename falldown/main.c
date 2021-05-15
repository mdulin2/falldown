#include <gb/gb.h>
#include <stdio.h>
#include "TileData.h"
#include "BlueWall.c"

// Blank color constant
unsigned char blank[] = 
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// Background mapping
// 0x0 is a blank tile and 0x1 is the 'bluewall' tile
unsigned char mapping[] = {
  0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x01, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 
  0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x01, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 
};

const UWORD spritepalette[] = {
    6076, 
    8935, 
    6596,
    5344, 
}; 

// Color palette
// https://github.com/gbdk-2020/gbdk-2020/blob/8de2a68801e1824459d93a0daf2270d2b53fc278/gbdk-lib/include/gb/cgb.h
UWORD jayPalette[] = {
    0, RGB_BLUE, RGB_RED, RGB_PURPLE,
    0, RGB_GREEN, RGB_BLUE, RGB_PURPLE,
    0, RGB_BLACK, RGB_DARKGRAY, RGB_WHITE
};

/*
These functions are SUPER nice! How does tihs actually work though? 

The GameBoy has specified regions of memory to specifc pixels on the screen.
Once data is put into this memory, the GameBoy screen will render the pixel
depending on the value. The size of the screen is 160 by 144 or 20 by 18 tiles.
This is what the USER sees though (a viewport). In reality, it is 32 by 32 tiles. So, 
to update the background, we edit data NOT in the viewport. The background
simply wraps around on the screen.

The color that we see depends on the pallete (grouping of colors) 
that has been loading for the sprite. 
- Only 9 palettes may be used per game (without interrupts) 
- Sprites can only have 4 colors
- 40 sprites on screen 

Using interrupts on the scanline x,y coordinates (writes horizontally per pixel then moves down veritically) 
more colors and effects can be added to the sprites or background. Commonly used for parellex (distance) 
scrolling. This seems SUPER complicated though. 

For using 'metasprites' (grouping of other sprites), we need to write logic
to write all of the sprites to the proper location. Move in a group.
*/
void set_sprites(){
    // Set the color scheme that we want to use
    set_sprite_palette(0, 3, jayPalette); 

    UINT8 currentspriteindex = 40;
    
    // Loading sprite information
    set_sprite_data(0, 1, BlueWall); // Load the sprites

    
    set_sprite_tile(0,0); // ?
    set_sprite_prop(0,0); // Set the sprite color pallete

    set_sprite_tile(1,0); // ?
    set_sprite_prop(0,0); // Set the sprite color pallete

    //set_sprite_tile(0,0); // ?
    //set_sprite_prop(0,0); // Set the sprite color pallete

    // Pixel locations
    move_sprite(0, 88, 78);
    move_sprite(1, 120, 78);


    // Macro to show sprites
    SHOW_SPRITES;
    
    
    // Move the sprite vertically
    while(1){
        move_sprite(0, 88, currentspriteindex);
        delay(10); 
        currentspriteindex += 4;
    }
    
    return; 
}

/*
Background modifications are a little bit more complicated than sprites.
For the background, there are two important things: 
- The background TILES
- Mapping of tiles to location in the background
*/
void set_background(){

    
    // Set the color palette of the background
    set_bkg_palette(0,1,jayPalette); 

    // Load the background tiles to use
    set_bkg_data(0,1,blank); 
    set_bkg_data(1,2, BlueWall);

    // Load the background 'image' to location mapping
    set_bkg_tiles(100, 100, 8, 8, mapping);

    while(1){
        scroll_bkg(0, 2);
        delay(100);
    }

    /*
   Background stuff
    // Load into memory
    set_bkg_data(0,1,TileData); 

    // Set the location of the pixels for the background
    set_bkg_tiles(60,60,1,10, TileData); 
    
    SHOW_BKG; 
    DISPLAY_ON; 

    To get the current position of the view (from scrolling), we can 
    access the SCX or SCY reigster directly.
    */
}

/*
Computers use a 'square' wave instead of a sine 'wine'
The GameBoy has four channels: 
- Square waves (1 and 2) 
- Progammable wave table (3) 
- Noise (4): 
    - Explosions, pokemon crying, etc.

In order to make the sounds, different registers need to be set. 
Each 'channel' has 5 registers that can be used for this that have special 
meanings. For channel 1: 
- Sweep settings: 
    - Bit 0-2: Shift in pitch per iteration
    - Bit 3: The direction (increase or decrease) 
    - Bit 4-6: The timing for the sweep
    - Bit 7: unused
- Wave Pattern and Sound Length: 
    - 0-5: Sound length - Higher the number shorter the length
    - 6-7: 12.5%, 25%, 50%, 75%
- Volume: 
    - 0-2: Length of each step in the sweep - 0 is volume off
    - 3: Volume sweep direction
    - 4-7: Initial volume
- Frequency: 
    - 0-7: Least significant bits of frequency
- Playback and Frequency (additional): 
    - 0-2: Significant bits of frequency 
    - 3-5: Unused
    - 6: Play the sound continously (or use the value from above) 
    - 7: Turn on the channel
*/
void sounds(){

    // Press a joypad button for something to happen
    while(1){
        if(joypad()){
            // Enable the sound via setting registers (nice wrapper macros) 
            NR52_REG = 0x80; // Turn on the sound hardware
            NR50_REG = 0x77; // Sets sound for left & right channels
            NR51_REG = 0xFF; // Channels to use - 2 bits per side with 4 channels

            /*
            Description
            */
            NR10_REG = 0x16; // Sweep settings
            NR11_REG = 0x40; // Wave Pattern/Sound Length
            NR12_REG = 0x73; // Volume handling
            NR13_REG = 0x00; // Frequency Lower bits
            NR14_REG = 0xC3; // Frequency Higher bits and turn on channel

            delay(1000);
        }
    }
}

/*
Example usage of the joypad

- http://gbdk.sourceforge.net/doc/html/c0505.html
*/
void use_inputs(){

    // Loading sprite information
    set_sprite_data(0, 1, TileData); // Load the sprites
    set_sprite_tile(0,0); // ?
    move_sprite(0, 88, 78);
    SHOW_SPRITES; 


    while(1){

        // Find inputs on the joypad
        // Use CONSTANTs for this
        UINT8 direction = joypad(); 
        switch(direction){
            case J_LEFT: // Left joypad
                scroll_sprite(0, -10, 0);
                break; 
            case J_RIGHT: // Right joypad
                scroll_sprite(0, 10, 0); 
                break; 
            case J_UP: // Up joypad
                scroll_sprite(0, 0, -10); 
                break; 
            case J_DOWN: // Down joypad
                scroll_sprite(0, 0, 10);
                break; 
            case J_START: 
            case J_SELECT: 
            case J_A: 
                scroll_sprite(0, 10, 10);
                break;
            case J_B: 
                break; 
        }

        delay(100);
    }
}

/*
Collision detection: 
- The IMPORTANT item to keep track of is the x,y location of sprites and the background at all times. 

When we scroll the screen, what should we keep track of? 
- Screen: 
    - 'TOP' of the screen in pixels
    - 'BOTTOM' of the screen in pixels
    - Offset of the view
- Current x and y of the ball
- What the 'map' currently looks like: 
    - This is in order to make collision detection later easy to do with simply checks

*/

void main(){
    //set_sprites();
    //set_background();
    //use_inputs();
    sounds();
}