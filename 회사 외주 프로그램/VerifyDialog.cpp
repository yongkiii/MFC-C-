
// VerifyDialog.cpp: 구현 파일
//

#include "pch.h"
#include "회사 외주 프로그램.h"
#include "afxdialogex.h"
#include "VerifyDialog.h"
#include "InfoManager.h"

// VerifyDialog 대화 상자

IMPLEMENT_DYNAMIC(VerifyDialog, CDialogEx)

VerifyDialog::VerifyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VERIFY, pParent)
	, process(_T(""))
	, name(_T(""))
{
	COleDateTime currentTime = COleDateTime::GetCurrentTime();
	CString date = currentTime.Format(_T("%Y년%m월%d일"));
}

VerifyDialog::~VerifyDialog()
{
}

void VerifyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SN, cbox_no);
	DDX_Text(pDX, IDC_EDIT_PROCESS, process);
	DDX_Text(pDX, IDC_EDIT_NAME, name);
	DDX_Text(pDX, IDC_EDIT_DATE, date);
	DDX_Control(pDX, IDC_STATIC_IMG, pbox_img);
	
}


BEGIN_MESSAGE_MAP(VerifyDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_SN, &VerifyDialog::OnCbnSelchangeComboSn)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &VerifyDialog::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// VerifyDialog 메시지 처리기


BOOL VerifyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	 /*TODO:  여기에 추가 초기화 작업을 추가합니다.*/

	InfoManager& im = InfoManager::GetInfoManager();
	im.AddAIEventHandler(this);		// 추가하면 나한테 알려줘
	im.AddRIEventHandler(this);		// 삭제하면 나한테 알려줘
	NList* nlist = new NList();
	im.GetInfoNoList(nlist);
	Nlter seek = nlist->begin();
	Nlter end = nlist->end();
	wchar_t buf[256];
	for (; seek != end; ++seek)
	{
		wsprintf(buf, TEXT("%d"), (*seek));
		cbox_no.AddString(buf);
	}
	return TRUE;
}

void VerifyDialog::AddedInfo(Info* info)
{
	wchar_t buf[256];
	wsprintf(buf, TEXT("%d"), info->GetNo());
	cbox_no.AddString(buf);

}

void VerifyDialog::OnCbnSelchangeComboSn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = cbox_no.GetCurSel();
	if (index == -1)
	{
		process = TEXT("");
		name = TEXT("");
		date.SetDate(2023, 9, 20);
	}
	else
	{
		CString nos;
		cbox_no.GetLBText(index, nos);		//변수 그대로 전달
		int sn = _wtoi(nos);
		InfoManager& im = InfoManager::GetInfoManager();
		Info* info = im.GetInfo(sn);
		if (info == 0)
		{
			throw  "버그 잡아";
		}
		process = info->GetProcess();
		name = info->GetName();
		date = info->GetDate();
	
		
		//image = info->GetImage();
		CImage cimg;
		cimg.Load(info->GetImage());
		CDC* cdc = pbox_img.GetDC();
		RECT rt;
		pbox_img.GetClientRect(&rt);
		cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
	}
	UpdateData(0);
}

void VerifyDialog::RemovedInfo(int ino)
{
	int cnt = cbox_no.GetCount();
	int ino2;
	CString nos;
	for (int i = 0; i < cnt; i++)
	{
		cbox_no.GetLBText(i, nos);
		ino2 = _wtoi(nos);
		if (ino = ino2)
		{
			cbox_no.DeleteString(i);
			return;
		}
	}
}


void VerifyDialog::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_SN);
	pComboBox->SetCurSel(-1);

	CEdit* pEditControl = (CEdit*)GetDlgItem(IDC_EDIT_PROCESS);
	pEditControl->SetWindowText(_T(""));

	CEdit* pEditControl2 = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	pEditControl2->SetWindowTextW(_T(""));

	CEdit* pEditControl3 = (CEdit*)GetDlgItem(IDC_EDIT_DATE);
	pEditControl3->SetWindowText(_T(""));


	CString imagePath = TEXT("C:/Users/BIT/Desktop/기업 사진들/noimage.bmp"); // "your_image.bmp"를 실제 이미지 파일 이름으로 변경

	CImage cimg;
	if (cimg.Load(imagePath) == S_OK)
	{
		CDC* cdc = pbox_img.GetDC();
		RECT rt;
		pbox_img.GetClientRect(&rt);

		cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
		pbox_img.ReleaseDC(cdc);
	}

}
