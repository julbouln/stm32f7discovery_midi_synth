/**
  ******************************************************************************
  * @file    FMC/FMC_SDRAM_DataMemory/Inc/main.h
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    18-November-2015 
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_sai.h"
#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_pcd.h"
#include "stm32f7xx_hal_hcd.h"
#include "stm32f7xx_hal_i2s.h"

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_audio.h"
#include "usbd_midi_if.h"

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_audio.h"
#include "stm32746g_discovery_sd.h"
#include "stm32746g_discovery_qspi.h"

#include "ff_gen_drv.h"
#include "sd_diskio.h"

#include "qspi_wrapper.h"

#include <arm_math.h>

#define MASTER_VOLUME 70

//#define SAMPLE_RATE 48000
//#define SAMPLE_RATE 96000
#define SAMPLE_RATE 44100
//#define SAMPLE_RATE 24000
#define POLYPHONY 32

//#define AUDIO_BUF_SIZE 4096
#define AUDIO_BUF_SIZE 8192 
//#define AUDIO_BUF_SIZE 16384
//#define AUDIO_BUF_SIZE 32768

//#define SOUNDFONT_FILE "4GMGSMT.SF2"
//#define SOUNDFONT_FILE "TIM.SF2"
//#define SOUNDFONT_FILE "8mbgmsfx.sf2"
//#define SOUNDFONT_FILE "CHAOSV20.sf2"
#define SOUNDFONT_FILE "CT4MGM.SF2"
//#define SOUNDFONT_FILE "MERLINSI.SF2"
//#define SOUNDFONT_FILE "MERLINCR.SF2"
//#define SOUNDFONT_FILE "32gmst.sf2"
//#define SOUNDFONT_FILE "MERLIN.SF2"
//#define SOUNDFONT_FILE "WEEDSGM3.SF2"
//#define SOUNDFONT_FILE "FLUIDR3.SF2"
//#define SOUNDFONT_FILE "COMPIFNT.SF2"


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
