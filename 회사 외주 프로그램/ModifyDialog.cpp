// ModifyDialog.cpp: 구현 파일
//

#include "pch.h"
#include "회사 외주 프로그램.h"
#include "afxdialogex.h"
#include "ModifyDialog.h"




// ModifyDialog 대화 상자

IMPLEMENT_DYNAMIC(ModifyDialog, CDialogEx)

ModifyDialog::ModifyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MOD, pParent)
	, no(0)
	, process(_T(""))
	, name(_T(""))
	
{
	date = COleDateTime::GetCurrentTime();
	currentTime = date.Format(_T("%Y-%m-%d"));
}


ModifyDialog::~ModifyDialog()
{
}

void ModifyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_STATIC_SN, no);
	DDX_Text(pDX, IDC_EDIT_PROCESS, process);
	DDX_Text(pDX, IDC_EDIT_NAME, name);
	DDX_Control(pDX, IDC_STATIC_IMG, pic_con);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, date);
	DDX_Control(pDX, IDC_LIST_INFO, list_info);
}

BEGIN_MESSAGE_MAP(ModifyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IMG, &ModifyDialog::OnBnClickedButtonImg)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &ModifyDialog::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &ModifyDialog::OnBnClickedButtonCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_INFO, &ModifyDialog::OnLvnItemchangedListInfo)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &ModifyDialog::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()


// ModifyDialog 메시지 처리기
BOOL ModifyDialog::OnInitDialog()
{
	__super::OnInitDialog();
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=LocalSQL; uid=scott;PWD=tiger"));
	if (re == FALSE)
	{
		MessageBox(TEXT("안됨"));
			return TRUE;
	}
//	POSITION pos = list_info.GetFirstSelectedItemPosition();
	list_info.InsertColumn(0, TEXT("No"), 0, 50);
	list_info.InsertColumn(1, TEXT("공정"), 0, 100);
	list_info.InsertColumn(2, TEXT("이름"), 0, 150);
	list_info.InsertColumn(3, TEXT("날짜"), 0, 150);
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, TEXT("select * from COMPANY"));
	int i = 0;
	Info* info;

	//InfoManager im = InfoManager::GetInfoManager();
	while (!rs.IsEOF()) //end of file 검색할 내용이 없을때 까지
	{
		rs.GetFieldValue((short)0, CNO);
		rs.GetFieldValue((short)1, CPROCESS);
		rs.GetFieldValue((short)2, CNAME);
		rs.GetFieldValue((short)3, CDATE);
		rs.GetFieldValue((short)4, CIMAGE);

		list_info.InsertItem(i, CNO);
		list_info.SetItemText(i, 1, CPROCESS);
		list_info.SetItemText(i, 2, CNAME);
		list_info.SetItemText(i, 3, CDATE);
		list_info.SetItemText(i, 4, CIMAGE);

		rs.MoveNext();
		i++;
	}


	
	
	//Info* info =0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ModifyDialog::OnBnClickedButtonImg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* fod = new CFileDialog(true, 0);
	int re = fod->DoModal();
	if (re != IDOK)
	{
		return;
	}
	image = fod->GetPathName(); // 파일은 전체경로
	CImage cimg;
	cimg.Load(image);

	CDC* cdc = pic_con.GetDC();
	RECT rt;
	pic_con.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}


void ModifyDialog::OnBnClickedButtonMod()
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
	POSITION pos = list_info.GetFirstSelectedItemPosition();
	int index = list_info.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}
	LVITEM li = { 0 };
	li.iItem = index;
	li.iSubItem = 0;
	wchar_t nbuf[256] = TEXT("");
	li.mask = LVIF_TEXT;
	li.pszText = nbuf;
	li.cchTextMax = 256;
	list_info.GetItem(&li);

	int no = _wtoi(nbuf);
	
	Info* info = im.GetInfo(no);
	
	
	//CImage cimg;
	//cimg.Load(info->GetImage());
	//CDC* cdc = pic_con.GetDC();
	//RECT rt;
	//pic_con.GetClientRect(&rt);
	//cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);

	
	//CString cno = list_info.GetItemText(index, 0);
	wchar_t query_str[256] = TEXT("");
	wsprintf(query_str, TEXT("update COMPANY set cprocess = '%s', cname ='%s' ,cdate='%s' ,cimage = '%s' where cno =%d"), process, name, currentTime, image, no); // query_str에 저장
	db.ExecuteSQL(query_str); // 이걸 실행
	list_info.SetItemText(index, 1, process); // 해당 이름 변경
	list_info.SetItemText(index, 2, name); // 해당 가격 변경
	list_info.SetItemText(index, 3, currentTime); // 해당 설명 변경
	list_info.SetItemText(index, 4, image); // 해당 설명 변경
	info->SetProcess(process);
	info->SetName(name);
	info->SetDate(date);
	info->SetImage(image);
	
	im.ModifyInfo(no, process, name, image, date);
	
	
	
}



void ModifyDialog::AddedInfo(Info* info)
{
	int ino = info->GetNo();
	wchar_t nbuf[256] = TEXT("");
	wsprintf(nbuf, TEXT("%d"), ino);

	 process = info->GetProcess();
	 name = info->GetName();
	 date = info->GetDate();
	 image = info->GetImage();

	int i = list_info.GetItemCount();

	list_info.InsertItem(i, nbuf);

	list_info.SetItemText(i, 1, process);
	list_info.SetItemText(i, 2, name);
	list_info.SetItemText(i, 3, currentTime);
	list_info.SetItemText(i, 4, image);


}
void ModifyDialog::RemovedInfo(int ino)
{
	LVITEM li = { 0 };
	wchar_t buf[256] = TEXT("");
	int cnt = list_info.GetItemCount();
	for (int i = 0; i < cnt; i++)
	{
		li.iItem = i; // i
		li.iSubItem = 0; // 열
		li.mask = LVIF_TEXT; //text로 가져와라
		li.pszText = buf; // 이 버퍼에 얻다
		li.cchTextMax = 256;
		list_info.GetItem(&li);
		if (ino == _wtoi(buf))
		{
			list_info.DeleteItem(i);
			return;
		}


	}
}



void ModifyDialog::OnLvnItemchangedListInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnBnClickedButtonCancel();
	//CDatabase db;
	
	
}

void ModifyDialog::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = list_info.GetFirstSelectedItemPosition();
	int index = list_info.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}

	LVITEM li = { 0 };
	li.iItem = index;
	li.iSubItem = 0;
	wchar_t nbuf[256] = TEXT("");
	li.mask = LVIF_TEXT; // 데이터를 가져와야 한다는걸 알려준다
	li.pszText = nbuf;  // text 저장할 버퍼를 설정
	li.cchTextMax = 256; // 크기
	list_info.GetItem(&li); // 저 리스트 배열에서 아이템을 가져와줘
	int no = _wtoi(nbuf); //문자열에서 정수형으로 변환시켜줘
	InfoManager& im = InfoManager::GetInfoManager();
	Info* info = im.GetInfo(no);
	
	

	process = info->GetProcess();
	name = info->GetName();
	date = info->GetDate();

	SetDlgItemInt(IDC_STATIC_SN, no);
	SetDlgItemText(IDC_EDIT_PROCESS, process);
	SetDlgItemText(IDC_EDIT_NAME, name);
	SetDlgItemText(IDC_EDIT_DATE, currentTime);

	CImage cimg;
	image = info->GetImage();
	cimg.Load(image);
	CDC* cdc = pic_con.GetDC();
	RECT rt;
	pic_con.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
	UpdateData();
}

void ModifyDialog::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
