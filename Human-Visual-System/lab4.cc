/*===
lab4-skeleton.cc

Abstract: Skeleton for Lab 4
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
		if (argc < 4) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	
	Image image;
	image.Resize (512, 512);
	Image imageH;
	image.Resize (512, 512);
	/*===
	
	Insert Lab 4 code here

	===*/

	int color, colval;
	int x,y,i;
	
	for(y=0; y<512; y++){
		for(x=0; x<16; x++){
			color = x;
			if(color == 0)
				colval= 0;
			else{
				colval= (16*color) -1;}
			for(i=0; i<32; i++ ){
				image.Pixel(x*32+i,y) = colval;}
				i= 0;
		}
	}
	image.SavePng ("day-name-test.png");
	for(x=0; x<512; x++){
		for(y=0; y<16; y++){
			color = y;
			if(color == 0)
				colval= 0;
			else{
				colval= (16*color) -1;}
			for(i=0; i<32; i++ ){
				image.Pixel(x,y*32+i) = colval;}
				i= 0;
		}
	}
	
	image.SavePng ("horizontal-test.png");
	image.Resize(1024,512);
	const double pi = 3.14159265358979323846;
	for (x = 0.0; x < 1024.0; x++) {   
        for (y = 0.0; y < 512.0; y++) {

            double fr = (pi/2.0)*(x/2024.0);    
            image.Pixel(x,y) = (127.5-y/4.0)*(sin(fr*x+pi/2)+1.0)/2.0;  


        }
    }
	image.SavePng ("grating.png");
	image.Resize(1024,512);
	for (y = 0; y < 512; y++) {
		for (x = 0; x < 512; x++) { 
			image.Pixel(x,y)=128;

		}
	}  
	for (y = 0; y < 512; y++) {
		for (x = 512; x < 1024; x++) { 
			image.Pixel(x,y)=255;

		}
	}  
	double X = 0.0;
	for (y = 224; y < 288; y++) {
		for (x = 224; x < 288; x++) { 
			image.Pixel(x,y)=X;

		}
	}  
	for (y = 224; y < 288; y++) {
		for (x = 735; x < 799; x++) { 
			image.Pixel(x,y)=X;
		}
	} 
	 image.SavePng ("boxes.png");
	image.Resize(512,512);
	double I = 255;
	double F = 254;
   
	for (y = 0; y < 512; y++) {
		for (x = 0; x < 512; x++) { 
			image.Pixel(x,y)=I;

		}
	}  	
	for (y = 252; y < 259; y++) {
		for (x = 252; x < 259; x++) { 
			image.Pixel(x,y)=F;

		}
	} 
	 image.SavePng ("IvsF.png");
	return 0;
}
