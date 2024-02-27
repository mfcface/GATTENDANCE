// WinLogin.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "WinLogin.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h> // 用到了cvGetWindowHandle

#include "FaceTool.h"
using namespace cv;
static cv::VideoCapture cap_WinReg; // 定义注册窗口的摄像头(static只能本文件使用)



// WinLogin 对话框

IMPLEMENT_DYNAMIC(WinLogin, CDialogEx)

WinLogin::WinLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Login, pParent)
{

}

WinLogin::~WinLogin()
{
}

void WinLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAMERA_LOG, m_camera);
}


BEGIN_MESSAGE_MAP(WinLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BT_L_face, &WinLogin::OnBnClickedBtLface)
	ON_BN_CLICKED(IDC_BT_L_Close, &WinLogin::OnBnClickedBtClose)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// WinLogin 消息处理程序


void WinLogin::OnBnClickedBtLface()
{
	// TODO: 在此添加控件通知处理程序代码


}


void WinLogin::OnBnClickedBtClose()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL WinLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	faceInit(&FaceModel);

	// TODO:  在此添加额外的初始化
	if (!Classifier.load("xml/haarcascade_frontalface_alt.xml"))   //加载训练文件  
	{
		std::cout << "xml文件加载失败" << std::endl;
		return -1;
	}
	// 调整摄像头显示的图片控件的位置(200,23)和大小(640x480)
	::MoveWindow(m_camera.m_hWnd, 200, 23, 640, 480, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void WinLogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		// 获取摄像头拍摄的单帧，并进行显示
		cv::Mat cam_frame;
		cap_WinReg >> cam_frame;
		std::vector<Rect> faces;
		Classifier.detectMultiScale(cam_frame, faces, 1.1, 3, 0, Size(30, 30));//人脸检测关键
		for (size_t t = 0; t < faces.size(); t++)
		{
			rectangle(cam_frame, faces[t], Scalar(0, 255, 0), 2, 8);//画个绿框
		}
		imshow("m_camera", cam_frame);
		if (!faces.empty())
		{
			// 假设 strText 是从编辑框中获取的文本值
			std::string filename = "face_data/" + std::string(CT2A(strText)) + ".jpg"; // 构建新的文件名

			img = imread(filename);
			
			Mat img_tmp(cam_frame);

			//人脸对比
			float num = faceCompare(FaceModel, img_tmp, img);
			if (num > 0.95)
			{
				MessageBox(_T("登录成功！"));
			}
				
		}


	}
	CDialogEx::OnTimer(nIDEvent);
}


void WinLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}
