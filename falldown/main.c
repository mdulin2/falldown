#include <gb/gb.h>
#include <stdio.h>
#include <rand.h>
#include <string.h>

#include "TileData.h"
#include "FalldownSprites.h"

// ball struct
struct Ball {
    UINT8 x;
    UINT8 y;
} ball;

UINT8 PIXEL_MV = 4;
UINT8 MAPPING_INDEX = 0;

// background mapping
// 0x0 is a blank tile
// 0x1 is the wall tile
unsigned char mapping[] = {
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x1, 0x1, 0x1, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x00, 0x01, 0x01, 0x0,  
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x00, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x00, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x00, 0x01, 0x01, 0x0, 
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0,
    0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x01, 0x01, 0x0, 
};

// color palettes
// https://github.com/gbdk-2020/gbdk-2020/blob/8de2a68801e1824459d93a0daf2270d2b53fc278/gbdk-lib/include/gb/cgb.h
UWORD palettes[] = {
    BallStraightCGBPal0c0,BallStraightCGBPal0c1, BallStraightCGBPal0c2, BallStraightCGBPal0c3, // Sprite
    BallStraightCGBPal1c0, BallStraightCGBPal1c1, BallStraightCGBPal1c2, BallStraightCGBPal1c3, // Walls
};

// CGBpalette entries
unsigned char BallStraightCGB[] = {
  0x01,0x00,0x00,0x00,0x00
};

// falldown wall
unsigned char wall[] = {
  0x00,0xFF,0x00,0xFF,0x00,0xFF,0xFF,0x00,
  0xFF,0x00,0x00,0xFF,0x00,0xFF,0x00,0xFF
};

// upright falldown ball
unsigned char ball_straight[] = {
  0xFF,0xFF,0xFF,0xE3,0xF7,0xDD,0xF7,0xBE,
  0xC1,0xBE,0xF7,0xBE,0xF7,0xDD,0xFF,0xE3
};

// rolling falldown ball
unsigned char ball_rotate[] = {
  0xFF,0xFF,0xFF,0xE3,0xFF,0xDD,0xEB,0xBE,
  0xF7,0xBE,0xEB,0xBE,0xFF,0xDD,0xFF,0xE3
};

// squished falldown ball
unsigned char ball_squish[] = {
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x81,
  0xE7,0x7E,0x81,0x7E,0xE7,0x7E,0xFF,0x81
};

// falldown blank (black)
unsigned char blank[] = {
  0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 
  0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 
};

/* 
--- SPRITES ---
These functions are SUPER nice!

The GameBoy has specified regions of memory to specifc pixels on the screen.
Once data is put into this memory, the GameBoy screen will render the pixel
depending on the value. The size of the screen is 160 by 144 or 20 by 18 tiles.
This is what the USER sees though (a viewport). 

In reality, the GameBoyscreen is 32 by 32 tiles. So, to update the background, 
we edit data NOT in the viewport. The background simply wraps around on the 
screen.

The color that we see depends on the pallete (grouping of colors) 
that has been loading for the sprite. 
- Only 9 palettes may be used per game (without interrupts) 
- Sprites can only have 4 colors
- 40 sprites on screen 

Using interrupts on the scanline X,Y coordinates (writes horizontally per pixel then moves down veritically) 
more colors and effects can be added to the sprites or background. Commonly used for parellex (distance) 
scrolling. 

For using 'metasprites' (grouping of other sprites), we need to write logic
to write all of the sprites to the proper location. Move in a group.

--- BACKGROUND ---
Setting the background are a little bit more complicated than sprites.
For the background, there are two important things: 
1. The background TILES
2. Mapping of tiles to location in the background

To get the current position of the view (from scrolling), we can access 
the SCX or SCY reigster directly.

--- SOUNDS ---
Computers use a 'square' wave instead of a 'sine' wave
The GameBoy has four channels: 
1. Square waves (1 and 2) 
2. Progammable wave table (3) 
3. Noise (4): 
    ex. Explosions, Pokemon Cries, etc.

In order to make the sounds, different registers need to be set. 
Each 'channel' has 5 registers that can be used for this that have special 
meanings. 

For channel 1: 
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

--- COLLISION DETECTION ---
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


// example of sprites
void set_sprites(){
    UINT8 currentspriteindex = 40;

    // set the color scheme that we want to use
    set_sprite_palette(0, 1, &palettes[4]); // load neon colors
    
    // loading sprite information
    set_sprite_data(0, 1, ball_straight); // load the sprites

    set_sprite_tile(0,0); // ?
    set_sprite_prop(0,0); // set the sprite color pallete

    set_sprite_tile(1,0); // ?
    set_sprite_prop(0,0); // set the sprite color pallete

    // pixel locations
    move_sprite(0, 88, 78);
    move_sprite(1, 120, 78);

    // macro to show sprites
    SHOW_SPRITES;
    
    // move the sprite vertically
    while(1) {
        move_sprite(0, 88, currentspriteindex);
        delay(10); 
        currentspriteindex += 4;
    }
    return; 
}

// example of background
void set_background(){
    // set the color palette of the background
    set_bkg_palette(0, 1, palettes); 

    // load the background tiles to use
    set_bkg_data(1, 2, wall);

    // load the background 'image' to location mapping
    set_bkg_tiles(100, 100, 8, 8, mapping);
    
    /*
    // load into memory
    set_bkg_data(0,1,TileData); 

    // set the location of the pixels for the background
    set_bkg_tiles(60,60,1,10, TileData); 
    
    SHOW_BKG; 
    DISPLAY_ON; 
    */
}

