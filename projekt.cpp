
#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;

void addGaussianNoise(const Mat& I, Mat& O, double mean, double stdev);
void saveImagePlusCrop (const Mat& imageToWrite, const std::string& name, const cv::Rect& cropper);

int main(int argc, char *argv[]) {

    std::string fileName;

    if (argc != 2) {
        cout << "Must have 1 parameter: name of input file" << '\n';
        return -1;
    } else {
        fileName = argv[1];
    }

    cv::Rect cropper(500, 2800, 2000, 2000);
    Mat noiseImage, noiseImageCropped, srcImageCropped;

    //Load image
    cv::Mat srcImage = imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);
    srcImageCropped = srcImage(cropper);
    imwrite("imgageCrop.bmp", srcImageCropped);

    addGaussianNoise(srcImage, noiseImage, 0, 0.1);
    saveImagePlusCrop(noiseImage, "gauss", cropper);

    return 0;

}

void saveImagePlusCrop (const Mat& imageToWrite, const std::string& name, const cv::Rect& cropper) {
    imwrite(name + ".bmp", imageToWrite);
    imwrite(name + "Crop.bmp", imageToWrite(cropper));

}

//http://answers.opencv.org/question/68589/adding-noise-to-image-opencv/
// I is the grayscale of the input image
void addGaussianNoise(const Mat& I, Mat& O, double mean, double stdev)
{

	Mat noise = Mat(I.size(),CV_64F);
	Mat r1    = Mat(I.size(),CV_64F);
	normalize(I, r1, 0.0, 1.0, CV_MINMAX, CV_64F);
	randn(noise, mean, stdev);
	r1 = r1 + noise;
	r1.convertTo(O, I.type(), 255.0);
	return;
}


void addSPNoise(const Mat& I, Mat& O, double p)
{
	Mat sp_noise = Mat::zeros(I.size(),CV_8U);
	randu(sp_noise,0,255);

	int limit_approx = floor(p*256);

	Mat black = sp_noise < limit_approx;
	Mat white = sp_noise > 256-limit_approx;

	O = I.clone();
	O.setTo(255,white);
	O.setTo(0,black);
	return;
}