
#ifndef __USB_MIDI_CORE_H
#define __USB_MIDI_CORE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup USBD_Midi
  * @brief This file is the header file for usbd_Midi_core.c
  * @{
  */ 


/** @defgroup USBD_Midi_Exported_Defines
  * @{
  */ 
#define MIDI_EPIN_ADDR                 0x81
#define MIDI_EPIN_SIZE                 0x10

#define USB_MIDI_CONFIG_DESC_SIZ       0x65

#define   MIDI_OUT_EP         0x01
#define   MIDI_IN_EP          0x81
#define   MIDI_DATA_IN_PACKET_SIZE  0x40
#define   MIDI_DATA_OUT_PACKET_SIZE 0x40

#define MIDI_BUF_SIZE 64


extern USBD_ClassTypeDef  USBD_Midi_ClassDriver;

typedef struct _USBD_Midi_Itf
{
  int8_t (* Receive)       (uint8_t *, uint32_t);  

}USBD_Midi_ItfTypeDef;


typedef struct
{
  
  uint8_t rxBuffer[MIDI_BUF_SIZE];
  uint32_t rxLen;
}
USBD_Midi_HandleTypeDef; 


uint8_t  USBD_Midi_RegisterInterface  (USBD_HandleTypeDef   *pdev, 
                                      USBD_Midi_ItfTypeDef *fops);

#ifdef __cplusplus
}
#endif

#endif  /* __USB_MIDI_CORE_H */
