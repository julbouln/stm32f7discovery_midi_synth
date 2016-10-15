#include "qspi_wrapper.h"
#include "main.h"

// do not really open a file
QSPI_FILE *QSPI_fopen(const char *p, const char *omode) {  
  QSPI_FILE *file=(QSPI_FILE *)malloc(sizeof(QSPI_FILE));
  file->pos=0;
//  file->size=8*1024*1024;
  file->size=4174814;
  return file;
}

inline int QSPI_fseek ( QSPI_FILE * f, size_t offset, int origin ) {
  switch (origin) {
  case SEEK_CUR:
    f->pos = f->pos + offset;
    break;
  case SEEK_SET:
    f->pos = offset;
    break;
  case SEEK_END:
    f->pos = f->size + offset;
    break;
  }

  return 0;
}

int QSPI_feof(QSPI_FILE * f) {
  if(f->pos==f->size) {
    return 1;
  } else {
    return 0;
  }
}

inline size_t QSPI_ftell(QSPI_FILE * f) {
  return f->pos;
}

void QSPI_fclose(QSPI_FILE *f) {
  free(f);
}

#ifdef QSPI_MEMORY_MAPPED

__IO uint8_t *qspi_addr = (__IO uint8_t *)(0x90000000);

inline uint8_t *QSPI_mmap(size_t pos) {
  return (uint8_t *)(qspi_addr + pos);
}

inline size_t QSPI_fread(void * ptr, size_t size, size_t count, QSPI_FILE * f ) {
  size_t max_size=count*size;
  uint8_t *buf = (uint8_t *)ptr;

  if(f->pos + count*size > f->size)
    max_size=f->size - f->pos;

  memcpy(buf,(uint8_t *)(qspi_addr + f->pos),max_size);

  f->pos+=max_size;
  return count;
}


#else

inline size_t QSPI_fread(void * ptr, size_t size, size_t count, QSPI_FILE * f ) {
  size_t max_size=count*size;
  uint8_t *buf = (uint8_t *)ptr;

  if(f->pos + count*size > f->size)
    max_size=f->size - f->pos;

  if(BSP_QSPI_Read(buf, f->pos, max_size) != QSPI_OK) {
    return -1;
  } else {
    f->pos+=max_size;
    return count;
  }
  

}


#endif