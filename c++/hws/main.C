#include <stdlib.h>
#include <iostream.h>
#include "Circle.H"

main(int argc, char *argv[])
{
  int x, y, radius;
  float noise;

  if (argc != 5) {
    cerr << "usage: " << argv[0] << " x y radius noise\n";
    exit(-1);
  }

  x = atoi(argv[1]);
  y = atoi(argv[2]);
  radius = atoi(argv[3]);
  noise = atof(argv[4]);

  // set random number generator seed (optional)
  srandom(123);

  circleImage ci(x,y,radius);

  cout << "Original Image:\n\n";
  ci.display();

  cout << "\nImage plus " << (100*noise) << "% noise:\n\n";
  ci.addNoise(noise);
  ci.display();
}
