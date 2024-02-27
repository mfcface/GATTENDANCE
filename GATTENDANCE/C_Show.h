#pragma once


// C_Show 对话框

class C_Show : public CDialogEx
{
	DECLARE_DYNAMIC(C_Show)

public:
	C_Show(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_Show();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonAttendance();
	afx_msg void OnBnClickedButtonAbsence();
	afx_msg void OnBnClickedButtonInformation();
};
