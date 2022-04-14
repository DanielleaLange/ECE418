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
	if (argc < 5) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png out.png out.png [flag] [factor]" << endl;
		return 1;
	}
	//load the subsampling rate and filter_flag
    int filter_flag = atoi(argv[5]);
	int F = atoi(argv[6]);
	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);
	ComplexFFTImage tempinputImage;
	tempinputImage.Resize(512,512);
	// initialize the output interpolated image
	ComplexFFTImage smallImage;
	smallImage.Resize(inputImage.Width()/F, inputImage.Height()/F);
	ComplexFFTImage restoredImage;
	restoredImage.Resize(inputImage.Width(), inputImage.Height());
	ComplexFFTImage prerestoredImage;
	prerestoredImage.Resize(inputImage.Width()/(F), inputImage.Height()/(F));
	ComplexFFTImage differenceImage;
	differenceImage.Resize(inputImage.Width(), inputImage.Height());
	double MSE = 0;
	ComplexFFTImage small1Image;
	small1Image.Resize(inputImage.Width()/(F), inputImage.Height()/(F));
	ComplexFFTImage imsmall1Image;
	imsmall1Image.Resize(256,256);
//	outputImage.Resize (128, 128);
//	Complex Small[][];
	double i,j,Height,Width;
	Complex z;
	int x,y;
	for(y = 0; y < 512; y++){ // traverse input image
		for(x = 0; x < 512; x++){
			tempinputImage.Pixel(x,y)=inputImage.Pixel(x,y);
		}
	}
	/*===

	Insert Lab 3 code here
	
	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image, 
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()
	
	===*/
	
	// save the image
	//method A resize for the subsampling rate 
	if(F == 2){
		small1Image.Resize(256,256);
		imsmall1Image.Resize(256,256);
		smallImage.Resize(256,256);
	}
	if(F == 8){
		small1Image.Resize(64,64);
		imsmall1Image.Resize(64,64);
		smallImage.Resize(64,64);
	}
	if(filter_flag == 0){
		for(y = 0; y < 512/F; y++){ // traverse input image
			for(x = 0; x < 512/F; x++){
				z= inputImage.Pixel(x*F,y*F);
				small1Image.Pixel(x,y)=z;
		
			} 
		}
	} 
	x,y =0;
	
	//Anti-aliasing filter 
	if(filter_flag == 1 ){
		tempinputImage.FourierTransform ();
		int newWidth = floor(512/(F*2));  
		int newHeight = floor(512/(F*2));
		int NFwidth = 512 -  newWidth; 
		int NFheight= 512 -  newHeight;
		for (y=0; y < newHeight; y++){
			for (x=0; x < newWidth; x++){
				small1Image.Pixel(x,y) = tempinputImage.Pixel(x,y);
			}
		}
		for (y=0; y < newHeight; y++){
			for (x=NFwidth ; x < 512; x++){
				small1Image.Pixel(x-((newWidth*F*2)-(2*newWidth)),y) = tempinputImage.Pixel(x,y);

			}
		}

		for (y=NFheight; y < 512; y++){
			for (x=0; x < newWidth; x++){
				small1Image.Pixel(x,y-((newHeight*F*2)-(2*newHeight))) = tempinputImage.Pixel(x,y);
				
			}
		}
		for (y=NFheight; y < 512; y++){
			for (x=NFwidth; x < 512; x++){
				small1Image.Pixel(x-NFwidth+newWidth,(y-NFheight+newHeight)) = tempinputImage.Pixel(x,y);
				
			}
		}

	small1Image.InverseFourierTransform ();
	for (y=0; y < 512/F; y++){
		for (x=0; x < 512/F; x++){
			Complex temp (1,1);
			temp = small1Image.Pixel(x,y);
			double divider;
			divider = (F*F);
			temp = temp/divider;
			small1Image.Pixel(x,y)= temp;
			}
		}
	
	for (y=0; y < 512/F; y++){
		for (x=0; x < 512/F; x++){
			double temp;
			if(small1Image.Pixel(x,y).real()<=0.0)
				small1Image.Pixel(x,y) =0;
			if(small1Image.Pixel(x,y).real()>=255.0)
				small1Image.Pixel(x,y)= 255;

		}
	}
	}




	//take copy from each corner into small 2-D F
