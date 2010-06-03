#ifndef CIRCLE_H
#define CIRCLE_H

enum Boolean { False = 0, True = 1 };

const unsigned long MAXRAND = 2147483647;

const int DIM = 32;  // images are DIMxDIM

// class Image
//
//   Provides storage, access and display for a DIMxDIM binary image.
//   Also provides a mechanism for adding noise to the image.
//
class Image {
public:
  Image();
  ~Image();

  char getPixel ( int x, int y );
  void setPixel (int x, int y, char val );
  void display();
  void addNoise ( float noise );
private:
  char image[DIM][DIM];
};


// class circleImage
//
//   Creates an image containing a circle with the given parameters and
//   noise.  This is passed into the Hough transform.
//
class circleImage : public Image {
public:
  circleImage ( int x, int y, int radius );
  ~circleImage();
private:
  int cx, cy, cradius;
};


// class Circle
//
//   A simple circle class, which should be returned from Hough transform.
//
class Circle {
public:
  Circle ( int xx, int yy, int rr );
  ~Circle();
  display();
  int x, y, radius;
};


/***** Utility Functions *****/

Boolean biasedCoinFlip ( float probability );


#endif
