#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

static void help()
{
		cout
				<< "\n--------------------------------------------------------------------------" << endl
				<< "This program shows how to scan image objects in OpenCV (cv::Mat). As use case"
				<< " we take an input image and divide the native color palette (255) with the "  << endl
				<< "input. Shows C operator[] method, iterators and at function for on-the-fly item address calculation."<< endl
				<< "Usage:"                                                                       << endl
				<< "./how_to_scan_images <imageNameToUse> <divideWith> [G]"                       << endl
				<< "if you add a G parameter the image is processed in gray scale"                << endl
				<< "--------------------------------------------------------------------------"   << endl
				<< endl;
}

// declare 3 functions
Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);

int main( int argc, char* argv[])
{
		help();
		if (argc < 3)
		{
				cout << "Not enough parameters" << endl;
				return -1;
		}

		Mat I, J;
		if( argc == 4 && !strcmp(argv[3],"G") )
				I = imread(argv[1], IMREAD_GRAYSCALE);
		else
				I = imread(argv[1], IMREAD_COLOR);

		if (I.empty())
		{
				cout << "The image" << argv[1] << " could not be loaded." << endl;
				return -1;
		}

		// ****************lookup table****************

		//! [dividewith]
		// calculating the lookup table
		// lookup table is used to avoid pixel-by-pixel calculation
		int divideWith = 0; // convert our input string to number - C++ style
		// stringstream: to divide a string
		stringstream s;
		// argv: argument vector
		// here argv = "./how_to_scan_images <imageNameToUse> <divideWith> [G]"
		// argv[2] is <divideWith>
		// see: http://crasseux.com/books/ctutorial/argc-and-argv.html
		s << argv[2];
		s >> divideWith;
		if (!s || !divideWith)
		{
				cout << "Invalid number entered for dividing. " << endl;
				return -1;
		}

		// unsigned char
		uchar table[256];
		for (int i = 0; i < 256; ++i)
			 table[i] = (uchar)(divideWith * (i/divideWith));
		//! [dividewith]

		//********************time for 4 methods***********************
		//******** 1 **********

		const int times = 100;
		double t;

		t = (double)getTickCount();

		for (int i = 0; i < times; ++i)
		{
				cv::Mat clone_i = I.clone();
				J = ScanImageAndReduceC(clone_i, table);
		}

		t = 1000*((double)getTickCount() - t)/getTickFrequency();
		t /= times;

		cout << "Time of reducing with the C operator [] (averaged for "
				 << times << " runs): " << t << " milliseconds."<< endl;

		//******** 2 **********

		t = (double)getTickCount();

		for (int i = 0; i < times; ++i)
		{
				cv::Mat clone_i = I.clone();
				J = ScanImageAndReduceIterator(clone_i, table);
		}

		t = 1000*((double)getTickCount() - t)/getTickFrequency();
		t /= times;

		cout << "Time of reducing with the iterator (averaged for "
				<< times << " runs): " << t << " milliseconds."<< endl;

		//******** 3 **********

		t = (double)getTickCount();

		for (int i = 0; i < times; ++i)
		{
				cv::Mat clone_i = I.clone();
				ScanImageAndReduceRandomAccess(clone_i, table);
		}

		t = 1000*((double)getTickCount() - t)/getTickFrequency();
		t /= times;

		cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
				<< times << " runs): " << t << " milliseconds."<< endl;

		//! [table-init]
		Mat lookUpTable(1, 256, CV_8U);
		uchar* p = lookUpTable.ptr();
		for( int i = 0; i < 256; ++i)
				p[i] = table[i];
		//! [table-init]

		//******** 4 **********

		t = (double)getTickCount();

		for (int i = 0; i < times; ++i)
				//! [table-use]
				// LUT： built-in function Performs a look-up table transform of an array.
				LUT(I, lookUpTable, J);
				//! [table-use]

		t = 1000*((double)getTickCount() - t)/getTickFrequency();
		t /= times;

		cout << "Time of reducing with the LUT function (averaged for "
				<< times << " runs): " << t << " milliseconds."<< endl;
		return 0;
}

//! [scan-c]
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
		// accept only char type matrices
		// CV_Accesss: Checks a condition at runtime and throws exception if it fails.
		CV_Assert(I.depth() == CV_8U);

		int channels = I.channels();

		int nRows = I.rows;
		int nCols = I.cols * channels;

		// use the cv::Mat::isContinuous() function to ask the matrix
		// if everything is in a single place following one after another
		// which can speed up the calculation
		if (I.isContinuous())
		{
				nCols *= nRows;
				nRows = 1;
		}

		// acquire a pointer to the start of each row and go through it until it ends
		int i,j;
		// declare a pointer p to uchar variable
		uchar* p;
		for( i = 0; i < nRows; ++i)
		{
				// Mat::ptr : Returns a pointer to the specified matrix row.
				p = I.ptr<uchar>(i);
				for ( j = 0; j < nCols; ++j)
				{
						// ??? is p a pointer???
						p[j] = table[p[j]];
				}
		}
		return I;
}
//! [scan-c]

//! [scan-iterator]
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
		// accept only char type matrices
		CV_Assert(I.depth() == CV_8U);


		// begin: Returns the matrix iterator and sets it to the first matrix element.

		const int channels = I.channels();
		switch(channels)
		{
		case 1:
				{
						// it, end: pointer
						MatIterator_<uchar> it, end;
						for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
								// *it: the value at the address
								// check the lookup table and modify the value at the address
								*it = table[*it];
						break;
				}
		case 3:
				{
						MatIterator_<Vec3b> it, end;
						for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
						{
								(*it)[0] = table[(*it)[0]];
								(*it)[1] = table[(*it)[1]];
								(*it)[2] = table[(*it)[2]];
						}
				}
		}

		return I;
}
//! [scan-iterator]

//! [scan-random]
// not recommended
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
		// accept only char type matrices
		CV_Assert(I.depth() == CV_8U);

		const int channels = I.channels();
		switch(channels)
		{
		case 1:
				{
						for( int i = 0; i < I.rows; ++i)
								for( int j = 0; j < I.cols; ++j )
										// at: Returns a reference to the specified array element.
										I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
						break;
				}
		case 3:
				{
				 Mat_<Vec3b> _I = I;

				 for( int i = 0; i < I.rows; ++i)
						for( int j = 0; j < I.cols; ++j )
							 {
									 _I(i,j)[0] = table[_I(i,j)[0]];
									 _I(i,j)[1] = table[_I(i,j)[1]];
									 _I(i,j)[2] = table[_I(i,j)[2]];
						}
				 I = _I;
				 break;
				}
		}

		return I;
}
//! [scan-random]
