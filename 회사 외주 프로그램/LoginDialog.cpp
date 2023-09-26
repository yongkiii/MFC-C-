// LoginDialog.cpp: ���� ����
//

#include "pch.h"
#include "ȸ�� ���� ���α׷�.h"
#include "afxdialogex.h"
#include "LoginDialog.h"
#include "ȸ�� ���� ���α׷�Dlg.h"


// LoginDialog ��ȭ ����

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


// LoginDialog �޽��� ó����


void LoginDialog::OnBnClickedButtonLog()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	Member* mem = new Member();
	if (mem->IDPWCorrect(log_id, log_pw) == true)
	{
		MessageBox(TEXT("�α��� ����"), TEXT("�α���"), MB_OK);
		CDialog::OnOK();
	}
	else
	{
		MessageBox(TEXT("�α��� ����"), TEXT("�α���"), MB_OK);

		//CDialog::OnCancel();
	}
}
void LoginDialog::LoginEndedEventHandler(EndDialogEventHandler* eld)
{
	this->eld = eld;
}

//���� �ٸ� oncancel
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

	// �̹��� ���� ���

	hbit = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), L"C:/Users/BIT/Desktop/��� ������/AP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	img_con.SetBitmap(hbit);
	return TRUE;
	// ��ȭ
}
//void LoginDialog::OnPaint()
//{
   // CPaintDC dc(this); // ��ȭ ������ Device Context�� ����ϴ�.

   // // �̹��� ���� ���
   // CString imagePath = _T("C:/Users/BIT/Desktop/��� ������/AP.bmp);

   // // �̹����� �ε��մϴ�.
   // CImage image;
   // if (image.Load(imagePath) == S_OK)
   // {
   //	 // �̹����� Ȯ�� �Ǵ� ����Ͽ� �׸� ũ�⸦ �����մϴ�.
   //	 int destWidth = 200; // ���ϴ� ���� ũ��
   //	 int destHeight = 150; // ���ϴ� ���� ũ��

   //	 // �̹����� �׸� ��ġ�� ũ�⸦ �����մϴ�.
   //	 CRect destRect(10, 10, 10 + destWidth, 10 + destHeight);

   //	 // �̹����� Ȯ�� �Ǵ� ����Ͽ� �׸��ϴ�.
   //	 image.StretchBlt(dc.m_hDC, destRect, SRCCOPY);
   // }
//}
