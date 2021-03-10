#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgcopy[height][width];
    float avg;

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            imgcopy[i][j].rgbtRed = image[i][j].rgbtRed;
            imgcopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imgcopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            avg = (float)(imgcopy[i][j].rgbtRed + imgcopy[i][j].rgbtBlue + imgcopy[i][j].rgbtGreen) / 3;

            avg = round(avg);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //upper bound for red
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            //upper bound for green
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            //upper bound for blue
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp[i][j] = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = tmp[i][j];
        }
    }
    return;
}

// Blur image
//inspired from try2filter.c
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgcopy[height][width];
    float avgRed;
    float avgGreen;
    float avgBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imgcopy[i][j].rgbtRed = image[i][j].rgbtRed;
            imgcopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imgcopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //top left corner
            if (i == 0 && j == 0)
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed +  imgcopy[i][j + 1].rgbtRed + imgcopy[i + 1][j].rgbtRed + imgcopy[i + 1][j + 1].rgbtRed) / 4;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i][j + 1].rgbtGreen + imgcopy[i + 1][j].rgbtGreen + imgcopy[i + 1][j + 1].rgbtGreen) / 4;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i][j + 1].rgbtBlue + imgcopy[i + 1][j].rgbtBlue + imgcopy[i + 1][j + 1].rgbtBlue) / 4;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //bottom left corner
            else if (i == height - 1 && j == 0)
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed +  imgcopy[i][j + 1].rgbtRed + imgcopy[i - 1][j].rgbtRed + imgcopy[i - 1][j + 1].rgbtRed) / 4;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i][j + 1].rgbtGreen + imgcopy[i - 1][j].rgbtGreen + imgcopy[i - 1][j + 1].rgbtGreen) / 4;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i][j + 1].rgbtBlue + imgcopy[i - 1][j].rgbtBlue + imgcopy[i - 1][j + 1].rgbtBlue) / 4;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //top right corner
            else if (i == 0 && j == width - 1)
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed +  imgcopy[i][j - 1].rgbtRed + imgcopy[i + 1][j].rgbtRed + imgcopy[i + 1][j - 1].rgbtRed) / 4;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i][j - 1].rgbtGreen + imgcopy[i + 1][j].rgbtGreen + imgcopy[i + 1][j - 1].rgbtGreen) / 4;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i][j - 1].rgbtBlue + imgcopy[i + 1][j].rgbtBlue + imgcopy[i + 1][j - 1].rgbtBlue) / 4;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed +  imgcopy[i][j - 1].rgbtRed + imgcopy[i - 1][j].rgbtRed + imgcopy[i - 1][j - 1].rgbtRed) / 4;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i][j - 1].rgbtGreen + imgcopy[i - 1][j].rgbtGreen + imgcopy[i - 1][j - 1].rgbtGreen) / 4;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i][j - 1].rgbtBlue + imgcopy[i - 1][j].rgbtBlue + imgcopy[i - 1][j - 1].rgbtBlue) / 4;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //top edge
            else if(i == 0 && (j > 0 && j < width - 1))
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed + imgcopy[i + 1][j].rgbtRed + imgcopy[i + 1][j - 1].rgbtRed + imgcopy[i + 1][j + 1].rgbtRed + imgcopy[i][j - 1].rgbtRed + imgcopy[i][j + 1].rgbtRed) / 6;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i + 1][j].rgbtGreen + imgcopy[i + 1][j - 1].rgbtGreen + imgcopy[i + 1][j + 1].rgbtGreen + imgcopy[i][j - 1].rgbtGreen + imgcopy[i][j + 1].rgbtGreen) / 6;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i + 1][j].rgbtBlue + imgcopy[i + 1][j - 1].rgbtBlue + imgcopy[i + 1][j + 1].rgbtBlue + imgcopy[i][j - 1].rgbtBlue + imgcopy[i][j + 1].rgbtBlue) / 6;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //left edge
            else if (j ==0 && (i < height - 1 && i > 0))
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed + imgcopy[i + 1][j].rgbtRed + imgcopy[i + 1][j + 1].rgbtRed + imgcopy[i][j + 1].rgbtRed + imgcopy[i - 1][j + 1].rgbtRed + imgcopy[i - 1][j].rgbtRed) / 6;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i + 1][j].rgbtGreen + imgcopy[i + 1][j + 1].rgbtGreen + imgcopy[i][j + 1].rgbtGreen + imgcopy[i - 1][j + 1].rgbtGreen + imgcopy[i - 1][j].rgbtGreen) / 6;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i + 1][j].rgbtBlue + imgcopy[i + 1][j + 1].rgbtBlue + imgcopy[i][j + 1].rgbtBlue + imgcopy[i - 1][j + 1].rgbtBlue + imgcopy[i - 1][j].rgbtBlue) / 6;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //right edge
            else if ((i > 0 && i < height - 1) && j == width - 1)
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed + imgcopy[i + 1][j].rgbtRed + imgcopy[i - 1][j - 1].rgbtRed + imgcopy[i][j - 1].rgbtRed + imgcopy[i - 1][j].rgbtRed + imgcopy[i + 1][j - 1].rgbtRed) / 6;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i + 1][j].rgbtGreen + imgcopy[i - 1][j - 1].rgbtGreen + imgcopy[i][j - 1].rgbtGreen + imgcopy[i - 1][j].rgbtGreen + imgcopy[i + 1][j - 1].rgbtGreen) / 6;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i + 1][j].rgbtBlue + imgcopy[i - 1][j - 1].rgbtBlue + imgcopy[i][j - 1].rgbtBlue + imgcopy[i - 1][j].rgbtBlue + imgcopy[i + 1][j - 1].rgbtBlue) / 6;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //bottom edge
            else if ((j > 0 && j < width - 1) && i == height - 1)
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed + imgcopy[i - 1][j].rgbtRed + imgcopy[i - 1][j - 1].rgbtRed + imgcopy[i][j + 1].rgbtRed + imgcopy[i][j - 1].rgbtRed + imgcopy[i][j + 1].rgbtRed) / 6;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i - 1][j].rgbtGreen + imgcopy[i - 1][j - 1].rgbtGreen + imgcopy[i][j + 1].rgbtGreen + imgcopy[i][j - 1].rgbtGreen + imgcopy[i][j + 1].rgbtGreen) / 6;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i - 1][j].rgbtBlue + imgcopy[i - 1][j - 1].rgbtBlue + imgcopy[i][j + 1].rgbtBlue + imgcopy[i][j - 1].rgbtBlue + imgcopy[i][j + 1].rgbtBlue) / 6;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //middle box (3 x 3)
            else
            {
                avgRed = (float)(imgcopy[i][j].rgbtRed + imgcopy[i][j + 1].rgbtRed + imgcopy[i][j - 1].rgbtRed + imgcopy[i - 1][j].rgbtRed + imgcopy[i + 1][j].rgbtRed + imgcopy[i - 1][j - 1].rgbtRed + imgcopy[i - 1][j + 1].rgbtRed + imgcopy[i + 1][j + 1].rgbtRed + imgcopy[i + 1][j - 1].rgbtRed) / 9;
                avgGreen = (float)(imgcopy[i][j].rgbtGreen + imgcopy[i][j + 1].rgbtGreen + imgcopy[i][j - 1].rgbtGreen + imgcopy[i - 1][j].rgbtGreen + imgcopy[i + 1][j].rgbtGreen + imgcopy[i - 1][j - 1].rgbtGreen + imgcopy[i - 1][j + 1].rgbtGreen + imgcopy[i + 1][j + 1].rgbtGreen + imgcopy[i + 1][j - 1].rgbtGreen) / 9;
                avgBlue = (float)(imgcopy[i][j].rgbtBlue + imgcopy[i][j + 1].rgbtBlue + imgcopy[i][j - 1].rgbtBlue + imgcopy[i - 1][j].rgbtBlue + imgcopy[i + 1][j].rgbtBlue + imgcopy[i - 1][j - 1].rgbtBlue + imgcopy[i - 1][j + 1].rgbtBlue + imgcopy[i + 1][j + 1].rgbtBlue + imgcopy[i + 1][j - 1].rgbtBlue) / 9;

                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);

                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
        }
    }
    return;
}