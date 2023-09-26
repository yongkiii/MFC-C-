#include "pch.h"
#include "InfoManager.h"

InfoManager InfoManager::im;
InfoManager& InfoManager::GetInfoManager()
{
	return im;
}

InfoManager::InfoManager()
{
	last_ino = 0;
}

int InfoManager::GetNextInfoNo()
{
	return last_ino + 1;
}

bool InfoManager::AddInfo(CString process, CString name, CString image, COleDateTime date)
{
	last_ino++;
	Info* info = new Info(last_ino, process, name, image, date);
	info_map[last_ino] = info;

	/*
	���� �߰��� ������ �˰��� �ϴ� �̵鿡�� �뺸�ϴ� �ڵ尡 �ʿ��� ��
	*/
	AIlter seek = aihandlers.begin();
	AIlter end = aihandlers.end();
	for (; seek != end; ++seek)
	{
		(*seek)->AddedInfo(info); //���� �߰� ����� �뺸�Ѵ�.
	}
	return true;

}

void InfoManager::GetInfoNoList(NList* sn_list)
{
	Info* info = 0;
	Ilter seek = info_map.begin();
	Ilter end = info_map.end();
	for (; seek != end; ++seek)
	{
		info = (*seek).second;	//�� info������ = *seek
		if (info)	//���� ��ȿ�ϴٸ�
		{
			sn_list->push_back((*seek).first);	//info->GetNo()
		}
	}
}

Info* InfoManager::GetInfo(int no)
{
	return info_map[no];		//��ȣ�� �ش��ϴ� ��ü ��ȯ
}
void InfoManager::AddAIEventHandler(AddInfoEventHandler* aieh)
{
	aihandlers.push_back(aieh);
}

void InfoManager::AddRIEventHandler(RemoveInfoEventHandler* rieh)
{
	rihandlers.push_back(rieh);
}

void InfoManager::AddMIEventHandler(ModifyInfoEventHandler* mieh)
{
	mihandlers.push_back(mieh);
}

bool InfoManager::RemoveInfo(int ino)
{
	Info* info = info_map[ino];
	if (info)
	{
		delete info;
		info_map[ino] = 0;
		RIIter seek = rihandlers.begin();
		RIIter end = rihandlers.end();
		for (; seek != end; ++seek)
		{
			(*seek)->RemovedInfo(ino);
		}
		return true;
	}
	return false;

}

bool InfoManager::ModifyInfo(int ino, CString process, CString name, CString image, COleDateTime date)
{
	Info* info = info_map[ino];
	if (info)
	{
		info->SetProcess(process);
		info->SetName(name);
		info->SetImage(image);
		info->SetDate(date);
		//info->SetDate(date);
		MIIter seek = mihandlers.begin();
		MIIter end = mihandlers.end();
		for (; seek != end; ++seek)
		{
			(*seek)->ModifiedInfo(info);

		}
		return true;
		
	}
	return false;
}