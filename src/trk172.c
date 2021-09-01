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

int trk172(void* buf, int max_size, int command, int trk_no, int price, int volume)
{
	if (command == TRK172_COM_STATE)
	{
		return trk172_state(buf, max_size, trk_no);
	}
	else
	if (command == TRK172_COM_LOAD)
	{
		return trk172_load(buf, max_size, trk_no, price, volume);
	}
	else
	if (command == TRK172_COM_START)
	{
		return trk172_start(buf, max_size, trk_no);
	}
	else
	if (command == TRK172_COM_STOP)
	{
		return trk172_stop(buf, max_size, trk_no);
	}
	else
	if (command == TRK172_COM_RESET)
	{
		return trk172_reset(buf, max_size, trk_no);
	}
	else
	{
		return EINVAL;
	}
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

int trk172_load(void* buf, int max_size, int trk_no, int price, int volume)
{
	if (buf == 0 || max_size < sizeof(TRK172_MSG))
	{
		return ENOMEM;
	}

	if (trk_no > TRK172_NO_MAX || price > TRK172_PRICE_MAX || volume > TRK172_VOLUME_MAX)
	{
		return EINVAL;
	}

	TRK172_MSG* const msg = (TRK172_MSG*)buf;
	memset(buf, 0, sizeof(TRK172_MSG));

	to_string(msg->command, sizeof(msg->command), TRK172_COM_LOAD, 16);
	to_string(msg->trk_no, sizeof(msg->trk_no), trk_no, 16);
	to_string(msg->price, sizeof(msg->price), price, 10);
	to_string(msg->volume, sizeof(msg->volume), volume, 10);

	msg->soh = 1;
	msg->stx = 2;
	msg->etx = 3;

	msg->crc = calc_xor((uint8_t*)msg + 1, sizeof(TRK172_MSG) - 2);

	return EOK;
}

int trk172_start(void* buf, int max_size, int trk_no)
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

	to_string(msg->command, sizeof(msg->command), TRK172_COM_START, 16);
	to_string(msg->trk_no, sizeof(msg->trk_no), trk_no, 16);
	to_string(msg->error, sizeof(msg->error), 0, 16);
	to_string(msg->code, sizeof(msg->code), 0, 16);

	msg->soh = 1;
	msg->stx = 2;
	msg->etx = 3;

	msg->crc = calc_xor((uint8_t*)msg + 1, sizeof(TRK172_MSG) - 2);

	return EOK;
}

int trk172_stop(void* buf, int max_size, int trk_no)
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

	to_string(msg->command, sizeof(msg->command), TRK172_COM_STOP, 16);
	to_string(msg->trk_no, sizeof(msg->trk_no), trk_no, 16);

	msg->soh = 1;
	msg->stx = 2;
	msg->etx = 3;

	msg->crc = calc_xor((uint8_t*)msg + 1, sizeof(TRK172_MSG) - 2);

	return EOK;
}

int trk172_reset(void* buf, int max_size, int trk_no)
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

	to_string(msg->command, sizeof(msg->command), TRK172_COM_RESET, 16);
	to_string(msg->trk_no, sizeof(msg->trk_no), trk_no, 16);

	msg->soh = 1;
	msg->stx = 2;
	msg->etx = 3;

	msg->crc = calc_xor((uint8_t*)msg + 1, sizeof(TRK172_MSG) - 2);

	return EOK;
}
