// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the CORESTUFF_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// CORESTUFF_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CORESTUFF_EXPORTS
#define CORESTUFF_API __declspec(dllexport)
#else
#define CORESTUFF_API __declspec(dllimport)
#endif


// This class is exported from the dll
class CORESTUFF_API CCoreStuff {
public:
	CCoreStuff(void);
	// TODO: add your methods here.
};

extern CORESTUFF_API int nCoreStuff;

CORESTUFF_API int fnCoreStuff(void);