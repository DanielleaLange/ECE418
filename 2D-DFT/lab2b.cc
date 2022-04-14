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
	
	===*/
	
	// save the image
	double Height = image.Height();
	double Width = image.Width();
	vector<Complex> myVector;
	double i,j,q =0;
	Complex z;
	Complex w;

	
	myVector.resize (Width);
	for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
			z = image.Pixel(i,j);
			myVector[i] = z ;
		} 
		i = 0;
		
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
		
		FFT::Transform (myVector); //comput fft of row
			for(q=0; q<= Height-1; q++){ //copy data back into row
				z = myVector[q];
				image.Pixel(j,q) = z;
	}
 	} i,j,q =0;

	j=0;
	i=0;
	q=0;
for(j=0; j<= Height-1; j++){ //new column
	for(i=0; i<=Width-1; i++){//store contents of first column into array
			
		image.Pixel(i,j)= image.Pixel(i,j) / abs(image.Pixel(i,j)); //set x to the magnitude of q
			
		}
} 
i,j,q =0;

	for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
			z = image.Pixel(i,j);
			myVector[i] = z ;
		} 
		i = 0;
		
		FFT::InverseTransform (myVector); //comput fft of row
			for(q=0; q<= Width-1; q++){ //copy data back into row
				z = myVector[q];
				image.Pixel(q,j) = z;
	} 
	}
	i,j,q =0; 
myVector.resize (Height);
for(j=0; j<= Width-1; j++){ //new column y
		for(i=0; i<=Height-1; i++){//store contents of first column into array
			z = image.Pixel(j,i);
			myVector[i] = z ;
		} 
		i = 0;
	
		FFT::InverseTransform (myVector); //compute fft of column
			for(q=0; q<= Height-1; q++){ //copy data back into column
				z = myVector[q];
				image.Pixel(j,q) = z;
						
	} 
 	} i,j,q =0;
// //scale the values of the real part 
// //of the inverse FFT to fill the range [0, 255]
// //modified_value = (initial_value - m)*255/(M-m)


double m = image.Pixel(0,0).real();
double M = image.Pixel(0,0).real();
double x = 0;
Complex d (1,1);
	for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
			d = image.Pixel(i,j);
			x = d.real();
			if (x<m){
				m=x;}
			if(x>M){
				M=x;}
		
		} 
	}

	for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
//image.Pixel(i,j).real() = (image.Pixel(i,j).real()-m)*255.0/(M-m);
 			d = image.Pixel(i,j);
 			x = d.real();
			x =((x-m)*255.0/(M-m));
			image.Pixel(i,j)= x;
		}
	} 

	image.SavePng (argv[2]);
	
	return 0;
}
