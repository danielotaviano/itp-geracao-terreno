#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "definitions.h"


Args get_args(int argc, char **argv) {
  Args args;
  int d = 0, o = 0;
  
  if( argc >= 2 )
    {
        for(int i = 1; i < argc; i++)
        {
          if(strcmp(argv[i], "-d") == 0){
            args.variation = atof(argv[i+1]);
            d = 1;
          }
          
          if(strcmp(argv[i], "-o") == 0){
            args.file_name = malloc(strlen(argv[i+1])*sizeof(char));
            args.file_name = argv[i+1];
            o = 1;
          }
        }
    }


  if(o == 0){
    args.file_name = malloc(strlen("default_name.ppm")*sizeof(char));
    args.file_name = "default_name.ppm";
  }
  if(d == 0)
    args.variation = 0.6;
  
  return args;
}
