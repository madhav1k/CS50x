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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            copy[r][c].rgbtBlue = image[r][c].rgbtBlue;
            copy[r][c].rgbtGreen = image[r][c].rgbtGreen;
            copy[r][c].rgbtRed = image[r][c].rgbtRed;
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int gxBlue = 0;
            int gxGreen = 0;
            int gxRed = 0;
            int gyBlue = 0;
            int gyGreen = 0;
            int gyRed = 0;

            for (int h = -1; h <= 1; h++)
            {
                for (int v = -1; v <= 1; v++)
                {
                    if (r + h < 0 || r + h >= height || c + v < 0 || c + v >= width)
                    {
                        continue;
                    }

                    gxBlue += copy[r + h][c + v].rgbtBlue * gx[h + 1][v + 1];
                    gxGreen += copy[r + h][c + v].rgbtGreen * gx[h + 1][v + 1];
                    gxRed += copy[r + h][c + v].rgbtRed * gx[h + 1][v + 1];
                    gyBlue += copy[r + h][c + v].rgbtBlue * gy[h + 1][v + 1];
                    gyGreen += copy[r + h][c + v].rgbtGreen * gy[h + 1][v + 1];
                    gyRed += copy[r + h][c + v].rgbtRed * gy[h + 1][v + 1];
                }
            }

            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            image[r][c].rgbtBlue = fmin(255, blue);
            image[r][c].rgbtGreen = fmin(255, green);
            image[r][c].rgbtRed = fmin(255, red);
        }
    }
    return;
}
