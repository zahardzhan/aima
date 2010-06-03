/*
   Circle.C
*/

#include <math.h>
#include <iostream.h>
#include "Circle.H"


/***** Image member functions *****/

Image::Image()
{
  int x, y;

  for (x = 0; x < DIM; ++x)
    for (y = 0; y < DIM; ++y)
      image[x][y] = 0;
}

Image::~Image()
{
}

char Image::getPixel ( int x, int y )
{
  return image[x][y];
}

void Image::setPixel ( int x, int y, char val )
{
  image[x][y] = val;
}

void Image::display()
// Display image with origin at lower left.
{
  int x, y;

  for (y = DIM-1; y >= 0; --y) {
    for (x = 0; x < DIM; ++x)
      switch (image[x][y]) {
        case 0: cout << "0 "; break;
        case 1: cout << "1 "; break;
      }
    cout << endl;
  }
}

void Image::addNoise ( float noise )
// Flip each pixel with probability equal to noise.
{
  int x, y;

  for (x = 0; x < DIM; ++x)
    for (y = 0; y < DIM; ++y)
      if (biasedCoinFlip(noise))
        if (image[x][y] == 0)
          image[x][y] = 1;
        else image[x][y] = 0;
}


/***** circleImage member functions *****/

circleImage::circleImage ( int x, int y, int radius )
{
  // record circle parameters
  cx = x;
  cy = y;
  cradius = radius;

  // set pixels (i,j) in image corresponding to given circle parameters
  int i, j, diff2, diff;
  for (i = x - radius; i <= x + radius; ++i) {
    diff2 = (radius * radius) - ((i - x) * (i - x));
    diff = (int) sqrt(((double) diff2));
    j = y - diff;
    setPixel(i,j,1);
    j = y + diff;
    setPixel(i,j,1);
  }
}

circleImage::~circleImage()
{
}


/***** Circle member functions *****/

Circle::Circle ( int xx, int yy, int rr )
{
  x = xx;
  y = yy;
  radius = rr;
}

Circle::~Circle()
{
}

Circle::display()
{
  cout << "circle: x = " << x << ", y = " << y
       << ", radius = " << radius << endl;
}


/***** utility functions *****/

Boolean biasedCoinFlip ( float probability )
// Returns True if a biased coin flip turns up heads where the
// probability of heads is given.
{
  long threshold = ((long) (probability * MAXRAND));
  if (random() < threshold)
    return True;
  else return False;
}
