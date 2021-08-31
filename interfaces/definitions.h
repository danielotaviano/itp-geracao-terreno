#ifndef DEF
#define DEF

typedef struct arguments {
   int variation;
   char * file_name;
} Args;

typedef struct img {
   char[3] code = "P3";
   int h;
   int w;
   int max_rgb = 255;
   char * line_representation;
} Img;

#endif