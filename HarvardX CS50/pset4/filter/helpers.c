#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int gray = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtBlue = gray;
            image[h][w].rgbtGreen = gray;
            image[h][w].rgbtRed = gray;
        }
    }
    return;
}

// RGBTRIPLE square(int height, int width, RGBTRIPLE image[height][width], int h, int w)
// {
//     RGBTRIPLE threeby[3][3];

//     for (int i = h - 1; i <= h + 1; i++);
//     return threeby;
// }

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE pixel = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a backup image before changing original
    RGBTRIPLE backup_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            backup_image[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float count = 0.0;
            long blue = 0;
            long green = 0;
            long red = 0;

            for (int i = fmax(0, h - 1); i < fmin(height, h + 2); i++)
            {
                for (int j = fmax(0, w - 1); j < fmin(width, w + 2); j++)
                {
                    blue += backup_image[i][j].rgbtBlue;
                    green += backup_image[i][j].rgbtGreen;
                    red += backup_image[i][j].rgbtRed;
                    count++;
                }
            }
            image[h][w].rgbtBlue = round(blue / count);
            image[h][w].rgbtGreen = round(green / count);
            image[h][w].rgbtRed = round(red / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create a backup image before changing original
    RGBTRIPLE backup_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            backup_image[h][w] = image[h][w];
        }
    }

    // create Sobel vectors
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            long blue_x = 0;
            long blue_y = 0;
            long green_x = 0;
            long green_y = 0;
            long red_x = 0;
            long red_y = 0;

            // initialize vector counters
            int Gi = 0;
            if (h == 0)
            {
                Gi = 1;
            }

            for (int i = fmax(0, h - 1); i < fmin(height, h + 2); i++)
            {
                int Gj = 0;
                if (w == 0)
                {
                    Gj = 1;
                }
                for (int j = fmax(0, w - 1); j < fmin(width, w + 2); j++)
                {
                    blue_x += backup_image[i][j].rgbtBlue * Gx[Gi][Gj];
                    green_x += backup_image[i][j].rgbtGreen * Gx[Gi][Gj];
                    red_x += backup_image[i][j].rgbtRed * Gx[Gi][Gj];
                    blue_y += backup_image[i][j].rgbtBlue * Gy[Gi][Gj];
                    green_y += backup_image[i][j].rgbtGreen * Gy[Gi][Gj];
                    red_y += backup_image[i][j].rgbtRed * Gy[Gi][Gj];
                    Gj++;
                }
                Gi++;
            }
            image[h][w].rgbtBlue = fmin(round(pow(blue_x*blue_x + blue_y*blue_y, 0.5)), 255);
            image[h][w].rgbtGreen = fmin(round(pow(green_x*green_x + green_y*green_y, 0.5)), 255);
            image[h][w].rgbtRed = fmin(round(pow(red_x*red_x + red_y*red_y, 0.5)), 255);
        }
    }
    return;
}
