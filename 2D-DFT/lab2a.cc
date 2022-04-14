/*===
lab2ab-skeleton.cc

Abstract: Skeleton for Lab 2 parts (a) and (b).
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
#include "fft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness
	if (argc != 3) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);

	
	/*===
	
	Insert Lab 2 code here:
	
	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation(s)
	3. Compute the inverse 2D FFT of the image
	4. For parts (b) and (c), re-normalize the image
	//Compute the 2D FFT of the image

	// first create temporary vector<Complex> 
	//and resize it to the size of the image's width
	//Then, row by row, copy the row's contents to the vector<Complex>
	//perform the DFT as shown above
	//copy the data back to the row it came from
	//do the same thing to each column

	===*/
	
	// save the image
	int Height = image.Height();
	int Width = image.Width();
	vector<Complex> myVector;
	int i,j,q =0;

	Complex z;
	myVector.resize (Width);
	for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
			z = image.Pixel(i,j);
			myVector[i] = z ;
		} 
		i = 0;
		z = 0;
		FFT::Transform (myVector); //comput fft of row
			for(q=0; q<= Width-1; q++){ //copy data back into row
				z = myVector[q];
				image.Pixel(q,j) = z;
	}
	}
	i,j,q =0; 
myVector.resize (Height);
for(j=0; j<= Width-1; j++){ //new row y
		for(i=0; i<=Height-1; i++){//store contents of first row into array
			z = image.Pixel(j,i);
			myVector[i] = z ;
		} 
		i = 0;
		z = 0;
		FFT::Transform (myVector); //comput fft of row
			for(q=0; q<= Height-1; q++){ //copy data back into row
				z = myVector[q];
				image.Pixel(j,q) = z;
	}
	}
//Perform frequency domain operations
//remove the phase of each complex frequency sample
//but preserve the magnitude
	j=0;
	i=0;
	q=0;
for(j=0; j<= Height-1; j++){ //new column
		for(i=0; i<=Width-1; i++){//store contents of first column into array
			Complex q = image.Pixel(i,j);
			Complex x = abs(q); //set x to the magnitude of q
			image.Pixel(i,j) = x;
		}
}
i,j,q =0;

for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
			z = image.Pixel(i,j);
			myVector[i] = z ;
		} 
		i = 0;
		z = 0;
		FFT::InverseTransform (myVector); //comput fft of row
			for(q=0; q<= Width-1; q++){ //copy data back into row
				z = myVector[q];
				image.Pixel(q,j) = z;
	}
	}
	i,j,q =0; 
myVector.resize (Height);
for(j=0; j<= Width-1; j++){ //new row y
		for(i=0; i<=Height-1; i++){//store contents of first row into array
			z = image.Pixel(j,i);
			myVector[i] = z ;
		} 
		i = 0;
		z = 0;
		q=0; 
		FFT::InverseTransform (myVector); //comput fft of row
			for(q=0; q<= Height-1; q++){ //copy data back into row
				z = myVector[q];
				image.Pixel(j,q) = z;
	}
	}

	image.SavePng (argv[2]);
	
	return 0;
}
