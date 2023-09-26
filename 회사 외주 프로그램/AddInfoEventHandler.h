#pragma once
class Info;

class AddInfoEventHandler
{
public:
	virtual void AddedInfo(Info* info) = 0;
};

class RemoveInfoEventHandler
{
public:
	virtual void RemovedInfo(int ino) = 0; 
};

class ModifyInfoEventHandler
{
public:
	virtual void ModifiedInfo(Info* info) = 0;
};