/*
    COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.

    "seamCarving.cpp"
    Algorithms - Project 3 - Seam Carving
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.01 04.20.2022
    Purpose: main file for Algorithms Project 3
*/

#include "header.h"
#include "functions.h"

// Main function for Algorithms Project 3 - Seam Carving
int main(int argc, char* argv[])
{
    // If no arguments are passed
    if (argc != 4)
    {
        quit(1, "\nThis program requires several specific arguments.\nPlease see the README for more information.\n");
    }

    // Print out argument information to the screen
    cout << endl << "File Name is: " << argv[1] << endl;    
    cout << "Vertical Seams to Carve: " << atoi(argv[2]) << endl;
    cout << "Horizontal Seams to Carve: " << atoi(argv[3]) << endl;

    // Create all of the required 2D Arrays and read in the PGM file
    pgmHeaderData hData;
    int **pgmValues = readPGM(argv[1], hData);
    int **pixelEnergy = dynamicallyAllocate2DArray(hData.columns, hData.rows);
    int **cumulEnergy = dynamicallyAllocate2DArray(hData.columns, hData.rows);

    // Calculate the Energy Matrix and Cumulative Energy Matrix of the original PGM File
    energyMatrix(hData.columns, hData.rows, pgmValues, pixelEnergy);
    verticalCumulativeEngergyMatrix(hData.columns, hData.rows, pixelEnergy, cumulEnergy);

    // Remove all requested vertical seams
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        // Remove leftmost lowest energy seam and decrement the number of columns
        removeVerticalSeam(hData.columns, hData.rows, pgmValues, cumulEnergy);
        hData.columns--;

        // Recalculate Energy Matrix and Cumulative Energy Matrix
        energyMatrix(hData.columns, hData.rows, pgmValues, pixelEnergy);
        verticalCumulativeEngergyMatrix(hData.columns, hData.rows, pixelEnergy, cumulEnergy);
    }

    // Create three transposed matricies for horizontal seam removal
    int **transposedPGM = transposeMatrix(hData.columns, hData.rows, pgmValues);
    int **transposedPixelEnergy = transposeMatrix(hData.columns, hData.rows, pixelEnergy);
    int **transposedCumulEnergy = transposeMatrix(hData.columns, hData.rows, cumulEnergy);

    // Calculate the Energy Matrix and Cumulative Energy Matrix of the transposed pixel matrix
    // NOTE: Switch rows and columns since the matrices are transposed
    energyMatrix(hData.rows, hData.columns, transposedPGM, transposedPixelEnergy);
    verticalCumulativeEngergyMatrix(hData.rows, hData.columns, transposedPixelEnergy, transposedCumulEnergy);

    // Remove all requested horizontal seams (via vertical seams in the transposed matrix)
    for (int j = 0; j < atoi(argv[3]); j++)
    {
        // Remove leftmost lowest energy seam and decrement the number of rows (since transposed)
        removeVerticalSeam(hData.rows, hData.columns, transposedPGM, transposedCumulEnergy);
        hData.rows--;

        // Recalculate Energy Matrix and Cumulative Energy Matrix
        energyMatrix(hData.rows, hData.columns, transposedPGM, transposedPixelEnergy);
        verticalCumulativeEngergyMatrix(hData.rows, hData.columns, transposedPixelEnergy, transposedCumulEnergy);
    }

    // Transpose the final pixel matrix back to the correct n - argv[2] x m - argv[3] array
    pgmValues = transposeMatrix(hData.rows, hData.columns, transposedPGM);

    // Construct the processed file name "image_student_processed_argv[2]_argv[3].pgm"
    string newFileName = string(argv[1]).substr(0, string(argv[1]).find(".pgm"));
    newFileName += "_student_processed_" + string(argv[2]) + "_" + string(argv[3]) + ".pgm";

    // Write the seam removed pixel array into the processed image file
    cout << endl << "Writing to file: " << newFileName << endl;
    writePGM(newFileName, hData, pgmValues);
    cout << "Done!" << endl;

    // End the program gracefully
    quit(0, "\nExiting gracefully\n");
    return 0;
}

// END OF FILE //
