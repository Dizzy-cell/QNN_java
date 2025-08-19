//
// Created by yyj on 8/19/25.
//

#ifndef SUPERRESOLUTION_DEPTHANYTHINGV2_H
#define SUPERRESOLUTION_DEPTHANYTHINGV2_H

#include "Model.h"

class DepthAnythingV2: public Model {

public:
    void preprocess(cv::Mat &img, std::vector<int> dims);
    void postprocess(cv::Mat &outputimg);
    void msg();

};

#endif //SUPERRESOLUTION_DEPTHANYTHINGV2_H
