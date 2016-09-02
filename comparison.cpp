#include "comparison.h"

using namespace std;
using namespace cv;

Mat ref_image;
Mat comp_image;
Ptr<BackgroundSubtractor> pMOG2;
Mat fgMask;

comparison::comparison()
{


}

bool comparison::loadimages(string refimage,string compimage)
{
    //load in images

    ref_image = imread(refimage,1);
    comp_image = imread(compimage,1);


    //confirm Mat's have data
    if(ref_image.empty() || comp_image.empty()){
        cout << "could not load images" << endl;
        return false;
    }

    //check sizes
    if(ref_image.cols != comp_image.cols || ref_image.rows != comp_image.rows){
        cout << "images must be the same size" << endl;
        return false;
    }

    //good to continue
    return true;
}

void comparison::compareimages()
{
    Mat ref_hsv, comp_hsv;

    //convert to hsv
    cvtColor(ref_image, ref_hsv, CV_BGR2HSV);
    cvtColor(comp_image,comp_hsv, CV_BGR2HSV);

    //use 50 bins for hue and 60 for saturation
    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = {h_bins,s_bins};

    //hue varies from 0 - 179, saturation from 0 - 255
    float h_ranges[] = {0,180};
    float s_ranges[] = {0,255};

    const float* ranges[] = {h_ranges, s_ranges};

    int channels[] = {0,1};

    MatND ref_hist, comp_hist;

    //calculate histograms
    calcHist(&ref_hsv, 1, channels, Mat(), ref_hist,2, histSize, ranges, true, false);
    normalize(ref_hist, ref_hist, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&comp_hsv, 1, channels, Mat(), comp_hist,2, histSize, ranges, true, false);
    normalize(comp_hist, comp_hist, 0, 1, NORM_MINMAX, -1, Mat());

    double comparison = compareHist(ref_hist, comp_hist, 0);

    cout << "comp result: " << comparison << endl;

    drawthresh();

    return;
}

void comparison::drawthresh()
{
    //create the subtractor
    pMOG2 = new BackgroundSubtractorMOG2();

    //convert to greyscale
    Mat ref_grey, comp_grey;
    cvtColor(ref_image, ref_grey, CV_BGR2GRAY);
    cvtColor(comp_image, comp_grey, CV_BGR2GRAY);

    //load in background image
    //pMOG2->getBackgroundImage(ref_grey);

    //pMOG2->operator ()(comp_grey, ref_grey);
    pMOG2->operator ()(ref_grey,fgMask);
    pMOG2->operator ()(comp_grey, fgMask);




    vector<int>compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    string file = "comp.png";
    imwrite(file, fgMask, compression_params);


}

