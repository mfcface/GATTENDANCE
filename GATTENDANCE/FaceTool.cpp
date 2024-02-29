#include "FaceTool.h"
#include "pch.h"

void faceInit(MHandle* handle) {
    //����ӿ�,����������
    MRESULT res = ASFOnlineActivation((char*)APPID, (char*)SDKKey);
    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
        printf("����ʧ��\n");

    //��ȡ�����ļ���Ϣ
    ASF_ActiveFileInfo  activeFileInfo;
    res = ASFGetActiveFileInfo(&activeFileInfo);
    if (res != MOK)
        printf("ASFGetActiveFileInfo fail: %d\n", res);

    //��ʼ���ӿ�
    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE | ASF_LIVENESS | ASF_IR_LIVENESS;
    res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_ONLY, 30, 10, mask, handle);
    if (res != MOK)
        printf("�ӿڳ�ʼ��ʧ��\n");
}

float faceCompare(MHandle handle, cv::Mat& img1, cv::Mat& img2) {
    ASF_MultiFaceInfo detectedFaces1{ 0 };          // �����������Ϣ
    ASF_SingleFaceInfo SingleDetectedFaces1{ 0 };   // ���嵥������Ϣ
    ASF_FaceFeature feature1{ 0 };                  // ������������
    ASF_FaceFeature copyfeature1{ 0 };              // �������������Ŀ���
    cv::Rect roiRect1(0, 0, img1.cols - img1.cols % 4, img1.rows); // ����Ҫ�ü�������ֻ����ΪҪ������4����������
    cv::Mat cutImg1 = img1(roiRect1).clone();       // �õ��ü��õ�ͼƬ

    // ����Ƿ����������ע���������SDK�ĵ�Ҫ��ͼƬ��ȱ�����4�ı�����
    MRESULT res;
    res = ASFDetectFaces(handle, cutImg1.cols, cutImg1.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg1.data, &detectedFaces1);

    if (MOK == res) {
        // ȡ��ͼƬ�еĵ�һ��������Ϣ
        if (detectedFaces1.faceRect != NULL && detectedFaces1.faceOrient != NULL) {
            // ��ʵ����жϿ��Բ�д����ΪֻҪres==MOK��detectedFaces1�о�һ���������ݣ�����ֱ�Ӹ�ֵû���⡣
            // ���������������������棬���Բż�������жϡ�
            SingleDetectedFaces1.faceRect.left = detectedFaces1.faceRect[0].left;
            SingleDetectedFaces1.faceRect.top = detectedFaces1.faceRect[0].top;
            SingleDetectedFaces1.faceRect.right = detectedFaces1.faceRect[0].right;
            SingleDetectedFaces1.faceRect.bottom = detectedFaces1.faceRect[0].bottom;
            SingleDetectedFaces1.faceOrient = detectedFaces1.faceOrient[0];
        }

        // ������������ȡ
        res = ASFFaceFeatureExtract(handle, cutImg1.cols, cutImg1.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg1.data, &SingleDetectedFaces1, &feature1);
        if (res == MOK) {
            // ����ȡ��������������Ϣ���Ž�����п�����
            // ����ΪʲôҪ���п�������ʱ��û�и㶮����
            copyfeature1.featureSize = feature1.featureSize;
            copyfeature1.feature = (MByte*)malloc(feature1.featureSize);
            memset(copyfeature1.feature, 0, feature1.featureSize);
            memcpy(copyfeature1.feature, feature1.feature, feature1.featureSize);
        }
        else {
            printf("ASFFaceFeatureExtract 1 fail: %d\n", res);
        }
    }
    else {
        printf("ASFDetectFaces 1 fail: %d\n", res);
    }

    //�ڶ�����������
    ASF_MultiFaceInfo detectedFaces2{ 0 };          // �����������Ϣ
    ASF_SingleFaceInfo SingleDetectedFaces2{ 0 };   // ���嵥������Ϣ
    ASF_FaceFeature feature2 = { 0 };               // ������������
    cv::Rect roiRect2(0, 0, img2.cols - img2.cols % 4, img2.rows); // ����Ҫ�ü�������ֻ����ΪҪ������4����������
    cv::Mat cutImg2 = img2(roiRect2).clone();       // �õ��ü��õ�ͼƬ

    // ���ͼƬ�е�������Ϣ
    res = ASFDetectFaces(handle, cutImg2.cols, cutImg2.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg2.data, &detectedFaces2);
    if (MOK == res) {
        if (detectedFaces2.faceRect != NULL && detectedFaces2.faceOrient != NULL) {
            // ��ʵ����жϿ��Բ�д����ΪֻҪres==MOK��detectedFaces1�о�һ���������ݣ�����ֱ�Ӹ�ֵû���⡣
            // ���������������������棬���Բż�������жϡ�
            SingleDetectedFaces2.faceRect.left = detectedFaces2.faceRect[0].left;
            SingleDetectedFaces2.faceRect.top = detectedFaces2.faceRect[0].top;
            SingleDetectedFaces2.faceRect.right = detectedFaces2.faceRect[0].right;
            SingleDetectedFaces2.faceRect.bottom = detectedFaces2.faceRect[0].bottom;
            SingleDetectedFaces2.faceOrient = detectedFaces2.faceOrient[0];
        }

        // ������������ȡ
        res = ASFFaceFeatureExtract(handle, cutImg2.cols, cutImg2.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg2.data, &SingleDetectedFaces2, &feature2);
        if (MOK != res) {
            printf("ASFFaceFeatureExtract 2 fail: %d\n", res);
        }
    }
    else {
        printf("ASFDetectFaces 2 fail: %d\n", res);
    }

    // �����������ȶ�
    MFloat confidenceLevel;
    res = ASFFaceFeatureCompare(handle, &copyfeature1, &feature2, &confidenceLevel);
    if (res != MOK) {
        confidenceLevel = -1;
    }

    SafeFree(copyfeature1.feature); //�ͷ��ڴ�

    return confidenceLevel;
}

// ����ͼƬ��ʶ�𵽵�����λ��
bool faceRegion(MHandle handle, cv::Mat img, cv::Rect& face_rect) {
    // �ü�ͼƬ��ʹ����Ϊ4����������ASFDetectFacesҪ��
    cv::Rect roiRect1(0, 0, img.cols - img.cols % 4, img.rows); // ����Ҫ�ü�������ֻ����ΪҪ������4����������
    cv::Mat cutImg1 = img(roiRect1).clone();       // �õ��ü��õ�ͼƬ

    // ����Ƿ��������
    ASF_MultiFaceInfo detectedFaces1{ 0 };          // �����������Ϣ
    MRESULT res = ASFDetectFaces(handle, cutImg1.cols, cutImg1.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg1.data, &detectedFaces1);
    // �����������ͷ��ص�һ��������Ϣ
    if (MOK == res && detectedFaces1.faceRect != NULL && detectedFaces1.faceNum) {
        face_rect.x = detectedFaces1.faceRect[0].left;
        face_rect.y = detectedFaces1.faceRect[0].top;
        face_rect.width = detectedFaces1.faceRect[0].right - detectedFaces1.faceRect[0].left;
        face_rect.height = detectedFaces1.faceRect[0].bottom - detectedFaces1.faceRect[0].top;
        return true;
    }
    else {
        printf("ASFDetectFaces 1 fail: %d\n", res);
        return false;
    }
}