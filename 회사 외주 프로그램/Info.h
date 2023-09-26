#pragma once
class Info
{
	 int no;
	CString process;
	CString name;
	CString image;
	COleDateTime date;
public:
	Info(int no, CString process, CString name, CString image, COleDateTime date);	
	int GetNo();
	CString GetProcess();
	CString GetName();
	CString GetImage();
	COleDateTime GetDate();
	Info();	
	void SetNo(int no);
	void SetProcess(CString process);
	void SetName(CString name);
	void SetImage(CString image);
	void SetDate(COleDateTime date);
};

