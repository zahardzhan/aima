#include "Image.hh"
#include "Orientations.hh"
#include "RndInt.h"

extern RandomInteger randInt;

#define WUMPUS_WIDTH 12
#define WUMPUS_HEIGHT 11
const char wumpusBitMap[ WUMPUS_WIDTH ][ WUMPUS_HEIGHT+1 ] =
{
  "     *     ",
  "    * *    ",
  "   *   *   ",
  "  *     *  ",
  "  *     *  ",
  "  * * * *  ",
  " *       * ",
  " *       * ",
  " *  ***  * ",
  "*         *",
  "*         *",
  "***********",
};

#define PIT_WIDTH 7
#define PIT_HEIGHT 13
const char pitBitMap[ PIT_WIDTH ][ PIT_HEIGHT+1 ] =
{
  "    *****    ",
  "  **     **  ",
  " *         * ",
  "*           *",
  " *         * ",
  "  **     **  ",
  "    *****    ",
};

#define GOLD_WIDTH 5
#define GOLD_HEIGHT 14
const char goldBitMap[ GOLD_WIDTH ][ GOLD_HEIGHT+1 ] =
{
  "    ******    ",
  "   *      *   ",
  "  *        *  ",
  " *          * ",
  "**************",
};

Image::Image()
{
  erase();
}

Image::~Image()
{
}

void Image::operator= ( const Image &image )
{
  int x, y;

  for ( x=0; x<IMAGE_SIZE; x++ )
    for ( y=0; y<IMAGE_SIZE; y++ )
      data[ x ][ y ] = image.data[ x ][ y ];
}

void Image::paint ( int wumpus, int pit, int gold, int wall )
{
  if ( wall )
    erase ( 1 );
  else
    {
      erase ( 0 );
      
      if ( wumpus )
	paintBitMap ( wumpusBitMap, WUMPUS_WIDTH, WUMPUS_HEIGHT );
      
      if ( pit )
	paintBitMap ( pitBitMap, PIT_WIDTH, PIT_HEIGHT );
      
      if ( gold )
	paintBitMap ( goldBitMap, GOLD_WIDTH, GOLD_HEIGHT );
    }
  
  addNoise();
}

extern Orientation g_or;

void Image::paintBitMap ( const void *ptr, int width, int height )
{
  int block;
  int x, y, i, j;
  const char *buf =  ( const char* ) ptr;
  
  do
    block = randInt(3);
  while ( blocks[ block ] );

  blocks[ block ] = 1;
  
  Orientation or = ( Orientation ) randInt(3);

  int max = width>height? width : height;
  
  if ( or == LEFT || or == RIGHT )
    {
      i = ((block%2) * (IMAGE_SIZE/2)) + randInt( (IMAGE_SIZE/2)-max-1 );
      j = ((block/2) * (IMAGE_SIZE/2)) + randInt( (IMAGE_SIZE/2)-max-1 );
    }
  else
    {
      i = ((block/2) * (IMAGE_SIZE/2)) + randInt( (IMAGE_SIZE/2)-max-1 );
      j = ((block%2) * (IMAGE_SIZE/2)) + randInt( (IMAGE_SIZE/2)-max-1 );
    }
  
  for ( x=i; x<i+width; x++ )
    {
      for ( y=j; y<j+height; y++, buf++ )
	{
	  int a, b;
	  
	  switch ( or )
	    {
	    case UP:    a = x;            b = y;            break;
	    case DOWN:  a = i+i+width-x;  b = j+j+height-y; break;
	    case LEFT:  a = y;            b = x;            break;
	    case RIGHT: a = j+j+height-y; b = i+i+width-x;  break;
	    default:
	      cout << "BAD: Orientation=" << (int)or << endl;
	      continue;
	    }

	  if ( a < 0 || a >= IMAGE_SIZE || b < 0 || b >= IMAGE_SIZE )
	    cout << "BAD: " << a << ", " << b << endl;
	  else
	    data[ a ][ b ] = *buf=='*';
	}
      buf++;
    }
}

void Image::addNoise()
{
  int x, y;

  for ( x=0; x<IMAGE_SIZE; x++ )
    for ( y=0; y<IMAGE_SIZE; y++ )
      if ( !randInt ( 100 ) )
	data[ x ][ y ] = !data[ x ][ y ];
}

void Image::erase( int val )
{
  int x, y;

  for ( x=0; x<4; x++ )
    blocks[ x ] = 0;
  
  for ( x=0; x<IMAGE_SIZE; x++ )
    for ( y=0; y<IMAGE_SIZE; y++ )
      data[ x ][ y ] = val;
}

ImageData Image::getData() const
{
  return data;
}
