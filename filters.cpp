#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;
cv::Rect cropper(500, 2800, 2000, 2000);

void saveImagePlusCrop (const Mat& imageToWrite, const std::string& name, const cv::Rect& cropper);
void medianFilters(const Mat& image_src);
void lowPassFilter(const Mat& src1);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//
// Examples of input parameters
// ./mt-05 ../../data/garden.png 

int main(int argc, char* argv[])
{
    std::string img_path;
     Mat noiseImage;

	// check input parameters
	if( argc > 1 ) img_path = std::string( argv[1] );

	// load testing images
	cv::Mat src_gray = imread(img_path, CV_LOAD_IMAGE_GRAYSCALE);

	// check testing images
	if( src_gray.empty() ) {
		std::cout << "Failed to load image: " << img_path << std::endl;
		return -1;
	}

	saveImagePlusCrop(src_gray, "gray", cropper);

	//medianFilters(src_gray);
	lowPassFilter(src_gray);

	
    return 0;
}

void saveImagePlusCrop (const Mat& imageToWrite, const std::string& name, const cv::Rect& cropper) {
    imwrite(name + ".bmp", imageToWrite);
    imwrite(name + "Crop.bmp", imageToWrite(cropper));

}

void medianFilters(const Mat& image_src){

	cv::Mat medi_img;
	int filter_size[3] = {3,5,7};

	for (int i = 0; i <= 2; i++)
	{
		cv::medianBlur(image_src, medi_img, filter_size[i]);
		//imwrite(std::to_string(filter_size[i])+"_median.bmp", medi_img);
		saveImagePlusCrop(medi_img, "median" + std::to_string(filter_size[i]), cropper);
	}
	return;
}

void lowPassFilter(const Mat& src1){

	Mat src2 = src1.clone();
	int a = 3;
	Scalar intensity1 = 0;

	for (int i = 0; i < src1.rows-a; i++){ 
		for (int j = 0; j < src1.cols-a; j++){ 
	   		Scalar intensity2;
	   		
	   		for (int p = 0; p<a; p++){ 
	     		for (int q = 0; q<a; q++){ 

	     			intensity1 = src1.at<uchar>(i+p,j+q); 
	      			intensity2.val[0] +=intensity1.val[0];
	     		}
	  		}
	    	src2.at<uchar>(i+(a-1)/2,j+(a-1)/2)=intensity2.val[0]/(a*a);
	   } 
	}
	//imwrite("lowPassFilter.bmp", src2);
	saveImagePlusCrop(src2, "lowPassFilter",cropper);
}