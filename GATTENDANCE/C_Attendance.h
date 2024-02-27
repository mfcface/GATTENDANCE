#pragma once


// C_Attendance 对话框

class C_Attendance : public CDialogEx
{
	DECLARE_DYNAMIC(C_Attendance)

public:
	C_Attendance(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_Attendance();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ATTENDANCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonOn();
	afx_msg void OnBnClickedButtonOff();
};
