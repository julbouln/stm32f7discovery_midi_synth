#ifndef FF_WRAPPER_H
#define FF_WRAPPER_H

#include "ff_gen_drv.h"


FIL *ff_fopen(const char *, const char *);
size_t ff_fread ( void * , size_t , size_t , FIL *  );
int ff_fseek ( FIL *, long int, int );
void ff_fclose(FIL *);

#endif
