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
	
	double mag =4.0;
	double y = topLeftRow;
	double x = topLeftColumn;
	double i,j= 0;
	Complex z,w;
// 	for (y = topLeftColumn; y <= topLeftColumn+127; y++){ // traverse input image
// 		for (x = topLeftRow; x <= topLeftRow+127; x++)
// 		{
// 			z = inputImage.Pixel(x,y);
// 			outputImage.Pixel(i,j)= z;
// 			i = i + 4;
// 		}
// 		i = 0;
// 	  	j = j + 4;
// 	}
// 	double cH,cR = 4;
// for (y = topLeftColumn; y <= topLeftColumn+126; y++){ // traverse input image
// 		for (x = topLeftRow; x <= topLeftRow+126; x++)
// 		{	
// 			z = inputImage.Pixel(x,y);
// 			w = inputImage.Pixel(x+1,y);
// 			i = mag*(x-topLeftRow);
// 			j = mag*(y-topLeftColumn);
// 			for(cH = 4; cH >=0; cH--){
// 				outputImage.Pixel(i,j)= ((cH/mag)* z) + ((1.0-(cH/mag)) * w);
// 				i = i + 1;
// 			}
// 		}
			
// 	}
// 	 x = topLeftRow;
// 	 y = topLeftColumn;
// for (y = topLeftColumn; y <= topLeftColumn+126; y++){
// 	for (x = topLeftRow; x <= topLeftRow+126; x++){
// 	 // traverse input image	
			
// 	//	z = inputImage.Pixel(x,y);
// 	//	w = inputImage.Pixel(x,y+4);
// 		i = mag*(x-topLeftRow);
// 		j = mag*(y-topLeftColumn);
		
// 		for( cR = 1; cR <=4; cR++){
// 			z = outputImage.Pixel(i, j );
// 			w = outputImage.Pixel(i, j+4);
// 			for(cH = 1; cH <=3; cH++){
// 				j = j + 1;
// 				outputImage.Pixel(i,j)= ((1.0-(cH/mag))* z) + ((cH/mag) * w);
				
// 				} 
// 			j = mag*(y-topLeftColumn);
// 			i = i+1;
// 		}
// 		}
			
// 	}
	for (y = topLeftRow; y < topLeftRow+128; y++){
		for (x = topLeftColumn; x < topLeftColumn+128; x++)
	{	
			z = inputImage.Pixel(x,y);
			outputImage.Pixel(i,j)= z;
			i = i + 4;
		}
		i = 0;
	  	j = j + 4;
	}
	int U = mag;
	for (i = topLeftColumn; i < topLeftColumn+128; i= i+U){
		for (j = topLeftRow; j < topLeftRow+128; j= j+U){
		
			for(int u=0; u<U;u++){
				for(int v=0; v<U;v++){
					outputImage.Pixel(i+u,j+v)= outputImage.Pixel(i,j);
		}
	}
	}
}
		double cH,cR = 4;
	for (y = topLeftRow; y < topLeftRow+128; y++){
		for (x = topLeftColumn; x < topLeftColumn+128; x++)
{	
			z = inputImage.Pixel(x,y);
			w = inputImage.Pixel(x+1,y);
			j = mag*(y-topLeftRow);
			i = mag*(x-topLeftColumn);
			for(cH = 4; cH >=0; cH--){
				outputImage.Pixel(i,j)= ((cH/mag)* z) + ((1.0-(cH/mag)) * w);
				i = i + 1;
			}
		}
			
 	}
	 y = topLeftRow;
	 x = topLeftColumn;
	for (y = topLeftRow; y <= topLeftRow+128; y++){
		for (x = topLeftColumn; x <= topLeftColumn+128; x++)
{		 // traverse input image	
			
	//	z = inputImage.Pixel(x,y);
	//	w = inputImage.Pixel(x,y+4);
		j = mag*(y-topLeftRow);
		i = mag*(x-topLeftColumn);
		
		for( cR = 1; cR <=4; cR++){
			z = outputImage.Pixel(i, j );
			w = outputImage.Pixel(i, j+4);
			for(cH = 1; cH <=3; cH++){
				j = j + 1;
				outputImage.Pixel(i,j)= ((1.0-(cH/mag))* z) + ((cH/mag) * w);
				
				} 
			j = mag*(y-topLeftRow);
			i = i+1;
		}
		}
			
	}

	/*===

	Insert Lab 3 code here
	
	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image, 
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()
	
	===*/
	//sparsly fill the 512 by 512 image with the smaller image



	// interpolate linearly along each row

	//interpolate linearly along each column


	// save the image
	outputImage.SavePng (argv[2]);

	return 0;
}
