/*===
lab7-part2-skeleton.cc

Abstract: Skeleton for part two of lab seven (histogram output)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// verify arguments' correctness
	if (argc != 4)
	{
		cerr << "Useage: " << argv[0] 
		     << " input.png histogram.txt bin_count" << endl;
		return 1;
	}
	int binCount = atoi (argv[3]);
	if (binCount < 1)
	{
		cerr << "Bin count must be greater than zero" << endl;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);
	int sum= 0;
	// set up the histogram (vector size binCount all values 0)
	vector<int> histogram (binCount, 0);
	int m = 256/binCount;
	// perform gamma point operation
	for(int i=1; i<= (binCount); i++){ //for every grey value
		//sum = 0;
		for (int x = 0; x < image.Width (); x++)
		{
			for (int y = 0; y < image.Height (); y++)
			{

				if(image.Pixel(x,y) < (i)*m && image.Pixel(x,y) >= (i-1)*m ){
				//else{
					sum = histogram[i-1] + 1;
					//sum = image.Pixel(x,y);
					histogram[i-1] = sum;
				}
			}
		}
	}
	
	
	// print the histogram the specified file
	ofstream out (argv[2]);
	if (out.fail () )
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	for (int i = 0; i < histogram.size (); i++)
	{
		out << histogram[i] << endl;
	}
	out.close ();

	return 0;
}

