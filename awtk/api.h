#ifndef _AWTK_API_H_
#define _AWTK_API_H_

#define wasmExport __attribute__((visibility("default"))) 

#define AWTK_REGULAR_HANDLER 1
#define AWTK_FETCH_HANDLER   2

void	wasmFetch(const char *url, void *component, int (*handler)(void *component, StringBuffer sb));
void	awtkRegisterGlobalHandlerHook(int (*hook)(int type, void *component, StringBuffer value));
int	wasmApiInit();

extern void fbackRenderWasm(StringBuffer id, StringBuffer str);

#endif
