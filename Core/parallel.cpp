// drawing a Mandelbrot set

//The Mandelbrot set is the set of values of c in the complex plane for which the orbit of 0 under iteration of the quadratic map
//z0=0
//zn+1=zn^2+c
//remains bounded.

// simple algorithm: for all the pixels, check whether the condition is true
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

// Namespaces provide a method for preventing name conflicts in large projects.
// Symbols declared inside a namespace block are placed in a named scope that prevents them from being mistaken for identically-named symbols in other scopes.
namespace
{
//! [mandelbrot-escape-time-algorithm]
// escape time algorithm: return the "time" used to escapes
int mandelbrot(const complex<float> &z0, const int max)
{
		complex<float> z = z0;
		for (int t = 0; t < max; t++)
		{
				if (z.real()*z.real() + z.imag()*z.imag() > 4.0f) return t;
				z = z*z + z0;
		}

		return max;
}
//! [mandelbrot-escape-time-algorithm]

//! [mandelbrot-grayscale-value]
int mandelbrotFormula(const complex<float> &z0, const int maxIter=500) {
		int value = mandelbrot(z0, maxIter);
		// if equal: not escape => in set => black
		if(maxIter - value == 0)
		{
				return 0;
		}
		// else escape: not in => the closer value and max are the whiter (to make the edge clean with a sqrt transformation)
		return cvRound(sqrt(value / (float) maxIter) * 255);
}
//! [mandelbrot-grayscale-value]

//! [mandelbrot-parallel]
// ParallelLoopBody: cv::ParallelLoopBody
class ParallelMandelbrot : public ParallelLoopBody
{
public:
		ParallelMandelbrot (Mat &img, const float x1, const float y1, const float scaleX, const float scaleY)
				: m_img(img), m_x1(x1), m_y1(y1), m_scaleX(scaleX), m_scaleY(scaleY)
		{
		}
		// override
		// The range in the operator () represents the subset of pixels that will be treated by an individual thread
		virtual void operator ()(const Range& range) const CV_OVERRIDE
		{
				for (int r = range.start; r < range.end; r++)
				{
						int i = r / m_img.cols;
						int j = r % m_img.cols;

						float x0 = j / m_scaleX + m_x1;
						float y0 = i / m_scaleY + m_y1;

						complex<float> z0(x0, y0);
						uchar value = (uchar) mandelbrotFormula(z0);
						m_img.ptr<uchar>(i)[j] = value;
				}
		}

		ParallelMandelbrot& operator=(const ParallelMandelbrot &) {
				return *this;
		};

private:
		Mat &m_img;
		float m_x1;
		float m_y1;
		float m_scaleX;
		float m_scaleY;
};
//! [mandelbrot-parallel]

//! [mandelbrot-sequential]
void sequentialMandelbrot(Mat &img, const float x1, const float y1, const float scaleX, const float scaleY)
{
		for (int i = 0; i < img.rows; i++)
		{
				for (int j = 0; j < img.cols; j++)
				{
						float x0 = j / scaleX + x1;
						float y0 = i / scaleY + y1;

						complex<float> z0(x0, y0);
						uchar value = (uchar) mandelbrotFormula(z0);
						img.ptr<uchar>(i)[j] = value;
				}
		}
}
//! [mandelbrot-sequential]
}

int main()
{
		//! [mandelbrot-transformation]
		Mat mandelbrotImg(4800, 5400, CV_8U);
		float x1 = -2.1f, x2 = 0.6f;
		float y1 = -1.2f, y2 = 1.2f;
		float scaleX = mandelbrotImg.cols / (x2 - x1);
		float scaleY = mandelbrotImg.rows / (y2 - y1);
		//! [mandelbrot-transformation]

		double t1 = (double) getTickCount();

		// C++ 11: can use lambbda function
		#ifdef CV_CXX11

		//! [mandelbrot-parallel-call-cxx11]
		//parallel_for_(range, functor "{}" part)
		// [&]: lambda function
		//[capture](parameters){body}
		//[&]: capture by reference (will modify the original value)
		// see: https://en.cppreference.com/w/cpp/language/lambda
		// access every variable by reference currently in scope within the lambda function (anonymous fucntion).
		parallel_for_(Range(0, mandelbrotImg.rows*mandelbrotImg.cols), [&](const Range& range){
				for (int r = range.start; r < range.end; r++)
				{
						int i = r / mandelbrotImg.cols;
						int j = r % mandelbrotImg.cols;

						float x0 = j / scaleX + x1;
						float y0 = i / scaleY + y1;

						complex<float> z0(x0, y0);
						uchar value = (uchar) mandelbrotFormula(z0);
						mandelbrotImg.ptr<uchar>(i)[j] = value;
				}
		});
		//! [mandelbrot-parallel-call-cxx11]

		#else

		//! [mandelbrot-parallel-call]
		ParallelMandelbrot parallelMandelbrot(mandelbrotImg, x1, y1, scaleX, scaleY);
		parallel_for_(Range(0, mandelbrotImg.rows*mandelbrotImg.cols), parallelMandelbrot);
		//! [mandelbrot-parallel-call]

		#endif

		t1 = ((double) getTickCount() - t1) / getTickFrequency();
		cout << "Parallel Mandelbrot: " << t1 << " s" << endl;

		Mat mandelbrotImgSequential(4800, 5400, CV_8U);
		double t2 = (double) getTickCount();
		sequentialMandelbrot(mandelbrotImgSequential, x1, y1, scaleX, scaleY);
		t2 = ((double) getTickCount() - t2) / getTickFrequency();
		cout << "Sequential Mandelbrot: " << t2 << " s" << endl;
		cout << "Speed-up: " << t2/t1 << " X" << endl;

		imwrite("Mandelbrot_parallel.png", mandelbrotImg);
		imwrite("Mandelbrot_sequential.png", mandelbrotImgSequential);

		return EXIT_SUCCESS;
}
