﻿#pragma once


// WinRegister 对话框

class WinRegister : public CDialogEx
{
	DECLARE_DYNAMIC(WinRegister)

public:
	WinRegister(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WinRegister();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Register };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtLClose();
	afx_msg void OnBnClickedBtRFace();
	CStatic m_camera;
	CString strText;
	BOOL m_get_face;
	BOOL m_open_camera;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
