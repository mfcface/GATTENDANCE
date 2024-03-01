// C_Show.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "C_Show.h"
#include "afxdialogex.h"


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

void C_Show::getInfo(SQL::info& Info)
{
	user = Info;
}


BEGIN_MESSAGE_MAP(C_Show, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_ATTENDANCE, &C_Show::OnBnClickedButtonAttendance)
	ON_BN_CLICKED(IDC_BUTTON_ABSENCE, &C_Show::OnBnClickedButtonAbsence)
	ON_BN_CLICKED(IDC_BUTTON_INFORMATION, &C_Show::OnBnClickedButtonInformation)
	ON_BN_CLICKED(IDC_BUTTON1, &C_Show::OnBnClickedButton1)
END_MESSAGE_MAP()


// C_Show 消息处理程序



void C_Show::OnBnClickedButtonAttendance()
{
	// TODO: 在此添加控件通知处理程序代码
	C_Attendance att;
	att.DoModal();
	CDialogEx::OnCancel();
}


void C_Show::OnBnClickedButtonAbsence()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void C_Show::OnBnClickedButtonInformation()
{
	// TODO: 在此添加控件通知处理程序代码
	C_Information inf;
	inf.getInfo(user);
	CDialogEx::OnCancel();
	inf.DoModal();
	
}


void C_Show::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL C_Show::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//info
	m_id.SubclassDlgItem(IDC_ST_ID, this);
	m_name.SubclassDlgItem(IDC_ST_NAME, this);
	m_gender.SubclassDlgItem(IDC_ST_GENDER, this);
	m_major.SubclassDlgItem(IDC_ST_MAJOR, this);

	m_id.SetWindowText(SQL::Utf8ToCString(user.ID));
	m_name.SetWindowText(SQL::Utf8ToCString(user.name));
	m_gender.SetWindowText(SQL::Utf8ToCString(user.gender));
	m_major.SetWindowText(SQL::Utf8ToCString(user.major));
	//========

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

