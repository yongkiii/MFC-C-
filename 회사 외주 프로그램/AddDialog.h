#pragma once
#include "afxdialogex.h"
#include "EndDialogEventHandler.h"
#include <afxdb.h> // 이것은 DB연결 할때

// AddDialog 대화 상자

class AddDialog : public CDialogEx
{
	EndDialogEventHandler* eeh;
	DECLARE_DYNAMIC(AddDialog)

public:
	AddDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif
public:
	void AddEndedEventHandler(EndDialogEventHandler* eeh);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
public:
	int sn;
	CString process;
	CString name;
	CString image;
	COleDateTime date;
	CStatic pic_con;
	CString currentTime;
	afx_msg void OnBnClickedButtonImg();
	afx_msg void OnBnClickedButtonAdd();

private:
	void InitControls();
public:
	virtual BOOL OnInitDialog();
	

	afx_msg void OnBnClickedButtonCancel();
};
