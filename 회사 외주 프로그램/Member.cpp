#include "pch.h"
#include "Member.h"


Member::Member(CString log_name, int log_pw)
{
	this->log_name = log_name;
	this->log_pw = log_pw;
}

CString Member::GetLogName()
{
	return log_name;
}

int Member::GetPW()
{
	return log_pw;
}

bool Member::IDPWCorrect(CString log_name, int log_pw)
{
	if ((this->log_name == log_name) && (this->log_pw == log_pw))
	{
		return true;
	}
	else
		return false;
}

Member::Member()
{

}