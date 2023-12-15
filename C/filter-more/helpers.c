#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float temp;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            float debugred = 0; // creating a float variable to e able to use values likes 2.3,
            float debuggreen = 0;// since they'd be rounded to 2 or such in case of int
            float debugblue = 0;
            temp = 0;
            debugred = (float)image[x][y].rgbtRed; // turning the values from the image into float
            debuggreen = (float)image[x][y].rgbtGreen;
            debugblue = (float)image[x][y].rgbtBlue;
            temp = round((debugred / 3) + (debuggreen / 3) + (debugblue / 3));
            // dividing than summing them, followed by rounding (since they need to be integer to be used)
            image[x][y].rgbtRed = temp; // copying them back into the image
            image[x][y].rgbtGreen = temp;
            image[x][y].rgbtBlue = temp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int Red;
    int Green;
    int Blue;
    int debugRed;
    int debugGreen;
    int debugBlue;
    int Width = width;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < (Width / 2); y++)
            // only up to the half, since nd i am switching the start with the end and on.
            //otherwise i'd end up switch it back.
        {
            Red = 0;
            Green = 0;
            Blue = 0;
            Red = image[x][y].rgbtRed;
            Green = image[x][y].rgbtGreen;
            Blue = image[x][y].rgbtBlue;
            image[x][y].rgbtRed = image[x][width - y - 1].rgbtRed;
            image[x][y].rgbtGreen = image[x][width - y - 1].rgbtGreen;
            image[x][y].rgbtBlue = image[x][width - y - 1 ].rgbtBlue;
            image[x][width - y - 1].rgbtRed = Red; // remember to add -1 at the end
            image[x][width - y - 1].rgbtGreen = Green; // since the "for" naturally goes only up to width -1 ( thx to the <)
            image[x][width - y - 1].rgbtBlue = Blue; // it's not a problem there, but here it's.
            // since the actual with (thx to start on 0), is width -1
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];
    float temprgbtRed;
    float temprgbtGreen;
    float temprgbtBlue;
    int n = 0;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            n = 0;
            temprgbtRed = 0;
            temprgbtGreen = 0;
            temprgbtBlue = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (x + i >= 0 && y + j >= 0 && x + i < height && y + j < width)
                    {
                        // to check if the values are within the image's matris
                        // if they are, sum them and increase n
                        n++;
                        temprgbtRed += image[x + i][y + j].rgbtRed;
                        temprgbtGreen += image[x + i][y + j].rgbtGreen;
                        temprgbtBlue += image[x + i][y + j].rgbtBlue;
                    }
                }
            }
            // than divide teh sun by N to get the average
            temprgbtRed = round(temprgbtRed / n);
            temprgbtGreen = round(temprgbtGreen / n);
            temprgbtBlue = round(temprgbtBlue / n);

            tempimage[x][y].rgbtRed = round(temprgbtRed);
            tempimage[x][y].rgbtGreen = round(temprgbtGreen);
            tempimage[x][y].rgbtBlue = round(temprgbtBlue);
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = tempimage[x][y].rgbtRed;
            image[x][y].rgbtGreen = tempimage[x][y].rgbtGreen;
            image[x][y].rgbtBlue = tempimage[x][y].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];
    int xtemprgbtRed;
    int xtemprgbtGreen;
    int xtemprgbtBlue;
    int ytemprgbtRed;
    int ytemprgbtGreen;
    int ytemprgbtBlue;
    double temprgbtRed;
    double temprgbtGreen;
    double temprgbtBlue;
    int gxcos[] = {-1, 0 , 1, -2, 0, 2, -1, 0, 1};
    int gycos[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int n = 0;
    int gxred;
    int gyred;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            n = -1;
            xtemprgbtRed = 0;
            xtemprgbtGreen = 0;
            xtemprgbtBlue = 0;
            ytemprgbtRed = 0;
            ytemprgbtGreen = 0;
            ytemprgbtBlue = 0;
            temprgbtRed = 0;
            temprgbtGreen = 0;
            temprgbtBlue = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (x + i < 0 || y + j < 0 || x + i >= height || y + j >= width) // to check if the values are within the matris,
                    {
                        //  if they aren't just increase n
                        n++;
                    }
                    else
                    {
                        n++;
                        xtemprgbtRed = xtemprgbtRed + gxcos[n] * image[x + i][y + j].rgbtRed;
                        xtemprgbtGreen = xtemprgbtGreen + gxcos[n] * image[x + i][y + j].rgbtGreen;
                        xtemprgbtBlue = xtemprgbtBlue + gxcos[n] * image[x + i][y + j].rgbtBlue;
                        ytemprgbtRed = ytemprgbtRed + gycos[n] * image[x + i][y + j].rgbtRed;
                        ytemprgbtGreen = ytemprgbtGreen + gycos[n] *image[x + i][y + j].rgbtGreen;
                        ytemprgbtBlue = ytemprgbtBlue + gycos[n] * image[x + i][y + j].rgbtBlue;
                    }
                }
            }

            gxred = (xtemprgbtRed) * (xtemprgbtRed);
            gyred = (ytemprgbtRed) * (ytemprgbtRed);
            temprgbtRed = round(sqrt((xtemprgbtRed * xtemprgbtRed) + (ytemprgbtRed * ytemprgbtRed)));
            temprgbtGreen = round(sqrt((xtemprgbtGreen * xtemprgbtGreen) + (ytemprgbtGreen * ytemprgbtGreen)));
            temprgbtBlue = round(sqrt((xtemprgbtBlue * xtemprgbtBlue) + (ytemprgbtBlue * ytemprgbtBlue)));

            if (temprgbtRed > 255)
            {
                temprgbtRed = 255;
            }
            if (temprgbtGreen > 255)
            {
                temprgbtGreen = 255;
            }
            if (temprgbtBlue > 255)
            {
                temprgbtBlue = 255;
            }

            tempimage[x][y].rgbtRed = temprgbtRed;
            tempimage[x][y].rgbtGreen = temprgbtGreen;
            tempimage[x][y].rgbtBlue = temprgbtBlue;
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = tempimage[x][y].rgbtRed;
            image[x][y].rgbtGreen = tempimage[x][y].rgbtGreen;
            image[x][y].rgbtBlue = tempimage[x][y].rgbtBlue;
        }
    }
    return;
}
