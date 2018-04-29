#ifdef IMAGE_EXPORTER
#define IMAGE_EXPORTER

#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

void saveImagePlusCrop(const Mat& imageToWrite, const std::string& name, const cv::Rect& cropper);

#endif // IMAGE_EXPORTER

