﻿#pragma once

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
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_camera;
	CString strText;
	BOOL m_open_camera;
	SQL db;
	SQL::info user; // 定义静态成员变量
	afx_msg void OnBnClickedButton1();
};

