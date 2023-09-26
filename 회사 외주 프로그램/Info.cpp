#include "pch.h"
#include "Info.h"

Info::Info(int no, CString process, CString name, CString image, COleDateTime date) : no(no)
{
	this->process = process;
	this->name = name;
	this->image = image;
	this->date = date;
}
Info::Info(): no(no)
{
	//this->no = no;
	this->process = process;
	this->name = name;
	this->image = image;
	this->date = date;
}
int Info::GetNo()
{
	return no;
}
CString Info::GetProcess()
{
	return process;
}
CString Info::GetName()
{
	return name;
}
CString Info::GetImage()
{
	return image;
}
COleDateTime Info::GetDate()
{
	return date;
}

void Info::SetProcess(CString process)
{
	this->process = process;
}
void Info::SetName(CString name)
{
	this->name = name;
}
void Info::SetImage(CString image)
{
	this->image = image;
}
void Info::SetDate(COleDateTime date)
{
	this->date = date;
}
void Info::SetNo(int no)
{
	this->no = no;
}