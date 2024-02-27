#pragma once


// C_Absence 对话框

class C_Absence : public CDialogEx
{
	DECLARE_DYNAMIC(C_Absence)

public:
	C_Absence(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_Absence();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ABSENCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
