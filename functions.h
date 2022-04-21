/*
    COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.

    "functions.h"
    Algorithms - Project 3 - Seam Carving
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.01 04.20.2022
    Purpose: function header file for Algorithms Project 3
*/

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#pragma once

#include "header.h"

// Struct for PGM File Type Header Data
struct pgmHeaderData
{
    string version;
    string comment;
    int columns;
    int rows;
    int maxGrayLevel;
};

///////////////////Function declarations///////////////////

// Comparison Functions
int smallestOfThree(int, int, int);

// Matrix / Array Functions
int** dynamicallyAllocate2DArray(int, int);
int** transposeMatrix(int, int, int**);

// PGM File Functions
int** readPGM(string, pgmHeaderData&);
void writePGM(string, pgmHeaderData&, int**);

// Seam Removal Algorithm Functions
void energyMatrix(int, int, int**, int**);
void verticalCumulativeEngergyMatrix(int, int, int**, int**);
void removeVerticalSeam(int, int, int**, int**);

// Quit Function
void quit(int, string errMsg="");

#endif // FUNCTIONS_H_INCLUDED

// END OF FILE //
