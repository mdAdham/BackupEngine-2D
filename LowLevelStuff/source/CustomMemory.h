#pragma once
#include "MemoryManagement.h"

struct MemoryAlocateData
{
	virtual size_t Get() = 0;
};

struct EntityAllocData : public MemoryAlocateData
{
	size_t Get() override
	{

	}
};

class Memory
{
private:

public:
	virtual void Allocate(MemoryAlocateData* data)
	{
		//ent = malloc(data->Get());
	}
};

class GameMemory : public Memory
{
private:
	void Allocate(MemoryAlocateData* data) override
	{

	}
};