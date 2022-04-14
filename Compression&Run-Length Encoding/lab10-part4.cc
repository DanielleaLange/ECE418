/*===
lab10-part4-skeleton.cc

Abstract: Skeleton for part for of lab ten (predictive coding)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
#include <iomanip>
using namespace std;

// calculate the log base 2 of a number using the convention log2(0)=0
double log2 (double x);

// snake raster scan function - updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y);

// main routine
int main (int argc, char* argv[])
{
	// verify arguments' correctness
	if (argc != 3)
	{
		cerr << "Useage: " << argv[0]
		     << " input.png histogram.txt" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);
	int totalPixels = image.Width () * image.Height ();

	// create the normalized (sum of elements is one) histogram for prediction errors
	vector<double> predictionErrorHistogram (511, 0);

	// traverse the image in raster-snake order
	double preVal = image.Pixel(0,0);
	int diff = 0;

	for (int x = 1, y = 0; SnakePixel (image, x, y); )
	{
		/*===

		Insert Lab 10 Part 4 Code Here
			-as in Part 2, you will need to initialize some variables before
			 the loop (the previous pixel's value, initialized to
			 image.Pixel (0, 0), for example.
			-note that the loop starts at coordinates (1,0).  this is because
			 we need don't have any pixel to use to predict the one at (0,0)

		===*/
		diff = image.Pixel(x,y) - preVal;

		predictionErrorHistogram[diff + 255] ++;	// increment the histogram ccounting for diffusion

		if (diff != 0){
			preVal = image.Pixel(x,y);	// set the new current value
		}

	}

	// begin section for run length shenanigans
	vector<double> runLengthHistogram (totalPixels + 1, 0);

	double currVal = image.Pixel(0,0);
	double histCounter = 0;
	double runCounter = 0;
	for (int x = 0, y = 0; SnakePixel (image, x, y); )
	{
		
		if(image.Pixel(x,y) != currVal){	// if the value of the next pixel isn't the same as the previous

			runLengthHistogram[histCounter] ++;	// increment the counter for the histogram according to the histogram counter
			currVal = image.Pixel(x,y);	// set the new current value
			histCounter = 0;	// reset the histogram counter
			runCounter ++;

		} else {

			histCounter ++;	// increment the histogram counter

		}

	}

	// calculate and print the entropy of the histogram
	double entropy = 0;
	double check = 0;

	for (int i = 0; i < predictionErrorHistogram.size (); i++)
	{

		predictionErrorHistogram[i] /= totalPixels-2;
		entropy += predictionErrorHistogram[i]*log2(predictionErrorHistogram[i]);
		check += predictionErrorHistogram[i];

	}

	entropy *= -1.0;
	cout << "Prediction Error Entropy is " << entropy << "." << endl;

	// print additional needed data
	cout << setprecision(10);
	double totalBits = (entropy*totalPixels)- entropy;
	cout << "Check is " << check << "." << endl;
	cout << "The total number of runs is " << runCounter << "." << endl;
	cout << "The total number of bits required is " << totalBits << "." << endl;
	cout << "The number of bits per pixel required is " << totalBits/totalPixels << "." << endl;

	// print the histogram to the specified file
	ofstream out (argv[2]);
	if (out.fail () )
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	for (int i = 0, pixels = 0; i < predictionErrorHistogram.size (); i++)
	{
		out << predictionErrorHistogram[i] << endl;
	}
	out.close ();

	return 0;
}

// calculate the log base 2 of a number
double log2 (double x)
{
	if (x == 0) return 0;
	return log (x) / (log (2.0) );
}

// snake raster scan function - updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y)
{
	if (y % 2 == 0)
	{
		x++;
		if (x == image.Width () )
		{
			x--;
			y++;
		}
	}
	else
	{
		x--;
		if (x == -1)
		{
			x++;
			y++;
		}
	}
	return (y < image.Height () );
}
