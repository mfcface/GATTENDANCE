// WinLogin.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "WinLogin.h"
#include "afxdialogex.h"
#include "C_Show.h"


// WinLogin 对话框

IMPLEMENT_DYNAMIC(WinLogin, CDialogEx)

WinLogin::WinLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Login, pParent)
{

}

WinLogin::~WinLogin()
{
}

void WinLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WinLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BT_L_face, &WinLogin::OnBnClickedBtLface)
END_MESSAGE_MAP()


// WinLogin 消息处理程序


void WinLogin::OnBnClickedBtLface()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	C_Show show;
	show.DoModal();
}
