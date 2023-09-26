#pragma once
#include "afxdialogex.h"
#include "Member.h"
#include "EndDialogEventHandler.h"
// LoginDialog 대화 상자

class LoginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDialog)
	EndDialogEventHandler* eld;
	//CRect m_image_rect;
	//CImage m_image;
	HBITMAP hbit;
public:
	LoginDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LoginDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButtonLog();
	// 아이디
	CString log_id;

	// image
	CStatic img_con;
	int log_pw;
public:
	void LoginEndedEventHandler(EndDialogEventHandler* eld); // 전달
	virtual BOOL OnInitDialog(); // 초기화
	//virtual void OnPaint();
};
