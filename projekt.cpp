
#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

#include "imageExporter.h"

using namespace std;
using namespace cv;

void whiteNoise(const cv::Mat& src, cv::Mat& dst, float intensity);
void addSPNoise(const Mat& I, Mat& O, double p);
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

	whiteNoise(srcImage, noiseImage, 0.1);
    saveImagePlusCrop(noiseImage, "gaussWhite-0_1", cropper);

	whiteNoise(srcImage, noiseImage, 1.0);
	saveImagePlusCrop(noiseImage, "gaussWhite-1_0", cropper);

	addSPNoise(srcImage, noiseImage, 0.1);
	saveImagePlusCrop(noiseImage, "SaP-0-1", cropper);

	addSPNoise(srcImage, noiseImage, 0.2);
	saveImagePlusCrop(noiseImage, "SaP-0-2", cropper);

	

	//salt and pepper
	//https://stackoverflow.com/questions/10310762/speckle-noise-generation

    return 0;

}


//  Funkce pro generování bílého šumu.
//  Intenzita udává maximální velikost šumu.
void whiteNoise(const cv::Mat& src, cv::Mat& dst, float intensity)
{
	cv::RNG rng;
	cv::Mat noise = cv::Mat::zeros(src.size(), CV_32SC1);
	for (int i = 0; i < noise.rows*noise.cols; ++i) {
		// vygenerujte hodnoty pro bílý šum a uložte do obrazu se šumem
		// využijte: rng.gaussian(double sigma)
		// a vztah pro gaussùv pásmový bílý šum
		// vzorky bílého šumu s výkonem (rozptylem) napø. 0.2 vypoèteme:
		// v = sqrt(výkon=0.2) * gaussian(sigma=1.0)
		// funkce gaussian() generuje náhodné vzorky s normálním rozlošením se støední hodnotou 0 a rozptylem 1.
		noise.at<int>(i) = round(sqrt(255 * intensity) * rng.gaussian(1.0));
	}
	cv::Mat tmp;
	src.convertTo(tmp, noise.type());
	tmp = tmp + noise;
	tmp.convertTo(dst, src.type());
}


//http://answers.opencv.org/question/68589/adding-noise-to-image-opencv/
// I is the grayscale of the input image
//Mean value of random value, standard deviaiton
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