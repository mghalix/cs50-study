#include "helpers.h"
#include <math.h>

#define SZ 3

const int GX[SZ][SZ] =
{
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
const int GY[SZ][SZ] =
{
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

void set_black(RGBTRIPLE *px)
{
    px->rgbtRed = px->rgbtGreen = px->rgbtBlue = 0;
}

RGBTRIPLE compute(int height, int width, RGBTRIPLE box[height][width], int i, int j)
{
    int gxrsum, gxgsum, gxbsum, gyrsum, gygsum, gybsum;
    gxrsum = gxgsum = gxbsum = gyrsum = gygsum = gybsum = 0;
    for (int row = (i - 1), x = 0; row <= (i + 1); row++)
    {
        for (int col = (j - 1), y = 0; col <= (j + 1); col++)
        {

            if (row < 0 || row >= height || col < 0 || col >= width)
            {
                continue;
            }

            gxrsum += box[row][col].rgbtRed * GX[row - i + 1][col - j + 1];
            gxgsum += box[row][col].rgbtGreen * GX[row - i + 1][col - j + 1];
            gxbsum += box[row][col].rgbtBlue * GX[row - i + 1][col - j + 1];

            gyrsum += box[row][col].rgbtRed * GY[row - i + 1][col - j + 1];
            gygsum += box[row][col].rgbtGreen * GY[row - i + 1][col - j + 1];
            gybsum += box[row][col].rgbtBlue * GY[row - i + 1][col - j + 1];
        }
    }

    RGBTRIPLE sobel;
    sobel.rgbtRed = (unsigned char) fmin(round(sqrt(gxrsum * gxrsum + gyrsum * gyrsum)), 255);
    sobel.rgbtGreen = (unsigned char) fmin(round(sqrt(gxgsum * gxgsum + gygsum * gygsum)), 255);
    sobel.rgbtBlue = (unsigned char) fmin(round(sqrt(gxbsum * gxbsum + gybsum * gybsum)), 255);
    return sobel;
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

float average_pixel(RGBTRIPLE px)
{
    return (px.rgbtRed + px.rgbtGreen + px.rgbtBlue) / 3.0;
}

void set_all(RGBTRIPLE *px, unsigned char val)
{
    px->rgbtRed = px->rgbtGreen = px->rgbtBlue = val;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            set_all(&(image[i][j]), round(average_pixel(image[i][j])));
        }
    }
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, end = width - 1; j < width / 2; j++, end--)
        {
            swap(&(image[i][j]), &(image[i][end]));
        }
    }
}

RGBTRIPLE box_average(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int rsum, gsum, bsum, count;
    rsum = gsum = bsum = count = 0;
    for (int row = (i - 1); row <= (i + 1); row++)
    {
        for (int col = (j - 1); col <= (j + 1); col++)
        {
            if (row < 0 || row >= height || col < 0 || col >= width)
            {
                continue;
            }

            rsum += image[row][col].rgbtRed;
            gsum += image[row][col].rgbtGreen;
            bsum += image[row][col].rgbtBlue;
            ++count;
        }
    }

    RGBTRIPLE avg =
    {
        round(bsum / (float) count),
        round(gsum / (float) count),
        round(rsum / (float) count)
    };
    return avg;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = box_average(height, width, image, i, j);
        }
    }

    copy(height, width, temp, image);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = compute(height, width, image, i, j);
        }
    }

    copy(height, width, temp, image);
}
