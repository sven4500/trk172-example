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

int to_string(char* buf, int max_len, int n, int base)
{
	char const digits[] = "0123456789ABCDEF";

	if (buf == 0 || max_len < 1)
	{
		return ENOMEM;
	}

	if (n < 0 || base > 16 || base < 1)
	{
		return EINVAL;
	}

	for (int i = 0; i < max_len; ++i)
	{
		buf[max_len - i - 1] = digits[n % base];
		n /= base;
	}

	return EOK;
}

int trk172_state(void* buf, int max_size, int trk_no)
{
	if (buf == 0 || max_size < sizeof(TRK172_MSG))
	{
		return ENOMEM;
	}

	if (trk_no > TRK172_NO_MAX)
	{
		return EINVAL;
	}

	TRK172_MSG* const msg = (TRK172_MSG*)buf;
	memset(buf, 0, sizeof(TRK172_MSG));

	to_string(msg->command, sizeof(msg->command), TRK172_COM_STATE, 16);
	to_string(msg->trk_no, sizeof(msg->trk_no), trk_no, 16);

	msg->soh = 1;
	msg->stx = 2;
	msg->etx = 3;
	
	msg->crc = calc_xor((uint8_t*)msg + 1, sizeof(TRK172_MSG) - 2);

	return EOK;
}

int trk172_load(void* buf, int max_size, int trk_no, int volume)
{
	if (buf == 0 || max_size < sizeof(TRK172_MSG))
	{
		return ENOMEM;
	}

	if (trk_no > TRK172_NO_MAX || volume > TRK172_VOLUME_MAX)
	{
		return EINVAL;
	}

	TRK172_MSG* const msg = (TRK172_MSG*)buf;
	memset(buf, 0, sizeof(TRK172_MSG));

	to_string(msg->command, sizeof(msg->command), TRK172_COM_LOAD, 16);
	to_string(msg->trk_no, sizeof(msg->trk_no), trk_no, 16);
	to_string(msg->volume, sizeof(msg->volume), volume, 10);

	msg->soh = 1;
	msg->stx = 2;
	msg->etx = 3;

	msg->crc = calc_xor((uint8_t*)msg + 1, sizeof(TRK172_MSG) - 2);

	return EOK;
}
