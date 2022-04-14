/*===
lab3-skeleton.cc

Abstract: Skeleton for Lab 3 parts (a), (b), and (c)
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "imagefft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness [for parts (a) and (b) -- this needs to be changed for (c)]
	if (argc < 3) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	// read the top row and left column that will be used [remove this for part (c)]
	int topLeftRow = atoi(argv[3]);
	int topLeftColumn = atoi(argv[4]);

	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);
	
	// initialize the output interpolated image
	ComplexFFTImage outputImage;
	outputImage.Resize (512, 512);
	
	/*===

	Insert Lab 3 code here
	
	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image, 
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()
	
	===*/
	double mag =4.0;
	double y = topLeftRow;
	double x = topLeftColumn;
	double i,j= 0;
	double cR = 3;
	double cH = 3;
	Complex z;
	// for (y = topLeftColumn; y <= topLeftColumn+127; y++){ // traverse input image
	// 	for (x = topLeftRow; x <= topLeftRow+127; x++) //traverse down
	// 	{	
	// 		z = inputImage.Pixel(x,y);
	// 		i = mag*(x-topLeftRow);
	// 		j = mag*(y-topLeftColumn);
	// 		for( cH = 3; cH >=0; cH--){
	// 			for( cR = 3; cR >=0; cR--){
	// 				outputImage.Pixel(i,j)= z;
	// 				i = i + 1;
	// 			}i = mag*(x-topLeftRow);
				
	// 			j = j +1;
	// 		}
			
	// 	}
	// }
	for (y = topLeftRow; y <= topLeftRow+127; y++) //traverse down
		for (x = topLeftColumn; x <= topLeftColumn+127; x++){ // traverse input image
		
		{	
			z = inputImage.Pixel(x,y);
			j = mag*(y-topLeftRow);
			i = mag*(x-topLeftColumn);
			for( cH = 3; cH >=0; cH--){
				for( cR = 3; cR >=0; cR--){
					outputImage.Pixel(i,j)= z;
					i = i + 1;
				}i = mag*(x-topLeftColumn);
				
				j = j +1;
			}
			
		}
	}
	// save the image
	outputImage.SavePng (argv[2]);

	return 0;
}
