// Main.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

    cv::Mat imgOriginal;
    cv::Mat imgBlurred;
    cv::Mat imgGrayscale;

    imgOriginal = cv::imread("image.png");          // open image

    if (imgOriginal.empty()) {                                  // if unable to open image
        std::cout << "error: image not read from file\n\n";     // show error message on command line
        _getch();                                               // may have to modify this line if not using Windows
        return(0);                                              // and exit program
    }

    cv::imshow("imgOriginal", imgOriginal);

    cv::GaussianBlur(imgOriginal, imgBlurred, cv::Size(3, 3), 0);
    cv::imshow("imgBlurred", imgBlurred);

    cv::cvtColor(imgBlurred, imgGrayscale, CV_BGR2GRAY);
    cv::imshow("imgGrayscale", imgGrayscale);

    cv::Mat gradX;
    cv::Mat gradY;
    cv::Mat absGradX;
    cv::Mat absGradY;
    cv::Mat imgSobel;

    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    cv::Sobel(imgGrayscale, gradX, ddepth, 1, 0);
    cv::convertScaleAbs(gradX, absGradX);

    cv::Sobel(imgGrayscale, gradY, ddepth, 0, 1);
    cv::convertScaleAbs(gradY, absGradY);

    cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, imgSobel);

    cv::imshow("imgSobel", imgSobel);

    cv::waitKey(0);                 // hold windows open until user presses a key

    return(0);
}

