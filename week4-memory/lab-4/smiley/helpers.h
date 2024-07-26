#include "bmp.h"

// colorize image
void colorize(int height, int width, RGBTRIPLE image[height][width]);

// check if the current rgb is black
int black(RGBTRIPLE rgb);

// sets current rgb to purple
void setPurple(RGBTRIPLE* rgb);