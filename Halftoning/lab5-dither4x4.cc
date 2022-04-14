/*===
lab5-dither4x4-skeleton.cc

Abstract: Skeleton code for a 4x4 dithering scheme
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
	// the dithering matrix (to access the pixel at column x, row y, the
	// index in this structure is [x][y]
	static short ditherMatrix[4][4] = { //transpose of the dithering matrix 
		{8,   200, 56,  248},
		{136, 72,  184, 120},
		{40,  232, 24,  216},
		{168, 104, 152, 88}};

	// dither the image
	for (int x = 0; x < image.Width()-1; x+=4)
	{
		for (int y = 0; y < image.Height()-1; y+=4)//could also inc x and y by 4 each time
		{
			for(int u=0;u<4; u++){
				for(int v=0;v<4; v++){
					image.Pixel(x+u,y+v)= ((image.Pixel(x+u,y+v)<ditherMatrix[u][v]) ? 0:255);
				}
			}
			/*===
	
			Insert Lab 5 4x4 dithering code here
	
			===*/	
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
	image.SavePng ("eiffeltower4x4.png");

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
			double in = tempinput.Pixel(x,y)- tempimage.Pixel(x,y);
			WMSE= WMSE + (in*in);
		}
	}

	WMSE=WMSE/(image.Width()*image.Height());
	cout<< "WMSE="<< WMSE<< endl;
		
	return 0;
}
