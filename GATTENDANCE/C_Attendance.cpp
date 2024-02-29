// C_Attendance.cpp: 实现文件
//

#include "pch.h"
#include "GATTENDANCE.h"
#include "C_Attendance.h"
#include "afxdialogex.h"


// C_Attendance 对话框

IMPLEMENT_DYNAMIC(C_Attendance, CDialogEx)

C_Attendance::C_Attendance(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ATTENDANCE, pParent)
{

}

C_Attendance::~C_Attendance()
{
}

void C_Attendance::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_Attendance, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_ON, &C_Attendance::OnBnClickedButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &C_Attendance::OnBnClickedButtonOff)
END_MESSAGE_MAP()


// C_Attendance 消息处理程序



CStatic* m_pDynamicText1;
CStatic* m_pDynamicText2;
CStatic* m_pDynamicText3;
void C_Attendance::OnBnClickedButtonOn()
{
    // TODO: 在此添加控件通知处理程序代码
    COleDateTime currentTime = COleDateTime::GetCurrentTime();
    CString strTime = currentTime.Format(L"%Y-%m-%d %H:%M:%S");

    if (m_pDynamicText1 == nullptr)
    {
        // 创建一个新的静态文本控件
        m_pDynamicText1 = new CStatic;
        m_pDynamicText1->Create(strTime, WS_CHILD | WS_VISIBLE, CRect(20, 50, 300, 70), this);
        m_pDynamicText1->SetParent(this);
    }
    else
    {
        // 更新现有控件的文本内容
        m_pDynamicText1->SetWindowText(strTime);
    }
}


void C_Attendance::OnBnClickedButtonOff()
{
    // TODO: 在此添加控件通知处理程序代码
    if (m_pDynamicText1 != nullptr)
    {
        // 获取之前按钮获取的时间
        CString strTime;
        m_pDynamicText1->GetWindowText(strTime);
        COleDateTime prevTime;
        prevTime.ParseDateTime(strTime);

        // 获取当前时间
        COleDateTime currentTime = COleDateTime::GetCurrentTime();
        CString currentTime2 = currentTime.Format(L"%Y-%m-%d %H:%M:%S");
        if (m_pDynamicText2 == nullptr)
        {
            // 创建一个新的静态文本控件
            m_pDynamicText2 = new CStatic;
            m_pDynamicText2->Create(currentTime2, WS_CHILD | WS_VISIBLE, CRect(20, 70, 200, 90), this);
            m_pDynamicText2->SetParent(this);
        }
        else
        {
            // 更新现有控件的文本内容
            m_pDynamicText2->SetWindowText(currentTime2);
        }
        // 计算时长
        COleDateTimeSpan duration = currentTime - prevTime;
        CString strDuration = duration.Format(L"%H:%M:%S");

        if (m_pDynamicText3 == nullptr)
        {
            // 创建一个新的静态文本控件
            m_pDynamicText3 = new CStatic;
            m_pDynamicText3->Create(strDuration, WS_CHILD | WS_VISIBLE, CRect(220, 50, 400, 70), this);
            m_pDynamicText3->SetParent(this);
        }
        else
        {
            // 更新现有控件的文本内容
            m_pDynamicText3->SetWindowText(strDuration);
        }
    }
}

