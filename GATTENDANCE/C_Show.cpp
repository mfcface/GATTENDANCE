// C_Show.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "C_Show.h"
#include "afxdialogex.h"
#include "C_Attendance.h"
#include "C_Absence.h"
#include "C_Information.h"


// C_Show 对话框

IMPLEMENT_DYNAMIC(C_Show, CDialogEx)

C_Show::C_Show(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SHOW, pParent)
{

}

C_Show::~C_Show()
{
}

void C_Show::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_Show, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_ATTENDANCE, &C_Show::OnBnClickedButtonAttendance)
	ON_BN_CLICKED(IDC_BUTTON_ABSENCE, &C_Show::OnBnClickedButtonAbsence)
	ON_BN_CLICKED(IDC_BUTTON_INFORMATION, &C_Show::OnBnClickedButtonInformation)
END_MESSAGE_MAP()


// C_Show 消息处理程序



void C_Show::OnBnClickedButtonAttendance()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	C_Attendance att;
	att.DoModal();
}


void C_Show::OnBnClickedButtonAbsence()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	C_Absence abs;
	abs.DoModal();
}


void C_Show::OnBnClickedButtonInformation()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	C_Information inf;
	inf.DoModal();
}
