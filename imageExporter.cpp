#include "imageExporter.h"

#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;

void saveImagePlusCrop(const Mat& imageToWrite, const std::string& name, const cv::Rect& cropper) {
	imwrite(name + ".bmp", imageToWrite);
	imwrite(name + "Crop.bmp", imageToWrite(cropper));

}
