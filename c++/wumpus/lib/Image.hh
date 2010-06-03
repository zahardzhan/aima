#ifndef __Image_HH__
#define __Image_HH__

#include <ostream.h>

#define IMAGE_SIZE   32

typedef char ImageRow[ IMAGE_SIZE ];
typedef const ImageRow *ImageData;

class Image
{
  friend inline ostream &operator<< ( ostream &o, const Image &i );
  
public:
  Image();
  virtual ~Image();
  virtual void operator= ( const Image &image );

  virtual void paint ( int wumpus, int pit, int gold, int wall );
  virtual void erase ( int val = 0 );
  virtual ImageData getData() const;

protected:

  virtual void addNoise();
  virtual void paintBitMap ( const void *buf, int width, int height );
  
  ImageRow data[ IMAGE_SIZE ];
  int blocks[ 4 ];
};

inline ostream &operator<< ( ostream &o, const Image &i )
{
  int x, y;

  o << '+';
  for ( x=0; x<IMAGE_SIZE; x++ )
    o << '-';
  o << '+' << endl;

  for ( x=0; x<IMAGE_SIZE; x++ )
    {
      o << '|';

      for ( y=0; y<IMAGE_SIZE; y++ )
	o << ( i.data[ x ][ y ]? '*' : ' ');
      
      o << '|' << endl;;
    }
  
  o << '+';
  for ( x=0; x<IMAGE_SIZE; x++ )
    o << '-';
  o << '+' << endl;

  return o;
}

#endif
