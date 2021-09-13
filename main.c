#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <math.h>

#include "definitions.h"
#include "io.h"
#include "funcs.h"

int main(int argc, char *argv[])
{
    Args args = get_args(argc, argv);

    int imageWidth = 1280;
    int imageHeight = 480;
    printf("%f", args.variation);
    
    double * terrain = generate_terrain(imageHeight, imageWidth, args.variation);

    generate_img_file(terrain, imageHeight, imageWidth, args.file_name);



  return 0;
}