// example of sounds
void sounds(){
    // press a joypad button for something to happen
    while(1) {
        if (joypad()) {
            // enable the sound via setting registers (nice wrapper macros) 
            NR52_REG = 0x80; // turn on the sound hardware
            NR50_REG = 0x77; // sets sound for left & right channels
            NR51_REG = 0xFF; // channels to use - 2 bits per side with 4 channels

            NR10_REG = 0x16; // sweep settings
            NR11_REG = 0x40; // wave pattern/sound length
            NR12_REG = 0x73; // volume handling
            NR13_REG = 0x00; // frequency lower bits
            NR14_REG = 0xC3; // frequency higher bits and turn on channel

            delay(1000);
        }
    }
}

// example of joypad
// http://gbdk.sourceforge.net/doc/html/c0505.html
void use_inputs(){
    set_sprite_palette(0, 1, palettes); 

    // loading sprite information
    set_sprite_data(0, 1, ball_straight);
    set_sprite_data(1, 2, ball_rotate);
    set_sprite_data(2, 3, ball_squish);

    set_sprite_tile(0, 1); // ?
    move_sprite(0, 88, 78);
    SHOW_SPRITES; 

    while(1) {
        UINT8 direction = joypad(); 

        // find inputs on the joypad
        // use CONSTANTs for this
        switch(direction){
            case J_LEFT: // left joypad
                scroll_sprite(0, -10, 0);
                break; 
            case J_RIGHT: // right joypad
                scroll_sprite(0, 10, 0); 
                break; 
            case J_UP: // up joypad
                scroll_sprite(0, 0, -10); 
                break; 
            case J_DOWN: // down joypad
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

// detects collisions between the sprite and background
UBYTE is_collision(UINT8 ball_x, UINT8 ball_y) {
    UBYTE collision = 0;
    UINT16 origin_x, origin_y, origin_tile;

    origin_x = (ball_x - 8) / 8;
    origin_y = (((ball_y - 16) / 8) + MAPPING_INDEX) % 32; // add MAPPING_INDEX to track scrolling
    origin_tile = 20 * origin_y + origin_x;

    if (mapping[origin_tile] == 0x01) {
        collision = 1;
    }

    return collision;
}

// handles ball movement
void move(UINT8 direction) {
    switch(direction){
        case J_LEFT: // left joypad
            if (is_collision(ball.x - 4, ball.y) == 0) {
                scroll_sprite(0, -PIXEL_MV, 0);
                ball.x = ball.x - 4;
            }
            break; 
        case J_RIGHT: // right joypad
            // TODO: ball.x + 8 bc overlap
            if (is_collision(ball.x + 4, ball.y) == 0) {
                scroll_sprite(0, PIXEL_MV, 0);
                ball.x = ball.x + 4;
            }
            break; 
        case J_UP: // up joypad
            if (is_collision(ball.x, ball.y - 4) == 0) {
                scroll_sprite(0, 0, -PIXEL_MV);
                ball.y = ball.y - 4;
            }
            break; 
        case J_DOWN: // down joypad
            if (is_collision(ball.x, ball.y + 4) == 0) {
                scroll_sprite(0, 0, PIXEL_MV);
                ball.y = ball.y + 4;
            }
            break; 
        case J_START: 
        case J_SELECT: 
        case J_A:
        case J_B: 
            break; 
    }
}

// scroll the background and update mapping index
void scroll() {
    
    scroll_bkg(0,8);
    MAPPING_INDEX = (MAPPING_INDEX + 1) % 32;

    // Check to see if the sprite is up top of a platform. If so, move the sprite WITH the platform
    UBYTE collision = 0;
    UINT16 origin_x, origin_y, origin_tile;
    origin_x = (ball.x - 8) / 8; // Find the 'X' coordinate of the ball
    origin_y = (((ball.y - 16) / 8) + MAPPING_INDEX) % 32; // add MAPPING_INDEX to track scrolling
    origin_tile = 20 * origin_y + origin_x; // 2D to 1D translation in the 'mapping' array

    // If the tile below is a wall, then move the ball with the background
    if (mapping[origin_tile] == 0x01) {
        scroll_sprite(0, 0, -8);
        ball.y = ball.y - 8;
    }
}

// add a new randomly generated row
// y: y coordinate value
// amount: the percentage that a blank space should be used

// TODO: Make bars consistently thick
UINT8 create_row(UINT8 y, UINT8 amount){
    UINT8 value; 
    UINT8 index = 0;
    unsigned char new_row[20];

    while(index < 20){
        value = rand(); 

        // add a blank
        if ((rand() % 100) < amount) {
            new_row[index] = 0x0;
        }
        // add a wall
        else {
            new_row[index] = 0x1;
        }
        
        index += 1; 
    }

    // edit the mapping for 'logic' reasons for collision
    index = y * 20; 
    memcpy(&mapping[index], new_row, 20);
    set_bkg_tiles(0, y, 20, 1, &mapping[index]);

    return 0;
}

// initializes the palettes and sprites
void initialize(){
    // load the two palettes for the background
    set_bkg_palette(0, 1, &palettes[4]); 

    // load the background tiles to use
    set_bkg_data(0, 1, blank); 
    set_bkg_data(1, 2, wall);

    // load the background 'image' to location mapping
    set_bkg_tiles(0, 0, 20, 32, mapping);

    // load the palette for the sprite
    set_sprite_palette(0, 1, palettes); 

    // loading sprite information
    set_sprite_data(0, 1, ball_straight); // load the sprites
    set_sprite_data(1, 2, ball_rotate); // load the sprites
    set_sprite_data(2, 3, ball_squish); // load the sprites

    // load the sprite 'image'
    set_sprite_tile(0,1);

    // start ball at center top of viewport
    move_sprite(0, 100, 16);
    ball.x = 100;
    ball.y = 16;

    SHOW_SPRITES; 
}

void main(){
    UINT8 animation = 0;
    initialize();

    while(1){
        UINT8 direction = joypad();
        move(direction);

        // set the ball to perform a rolling animation
        set_sprite_tile(0, animation % 2);

        // add a new randomly generated row to the tile map
        //create_row(animation + 18, 50);

        // scroll the background 8 pixels at a time
        scroll();

        delay(1000);
        animation += 1;
    }

    //set_bkg_tiles(32, 32, 8, 1, &mapping[2]);
    while(1){
        scroll_bkg(0,1);
        set_bkg_tiles(rand() % 20, rand() % 20, 1, 1, mapping);
        delay(100);
    }
}