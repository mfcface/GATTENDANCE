// C_Absence.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "C_Absence.h"
#include "afxdialogex.h"


// C_Absence 对话框

IMPLEMENT_DYNAMIC(C_Absence, CDialogEx)

C_Absence::C_Absence(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ABSENCE, pParent)
{

}

C_Absence::~C_Absence()
{
}

void C_Absence::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_Absence, CDialogEx)
END_MESSAGE_MAP()


// C_Absence 消息处理程序
