
// 회사 외주 프로그램Dlg.h: 헤더 파일
//

#pragma once
#include "AddDialog.h"
#include "VerifyDialog.h"
#include "ModifyDialog.h"
#include "EndDialogEventHandler.h"
#include "AddInfoEventHandler.h"
#include "Info.h"
#include "InfoManager.h"
#include <afxdb.h> // 이것은 DB연결 할때

// C회사외주프로그램Dlg 대화 상자
class C회사외주프로그램Dlg : public CDialogEx, public AddInfoEventHandler, public EndDialogEventHandler, public ModifyInfoEventHandler
{
	AddDialog* mrd;
	CString strUrl;
// 생성입니다.
public:
	C회사외주프로그램Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CString CNO;
	CString CNAME;
	CString CPROCESS;
	CString CIMAGE;
	CString CDATE;
	COleDateTime date = COleDateTime::GetCurrentTime();
//String currentTime = date.Format(_T("%Y-%m-%d"));
	
	afx_msg void OnBnClickedButtonAdd();
	virtual void EndedDialog();
	afx_msg LRESULT OnEndedAdd(WPARAM, LPARAM);
	CListCtrl blist;
	virtual void AddedInfo(Info* info);

	afx_msg void OnBnClickedButtonVerify();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonLink();

	int scroll;

	virtual void ModifiedInfo(Info* info);
	afx_msg void OnBnClickedButtonMod();
	
};
