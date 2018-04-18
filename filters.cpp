#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;

void saveImagePlusCrop (const Mat& imageToWrite, const std::string& name, const cv::Rect& cropper);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//
// Examples of input parameters
// ./mt-05 ../../data/garden.png 

int main(int argc, char* argv[])
{
    std::string img_path;
    int filter_size[3] = {3,5,7};
    cv::Mat medi_img;
    cv::Rect cropper(50, 280, 200, 200);

	// check input parameters
	if( argc > 1 ) img_path = std::string( argv[1] );

	// load testing images
	cv::Mat src_rgb = cv::imread( img_path );

	// check testing images
	if( src_rgb.empty() ) {
		std::cout << "Failed to load image: " << img_path << std::endl;
		return -1;
	}

	cv::Mat src_gray;
	cv::cvtColor( src_rgb, src_gray, CV_BGR2GRAY );

	//---------------------------------------------------------------------------


	for (int i = 0; i <= 2; i++)
	{
		cv::medianBlur( src_gray, medi_img, filter_size[i]);
		imwrite(std::to_string(filter_size[i])+"_median.bmp", medi_img);
		//saveImagePlusCrop(medi_img, "median" + std::to_string(filter_size[i]), cropper);
	}
	
    return 0;
}

void saveImagePlusCrop (const Mat& imageToWrite, const std::string& name, const cv::Rect& cropper) {
    imwrite(name + ".bmp", imageToWrite);
    imwrite(name + "Crop.bmp", imageToWrite(cropper));

}
