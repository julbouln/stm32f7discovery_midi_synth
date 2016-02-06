#include "ff_wrapper.h"

#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>

FIL *ff_fopen(const char *p, const char *omode) {
	FIL *file;
	file = (FIL *)malloc(sizeof(FIL));
/*
	int		fRead	= 0;
	int		fWrite	= 0;
	int		fPlus	= 0;
	int		fAppend	= 0;
	int		fBad	= 0;
	BYTE	mode	= 0;
	char	c;

	while ((c = *(omode++)) != 0)
	{
		switch (c)
		{
		case 'r':								// read mode
			fRead = 1;
			break;
		case 'w':								// write mode
			fWrite = 1;
			break;
		case '+':								// extends read+write
			fPlus = 1;
			break;
		case 'a':								// append mode
			fAppend = 1;
			break;
		case 'b':								// binary :: not yet implemented
//				fBinary = 1;
			break;
		default:
			fBad = 1;
			break;
		}
	}
	if (fBad)
		;
	else if (fRead)
	{
		if (fWrite == 0 && fAppend == 0)
		{
			mode  =	FA_READ | FA_OPEN_EXISTING |
			        (fPlus ? FA_WRITE : 0);
		}
	}
	else if (fWrite)
	{
		if (fAppend == 0)
		{
			mode  =	FA_WRITE | FA_CREATE_ALWAYS |
			        (fPlus ? FA_READ : 0);
		}
	}
	else if (fAppend)
	{
		// not fully implemented!! normally write is always at end of file ...
		mode  =	FA_WRITE | FA_OPEN_ALWAYS |
		        (fPlus ? FA_READ : 0);
	}
*/

	if (f_open(file, p, FA_READ) == FR_OK) {
		return file;
	} else {
		free(file);
		return NULL;
	}
}

size_t ff_fread ( void * ptr, size_t size, size_t count, FIL * f ) {
	unsigned int l;
	f_read(f, ptr, count * size, &l);
	return (size_t)(l/size);
}

int ff_fseek ( FIL * f, long int offset, int origin ) {
	long int pos = 0;

	switch (origin) {
	case SEEK_CUR:
		pos = f_tell(f) + offset;
		break;
	case SEEK_SET:
		pos = offset;
		break;
	case SEEK_END:
		pos = f_size(f) + offset;
		break;
	}
	if (f_lseek(f, pos) == FR_OK)
		return 0;
	else
		return 1;
}

void ff_fclose(FIL *f) {
	f_close(f);
	free(f);
}