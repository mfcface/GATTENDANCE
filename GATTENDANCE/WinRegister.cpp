// WinRegister.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "WinRegister.h"
#include "afxdialogex.h"


// WinRegister 对话框

IMPLEMENT_DYNAMIC(WinRegister, CDialogEx)

WinRegister::WinRegister(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Register, pParent)
{

}

WinRegister::~WinRegister()
{
}

void WinRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WinRegister, CDialogEx)
END_MESSAGE_MAP()


// WinRegister 消息处理程序
