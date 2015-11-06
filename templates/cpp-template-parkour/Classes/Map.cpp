/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Map.h"

//
// map 0
//
static const char* mapBuffer_getReady[5] =
{
    /*          1         2         3         4         5
      12345678901234567890123456789012345678901234567890123456789*/
     ".CC...CC...C.C",
     "C....C..C..C.C",
     "CCC..C..C..C.C",
     "C..C.C..C.....",
     ".CC...CC...C.C",

	/*
     ".CC..CCC.CCCCC..CCC..CCC..CC..CCC..C...C....",
     "C....C.....C....C..C.C...C..C.C..C..C.C.....",
     "CCC..CCC...C....CCC..CCC.CCCC.C..C...C......",
     "C..C.C.....C....C..C.C...C..C.C..C...C......",
     ".CC..CCC...C....C..C.CCC.C..C.CCC....C......"
     */
};
static const struct Map map_getReady =
{
    &mapBuffer_getReady[0],
    {14,5},           // size of buffer
    {36,36}           // space between tiles
};

//
// map 0
//
static const char* mapBuffer_0[2] =
{
    /*         1         2         3
     123456789012345678901234567890123456789 */
    "...Bb................Bb.........",
    "..BbBb......C.C.C..BbBbBb.....Bb"
};
static const struct Map map_0 =
{
    &mapBuffer_0[0],
    {32,2},           // size of buffer
    {28,44}           // space between tiles. Using tile_width/2 as width };
};

//
// map 1
//
static const char* mapBuffer_1[3] =
{
    /*          1         2         3         4         5
     12345678901234567890123456789012345678901234567890123456789*/
    "................BbBbBb..........................",
    ".............BbBbBbBbBbBb.......................",
    "BbBbBbBb..BbBbBbBb.C..BbBbBb..BbBbBbBb..BbBbBbBb"
};
static const struct Map map_1 =
{
    &mapBuffer_1[0],
    {48,3},           // size of buffer
    {28,44}           // space between tiles. Using tile_width/2 as width };
};

//
// map 2
//
static const char* mapBuffer_2[5] =
{
    /*          1         2         3         4         5
     12345678901234567890123456789012345678901234567890123456789*/
    "....C.C.C.C.C.C...........................C.C.C.",
    "..........................AaAaAaAa..............",
    "................................................",
    ".............Bb.................................",
    "BbBbBbBbBbBbBbBbBb..C.C.BbBb....C.C.C...BbBbBbBb"
};
static const struct Map map_2 =
{
    &mapBuffer_2[0],
    {48,5},           // size of buffer
    {28,44}           // space between tiles. Using tile_width/2 as width };
};

//
// map 3
//
static const char* mapBuffer_3[5] =
{
    /*          1         2         3         4         5
     12345678901234567890123456789012345678901234567890123456789*/
    "Aa...............C.C...........Aa...............",
    ".................C.C............................",
    "................BbBbBb...............C.C........",
    ".............BbBbBbBbBbBb............C.C.....Bb.",
    "..........BbBbBb..C.C.BbBbBb.........C.C....BbBb"
};
static const struct Map map_3 =
{
    &mapBuffer_3[0],
    {48,5},           // size of buffer
    {28,44}           // space between tiles. Using tile_width/2 as width };
};

//
// map 4
//
static const char* mapBuffer_4[5] =
{
    /*          1         2         3         4         5       6
     123456789012345678901234567890123456789012345678901234567890*/
    "....................B.B.B.B.B.B.B.B.........A.A....C.C.C....",
    "...............B.B.B.B.B.B.B.B.B.B.B................C.C.C...",
    "..........B.B.B.B.B.B.B.B.B.B.B.B.B.B................C.C.C..",
    ".....B.B.B.B.B.B.B.B.B.B.B.B.B.B.B.B.B................C.C.C.",
    "B.B.B.B.B.B.B.B.B.B.B.B.B.B.B.B.B.B.B.B................C.C.C"
};
static const struct Map map_4 =
{
    &mapBuffer_4[0],
    {60,5},           // size of buffer
    {28,44}           // space between tiles. Using tile_width/2 as width };
};

// all maps
static const Map* maps[] =
{
    &map_0,
    &map_1,
    &map_2,
    &map_3,
    &map_4,
};
static const int TOTAL_MAPS = sizeof(maps)/sizeof(maps[0]);

const Map* getGetReadyMap()
{
    return &map_getReady;
}

const Map* getRandomMap()
{
    int idx = CCRANDOM_0_1() * TOTAL_MAPS;
    return maps[idx];
}
