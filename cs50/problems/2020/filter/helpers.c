#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get blue, green and red values for current pixel
            BYTE blue_value = image[i][j].rgbtBlue;
            BYTE green_value = image[i][j].rgbtGreen;
            BYTE red_value = image[i][j].rgbtRed;

            //calculate average pixel value
            BYTE average_value = round((blue_value + green_value + red_value) / 3.0);

            //assign calculated average to b,r,g in original pixel
            image[i][j].rgbtBlue = average_value;
            image[i][j].rgbtGreen = average_value;
            image[i][j].rgbtRed = average_value;
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
            //for every pixel in image, get original b, g, r values, calculate new values and
            //store back in image

            BYTE blue_value = image[i][j].rgbtBlue;
            BYTE green_value = image[i][j].rgbtGreen;
            BYTE red_value = image[i][j].rgbtRed;

            float new_blue_value = round(0.272 * red_value + 0.534 * green_value + 0.131 * blue_value);
            if (new_blue_value <= 0xFF) //if less than equal to 255
            {
                image[i][j].rgbtBlue = new_blue_value;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }


            float new_green_value = round(0.349 * red_value + 0.686 * green_value + 0.168 * blue_value);
            if (new_green_value <= 0xFF)
            {
                image[i][j].rgbtGreen = new_green_value;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }


            float new_red_value = round(0.393 * red_value + .769 * green_value + .189 * blue_value);
            if (new_red_value <= 0xFF)
            {
                image[i][j].rgbtRed = new_red_value;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //making copy of image array
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    //reflect image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][(width - 1) - j]; //i remains same, j changes to width - 1 - j
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width]; /*Temporary image array where new calculated pixels will be stored.
                                         in the end, content of this array will be copied to original array.
                                         This is done because every pixel's calculation needs ORIGINAL values of surrounding pixels.
                                         */

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float count_surrounding_pixels = 0.0; //this variable will be used to calculate average pixel values.

            //variables to store sum of surrounding pixel values for average calculation
            int sum_blue = 0;
            int sum_green = 0;
            int sum_red = 0;

            //surrounding pixels are within -1 and +1 (in both x and y cordinate) of a pixel.
            for (int k = (i - 1); k <= (i + 1); k++)
            {
                for (int l = (j - 1); l <= (j + 1); l++)
                {
                    if (k == -1 || k == height || l == -1 || l == width) //if out of bounds
                    {
                        //pass
                    }
                    else
                    {
                        count_surrounding_pixels++;
                        sum_blue += image[k][l].rgbtBlue;
                        sum_green += image[k][l].rgbtGreen;
                        sum_red += image[k][l].rgbtRed;
                    }
                }
            }

            temp_image[i][j].rgbtBlue = round(sum_blue / count_surrounding_pixels);
            temp_image[i][j].rgbtGreen = round(sum_green / count_surrounding_pixels);
            temp_image[i][j].rgbtRed = round(sum_red / count_surrounding_pixels);
        }

    }

    //copy contents of the temporary array to new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }

    return;
}
