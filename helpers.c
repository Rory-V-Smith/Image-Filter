#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through rows and columns
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            // assign colour channels to floats
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            
            // calculate average
            int average = round((red + green + blue) / 3);
            
            // set colour channels to average
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
            
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy of image
    RGBTRIPLE temp[height][width];
 
    // iterate through half of the width of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // set temp pixel as equal to image
            temp[i][j] = image[i][j];
            // reflect left side of image
            image[i][j] = image[i][width - j  - 1];
            // reflect right side of image
            image[i][width - j - 1] = temp[i][j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
        // declare variables
    int counter;
    float red, blue, green;
    
    // declare and set new image copy
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            copy_image[i][j] = image[i][j];

    // loop through rows
    for (int i = 0; i < height; i++)
    {
        // loop through columns
        for (int j = 0; j < width; j++)
        {
            // set/reset variable values
            red = blue = green = counter = 0;
            
            // loop through surrounding pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // if pixel within boundary...
                    if (i + x < height && i + x >= 0 && j + y < width && j + y >= 0)
                    {
                        // ...calculate average colour of surrounding pixels
                        red += image[i + x][j + y].rgbtRed;
                        blue += image[i + x][j + y].rgbtBlue;
                        green += image[i + x][j + y].rgbtGreen;
                        counter++;
                    }
                }
            }
            // set colour averages to new array
            copy_image[i][j].rgbtRed = round(red / counter);
            copy_image[i][j].rgbtGreen = round(green / counter);
            copy_image[i][j].rgbtBlue = round(blue / counter);
        }
    }
    // assign blurred image to origional image
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b] = copy_image[a][b];
        }
    }
    return;
}



// Calculate sobel value for each channel (capping at 255)
int sobel (float Gx, float Gy)
{
    float n = sqrt((Gx*Gx) + (Gy*Gy));
    if (n > 255)
    {
        n = 255;
    }
    return round(n);
}

// sobel edge detection algorithm
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // define kernals
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // define variables
    float Gx_red, Gx_green, Gx_blue;
    float Gy_red, Gy_green, Gy_blue;

    // define temporary array as a copy of origional array
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            copy_image[i][j] = image[i][j];

    // loop through columns
    for (int i = 0; i < height; i++)
    {
        // loop through rows
        for (int j = 0; j < width; j++)
        {
            // set/reset sobel values for each colour channel
            Gx_red = Gx_green = Gx_blue = 0;
            Gy_red = Gy_green = Gy_blue = 0;

            // 3x3 kernal around [i][j]
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x < 0 || j + y < 0 || i + x >= height || j + y >= width)
                    {
                        continue;
                    }
                    // multiply pixel within image boundary by corresponding kernal values and store accumilated value
                    // Gx kernal
                    Gx_red += copy_image[i + x][j + y].rgbtRed * Gx[x + 1][y + 1];
                    Gx_green += copy_image[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];
                    Gx_blue += copy_image[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1];

                    // Gy kernal
                    Gy_red += copy_image[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];
                    Gy_green += copy_image[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];
                    Gy_blue += copy_image[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                }
            }
            // Perform sobel operatationa and assign each colour channel value to new array
            image[i][j].rgbtRed = sobel(Gx_red, Gy_red);
            image[i][j].rgbtGreen = sobel(Gx_green, Gy_green);
            image[i][j].rgbtBlue = sobel (Gx_blue, Gy_blue);
        }
    }
    return;
}
