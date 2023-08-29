#ifndef _LIBWASM_API_H_
#define  _LIBWASM_API_H_

#define wasmExport __attribute__((visibility("default"))) 


void	wasmFetch(const char *url, void *component, int (*handler)(void *component, StringBuffer sb));
int	wasmApiInit();
void	render(void *trash);

#endif
