
// 회사 외주 프로그램Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "회사 외주 프로그램.h"
#include "회사 외주 프로그램Dlg.h"
#include "afxdialogex.h"
#include "LoginDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int  VPageSize = 0;
enum MY_W_MSG
{
	MWM_ENDED_ADD = WM_APP + 1
};
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C회사외주프로그램Dlg 대화 상자



C회사외주프로그램Dlg::C회사외주프로그램Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
	, scroll(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C회사외주프로그램Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COMP, blist);
	DDX_Scroll(pDX, IDC_SCROLLBAR3, scroll);
}

BEGIN_MESSAGE_MAP(C회사외주프로그램Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(MWM_ENDED_ADD, &C회사외주프로그램Dlg::OnEndedAdd)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &C회사외주프로그램Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &C회사외주프로그램Dlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_LINK, &C회사외주프로그램Dlg::OnBnClickedButtonLink)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &C회사외주프로그램Dlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_VERIFY, &C회사외주프로그램Dlg::OnBnClickedButtonVerify)
END_MESSAGE_MAP()


// C회사외주프로그램Dlg 메시지 처리기

BOOL C회사외주프로그램Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	mrd = 0; 
	ShowWindow(SW_HIDE); // 암묵적으로 해주네
	LoginDialog lgdlg;

	InfoManager& im = InfoManager::GetInfoManager();
	if (lgdlg.DoModal() == IDOK)
	{
		ShowWindow(SW_SHOW); 
		CDatabase db;
		bool re = db.OpenEx(TEXT("DSN=LocalSQL; uid=scott;PWD=tiger"));
		if (re == FALSE)
		{
			MessageBox(TEXT("안됨"));
			//	return TRUE;
		}
		// 열이름 설정
		LPWSTR texts[4] = { TEXT("No"), TEXT("공정"), TEXT("기업명"),  TEXT("등록일자")};
		int widths[4] = { 30, 70, 100, 100 };
		//열에 관련된 구조체
		LV_COLUMN col;
		col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		col.fmt = LVCFMT_CENTER;
		// 밑에 행 항목들을 나열
		for (int i = 0; i < 4; i++)
		{
			col.pszText = texts[i];
			col.iSubItem = i;
			col.cx = widths[i];
			blist.InsertColumn(i, &col);
		}

		CRecordset rs(&db);
		rs.Open(CRecordset::forwardOnly, TEXT("select * from COMPANY"));
		int index = 0;
		Info* info = 0;
		
		while (!rs.IsEOF()) //end of file 검색할 내용이 없을때 까지
		{
			rs.GetFieldValue((short)0, CNO);
			rs.GetFieldValue((short)1, CPROCESS);
			rs.GetFieldValue((short)2, CNAME);
			
			rs.GetFieldValue((short)3, CDATE);
			rs.GetFieldValue((short)4, CIMAGE);

			blist.InsertItem(index, CNO);
			blist.SetItemText(index, 1, CPROCESS);
			blist.SetItemText(index, 2, CNAME);
			
			blist.SetItemText(index,3,CDATE);
			blist.SetItemText(index, 4, CIMAGE);
			//info->GetNo(_ttoi(CNO));
			im.AddInfo( CPROCESS,CNAME,CIMAGE, date);
			rs.MoveNext();
			index++;
		}
	}
	else
	{

		ShowWindow(SW_HIDE);
	}

	
	im.AddAIEventHandler(this); 
	im.AddMIEventHandler(this);
	

	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void C회사외주프로그램Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void C회사외주프로그램Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR C회사외주프로그램Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C회사외주프로그램Dlg::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mrd == 0)
	{
		mrd = new AddDialog();
		mrd->AddEndedEventHandler(this);
		mrd->Create(IDD_DIALOG_ADD,GetDesktopWindow());
		mrd->ShowWindow(SW_SHOW);

	}
}


void C회사외주프로그램Dlg::EndedDialog()
{
	PostMessage(MWM_ENDED_ADD, 0, 0);
}

LRESULT C회사외주프로그램Dlg::OnEndedAdd(WPARAM, LPARAM)
{
	if (mrd == 0)
	{
		delete mrd;
	}
	mrd = 0;
	return 0;
}

void C회사외주프로그램Dlg::AddedInfo(Info* info)
{
	int index = blist.GetItemCount();
	wchar_t nobuf[256];
	wsprintf(nobuf, TEXT("%d"), info->GetNo());
	blist.InsertItem(index, nobuf);

	blist.SetItemText(index, 1, info->GetProcess());
	blist.SetItemText(index, 2, info->GetName());

	CTime currentTime = CTime::GetCurrentTime();
	COleDateTime oleCurrentTime(currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay(),
		currentTime.GetHour(), currentTime.GetMinute(), currentTime.GetSecond());
	CString strCurrentTime = oleCurrentTime.Format(_T("%Y-%m-%d "));
	blist.SetItemText(index, 3, strCurrentTime);
}


void C회사외주프로그램Dlg::OnBnClickedButtonVerify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	VerifyDialog* vd = new VerifyDialog();
	vd->Create(IDD_DIALOG_VERIFY, GetDesktopWindow());
	vd->ShowWindow(SW_SHOW);
}


void C회사외주프로그램Dlg::OnBnClickedButtonDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//단일체
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=LocalSQL; uid=scott;PWD=tiger"));
	if (re == FALSE)
	{
		return;
	}
	InfoManager& im = InfoManager::GetInfoManager();
	POSITION pos = blist.GetFirstSelectedItemPosition();
	int index = blist.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}
	CString cno = blist.GetItemText(index, 0);
	int no = _wtoi(cno);
	wchar_t query_str[100] = TEXT("");
	wsprintf(query_str, TEXT("delete from company where CNO = %d"), no); // query_str에 저장
	db.ExecuteSQL(query_str); // 이걸 실행
	blist.DeleteItem(index);

	
}




void C회사외주프로그램Dlg::OnBnClickedButtonLink()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	strUrl = _T("https://www.jusung.com/");
	CLinkCtrl* pLinkCtrl = (CLinkCtrl*)GetDlgItem(IDC_SYSLINK_LINK);
	pLinkCtrl->GetItemUrl(0, strUrl);
	::ShellExecute(NULL, TEXT("open"), strUrl, NULL, NULL, SW_SHOW);
	//
}




void C회사외주프로그램Dlg::OnBnClickedButtonMod()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ModifyDialog* md = new ModifyDialog();
	md->Create(IDD_DIALOG_MOD, GetDesktopWindow());
	md->ShowWindow(SW_SHOW);
}

void C회사외주프로그램Dlg::ModifiedInfo(Info* info)
{
	int ino = info->GetNo();
	LVITEM li = { 0 };
	wchar_t buf[256] = TEXT("");
	int cnt = blist.GetItemCount();
	COleDateTime dt;
	wchar_t dtbuf[256] = TEXT("");
	for (int i = 0; i < cnt; i++)
	{
		li.iItem = i;	//i번째 항목에
		li.iSubItem = 0;
		li.mask = LVIF_TEXT;	//문자열
		li.pszText = buf;	//이 메모리에
		li.cchTextMax = 256;	//256자까지 채워줘
		blist.GetItem(&li);
		if (ino == _wtoi(buf))
		{
			blist.SetItemText(i, 1, info->GetProcess());		//바꾸는 거
			blist.SetItemText(i, 2, info->GetName());

			dt = info->GetDate();
			wsprintf(dtbuf, TEXT("%d- %d- %d"), dt.GetYear(), dt.GetMonth(), dt.GetDay());
			blist.SetItemText(i, 3, dtbuf);
			return;
		}
	}
}