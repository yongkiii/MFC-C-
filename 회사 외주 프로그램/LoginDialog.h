#pragma once
#include "afxdialogex.h"
#include "Member.h"
#include "EndDialogEventHandler.h"
// LoginDialog ��ȭ ����

class LoginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDialog)
	EndDialogEventHandler* eld;
	//CRect m_image_rect;
	//CImage m_image;
	HBITMAP hbit;
public:
	LoginDialog(CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.
	virtual ~LoginDialog();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButtonLog();
	// ���̵�
	CString log_id;

	// image
	CStatic img_con;
	int log_pw;
public:
	void LoginEndedEventHandler(EndDialogEventHandler* eld); // ����
	virtual BOOL OnInitDialog(); // �ʱ�ȭ
	//virtual void OnPaint();
};
