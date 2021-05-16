/*

 FALLDOWNSPRITES.C

 Tile Source File.

 Info:
  Form                 : Each tile separate.
  Format               : Gameboy 4 color.
  Compression          : None.
  Counter              : None.
  Tile size            : 8 x 8
  Tiles                : 0 to 4

  Palette colors       : Included.
  SGB Palette          : None.
  CGB Palette          : 1 Byte per entry.

  Convert to metatiles : No.

 This file was generated by GBTD v2.2

*/

/* CGBpalette entries. */
unsigned char BallStraightCGB[] =
{
  0x01,0x00,0x00,0x00,0x00
};
unsigned char wall[] =
{
  0x00,0xFF,0x00,0xFF,0x00,0xFF,0xFF,0x00,
  0xFF,0x00,0x00,0xFF,0x00,0xFF,0x00,0xFF
};
unsigned char ball_straight[] =
{
  0xFF,0xFF,0xFF,0xE3,0xF7,0xDD,0xF7,0xBE,
  0xC1,0xBE,0xF7,0xBE,0xF7,0xDD,0xFF,0xE3
};
unsigned char ball_rotate[] =
{
  0xFF,0xFF,0xFF,0xE3,0xFF,0xDD,0xEB,0xBE,
  0xF7,0xBE,0xEB,0xBE,0xFF,0xDD,0xFF,0xE3
};
unsigned char ball_squish[] =
{
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x81,
  0xE7,0x7E,0x81,0x7E,0xE7,0x7E,0xFF,0x81
};
unsigned char blank[] =
{
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

/* End of FALLDOWNSPRITES.C */