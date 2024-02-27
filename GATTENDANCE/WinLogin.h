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
};
