// The two authors of this tutorial have different code styles.
// Interesting

// https://docs.opencv.org/master/d8/d01/tutorial_discrete_fourier_transform.html

// Fourier Transform
// transform an image from its spatial domain to its frequency domain

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

static void help(char ** argv)
{
		cout << endl
				<<  "This program demonstrated the use of the discrete Fourier transform (DFT). " << endl
				<<  "The dft of an image is taken and it's power spectrum is displayed."  << endl << endl
				<<  "Usage:"                                                                      << endl
				<< argv[0] << " [image_name -- default lena.jpg]" << endl << endl;
}

int main(int argc, char ** argv)
{
		help(argv);

		const char* filename = argc >=2 ? argv[1] : "lena.jpg";

		Mat I = imread( samples::findFile( filename ), IMREAD_GRAYSCALE);
		// I.empty() returns true / false
		if( I.empty()){
				cout << "Error opening image" << endl;
				return EXIT_FAILURE;
		}

//The performance of a DFT is dependent of the image size.
//It tends to be the fastest for image sizes that are multiple of the numbers two, three and five.
//Therefore, to achieve maximal performance it is generally a good idea to pad border values to the image to get a size with such traits.
//The getOptimalDFTSize() returns this optimal size
// and we can use the copyMakeBorder() function to expand the borders of an image (the appended pixels are initialized with zero).

//TL DR: expand the borders to accelerate the computation

//! [expand]
		Mat padded;                            //expand input image to optimal size
		int m = getOptimalDFTSize( I.rows );
		int n = getOptimalDFTSize( I.cols ); // on the border add zero values
		//             src  dst   top   botom   left   right
		copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
//! [expand]

//! [complex_and_real]
		// fesquency domain: float
		// complex & real 2 parts
		Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
		Mat complexI;
		merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
//! [complex_and_real]

//! [dft]
		// Discrete Fourier transform
		dft(complexI, complexI);            // this way the result may fit in the source matrix
//! [dft]

		// compute the magnitude and switch to logarithmic scale
		// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
//! [magnitude]
		split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		// save the magnitude (norm) to planes[0]
		magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
		Mat magI = planes[0];
//! [magnitude]

//! [log]
		magI += Scalar::all(1);                    // switch to logarithmic scale
		log(magI, magI);
//! [log]

//! [crop_rearrange]
		// crop the spectrum, if it has an odd number of rows or columns
		// bitwise and with -2
		// There are three steps necessary to convert a negative decimal integer to two’s complement form:
		// 1. Start with the positive binary value, expanded to fill the number of bits you will be storing the number into.
		// 0000000000010
		// 2. Complement/flip all of the bits. This means all of the 1s become 0s and all of the 0s become 1s
		// 1111111111101
		// 3. Add one to the flipped bits.
		// 1111111111110

		// -1 twice from 0000000000000

		magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

		// rearrange the quadrants of Fourier image  so that the origin is at the image center
		int cx = magI.cols/2;
		int cy = magI.rows/2;

		Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
		Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
		Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
		Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

		Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
		q0.copyTo(tmp);
		q3.copyTo(q0);
		tmp.copyTo(q3);

		q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
		q2.copyTo(q1);
		tmp.copyTo(q2);
//! [crop_rearrange]

//! [normalize]
		normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
																						// viewable image form (float between values 0 and 1).
//! [normalize]

		imshow("Input Image"       , I   );    // Show the result
		imshow("spectrum magnitude", magI);
		waitKey();

		return EXIT_SUCCESS;
}
