#pragma once

#include "Info.h"
#include "AddInfoEventHandler.h"
#include <map>
#include <list>

using std::map;
using std::list;

typedef map<int, Info*>IMap;

typedef list<int> NList;
typedef NList::iterator Nlter;

typedef IMap::iterator Ilter;

typedef list <AddInfoEventHandler*> AIHList;
typedef AIHList::iterator AIlter;

typedef list<RemoveInfoEventHandler*> RIHList;
typedef RIHList::iterator RIIter;

typedef list<ModifyInfoEventHandler*> MIHList;
typedef MIHList::iterator MIIter;

class InfoManager
{
	IMap info_map;
	int last_ino;	//가장 최근에 부여한 번호

	AIHList aihandlers;
	RIHList rihandlers;
	MIHList mihandlers;
	static InfoManager im;	
public:
	static InfoManager& GetInfoManager();
	int GetNextInfoNo();
	bool AddInfo(CString process, CString name, CString image, COleDateTime date);
	void GetInfoNoList(NList* sn_list);
	Info* GetInfo(int no);
	

	bool RemoveInfo(int ino);
	void AddAIEventHandler(AddInfoEventHandler* aieh);	//정보 추가하면 list에 띄움
	void AddRIEventHandler(RemoveInfoEventHandler* rieh);	//정보 추가하면 list에 띄움
	void AddMIEventHandler(ModifyInfoEventHandler* mieh);	//정보 추가하면 list에 띄움
	
	bool ModifyInfo(int ino, CString process, CString name, CString image, COleDateTime date);
private:
	InfoManager();
};

