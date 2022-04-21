/*
    COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.

    "functions.cpp"
    Algorithms - Project 3 - Seam Carving
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.01 04.20.2022
    Purpose: functions file for Algorithms Project 3
*/

#include "functions.h"

// Return the smallest of three integer values
int smallestOfThree(int x, int y, int z)
{
    return min(min(x, y), z);
}

// Dynamically Allocate a 2D n x m array
int** dynamicallyAllocate2DArray(int n, int m)
{
    // Initialize the first dimension of m rows
    int **arr = new int *[m];

    // In each row, initialize n columns
    for (int j = 0; j < m; j++)
    {
        arr[j] = new int[n];
    }

    return arr;
}

// Transpose a matrix by returning a new dynamically allocated m x n matrix
int** transposeMatrix(int n, int m, int** arr)
{
    int **newArr = dynamicallyAllocate2DArray(m, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            newArr[i][j] = arr[j][i];
        }
    }

    return newArr;
}

// Reads a PGM file into a pgmHeaderData struct and a dynamically allocated 2D array
int** readPGM(string fileName, pgmHeaderData &data)
{
    ifstream image;
    image.open(fileName);

    if (!image)
    {
        quit(1, "Image file could not be opened.");
    }

    // Read in all PGM Header Data
    getline(image, data.version);
    getline(image, data.comment);
    image >> data.columns >> data.rows >> data.maxGrayLevel;

    // Print Header Data (debug purposes)
    // cout << "Version: " << data.version << endl;
    // cout << "Comment: " << data.comment << endl;
    // cout << "Width: " << data.columns << endl;
    // cout << "Height: " << data.rows << endl;
    // cout << "Max Gray Level: " << data.maxGrayLevel << endl;

    int **arr = dynamicallyAllocate2DArray(data.columns, data.rows);

    for (int i = 0; i < data.rows; i++)
    {
        for (int j = 0; j < data.columns; j++)
        {
            image >> arr[i][j];
        }
    }

    return arr;
}

// Write header data and an array of pixel values to a PGM file
void writePGM(string fileName, pgmHeaderData& data, int** arr)
{
    ofstream imageProcessed;
    imageProcessed.open(fileName);

    // Insert all header data at the top of the file
    imageProcessed << data.version << endl;
    imageProcessed << data.comment << endl;
    imageProcessed << data.columns << ' ' << data.rows << endl;
    imageProcessed << data.maxGrayLevel << endl;

    // Insert pixel values
    for (int i = 0; i < data.rows; i++)
    {
        for (int j = 0; j < data.columns; j++)
        {
            imageProcessed << arr[i][j] << ' ';
        }

        imageProcessed << endl;
    }

    imageProcessed.close();
}

// Calculate the energy matrix of an n x m pixel array
void energyMatrix(int n, int m, int** arr, int** newArr)
{
    int curr, above, below, left, right;

    // Loop through all rows
    for (int i = 0; i < m; i++)
    {
        // Loop through all columns
        for (int j = 0; j < n; j++)
        {
            curr = arr[i][j];
            
            // Top row of the pixel matrix
            if (i == 0)
            {
                above = curr;
                below = arr[i + 1][j];
            }

            // Bottom row of the pixel matrix
            else if (i == (m - 1))
            {
                above = arr[i - 1][j];
                below = curr;
            }

            // Any other row in the pixel matrix
            else
            {
                above = arr[i - 1][j];
                below = arr[i + 1][j];
            }

            // Leftmost column in the pixel matrix
            if (j == 0)
            {
                left = curr;
                right = arr[i][j + 1];
            }

            // Rightmost column in the pixel matrix
            else if (j == (n - 1))
            {
                left = arr[i][j - 1];
                right = curr;
            }

            // Any other column in the pixel matrix
            else
            {
                left = arr[i][j - 1];
                right = arr[i][j + 1];
            }

            // Equation to determine the average energy of a pixel from the pixels around it
            newArr[i][j] = abs(curr - above) + abs(curr - below) + abs(curr - left) + abs(curr - right);
        }
    }
}

