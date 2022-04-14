/*===
lab2c-skeleton.cc

Abstract: Skeleton for Lab 2 part (c)
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
	if (argc != 4) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png frequency" << endl;
		return 1;
	}
	double frequency = atof (argv[3]);
	if (frequency < 0 || frequency > 0.5)
	{
		cerr << "Cutoff frequency must be in [0,0.5]" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);
	
	/*===
	
	Insert Lab 2 code here:
	
	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation
	3. Compute the inverse 2D FFT of the image
	4. Re-normalize the image
	
	===*/
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
	

	int newWidth = floor(Width * frequency);  // 128 if width is 512
	int newHeight = floor(Height * frequency);
	int NFwidth = Width -  newWidth; 
	int NFheight= Height -  newHeight;
	int x,y;
	for (y=0; y < Height; y++){
		for (x=0; x < Width; x++){
			if(x<newWidth && y<newHeight)
				continue;
			if(x<newWidth && y>=NFheight)
				continue;
			if(x>=NFwidth && y>=NFheight)
				continue;
			if(x>=NFwidth && y<newHeight)
				continue;
			image.Pixel(x,y) = 0;
}
}
	//new row y
	// for(int y = 0; y < Height; y++){
	// 	for(int x = newWidth; x < NFwidth; x++){
	// 		image.Pixel(x,y) = 0;
	// 		}
	// } 
	// //y = newHeight-1;
	// for(int y = newHeight; y < NFheight; y++){
	// 	for(int x=0; x< Width; x++){ //new row y
	// 		image.Pixel(x,y) = 0;}
	// }

	for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
			z = image.Pixel(i,j);
			myVector[i] = z ;
		}
		FFT::InverseTransform (myVector); //comput fft of row
			for(q=0; q<= Width-1; q++){ //copy data back into row
				z = myVector[q];
				image.Pixel(q,j) = z;
	} 
	}
	 
	//myVector.resize (Height);
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
	} 

	double m = image.Pixel(0,0).real();
	double M = image.Pixel(0,0).real();
	double orig = 0;
	Complex d (1,1);
	for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
			d = image.Pixel(i,j);
			orig = d.real();
			if (orig<m){
				m=orig;}
			if(orig>M){
				M=orig;}	
		} 
	}

	for(j=0; j<= Height-1; j++){ //new row y
		for(i=0; i<=Width-1; i++){//store contents of first row into array
	//image.Pixel(i,j).real() = (image.Pixel(i,j).real()-m)*255.0/(M-m);
 			d = image.Pixel(i,j);
 			orig = d.real();
			orig =((orig-m)*255.0/(M-m));
			image.Pixel(i,j)= orig;
		}
	} 


	// save the image

	image.SavePng (argv[2]);
	
	return 0;
}
