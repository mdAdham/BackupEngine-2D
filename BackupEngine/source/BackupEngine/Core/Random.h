#pragma once
#ifdef CORESTUFF_EXPORTS
#define CORESTUFF_API 
#else
#define CORESTUFF_API 
#endif

namespace Utility::Core
{
	namespace Random
	{
		CORESTUFF_API int Int();
		CORESTUFF_API int Int(int min, int max);
		CORESTUFF_API float Float();
		CORESTUFF_API float Float(float min, float max);
	}
}