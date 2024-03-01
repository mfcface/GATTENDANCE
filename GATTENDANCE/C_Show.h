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
	SQL::info user;
	void getInfo(SQL::info& Info);
	CStatic m_id;
	CStatic m_name;
	CStatic m_gender;
	CStatic m_major;
	afx_msg void OnBnClickedButtonAttendance();
	afx_msg void OnBnClickedButtonAbsence();
	afx_msg void OnBnClickedButtonInformation();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	void UpdateStaticText(CStatic& st,const CString& newText);
};
