#include "helpers.h"

int black(RGBTRIPLE rgb) {
    return (rgb.rgbtRed == 0x00 && rgb.rgbtGreen == 0x00 && rgb.rgbtBlue == 0x00);
}

void setPurple(RGBTRIPLE* rgb) {
    (*rgb).rgbtRed = 0x95;
    (*rgb).rgbtGreen = 0x0;
    (*rgb).rgbtBlue = 0xA0;
}

void colorize(int height, int width, RGBTRIPLE image[height][width]) {
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (black(image[i][j]) == 1) {
                setPurple(&image[i][j]);
            }
        }
    }
}
