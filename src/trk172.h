#pragma once
#ifndef TRK172_H_
#define TRK172_H_

#include <stdint.h> // uint8_t

#define TRK172_MSG_LEN sizeof(TRK172_MSG)

#define TRK172_COM_STATE ('\x34')
#define TRK172_COM_LOAD ('\x31')
#define TRK172_COM_START ('\x35')
#define TRK172_COM_STOP ('\x36')
#define TRK172_COM_RESET ('\x37')

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

#ifdef __cplusplus
}
#endif

#endif
