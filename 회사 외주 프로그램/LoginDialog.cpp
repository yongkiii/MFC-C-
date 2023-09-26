// LoginDialog.cpp: 구현 파일
//

#include "pch.h"
#include "회사 외주 프로그램.h"
#include "afxdialogex.h"
#include "LoginDialog.h"
#include "회사 외주 프로그램Dlg.h"


// LoginDialog 대화 상자

IMPLEMENT_DYNAMIC(LoginDialog, CDialogEx)

LoginDialog::LoginDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, log_id(_T(""))

	, log_pw(NULL)
{

}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, log_id);

	DDX_Control(pDX, IDC_STATIC_IMG, img_con);
	DDX_Text(pDX, IDC_EDIT_PW, log_pw);
}


BEGIN_MESSAGE_MAP(LoginDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &LoginDialog::OnBnClickedButtonLog)
END_MESSAGE_MAP()


// LoginDialog 메시지 처리기


void LoginDialog::OnBnClickedButtonLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	Member* mem = new Member();
	if (mem->IDPWCorrect(log_id, log_pw) == true)
	{
		MessageBox(TEXT("로그인 성공"), TEXT("로그인"), MB_OK);
		CDialog::OnOK();
	}
	else
	{
		MessageBox(TEXT("로그인 실패"), TEXT("로그인"), MB_OK);

		//CDialog::OnCancel();
	}
}
void LoginDialog::LoginEndedEventHandler(EndDialogEventHandler* eld)
{
	this->eld = eld;
}

//둘이 다른 oncancel
void LoginDialog::OnCancel()
{
	if (eld)
	{
		eld->EndedDialog();
	}
	CDialogEx::OnCancel();
}

BOOL LoginDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이미지 파일 경로

	hbit = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), L"C:/Users/BIT/Desktop/기업 사진들/AP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	img_con.SetBitmap(hbit);
	return TRUE;
	// 대화
}
//void LoginDialog::OnPaint()
//{
   // CPaintDC dc(this); // 대화 상자의 Device Context를 얻습니다.

   // // 이미지 파일 경로
   // CString imagePath = _T("C:/Users/BIT/Desktop/기업 사진들/AP.bmp);

   // // 이미지를 로드합니다.
   // CImage image;
   // if (image.Load(imagePath) == S_OK)
   // {
   //	 // 이미지를 확대 또는 축소하여 그릴 크기를 설정합니다.
   //	 int destWidth = 200; // 원하는 가로 크기
   //	 int destHeight = 150; // 원하는 세로 크기

   //	 // 이미지를 그릴 위치와 크기를 설정합니다.
   //	 CRect destRect(10, 10, 10 + destWidth, 10 + destHeight);

   //	 // 이미지를 확대 또는 축소하여 그립니다.
   //	 image.StretchBlt(dc.m_hDC, destRect, SRCCOPY);
   // }
//}
