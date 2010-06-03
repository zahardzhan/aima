#include "RndGen.hh"
#include <sys/time.h>
#include <values.h>

ACG rng ( 4847, 20 ); //( time ( 0 ), 20 );

RandomInteger randInt ( 0, MAXLONG, &rng );
