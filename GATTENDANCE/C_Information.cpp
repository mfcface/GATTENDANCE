// C_Information.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "C_Information.h"
#include "afxdialogex.h"


// C_Information 对话框

IMPLEMENT_DYNAMIC(C_Information, CDialogEx)

C_Information::C_Information(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFORMATION, pParent)
{

}

C_Information::~C_Information()
{
}

void C_Information::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_Information, CDialogEx)
END_MESSAGE_MAP()


// C_Information 消息处理程序
