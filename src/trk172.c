#include <string.h> // memset
#include <errno.h>
#include <trk172.h>

// Не все ОС дают определение для EOK, определяем сами.
#ifndef EOK
#define EOK 0
#endif

uint8_t calc_xor(void const* buf, int const size)
{
	uint8_t const* const addr = (uint8_t*)buf;
	uint8_t sum = 0;

	for (int i = 0; i < size; ++i)
	{
		sum ^= addr[i];
	}

	return sum;
}

int to_string(char* buf, int max_len, int n)
{
	if (n < 0)
	{
		return EINVAL;
	}

	if (max_len == 1)
	{
		buf[0] = '0' + n % 10;
		return EOK;
	}
	else
	if (max_len == 2)
	{
		buf[0] = '0' + n / 10;
		buf[1] = '0' + n % 10;
		return EOK;
	}
	else
	{
		return EINVAL;
	}
}

int trk172_state(void* buf, int max_size, int trk_no)
{
	if (max_size < TRK172_MSG_LEN)
	{
		return ENOMEM;
	}

	if (trk_no > 0x7F)
	{
		return EINVAL;
	}

	TRK172_MSG* const msg = (TRK172_MSG*)buf;
	memset(buf, 0, TRK172_MSG_LEN);

	to_string(msg->trk_no, sizeof(msg->trk_no), trk_no);
	msg->soh = 1;
	msg->stx = 2;
	msg->etx = 3;
	msg->command[0] = TRK172_COM_STATE;
	msg->crc = calc_xor((uint8_t*)msg + 1, TRK172_MSG_LEN - 2);

	return EOK;
}
