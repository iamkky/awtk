#ifndef _AWTK_API_H_
#define _AWTK_API_H_

#include <helium/He.h>

#define wasmExport __attribute__((visibility("default"))) 

#define AWTK_REGULAR_HANDLER 1
#define AWTK_FETCH_HANDLER   2

//typedef int eventHandler_t(AString type, void *component, AString value);
typedef int HEventHandler_t(AString type, void *component, AString value);
typedef int eventHandlerHook_t(int type, AString event_type, void *component, AString value);

int	wasmApiInit();

void	awtkRegisterGlobalHandlerHook(eventHandlerHook_t *hook);

void	wasmFetch(const char *url, void *component, int (*handler)(void *component, AString sb));

extern void fbackRenderWasm(AString id, AString str);

#endif
