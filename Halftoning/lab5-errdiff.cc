/*===
lab5-errdiff-skeleton.cc

Abstract: Skeleton code for an error diffusion scheme
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// load the input and error image
	Image image;
	image.Resize (512,512);
	Image input;
	input.Resize(image.Width(), image.Height());
	Image error;
	error.Resize(image.Width(), image.Height());
	Image tempimage;
	tempimage.Resize(image.Width(), image.Height());
	Image tempinput;
	tempinput.Resize(image.Width(), image.Height());
	//clear error image
	for (int y = 0; y < image.Height (); y++)
	{
		for (int x = 0; x < image.Width (); x++)
		{
			image.Pixel(x,y)=57;
			input.Pixel(x,y)=57;
		}
	}
	for (int y = 0; y < image.Height (); y++)
	{
		for (int x = 0; x < image.Width (); x++)
		{
			error.Pixel(x,y)=0;
		}
	}
	// dither the image 
	for (int y = 0; y < image.Height (); y++)
	{
		for (int x = 0; x < image.Width (); x++)
		{
			//unquantized iamge
			double unquantized = image.Pixel(x,y);
			//quantize the image and store in input image
			double quantized = (unquantized<128) ? 0:255;
			image.Pixel(x,y) = quantized;
			//error image gets difference between quantized 
			error.Pixel(x,y) = unquantized-quantized;

			if(x<image.Width()-1){ //check pixel X is max width
				image.Pixel(x+1,y) = image.Pixel(x+1,y)+(7.0/16.0)*error.Pixel(x,y);
			}
			if((y<image.Height()-1) && x>0){ //check pixel X is not on left edge or top edge of image
				image.Pixel(x-1,y+1) = image.Pixel(x-1,y+1)+(3.0/16.0)*error.Pixel(x,y);
			}
			if(y<image.Height()-1){ //check pixel X is not on top edge of image
				image.Pixel(x,y+1) = image.Pixel(x,y+1)+(5.0/16.0)*error.Pixel(x,y);
			}
			if((x<image.Width()-1) && (y<image.Height()-1)){ //check pixel X is not on top edge or right edge of image
				image.Pixel(x+1,y+1) = image.Pixel(x+1,y+1)+(1.0/16.0)*error.Pixel(x,y);
			}
		}
	}
	double MSE=0.0;
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			double in = input.Pixel(x,y)-image.Pixel(x,y);
			MSE= MSE + (in*in);
		}
	}
	MSE=MSE/(image.Width()*image.Height());
	cout<< "MSE="<< MSE<< endl;
	// save the image
	image.SavePng ("errdiff.png");
	
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			if(x<image.Width()-1){ //check pixel X is max width
				tempinput.Pixel(x,y) += input.Pixel(x+1,y);
			}
			if(y<image.Height()-1){ //check pixel X is not on top edge of image
				tempinput.Pixel(x,y) += input.Pixel(x,y+1);
			}
			if((x<image.Width()-1) && (y<image.Height()-1)){ //check pixel X is not on top edge or right edge of image
				tempinput.Pixel(x,y) += input.Pixel(x+1,y+1);
			}
			tempinput.Pixel(x,y)+= input.Pixel(x,y);
		}
	}
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			if(x<image.Width()-1){ //check pixel X is max width
				tempimage.Pixel(x,y) = tempimage.Pixel(x,y) + image.Pixel(x+1,y);
			}
			if(y<image.Height()-1){ //check pixel X is not on top edge of image
				tempimage.Pixel(x,y) = tempimage.Pixel(x,y)+image.Pixel(x,y+1);
			}
			if((x<image.Width()-1) && (y<image.Height()-1)){ //check pixel X is not on top edge or right edge of image
				tempimage.Pixel(x,y) = tempimage.Pixel(x,y)+image.Pixel(x+1,y+1);
			}
			
			tempimage.Pixel(x,y) = (tempimage.Pixel(x,y) +image.Pixel(x,y));
		}
	}
	double WMSE= 0.0;
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			double in = tempimage.Pixel(x,y)- tempinput.Pixel(x,y);
			WMSE= WMSE + (in*in)/16;
		}
	}

	WMSE=WMSE/(image.Width()*image.Height());
	cout<< "WMSE="<< WMSE<< endl;
		

	return 0;
}
