COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.
    Algorithms Project 3 - Seam Carving
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.10 04.20.2022
    Purpose: This README covers the important things to know for Algorithms Project 3 - Seam Carving 

Original project description and test cases provided by Dr. Duan for Algorithms 435 - Project 3

The code for this project can be found at: https://github.com/jaccon236/Algorithms_435_Seam_Carving

% Seam Carving
    Purpose:
        This program removes x vertical seams and y horizontal seams from an image stored as a PGM file
            The input file must be a .pgm file with a version, comment, width x height values, and a max grayscale value as the header
            The output file will be a file of the same name as the input with "_student_processed_x_y" appended to it where x and y are the number of removed seams

    Compilation:
        To compile seamCarving.cpp, multiple files are required. This README assumes you have a C++ compiler installed and are able to utilize Makefiles. 
            If this project has been accessed via GitHub, you may skip to step 3.

     1) Put seamCarving.cpp in the same directory as the files listed below. All of these files can be found via GitHub but should also have been submitted via zip files. 
        The files that are needed in conjunction with seamCarving.cpp to compile the program are:
            header.h
            functions.h
            functions.cpp
            Makefile

     2) Using the Makefile provided with the code for this project, no modifications are necessary 
            You can create your own Makefile as long as you know how to do this properly if you would like to

     3) Once all required files are in the same directory, run the "make" command or it's equivalent on your system to build the project.
            No warnings or errors should appear

     4) Assuming everything has been done correctly, multiple object and *.d files appear in the directory along with carve.exe.
            If they have not, verify that you have followed all of the steps correctly. If you are still having issues, email me any questions you may have.
            To remove these files from the directory when finished using the program, an OS specific clean command can be run
                1) If your OS is Linux based use: make clean
                2) If your OS is Windows based use: make cleanw

    Execution:
        Arguments: This program expects multiple arguments.
            1) The name of the program
            2) The name of the file to be carved
            3) The number of vertical seams to remove
            4) The number of horizontal seams to remove
        
        Formatting: Replace filename with the name of the *.pgm file. Make sure to include all file extensions.
            To carve x vertical seams and y horizontal seams from an image: 
                .\carve.exe filename.pgm x y
           
        Output: This program will output text to the console and to *.pgm files.
            1) The console will show the name of the pgm file to be carved and the number of vertical and horizontal seams to carve.
            2) The console will also show the name of the file which the carved pgm image will be saved to then exit gracefully.
            3) A pgm file with the naming convention "originalImageName_student_processed_x_y.pgm" will be created or updated.
                Here x and y are the number of removed vertical and horizontal seams respectively.
            4) If incorrect formatting of arguments are provided, the program will terminate and prompt the user with their mistake.
            5) If the file name specified does not exist in the current directory, the program will terminate and prompt the user with their mistake.