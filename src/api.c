#include <stdlib.h>
#include <string.h>
#include <abd/AString.c.h>
#include <abd/errLog.h>
//#include <helium/He.h>

#include <awtk/api.h>

//extern He AppRender();

// JS API
//extern void fbackRenderWasm(AString w);
extern void wasmFetch__(AString st, void *component, int (*handler)(void *component, AString));

//static int (*globalHandlerHook)(int type, void *component, AString value);
static eventHandlerHook_t *globalHandlerHook;


// Most of the functions here will be called by JS, end is not required by C code itself.
// Because of this, there is a chance the the object file will not be included in linking
// This is a trick to force .o (end all functions defined here to be included):
// This function needs to be called from main module so the whole object file is included
int wasmApiInit()
{
	// useless number :-)
	// means nothing
	errLogf("wasmApiInit");
	globalHandlerHook = NULL;
	return 764;
}

//void awtkRegisterGlobalHandlerHook(int (*hook)(int type, void *component, AString value))
void awtkRegisterGlobalHandlerHook(eventHandlerHook_t *hook)
{
	globalHandlerHook = hook;
}

wasmExport
//int globalHandler(int (*handler)(void *component, AString value), void *component, AString value)
int globalHandler_(AString type, HEventHandler_t handler, void *component, AString value)
{
int ret;

	if(handler==NULL) return -1;
	ret = handler(type, component, value);
	if(globalHandlerHook) globalHandlerHook(AWTK_REGULAR_HANDLER, type, component, value);
	return ret;
}

wasmExport
int globalFetchHandler2(AString sb, void *component, int (*handler)(void *component, AString sb))
{
int ret;

	errLogf(aStringGetBuffer(sb));
	ret = handler(component, sb);
	if(globalHandlerHook) globalHandlerHook(AWTK_FETCH_HANDLER, NULL, component, sb);
	return ret;
}

void wasmFetch(const char *url, void *component, int (*handler)(void *component, AString sb))
{
	AString st = CNew(AString,strlen(url)+1);
	aStringAddStr(st, url);
	wasmFetch__(st, component, handler);	
	AStringFree(st);
}


// Warpping String Buffer Method to access from JS
//

wasmExport
AString AStringNew_(int initialSize)
{
AString sb;

	sb = CNew(AString, initialSize);
	//errLogf("String Buffer new : %p %d", sb, initialSize);
	return sb;
}

wasmExport
void aStringFree_(AString w)
{
	//errLogf("String Buffer free: %p", w);
	if(nullAssert(w)) return;
	AStringFree(w);
}

wasmExport
void aStringHardsetLength_(AString w, int len)
{
	//errLogf("String Buffer hardset: %d", len);
	if(nullAssert(w)) return;
	aStringHardsetLength(w, len);
}

wasmExport
int aStringLength_(AString w)
{
	if(nullAssert(w)) return 0;
	return aStringLength(w);
}

wasmExport
char *aStringGetBuffer_(AString w)
{
	if(nullAssert(w)) return NULL;
	return aStringGetBuffer(w);
}

