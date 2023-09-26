// AddDialog.cpp: 구현 파일
//

#include "pch.h"
#include "InfoManager.h"
#include "회사 외주 프로그램.h"
#include "afxdialogex.h"
#include "AddDialog.h"



// AddDialog 대화 상자

IMPLEMENT_DYNAMIC(AddDialog, CDialogEx)

AddDialog::AddDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, sn(0)
	, process(_T(""))
	, name(_T(""))
	,image(_T(""))
	
	
{
	eeh = 0;
	 date = COleDateTime::GetCurrentTime();
	currentTime = date.Format(_T("%Y-%m-%d"));
	
}


AddDialog::~AddDialog()
{
}

void AddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_STATIC_SN, sn);
	DDX_Text(pDX, IDC_EDIT_PROCESS, process);
	DDX_Text(pDX, IDC_EDIT_NAME, name);
	DDX_Control(pDX, IDC_STATIC_IMG, pic_con);
	DDX_Text(pDX, IDC_EDIT_DATE, date);
}

BEGIN_MESSAGE_MAP(AddDialog, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_IMG, &AddDialog::OnBnClickedButtonImg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &AddDialog::OnBnClickedButtonAdd)

	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &AddDialog::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// AddDialog 메시지 처리기

void AddDialog::AddEndedEventHandler(EndDialogEventHandler* eeh)
{
	this->eeh = eeh;
}



void AddDialog::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (eeh)
	{
		eeh->EndedDialog();		//나 죽음을 통보
	}
	CDialogEx::OnCancel();
}


void AddDialog::OnBnClickedButtonImg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* fod = new CFileDialog(TRUE, 0);
	int re = fod->DoModal();
	if (re != IDOK)//
	{
		return;
	}

	image = fod->GetPathName();
	CImage cimg;
	cimg.Load(image);
	CDC* cdc = pic_con.GetDC();
	RECT rt;
	pic_con.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}


void AddDialog::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	CDatabase db;
	InfoManager& im = InfoManager::GetInfoManager();	
	bool re = db.OpenEx(TEXT("DSN=LocalSQL; uid=scott;PWD=tiger"));
	if (re == FALSE)
	{
		return;
	}
	wchar_t query_str[256] = TEXT("");

	//wchar_t query_str1[100] = TEXT("");
	
	//query_str1.Format(date);
	//leDateTime TIME;

  // CString strCurrentTime = oleCurrentTime.Format(_T("%Y년%m월%d일"));
	wsprintf(query_str, TEXT("insert into COMPANY(CPROCESS,CNAME,CIMAGE,CDATE) values ('%s','%s','%s','%s')"), process, name, image,currentTime); // query_str에 저장
	
	db.ExecuteSQL(query_str); // 이걸 실행
	//db.ExecuteSQL(query_str1); // 이걸 실행
	
	
	//싱글톤개체 받아옴
	if (im.AddInfo(process, name, image, date) == FALSE)
	{
		MessageBox(TEXT("추가 실패"));
	}
	InitControls();
}

void AddDialog::InitControls()
{
	process = TEXT("");
	name = TEXT("");
	image = TEXT("");
	UpdateData(FALSE);	//변수->컨트롤
	InfoManager& im = InfoManager::GetInfoManager();
	int sn = im.GetNextInfoNo();
	SetDlgItemInt(IDC_STATIC_SN, sn, FALSE);
}

BOOL AddDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InfoManager& im = InfoManager::GetInfoManager();
	int sn = im.GetNextInfoNo();
	SetDlgItemInt(IDC_STATIC_SN, sn, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}




void AddDialog::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	process = TEXT("");
	name = TEXT("");


	CString imagePath =TEXT("C:/Users/BIT/Desktop/기업 사진들/noimage.bmp"); // "your_image.bmp"를 실제 이미지 파일 이름으로 변경

	CImage cimg;
	if (cimg.Load(imagePath) == S_OK)
	{
		CDC* cdc = pic_con.GetDC();
		RECT rt;
		pic_con.GetClientRect(&rt);

		cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
		pic_con.ReleaseDC(cdc);
	}

	UpdateData(FALSE);

}
