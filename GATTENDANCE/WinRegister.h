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
};