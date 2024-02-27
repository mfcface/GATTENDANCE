#pragma once


// WinLogin 对话框

class WinLogin : public CDialogEx
{
	DECLARE_DYNAMIC(WinLogin)

public:
	WinLogin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WinLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Login };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtLface();
	afx_msg void OnBnClickedBtClose();
	CStatic m_camera;
	CString strText;
	CascadeClassifier Classifier;//定义分类器

	Mat img; //对比图像
	MHandle FaceModel; //人脸对比
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
