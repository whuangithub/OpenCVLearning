#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*
The idea of mask operation is that we recalculate each pixel's value in an image according to a mask matrix (kernel).
This mask holds values that will adjust how much influence neighboring pixels (and the current pixel) have on the new pixel value.
From a mathematical point of view we make a weighted average, with our specified values.
example
I(i,j)= 5∗I(i,j)−[I(i−1,j)+I(i+1,j)+I(i,j−1)+I(i,j+1)]
⟺
I(i,j)∗M where
M=
i∖j	|	−1		0		+1
----+--------------
 −1	|	 0		−1	 0
	0	|	−1	  5		−1
 +1	|  0	 −1	   0
*/

// why pointer?
static void help(char* progName)
{
		cout << endl
				<<  "This program shows how to filter images with mask: the write it yourself and the"
				<< "filter2d way. " << endl
				<<  "Usage:"                                                                        << endl
				<< progName << " [image_path -- default lena.jpg] [G -- grayscale] "        << endl << endl;
}

//declare fucntion Sharpen
void Sharpen(const Mat& myImage,Mat& Result);

// argc: (argument count) number of strings pointed by argv
// argv: (argument vector) array of  pointer
int main( int argc, char* argv[])
{
		help(argv[0]);
		// “？ ：” condition operator
		// if argc >= 2 filename = argv[1] (pointer to a char)(array of char)
		// else filename = "lena.jpg"
		// filename is a pointer to a char <==> a array of char
		// so filename = "lena.jpg" / *filename = l (the first character)
		const char* filename = argc >=2 ? argv[1] : "lena.jpg";

		Mat src, dst0, dst1;

		// read image gray/color
		if (argc >= 3 && !strcmp("G", argv[2]))
				src = imread( samples::findFile( filename ), IMREAD_GRAYSCALE);
		else
				src = imread( samples::findFile( filename ), IMREAD_COLOR);

		if (src.empty())
		{
				cerr << "Can't open image ["  << filename << "]" << endl;
				return EXIT_FAILURE;
		}



		namedWindow("Input", WINDOW_AUTOSIZE);
		namedWindow("Output", WINDOW_AUTOSIZE);

		imshow( "Input", src );
		double t = (double)getTickCount();

		Sharpen( src, dst0 );

		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Hand written function time passed in seconds: " << t << endl;

		imshow( "Output", dst0 );
		waitKey();

	//*********** [filter2D ]**************

	//![kern]
		Mat kernel = (Mat_<char>(3,3) <<  0, -1,  0,
																	 -1,  5, -1,
																		0, -1,  0);
	//![kern]

		t = (double)getTickCount();

	//![filter2D]
		filter2D( src, dst1, src.depth(), kernel );
	//![filter2D]
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Built-in filter2D time passed in seconds:     " << t << endl;

		imshow( "Output", dst1 );

		waitKey();
		return EXIT_SUCCESS;
}
//************* [basic_method] *****************
void Sharpen(const Mat& myImage,Mat& Result)
{
	//! [8_bit]
		//CV_Assert: Checks a condition at runtime and throws exception if it fails
		CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
	//! [8_bit]

	//! [create_channels]
		const int nChannels = myImage.channels();
		Result.create(myImage.size(),myImage.type());
	//! [create_channels]

	//! [basic_method_loop]
		for(int j = 1 ; j < myImage.rows-1; ++j)
		{
				// use pointer to denote different rows (array)
				const uchar* previous = myImage.ptr<uchar>(j - 1);
				const uchar* current  = myImage.ptr<uchar>(j    );
				const uchar* next     = myImage.ptr<uchar>(j + 1);

				// output: pointer in the Result matrix for exporting
				uchar* output = Result.ptr<uchar>(j);

				// calculate based on the mask matrix
				for(int i= nChannels;i < nChannels*(myImage.cols-1); ++i)
				{
						*output++ = saturate_cast<uchar>(5*current[i]
												 -current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
				}
		}
	//! [basic_method_loop]

	//! [borders]
		Result.row(0).setTo(Scalar(0));
		Result.row(Result.rows-1).setTo(Scalar(0));
		Result.col(0).setTo(Scalar(0));
		Result.col(Result.cols-1).setTo(Scalar(0));
	//! [borders]
}
//! [basic_method]
