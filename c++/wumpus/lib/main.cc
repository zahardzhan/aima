#include "WumpusEnvironment.hh"

const int MaxSteps = 1000;

#ifndef TEST
main ( int argc, char **argv )
{
  int size=0, trials=1;
  char *filename;
  WumpusEnvironment *env;
  
  switch ( argc )
    {
    case 1:
      break;

    case 3:
      if ((size = atoi ( argv[ 2 ] )) == 0) {
         filename = argv[2];
         size = -1;
      }
      
    case 2:
      trials = atoi ( argv[ 1 ] );
      break;

    default:
      cerr << "Usage: " << argv[0]
           << "[ num_trials [ size_of_world | world_file ] ]"
           << endl;
      exit ( 0 );
    }

  if (size != -1)
     env = new WumpusEnvironment ( size );
  else env = new WumpusEnvironment ( filename );
      
  if ( trials > 1 )
    env->trials ( trials, MaxSteps );
  else
    env->run ( MaxSteps );
}

#else
#include "Image.hh"

Orientation g_or;

main()
{
  WumpusEnvironment dummy;
  Image image;
  int i;

  for ( g_or=0; g_or<4; g_or+=1 )
    for ( i=0; i<10; i++ )
      {
	image.paint ( 1, 1, 1, 0 );
	cout << image << endl;
      }
}

#endif
