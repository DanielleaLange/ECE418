/*===
lab5-dither1x1.cc

Abstract: Implementation of a 1x1 dithering scheme
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// load the input image
	Image image;
	image.LoadPng ("eiffeltower.png");
	Image input;
	input.LoadPng ("eiffeltower.png");
	Image tempimage;
	tempimage.Resize(image.Width(), image.Height());
	Image tempinput;
	tempinput.Resize(image.Width(), image.Height());
	// do 1x1 dithering
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			int& value = image.Pixel (x, y);
			value = (value < 128) ? 0 : 255;
		}
	}
	double MSE=0.0;
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			double in = image.Pixel(x,y)- input.Pixel(x,y);
			MSE= MSE + (in*in);
		}
	}

	MSE=MSE/(image.Width()*image.Height());
	cout<< "MSE="<< MSE<< endl;
	image.SavePng ("eiffeltower1x1.png");

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
				tempimage.Pixel(x,y) += image.Pixel(x+1,y);
			}
			if(y<image.Height()-1){ //check pixel X is not on top edge of image
				tempimage.Pixel(x,y) += image.Pixel(x,y+1);
			}
			if((x<image.Width()-1) && (y<image.Height()-1)){ //check pixel X is not on top edge or right edge of image
				tempimage.Pixel(x,y) += image.Pixel(x+1,y+1);
			}
			tempimage.Pixel(x,y)+= image.Pixel(x,y);
		}
	}
	double WMSE= 0.0;
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			double in = tempimage.Pixel(x,y)- tempinput.Pixel(x,y);
			WMSE= WMSE + (in*in);
		}
	}

	WMSE=WMSE/(image.Width()*image.Height());
	cout<< "WMSE="<< WMSE<< endl;
		
		
	

	return 0;
}