// }
	//interpolation
	int u,v;
	x = 0;
	 y = 0;
	 i,j= 0;
	Complex w;
	restoredImage.Resize(512,512);
	// uncompress the image
	for (y = 0; y < small1Image.Height(); y++){ // traverse the columns of the input image
		for (x = 0; x < small1Image.Width(); x++) // traverse the rows of the input image
		{
			z = small1Image.Pixel(x,y);
			restoredImage.Pixel(x*F,y*F)= z;
		}
	
	}
	// Zero order hold 
	for (i = 0; i < small1Image.Height(); i= i+F){
		for (j = 0; j < small1Image.Width(); j= j+F){
		
			for(int u=0; u<F;u++){
				for(int v=0; v<F;v++){
					restoredImage.Pixel(i+u,j+v)= restoredImage.Pixel(i,j);
		}
	}
	}
}
	double cH,cR = F;
for (y = 0; y < small1Image.Height(); y++){ // traverse input image's rows 
		for (x = 0; x < small1Image.Width(); x++)
		{	
			z = small1Image.Pixel(x,y);
			w = small1Image.Pixel(x+1,y);
			i = F*(x);
			j = F*(y);
			for(cH = F; cH >=0; cH--){
				restoredImage.Pixel(i,j)= ((cH/F)* z) + ((1.0-(cH/F)) * w);
				i = i + 1;
			}
		}
			
 	}
	 x = 0;
	 y = 0;
	 cR= 1;
	 cR=1;
for (y = 0; y < small1Image.Height(); y++){ // traverse input image's columns
	for (x = 0; x < small1Image.Width(); x++){	
		i = F*(x);
		j = F*(y);
		
		for( cR = 1; cR <=F; cR++){
			z = restoredImage.Pixel(i, j );
			w = restoredImage.Pixel(i, j+F);
			for(cH = 1; cH <=F-1; cH++){
				j = j + 1;
				restoredImage.Pixel(i,j)= ((1.0-(cH/F))* z) + ((cH/F) * w);
				
				} 
			j = F*(y);
			i = i+1;
		}

		}
			
	}

for (y = 0; y < differenceImage.Height(); y++){
	for (x = 0; x < differenceImage.Width(); x++){
			differenceImage.Pixel(x,y) = inputImage.Pixel(x,y)- restoredImage.Pixel(x,y);
			MSE= MSE + ( abs(differenceImage.Pixel(x,y)*abs(differenceImage.Pixel(x,y))));
		//	double k= differenceImage.Pixel(x,y).real();

	}
}
//find min and max
		double m =100.0;
		double M = 0.0;
		double orig = 0;
		Complex d (1,1);
		for(j=0; j<= differenceImage.Height()-1; j++){ //new row y
			for(i=0; i<=differenceImage.Width()-1; i++){//store contents of first row into array
				d = differenceImage.Pixel(i,j);
				orig = d.real();
				if (orig<m){ //m is the min
					m=orig;}
				if(orig>M){ //M is the max
					M=orig;}	
			} 
		} // scale the values
		for(j=0; j< differenceImage.Height()-1; j++){ //new row y
			for(i=0; i<differenceImage.Width()-1; i++){
					d = differenceImage.Pixel(i,j);
 					orig = d.real();
				if( orig<= 0){
					orig =((orig-m)*128.0/(-m));
					differenceImage.Pixel(i,j)= orig;
					}
				else{
					orig =((orig)*127.0/(M) +128);
					differenceImage.Pixel(i,j)= orig;

				}
			}
		}

//get final MSE and print the output
	MSE = MSE/(differenceImage.Height() * differenceImage.Width());
	cout<< "MSE="<< MSE<< endl;
//save all the images to output
small1Image.SavePng(argv[2]);
restoredImage.SavePng(argv[3]);
differenceImage.SavePng(argv[4]);


	return 0;
}
