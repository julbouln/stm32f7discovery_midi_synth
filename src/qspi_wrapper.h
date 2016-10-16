#ifndef _QSPI_WRAPPER_H
#define _QSPI_WRAPPER_H

#include "stm32746g_discovery_qspi.h"

typedef struct QSPI_FILE {
  size_t pos;
  size_t size;
} QSPI_FILE;

QSPI_FILE *QSPI_fopen(const char *p, const char *omode);
int QSPI_fseek ( QSPI_FILE * f, size_t offset, int origin );
int QSPI_feof(QSPI_FILE * f);
size_t QSPI_ftell(QSPI_FILE * f);
size_t QSPI_fread(void * ptr, size_t size, size_t count, QSPI_FILE * f );
void QSPI_fclose(QSPI_FILE *);

uint8_t *QSPI_mmap(size_t pos, size_t size, QSPI_FILE *f);
#endif