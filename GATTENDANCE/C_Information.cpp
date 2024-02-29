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
	ON_BN_CLICKED(IDC_EDIT3, &C_Information::OnBnClickedEdit3)
END_MESSAGE_MAP()


// C_Information 消息处理程序


void C_Information::OnBnClickedEdit3()
{
	// TODO: 在此添加控件通知处理程序代码

}


BOOL C_Information::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	db.setDB("SQL/database/userInfo.db");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
