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

// 32λ
//#define SDKKey "8LJqeAmH6wsjcdBBMt6E1WRjt8aHyaWdsfUg7ELx8KPD"

//64λ
#define SDKKey  "TcxQ7fFta7yeFYyEFL8YFz5KonQHyLEM6Qgsj6pRsWy"

// ��������ʶ��SDK��ʼ��
void faceInit(MHandle* handle);

// �����ԱȺ������������ƶ�
float faceCompare(MHandle handle, cv::Mat& img1, cv::Mat& img2);

// ����ͼƬ��ʶ�𵽵�����λ��
bool faceRegion(MHandle handle, cv::Mat img, cv::Rect& face_rect);
