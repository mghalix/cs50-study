#include "helpers.h"
#include <math.h>

float average(RGBTRIPLE rgb)
{
    return (rgb.rgbtRed + rgb.rgbtGreen + rgb.rgbtBlue) / 3.0;
}

RGBTRIPLE two_dimensional_average(int height, int width, RGBTRIPLE box[height][width], int i, int j)
{
    int rsum, gsum, bsum, count;
    rsum = gsum = bsum = count = 0;

    // relative location on each row from -1 to 1
    for (int row = (i - 1); row <= (i + 1); row++)
    {
        // relative location on each column from -1 to 1
        for (int col = (j - 1); col <= (j + 1); col++)
        {
            // skip the current loop if it passed the pixels
            // left or right, top or bottom walls
            if (row < 0 || row >= height || col < 0 || col >= width)
            {
                continue;
            }

            rsum += box[row][col].rgbtRed;
            gsum += box[row][col].rgbtGreen;
            bsum += box[row][col].rgbtBlue;
            count++;
        }
    }

    RGBTRIPLE avg;
    avg.rgbtRed = round(rsum / (float) count);
    avg.rgbtGreen = round(gsum / (float) count);
    avg.rgbtBlue = round(bsum / (float) count);
    return avg;
}

void set_all_same(RGBTRIPLE *rgb, uint8_t val)
{
    (*rgb).rgbtRed = (*rgb).rgbtGreen = (*rgb).rgbtBlue = val;
}

void set_all_rgb(RGBTRIPLE *rgb, uint8_t r, uint8_t g, uint8_t b)
{
    (*rgb).rgbtRed = r;
    (*rgb).rgbtGreen = g;
    (*rgb).rgbtBlue = b;
}

void set_all_rgbtriple(RGBTRIPLE *rgb, RGBTRIPLE val)
{
    set_all_rgb(rgb, val.rgbtRed, val.rgbtGreen, val.rgbtBlue);
}

uint8_t min(int a, int b)
{
    return (a > b ? b : a);
}

void correct(float *r, float *g, float *b)
{
    *r = round(*r);
    *g = round(*g);
    *b = round(*b);

    // if the value of any rgb pixel passes 255
    // cap it to 255
    *r = min(*r, 255);
    *g = min(*g, 255);
    *b = min(*b, 255);
}

void swap(uint8_t *a, uint8_t *b)
{
    if (*a == *b)
    {
        return;
    }

    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void swap_rgb(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}

RGBTRIPLE sepiaOf(RGBTRIPLE rgb)
{
    float sepiaRed = .393 * rgb.rgbtRed + .769 * rgb.rgbtGreen + .189 * rgb.rgbtBlue;
    float sepiaGreen = .349 * rgb.rgbtRed + .686 * rgb.rgbtGreen + .168 * rgb.rgbtBlue;
    float sepiaBlue = .272 * rgb.rgbtRed + .534 * rgb.rgbtGreen + .131 * rgb.rgbtBlue;
    // round and cap to 255 if larger
    correct(&sepiaRed, &sepiaGreen, &sepiaBlue);
    set_all_rgb(&rgb, sepiaRed, sepiaGreen, sepiaBlue);
    return rgb;
}

void copy(int height, int width, RGBTRIPLE src[height][width], RGBTRIPLE dest[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            set_all_same(&(image[i][j]), round(average(image[i][j])));
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            set_all_rgbtriple(&(image[i][j]), sepiaOf(image[i][j]));
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int start = 0, end = width - 1; start < (width / 2); start++, end--)
        {
            swap_rgb(&(image[i][start]), &(image[i][end]));
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // extra array to not lose original image rgbs
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set each pixel to the blurred version of it by calculating
            // the average of neighboring pixels
            temp[i][j] = two_dimensional_average(height, width, image, i, j);

        }
    }

    //                  src , dest
    copy(height, width, temp, image); // replace the image with the blurred version of it
}