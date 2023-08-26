#pragma once
#ifdef CORESTUFF_EXPORTS
#define CORESTUFF_API __declspec(dllexport)
#else
#define CORESTUFF_API __declspec(dllimport)
#endif

struct CORESTUFF_API MemoryManagement
{
	float totalalocations = 0;
	float removedalocations = 0;

	float getActiveMemory()
	{
		return totalalocations - removedalocations;
	}
};