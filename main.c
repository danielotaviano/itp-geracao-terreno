#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <math.h>







int main(int argc, char *argv[])
{
//     int i;
//     if( argc >= 2 )
//     {
//         printf("The arguments supplied are:\n");
//         for(i = 1; i < argc; i++)
//         {
//             printf("%s\t", argv[i]);
//         }
//     }
//     else
//     {
//         printf("argument list is empty.\n");
//     }

  srand(time(0));

 int imageWidth, imageHeight, displace;
 float roughness;

  imageWidth = 1280;
  imageHeight = 480;
  roughness = 0.6;
  displace = imageHeight / 4;

  int power = pow(2, ceil(log(imageWidth) / (log(2))));

  double heights[power];

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


  char * fileType = "P3\n";
  char sizeString[16];

  char skyString[16] = "17 19 40\n";
  char montainString[16] = "17 14 25\n";
  char startString[16] = "128 128 128\n";
  char shineString[16] = "255 255 204\n";

  FILE *fp;
  fp = fopen ("examplefile.ppm", "w");
  fputs(fileType, fp);
  sprintf(sizeString, "%d %d\n", imageWidth, imageHeight);
  fputs(sizeString, fp);
  fputs("255\n",fp);

  for(int i = imageHeight-1; i >= 0; i--) {
    for(int j = imageWidth-1; j >= 0; j--) {
      if(heights[j] < i) {
        int randomSkyNumber = rand() % 1000;
        if(randomSkyNumber > 2) {
          fputs(skyString,fp);
        } else {
          fputs(startString,fp);
        }
      } else {
        fputs(montainString,fp);
      }
    }
  }

  fclose(fp);
  return 0;
}
