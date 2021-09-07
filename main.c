#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>






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

 int imageWidth, imageHeight, roughness;

  imageWidth = 1280;
  imageHeight = 480;
  roughness = 2;

  int heights[imageWidth];

  for (int n = 0; n < imageWidth; n++) {
    heights[n] = 0;
  }

  heights[imageWidth-1] = rand() % imageHeight+1;
  heights[0] = rand() % imageHeight+1;

  while (1) {
    int isOver = 1;
    for(int n = 0; n < imageWidth; n++){
      if(heights[n] == 0)
        isOver = 0;
    }
    if(isOver == 1)
      break;

    int left, right;

    for(int n = 0; n < imageWidth; n++) {
      if(heights[n] == 0) {
        left = n-1;
        break;
      }
    }

    for(int n = left+1; n < imageWidth; n++) {
      if(heights[n] != 0) {
        right = n;
        break;
      }
    }

    int center = (left+right+1)/2;

    heights[center] = (heights[left] + heights[right]) / 2;
    heights[center] = heights[center] + (rand() % (roughness*2+1)) + (-roughness);
    
  }

  char * fileType = "P3\n";
  char sizeString[16];

  char montainString[16] = "17 17 40\n";
  char montainFade[16] = "25 29 76\n";
  char skyString[16] = "17 14 25\n";

  FILE *fp;
  fp = fopen ("examplefile.ppm", "w");
  fputs(fileType, fp);
  sprintf(sizeString, "%d %d\n", imageWidth, imageHeight);
  fputs(sizeString, fp);
  fputs("255\n",fp);

  for(int i = imageHeight-1; i >= 0; i--) {
    for(int j = imageWidth-1; j >= 0; j--) {
      if(heights[j] < i) {
        if((i - heights[j]) < 6){
          fputs(montainFade,fp);
        } else {
          fputs(skyString,fp);
        }
      } else {
        fputs(montainString,fp);
      }
    }
  }

  fclose(fp);
  return 0;
}
