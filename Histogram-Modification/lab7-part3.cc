/*===
lab7-part3-skeleton.cc

Abstract: Skeleton for part three of lab seven (histogram equalization)
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
	if (argc != 3)
	{
		cerr << "Useage: " << argv[0] 
		     << " input.png output.png" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);

	// set up the histogram
	vector<int> histogram (256, 0);
	
	int sum = 0;
	// calculate the image's histogram
	for(int i=1; i< (256); i++){ 
		for (int x = 0; x < image.Width (); x++)
		{
			for (int y = 0; y < image.Height (); y++)
			{
				if(image.Pixel(x,y) < (i) && image.Pixel(x,y) >= (i-1) ){

					sum = histogram[i-1] + 1;
					histogram[i-1] = sum;
		}
	}
	}
	}
	
	// calculate the cumulative distribution function from the histogram
	vector<int> CDF (256, 0);
	//num pixels in range/total num pixels
	double pixelNum = image.Width() * image.Height();
	double Summ = 0;
	double minimum = 100000000;

	for (int i = 0; i < 256; i++) {

		minimum += ((double) histogram[i]);
		CDF[i] = Summ;

		if (CDF[i] < minimum && Summ > 0) {
			minimum = CDF[i];
		}

	}

	// apply the cumulative distribution function
	/*===
	Insert Lab 7 Part 3 Code Here - Apply the cumulative distribution
	function to equalize the image's histogram.  You can then use part two
	to compute the equalized image's histogram.
	===*/

	for (int x = 0; x < image.Width(); x++) {
		for (int y = 0; y < image.Height(); y++) {
			double q = image.Pixel(x,y);
			image.Pixel(x,y) = round((CDF[(int)q]-minimum)/(image.Width()*image.Height()-minimum)*(255));

		}
	}

	// save the image
	image.SavePng (argv[2]);

	return 0;
}