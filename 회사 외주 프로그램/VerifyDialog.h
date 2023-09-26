#pragma once
#include "afxdialogex.h"
#include "AddInfoEventHandler.h"
#include "회사 외주 프로그램Dlg.h"

// VerifyDialog 대화 상자

class VerifyDialog : public CDialogEx, public AddInfoEventHandler, public RemoveInfoEventHandler
{
	DECLARE_DYNAMIC(VerifyDialog)

public:
	VerifyDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~VerifyDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VERIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CComboBox cbox_no;
	CString process;
	CString name;
	COleDateTime date;
	CStatic pbox_img;
	CString image;
	CString currentTime;
	
public:
	virtual BOOL OnInitDialog();
	virtual void AddedInfo(Info* info);
	afx_msg void OnCbnSelchangeComboSn();
	virtual void RemovedInfo(int ino);

	afx_msg void OnBnClickedButtonCancel();
};