// Calculate the vertical cumulative energy matrix for a given energy matrix of size n x m
void verticalCumulativeEngergyMatrix(int n, int m, int** arr, int** newArr)
{
    int curr, upLeft, upMid, upRight;

    // Loop through rows
    for (int i = 0; i < m; i++)
    {
        // Loop through columns
        for (int j = 0; j < n; j++)
        {
            curr = arr[i][j];

            // Top row of the energy matrix
            if (i == 0)
            {
                newArr[i][j] = curr;
            }

            else
            {
                // Leftmost column of the energy matrix
                if (j == 0)
                {
                    // No value exists up left; largest value ensures it is never chosen
                    upLeft = 65535;
                    upMid = newArr[i - 1][j];
                    upRight = newArr[i - 1][j + 1];
                }

                // Rightmost column of the energy matrix
                else if (j == (n - 1))
                {
                    // No value exists up right; largest value ensures it is never chosen
                    upLeft = newArr[i - 1][j - 1];
                    upMid = newArr[i - 1][j];
                    upRight = 65535;
                }

                // Anywhere else in the energy matrix
                else
                {
                    upLeft = newArr[i - 1][j - 1];
                    upMid = newArr[i - 1][j];
                    upRight = newArr[i - 1][j + 1];
                }

                newArr[i][j] = curr + smallestOfThree(upLeft, upMid, upRight);
            }
        }
    }
}

// Removes the lowest energy vertical seam in the cumulative energy matrix
// Note: This function prioritizes ALWAYS picking the leftmost lowest energy seam
void removeVerticalSeam(int n, int m, int** imageArr, int** cEnergyArr)
{
    // Start with the bottom left pixel as the lowest energy seam
    int lowestEnergySeam = cEnergyArr[m - 1][0];
    int upLeft, upMid, upRight;
    int index = 0;

    // Traverse the bottom row and find the leftmost lowest energy seam
    for (int j = 0; j < n; j++)
    {
        if (cEnergyArr[m - 1][j] < lowestEnergySeam)
        {
            lowestEnergySeam = cEnergyArr[m - 1][j];
            index = j;
        }
    }

    // Loop through all of the rows from the bottom up
    for (int i = (m - 1); i >= 0; i--)
    {
        // Remove the lowest cumulative energy pixel by shifting all pixels to its right to the left one
        for (int j = 0; j < n - index; j++)
        {
            // Shift the pixels in the original pixel array to the left to remove the current pixel in the seam
            if (j < n - index - 1)
            {
                imageArr[i][index + j] = imageArr[i][index + j + 1];
            }

            // If in the rightmost column, replace the pixel with -1 (to avoid out of bounds memory access)
            else
            {
                imageArr[i][index + j] = -1;
            }
        }

        // If there are more rows above the most recent pixel removed, move up to the next leftmost pixel in the seam
        if (i > 0)
        {
            // Index is in the furthest left column
            if (index == 0)
            {
                // No value exists up left; largest value ensures it is never chosen
                upLeft = 65535;
                upMid = cEnergyArr[i - 1][index];
                upRight = cEnergyArr[i - 1][index + 1];
            }

            // Index is in the furthest right column
            else if (index == (n - 1))
            {
                // No value exists up right; largest value ensures it is never chosen
                upLeft = cEnergyArr[i - 1][index - 1];
                upMid = cEnergyArr[i - 1][index];
                upRight = 65535;

            }

            // Index is anywhere else in the matrix
            else
            {
                upLeft = cEnergyArr[i - 1][index - 1];
                upMid = cEnergyArr[i - 1][index];
                upRight = cEnergyArr[i - 1][index + 1];
            }

            // Determine the lowest next pixel prioritizing the leftmost pixel
            lowestEnergySeam = smallestOfThree(upLeft, upMid, upRight);

            if (lowestEnergySeam == upLeft)
            {
                index--;
            }

            else if (lowestEnergySeam == upMid)
            {
                continue;
            }

            else
            {
                index++;
            }
        }
    }
}

// Quit the program with a provided exit code and an optional message to print
void quit(int code, string message)
{
    if (message != "")
    {
        cout << message << endl;
    }

    exit(code);
}

// END OF FILE //
