#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <math.h>
#include "definitions.h"




double * generate_terrain(int imageHeight, int imageWidth, double roughness) {
  srand(time(0));
  printf("%f", roughness);

  int  displace;

  displace = imageHeight / 4;

  int power = pow(2, ceil(log(imageWidth) / (log(2))));

  double * heights;

  heights = malloc(sizeof(double) * power);

  for (int n = 0; n < power; n++) {
    heights[n] = 0;
  }

  heights[0] = imageHeight/2 + (((double)rand() / (double)RAND_MAX) * displace*2) - displace;
  heights[power] = imageHeight/2 + (((double)rand() / (double)RAND_MAX) * displace*2) - displace;
  displace *= roughness;

   for(int i = 1; i < power; i *=2){
        for(int j = (power/i)/2; j < power; j+= power/i){
          heights[j] = ((heights[j - (power / i) / 2] + heights[j + (power / i) / 2]) / 2);
          heights[j] += ((((double)rand() / (double)RAND_MAX))*displace*2) - displace;
        }
        displace *= roughness;
  }
  return heights;
}

void generate_img_file(double * terrain, int height, int width, char * file_name) {
  char * fileType = "P3\n";
  char sizeString[16];

  char skyString[16] = "17 19 40\n";
  char montainString[16] = "17 14 25\n";
  char starString[16] = "128 128 128\n";

  FILE *fp;
  fp = fopen (file_name, "w");
  fputs(fileType, fp);
  sprintf(sizeString, "%d %d\n", width, height);
  fputs(sizeString, fp);
  fputs("255\n",fp);

  for(int i = height-1; i >= 0; i--) {
    for(int j = width-1; j >= 0; j--) {
      if(terrain[j] < i) {
        int randomSkyNumber = rand() % 1000;
        if(randomSkyNumber > 2) {
          fputs(skyString,fp);
        } else {
          fputs(starString,fp);
        }
      } else {
        fputs(montainString,fp);
      }
    }
  }

  fclose(fp);
}
