#pragma once


// C_Information 对话框

class C_Information : public CDialogEx
{
	DECLARE_DYNAMIC(C_Information)

public:
	C_Information(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_Information();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFORMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	SQL db;
	afx_msg void OnBnClickedEdit3();
	virtual BOOL OnInitDialog();
};
