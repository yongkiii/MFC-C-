#pragma once
#include "afxdialogex.h"
#include "AddInfoEventHandler.h"
#include "InfoManager.h"
#include <afxdb.h> // 이것은 DB연결 할때
#include "회사 외주 프로그램Dlg.h"
#include "Info.h"
// ModifyDialog 대화 상자

class ModifyDialog : public CDialogEx, public AddInfoEventHandler, public RemoveInfoEventHandler
{
	DECLARE_DYNAMIC(ModifyDialog)

public:
	ModifyDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.

	virtual ~ModifyDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MOD };
#endif
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//ModifyDialog();
	int no;
	CListCtrl list_info;
	CString image;
	CString process;
	CString name;
	CStatic pic_con;
	COleDateTime date;
	CString CNO;
	CString CNAME;
	CString CPROCESS;
	CString CDATE;
	CString currentTime;
	CString CIMAGE;
	afx_msg void OnBnClickedButtonImg();
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonCancel();

	virtual void AddedInfo(Info* info); // 추가 바로 활성화 시키는거
	virtual void RemovedInfo(int ino); //// 삭제 바로 활성화 시키는거

	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	
};
