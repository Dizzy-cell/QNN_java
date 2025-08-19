//
// Created by honor on 8/19/25.
//

#include <opencv2/imgcodecs.hpp>
#include "../include/DepthAnythingV2.h"

void DepthAnythingV2::preprocess(cv::Mat &img, std::vector<int> dims)
{
    LOGI("XLSR Class Preprocess is called");

    //dims is of size [batchsize(1), height, width, channels(3)]
    //cv::resize(img,img,cv::Size(dims[1],dims[0]),cv::INTER_LINEAR); //Resizing based on input
    cv::resize(img,img,cv::Size(518,518),cv::INTER_LINEAR); //Resizing based on input

    LOGI("inputimage SIZE width::%d height::%d",img.cols, img.rows);

    float inputScale = 0.00392156862745f;    //normalization value, this is 1/255

    //opencv read in BGRA by default
    cvtColor(img, img, CV_BGRA2RGB);
    img.convertTo(img,CV_32FC3,inputScale);
    LOGI("num of channels: %d",img.channels());

//    float* temp = reinterpret_cast<float *>(img.data);
//    for(int i=0;i<10;i++)
//    {
//        __android_log_print(ANDROID_LOG_ERROR, "QNN_INF", "input buffer[%d] = %f\n",i,temp[i]);
//    }
}

void DepthAnythingV2::postprocess(cv::Mat &outputimg) {
    //This function will multiply by 255 and convert 4byte float value to 1byte int.
    LOGI("postprocess");
    LOGI("width = %d",outputimg.cols);
    LOGI("height = %d\n",outputimg.rows);
    LOGI("channel = %d\n",outputimg.channels());
    double minVal, maxVal;
    cv::minMaxLoc(outputimg, &minVal, &maxVal);

    LOGI("min = %f, max = %f", minVal, maxVal);

    // 2. 归一化到 [0,1]
    if (maxVal > minVal) {
        outputimg = (outputimg - minVal) / (maxVal - minVal);
    } else {
        outputimg = cv::Mat::zeros(outputimg.size(), outputimg.type());
    }

    outputimg.convertTo(outputimg,CV_8UC3, 255);
    LOGI("postprocess done");
}

void DepthAnythingV2::msg()
{
    LOGI("XLSR Class msg");
}