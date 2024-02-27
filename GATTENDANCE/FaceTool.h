#pragma once

#include "arcsoft_face_sdk.h"
#include "amcomdef.h"
#include "asvloffscreen.h"
#include "merror.h"
#include <direct.h>
#include <iostream>  
#include <stdarg.h>
#include <string>
#include<opencv2\opencv.hpp>

using namespace std;

#define SafeFree(p) { if ((p)) free(p); (p) = NULL; }
#define SafeArrayDelete(p) { if ((p)) delete [] (p); (p) = NULL; } 
#define SafeDelete(p) { if ((p)) delete (p); (p) = NULL; } 

#define APPID "Dff3C1yRzC6o4RvJ9CfPnKAQC4ZLEmYmnJMekrZ17uBB"

// 32位
//#define SDKKey "8LJqeAmH6wsjcdBBMt6E1WRjt8aHyaWdsfUg7ELx8KPD"

//64位
#define SDKKey  "TcxQ7fFta7yeFYyEFL8YFz5KonQHyLEM6Qgsj6pRsWy"

// 虹软人脸识别SDK初始化
void faceInit(MHandle* handle);

// 人脸对比函数，返回相似度
float faceCompare(MHandle handle, cv::Mat& img1, cv::Mat& img2);

// 返回图片中识别到的人脸位置
bool faceRegion(MHandle handle, cv::Mat img, cv::Rect& face_rect);
