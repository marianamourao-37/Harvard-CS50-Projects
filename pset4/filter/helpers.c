// libraries imported
#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbgray;

    // loops over every pixel(row = i,column = j) in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // floating average of the red, green, and blue values of the current pixel(i,j), followed by conversion to an integer (by the
            // round function)
            rgbgray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            if (rgbgray > 255) // if the average exceeds the maximum value permitted
            {
                rgbgray = 255; // assigns the maximum value
            }

            // shade of grey assigned to the three color channels, casting to an integer
            image[i][j].rgbtBlue = (int) rgbgray;
            image[i][j].rgbtGreen = (int) rgbgray;
            image[i][j].rgbtRed = (int) rgbgray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp; // structure that contains the fields referring to the rgb channels, and to which is going to be assigned a temporal
    // pixel for posterior exchange with its horizontal reflection pair

    // loops over the pixels that belong to the image's first half
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            temp = image[i][j]; // stores the present pixel value for posterior exchange with its horizontal reflection pair

            // exchange of present pixel rgb values with its horizontal reflection pair, and vice versa, respectively
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float num_pixel; // creates the variable to which is assigned the number of pixels involved in the blurring operation of a specific pixel

    RGBTRIPLE image_temp[height][width]; // creates a matrix of the same size as the original image, that is going to store the blurred pixels

    int temp[3]; // creates an array that stores the total sum of rgb values involved in the blurring operation of a specific pixel

    // loops over every pixel(row = i,column = j) in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            num_pixel = 0.0; // initiates the number of pixels involved in the blurring operation of the present pixel(i,j)
            temp[0] = 0; // initiates the total sum of the blue value for the present pixel(i,j)
            temp[1] = 0; // initiates the total sum of the red value for the present pixel(i,j)
            temp[2] = 0; // initiates the total sum of the green value for the present pixel(i,j)

            // loops over the neighboring pixels (row = k, column = t)
            for (int k = - 1; k <= 1; k ++)
            {
                for (int t = - 1; t <= 1; t ++)
                {
                    if (i + k !=  -1 && i + k != height && j + t != -1 && j + t != width) // if the neighboring pixel(k+i,t+j) doesn't transpass
                        // the image edge
                    {
                        // actualizes the total sum of the rgb channels for the present pixel(i,j) by adding the rgb values of the neighboring
                        // pixel(k+i,t+j)
                        temp[0] += image[i + k][j + t].rgbtBlue;
                        temp[1] += image[i + k][j + t].rgbtRed;
                        temp[2] += image[i + k][j + t].rgbtGreen;
                        num_pixel ++; // increments by 1 the number of pixels involved in the blurring operation of the present pixel(i,j)
                    }
                }
            }
            // floating average of the red, green, and blue values of the current pixel(i,j), followed by conversion to an integer
            // (by the round function)
            image_temp[i][j].rgbtBlue = round(temp[0] / num_pixel);
            image_temp[i][j].rgbtRed = round(temp[1] / num_pixel);
            image_temp[i][j].rgbtGreen = round(temp[2] / num_pixel);
        }
    }

    // copies values from temporary matrix to the input image, producing the output blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_temp[i][j].rgbtRed;
        }

    }
}

// Evalutes if the pixel value exceeds the maximum permitted
int limit_rgb(int pixel)
{
    if (pixel > 255)
    {
        pixel = 255; // assigns the maximum value
    }

    return pixel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // horizontal and vertical kernels (Sobel edge filter)
    float gx[3][3] = {{-1.0, 0.0, 1.0},
        {-2.0, 0.0, 2.0},
        {-1.0, 0.0, 1.0}

    };
    float gy[3][3] = {{-1.0, -2.0, -1.0},
        {0.0, 0.0, 0.0},
        {1.0, 2.0, 1.0}

    };

    // creation of arrays that stores the dot product between each rgb channels of a specific pixel with gx and gy, respectively
    float image_edge_x[3];
    float image_edge_y[3];

    RGBTRIPLE image_edge_final[height][width]; // creates a matrix of the same size as the original image, that is going to store the
    // total derivative (g = sqrt(gx^2 + gy^2)) of a specific pixel

    // loops over every pixel(row = i,column = j) in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initiates the dot product between the blue matrix values of the present pixel(i,j) with gx and gy, respectively
            image_edge_x[0] = 0.0;
            image_edge_y[0] = 0.0;

            // initiates the dot product between the red matrix values of the present pixel(i,j) with gx and gy, respectively
            image_edge_x[1] = 0.0;
            image_edge_y[1] = 0.0;

            // initiates the dot product between the green matrix values of the present pixel(i,j) with gx and gy, respectively
            image_edge_x[2] = 0.0;
            image_edge_y[2] = 0.0;

            // loops over the neighboring pixels (row = k, column = t)
            for (int k = - 1; k <= 1; k ++)
            {
                for (int t = - 1; t <= 1; t ++)
                {
                    if (i + k !=  -1 && i + k != height && j + t != -1 && j + t != width) // if the neighboring pixel(k,t) doesn't transpass the
                        // image edge
                    {
                        // actualizes the dot product between the rgb values for the present pixel (i,j) with gx and gy, respectively, by adding
                        // the product between the neighboring pixel(k + i,t + j) rgb values with gx(k+1,t+1) and gy(k+1,t+1), respectively
                        image_edge_x[0] += (gx[k + 1][t + 1] * image[k + i][t + j].rgbtBlue);
                        image_edge_y[0] += (gy[k + 1][t + 1] * image[k + i][t + j].rgbtBlue);
                        image_edge_x[1] += (gx[k + 1][t + 1] * image[k + i][t + j].rgbtRed);
                        image_edge_y[1] += (gy[k + 1][t + 1] * image[k + i][t + j].rgbtRed);
                        image_edge_x[2] += (gx[k + 1][t + 1] * image[k + i][t + j].rgbtGreen);
                        image_edge_y[2] += (gy[k + 1][t + 1] * image[k + i][t + j].rgbtGreen);
                    }
                }
            }

            // stores to the temporary matrix the total derivative (g = sqrt(gx^2 + gy^2)) of the present pixel(i,j), for each rgb channel,
            // followed by conversion to an integer (by the roundfunction) and evaluation if the pixel value exceeds the maximum permitted
            // (calls the funcStion limit_rgb)
            image_edge_final[i][j].rgbtBlue = limit_rgb(round(sqrt(image_edge_x[0] * image_edge_x[0] +
                                              image_edge_y[0] * image_edge_y[0])));
            image_edge_final[i][j].rgbtRed = limit_rgb(round(sqrt(image_edge_x[1] * image_edge_x[1] +
                                             image_edge_y[1] * image_edge_y[1])));
            image_edge_final[i][j].rgbtGreen = limit_rgb(round(sqrt(image_edge_x[2] *  image_edge_x[2] +
                                               image_edge_y[2] * image_edge_y[2])));

        }
    }

    // copies values from temporary matrix to the input image, producing the edge detection image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_edge_final[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_edge_final[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_edge_final[i][j].rgbtRed;
        }

    }
}
