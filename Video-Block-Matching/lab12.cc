/*===
lab12-skeleton.cc

Abstract: Skeleton code for lab 12
===*/

#include "image.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// main
int main (int argc, char* argv[]) {
	
	// check arguments' correctness
	if (argc != 8) {
		cout << "Usage : " << argv[0] 
		     << " current previous blocksize"
		     << " xblock yblock search_size output_ascii_file" 
		     << endl;
	  return 1;
	}

	// load the current frame
Image current;
	current.LoadPng ( argv[1] );

	// load the previous frame
	Image previous;
	previous.LoadPng ( argv[2] );

	// parse command line arguments
	int blockSize = atoi(argv[3]);  // the size of the block we will be comparing
	int xStart = atoi(argv[4]);     // starting horizontal pixel for the block we will compare
	int yStart = atoi(argv[5]);     // starting vertical pixel for the block we will compare
	int searchSize = atoi(argv[6]); // number of pixels up and down our search will encompass

	// initialize the 2D array holding the MSE for each displacement to have size searchSize^2
	vector<vector<double> > displacementMSE (searchSize, vector<double> (searchSize, 0) );

	// fill in the displacementMSE table and print the displacement that minimizes MSE

	for (int x = 0; x < searchSize; x++) {	// set all displacement MSE's to 0
		for (int y = 0; y < searchSize; y++) {
			displacementMSE[x][y] = 0;
		}
	}



	double temp = 0;	// create a temporary varialbe
	double saveX, saveY;	// create some variables to save the motion vector values
	double min = 9999999999999;	// create a dummy min

    for (int x = 0; x < searchSize; x++) {
        for (int y = 0; y < searchSize; y++) {    // iterate through the entire catalog of motion vectors
            temp = 0;
            for (int i = 0; i < blockSize; i++) {
                for (size_t j = 0; j < blockSize; j++) {    // iterate through every pixel in the block

                    temp += (previous.Pixel(xStart + i + x - (searchSize-1)/2, yStart + j + y - (searchSize-1)/2) - current.Pixel(xStart + i, yStart + j))*(previous.Pixel(xStart + i + x - (searchSize-1)/2, yStart + j + y - (searchSize-1)/2) - current.Pixel(xStart + i, yStart + j));

                }
            }

            displacementMSE[x][y] = temp/((double)blockSize*(double)blockSize);    // add the MSE for an individual pixel
        }
    }


    for (int x = 0; x < searchSize; x++) {
        for (int y = 0; y < searchSize; y++) {

            if (displacementMSE[x][y] < displacementMSE[0][0] && displacementMSE[x][y] < min){    // find the minimum
                saveX = x-(searchSize-1)/2;
                saveY = y-(searchSize-1)/2;
                min = displacementMSE[x][y];
            }

        }
    }

	printf("xmin: %f\n", saveX);
	printf("ymin: %f\n", saveY);
	printf("min: %f\n", min);

   


   
	// fill in the displacementMSE table and print the displacement that minimizes MSE
	/*===
	
	Insert Lab 12 Code Here
	
	===*/

	// save each displacement's MSE to a file
	

	ofstream out (argv[7]);
	if (out.fail () ) 
	{
		cout << "Failed to open " << argv[7] << " for writing." << endl;
		return 1;
	}	
	for (int x = 0; x < searchSize; x++)
	{
		int xOffset = x - (searchSize - 1)/2;
		for (int y = 0; y < searchSize; y++)
		{
			int yOffset = y - (searchSize - 1)/2;
			out << xOffset << " " << yOffset << " " << displacementMSE[x][y] << endl;
		}
	}
	out.close ();	
}
