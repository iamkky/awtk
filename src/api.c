#include <stdlib.h>
#include <string.h>
#include <abd/StringBuffer.h>
#include <abd/errLog.h>
#include <helium/He.h>

#include <awtk/api.h>

extern He AppRender();

// JS API
//extern void fbackRenderWasm(StringBuffer w);
extern void wasmFetch__(StringBuffer st, void *component, int (*handler)(void *component, StringBuffer));

static int (*globalHandlerHook)(int type, void *component, StringBuffer value);


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

void awtkRegisterGlobalHandlerHook(int (*hook)(int type, void *component, StringBuffer value))
{
	globalHandlerHook = hook;
}

wasmExport
int globalHandler(int (*handler)(void *component, StringBuffer value), void *component, StringBuffer value)
{
int ret;

	if(handler==NULL) return -1;
	ret = handler(component, value);
	if(globalHandlerHook) globalHandlerHook(AWTK_REGULAR_HANDLER, component, value);
	return ret;
}

wasmExport
int globalFetchHandler2(StringBuffer sb, void *component, int (*handler)(void *component, StringBuffer sb))
{
int ret;

	errLogf(sb->buffer);
	ret = handler(component, sb);
	if(globalHandlerHook) globalHandlerHook(AWTK_FETCH_HANDLER, component, sb);
	return ret;
}

void wasmFetch(const char *url, void *component, int (*handler)(void *component, StringBuffer sb))
{
	StringBuffer st = StringBufferNew(strlen(url)+1);
	stringBufferAddStr(st, url);
	wasmFetch__(st, component, handler);	
	stringBufferFree(st);
}


// Warpping String Buffer Method to access from JS
//

wasmExport
StringBuffer StringBufferNew_(int initialSize)
{
	return StringBufferNew(initialSize);
}

wasmExport
void stringBufferFree_(StringBuffer w)
{
	stringBufferFree(w);
}

wasmExport
void stringBufferHardsetLength_(StringBuffer self, int len)
{
	stringBufferHardsetLength(self, len);
}

wasmExport
int stringBufferLength_(StringBuffer w)
{
	return stringBufferLength(w);
}

wasmExport
char *stringBufferGetBuffer_(StringBuffer w)
{
	return stringBufferGetBuffer(w);
}

