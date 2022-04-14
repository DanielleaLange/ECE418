/*===
lab10-part1-solution.cc

Abstract: Skeleton for part one of lab ten (entropy calculation)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "image.h"
using namespace std;

// calculate the log base 2 of a number, using the conventation that log2(0)=0
double log2 (double x)
{
	if (x == 0) return 0;
	return log (x) / (log (2.0) );
}

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

	// create the normalized (sum of elements is one) histogram for image
	vector<double> histogram (256, 0.0);
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			histogram[image.Pixel (x, y)] += 1.0;
		}
	}

	// calculate and print the entropy of the histogram
	double entropy = 0.0;
	//start lab10-part1 code

	for (int x = 0; x < 256; x++){
		histogram[x] = histogram[x]/(image.Width ()*image.Height ()) ;
	}
	for (int x = 0; x < 256; x++){
		entropy= entropy + (histogram[x]*log2(histogram[x]));
	}
	entropy= 0-entropy;
	//end lab10-part1 code
	cout << "Entropy = " << entropy << endl;
	double bits = entropy*image.Height ()*image.Width ();
	cout << setprecision(10);
	cout << "total number of bits = " << bits << endl;

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
