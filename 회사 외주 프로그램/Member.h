#pragma once

class Member
{
private:
	CString log_name = L"±¸º»¿ë";
	int  log_pw = 1234;

public:
	Member(CString log_name, int log_pw);

	CString GetLogName();
	int GetPW();
	bool IDPWCorrect(CString log_name, int log_pw);
	Member();
};

