#pragma once
#ifndef TRK172_H_
#define TRK172_H_

#include <stdint.h> // uint8_t

#define TRK172_NO_MAX		0x7F

#define TRK172_PRICE_MAX	999999
#define TRK172_VOLUME_MAX	999999

#define TRK172_COM_LOAD		1
#define TRK172_COM_STATE	4
#define TRK172_COM_START	5
#define TRK172_COM_STOP		6
#define TRK172_COM_RESET	7

typedef struct
{
	uint8_t soh;
	char trk_no[2];
	char command[1];
	uint8_t stx;
	char price[6];
	char volume[6];
	char error[2];
	char code[2];
	uint8_t etx;
	uint8_t crc;

} TRK172_MSG;

#ifdef __cplusplus
extern "C"
{
#endif

int trk172_state(void* buf, int max_size, int trk_no);
int trk172_load(void* buf, int max_size, int trk_no, int volume);

#ifdef __cplusplus
}
#endif

#endif
