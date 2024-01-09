#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int rgbtGray = round((image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed) / 3.0);
            image[r][c].rgbtBlue = rgbtGray;
            image[r][c].rgbtGreen = rgbtGray;
            image[r][c].rgbtRed = rgbtGray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int sepiaBlue = round(0.131 * image[r][c].rgbtBlue + 0.534 * image[r][c].rgbtGreen + 0.272 * image[r][c].rgbtRed);
            int sepiaGreen = round(0.168 * image[r][c].rgbtBlue + 0.686 * image[r][c].rgbtGreen + 0.349 * image[r][c].rgbtRed);
            int sepiaRed = round(0.189 * image[r][c].rgbtBlue + 0.769 * image[r][c].rgbtGreen + 0.393 * image[r][c].rgbtRed);

            image[r][c].rgbtBlue = fmin(255, sepiaBlue);
            image[r][c].rgbtGreen = fmin(255, sepiaGreen);
            image[r][c].rgbtRed = fmin(255, sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width / 2; c++)
        {
            temp = image[r][c];
            image[r][c] = image[r][width - 1 - c];
            image[r][width - 1 - c] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            copy[r][c] = image[r][c];
        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            float count = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;

            for (int h = -1; h <= 1; h++)
            {
                for (int v = -1; v <= 1; v++)
                {
                    if (r + h < 0 || r + h >= height || c + v < 0 || c + v >= width)
                    {
                        continue;
                    }
                    sumBlue += copy[r + h][c + v].rgbtBlue;
                    sumGreen += copy[r + h][c + v].rgbtGreen;
                    sumRed += copy[r + h][c + v].rgbtRed;
                    count++;
                }
            }
            image[r][c].rgbtBlue = round(sumBlue / count);
            image[r][c].rgbtGreen = round(sumGreen / count);
            image[r][c].rgbtRed = round(sumRed / count);
        }
    }
    return;
}