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
	DDX_Control(pDX, IDC_EDIT3, m_gender);
	DDX_Control(pDX, IDC_EDIT4, m_ID);
	DDX_Control(pDX, IDC_EDIT5, m_major);
}


BEGIN_MESSAGE_MAP(C_Information, CDialogEx)
	
	ON_BN_CLICKED(IDC_BT_Updata, &C_Information::OnBnClickedBtUpdata)
	ON_BN_CLICKED(IDC_BUTTON2, &C_Information::OnBnClickedButton2)
END_MESSAGE_MAP()


// C_Information 消息处理程序





void C_Information::getInfo(SQL::info& Info)
{
	user = Info;
}

CString C_Information::getCString(CEdit* staticCtrl)
{
	// 获取静态文本框文本长度
	int textLength = staticCtrl->GetWindowTextLength();

	// 创建一个缓冲区来存储文本
	CString buffer;
	buffer.GetBufferSetLength(textLength+1);
	staticCtrl->GetWindowText(buffer);

	// 释放缓冲区，并将文本赋值给 str
	buffer.ReleaseBuffer();
	return buffer;
}

BOOL C_Information::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	db.setDB("SQL/database/Info.db");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void C_Information::OnBnClickedBtUpdata()
{
	user.ID = SQL::ConvertUnicodeToUTF8(getCString(&m_ID));
	user.gender = SQL::ConvertUnicodeToUTF8(getCString(&m_gender));
	user.major = SQL::ConvertUnicodeToUTF8(getCString(&m_major));
	// TODO: 在此添加控件通知处理程序代码
	std::string data =	  "ID = '" + user.ID + "', "
					+ "gender = '" + user.gender + "', "
					 + "major = '" + user.major + "' ";
	std::string where = "name = '" + user.name + "' ";
	db.updateData("Info", data.c_str(), where.c_str());
	MessageBox(_T("修改成功"));
	C_Show show;
	show.getInfo(user);
	show.DoModal();
	CDialogEx::OnCancel();
}


void C_Information::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	C_Show show;
	show.getInfo(user);
	show.DoModal();
	CDialogEx::OnCancel();
	
}
