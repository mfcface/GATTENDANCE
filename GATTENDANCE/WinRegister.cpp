// WinRegister.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "WinRegister.h"
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h> // 用到了cvGetWindowHandle
using namespace cv;
static cv::VideoCapture cap_WinReg; // 定义注册窗口的摄像头(static只能本文件使用)
CascadeClassifier Classifier;//定义分类器
// WinRegister 对话框

IMPLEMENT_DYNAMIC(WinRegister, CDialogEx)

WinRegister::WinRegister(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Register, pParent)
{

}

WinRegister::~WinRegister()
{
}

void WinRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAMERA_REG, m_camera);
}


BEGIN_MESSAGE_MAP(WinRegister, CDialogEx)
	ON_BN_CLICKED(IDC_BT_R_face, &WinRegister::OnBnClickedBtRface)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// WinRegister 消息处理程序


void WinRegister::OnBnClickedBtRface()
{
	// TODO: 在此添加控件通知处理程序代码
	// 假设 pEdit 是您的 CEdit 对象指针

	GetDlgItemText(IDC_EDIT1, strText);
	if (strText.GetLength() == 0)
	{
		MessageBox(_T("请输入用户名!!!用户名不能为空！！"));
		return;
	}
	if (!m_open_camera)
	{
		// 将opencv的窗体嵌入到图片控件m_imgCamera_single中
		cv::namedWindow("m_camera", cv::WINDOW_AUTOSIZE);     // 打开一个opencv窗口，注意名称要与图片控件一致
		HWND hWnd = (HWND)cvGetWindowHandle("m_camera");      // 获取opencv窗口句柄
		HWND hParent = ::GetParent(hWnd);                               // 获取opencv窗口的父窗口句柄
		::SetParent(hWnd, GetDlgItem(IDC_CAMERA_REG)->m_hWnd);          // 将opencv窗口的句柄设置为图片控件的句柄
		::ShowWindow(hParent, SW_HIDE);                                 // 隐藏原父窗口


		// 打开默认摄像头0
		cap_WinReg.open(0);
		m_open_camera = true;
		if (!cap_WinReg.isOpened()) {
			::MessageBox(NULL, _T("摄像头打开失败！\n请检查摄像头是否正确连接并开启！"), _T("警告"), MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		// 开启摄像头的定时器
		SetTimer(1, 20, NULL);
	}
	else if (!m_get_face)
	{
		m_get_face = true;
	}

}


BOOL WinRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!Classifier.load("xml/haarcascade_frontalface_alt.xml"))   //加载训练文件  
	{
		std::cout << "xml文件加载失败" << std::endl;
		return -1;
	}
	// 调整摄像头显示的图片控件的位置(200,23)和大小(640x480)
	::MoveWindow(m_camera.m_hWnd, 200, 23, 640, 480, 1);
	m_get_face = false;
	m_open_camera = false;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void WinRegister::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int shoot_count = 0;
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
		if (!faces.empty() && m_get_face)
		{
			// 假设 strText 是从编辑框中获取的文本值
			std::string filename = "face_data/" + std::string(CT2A(strText)) + ".jpg"; // 构建新的文件名

			cv::imwrite(filename, cam_frame); // 保存单帧照片，文件名为编辑框中的文本值
			shoot_count = 0;                    // 清零计数
			KillTimer(1);                       // 关闭定时器
			cap_WinReg.release();               // 关闭摄像头
			CDialogEx::OnOK();                  // 关闭注册窗口
			MessageBox(_T("注册成功！"));
		}


	}

	CDialogEx::OnTimer(nIDEvent);
}
