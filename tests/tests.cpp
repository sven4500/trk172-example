#include <gmock/gmock.h>
#include <trk172.h>
using namespace testing; // Eq

// Тесты функции trk172_state.

TEST(TRK172State, EnomemIfBufferTooSmall)
{
	TRK172_MSG msg;
	int const error = trk172_state(&msg, 0, 0);
	ASSERT_THAT(error, Eq(ENOMEM));
}

TEST(TRK172State, EinvalIfBadTrkNo)
{
	TRK172_MSG msg;
	int const error = trk172_state(&msg, sizeof(TRK172_MSG), TRK172_NO_MAX + 1);
	ASSERT_THAT(error, Eq(EINVAL));
}

TEST(TRK172State, SohEq1)
{
	TRK172_MSG msg;
	trk172_state(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.soh, Eq(1));
}

TEST(TRK172State, StxEq2)
{
	TRK172_MSG msg;
	trk172_state(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.stx, Eq(2));
}

TEST(TRK172State, EtxEq3)
{
	TRK172_MSG msg;
	trk172_state(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.etx, Eq(3));
}

TEST(TRK172State, CommandEq)
{
	TRK172_MSG msg;
	trk172_state(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.command[0], Eq('0' + TRK172_COM_STATE));
}

TEST(TRK172State, TrkNoOneDigitEqHexString)
{
	TRK172_MSG msg;
	trk172_state(&msg, sizeof(TRK172_MSG), 0x0A);
	ASSERT_THAT(msg.trk_no, StartsWith("0A"));
}

TEST(TRK172State, TrkNoEqHexString)
{
	TRK172_MSG msg;
	trk172_state(&msg, sizeof(TRK172_MSG), 0x7C);
	ASSERT_THAT(msg.trk_no, StartsWith("7C"));
}

// Тесты функции trk172_load.

TEST(TRK172Load, SohEq1)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(TRK172_MSG), 0, 0, 0);
	ASSERT_THAT(msg.soh, Eq(1));
}

TEST(TRK172Load, StxEq2)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(TRK172_MSG), 0, 0, 0);
	ASSERT_THAT(msg.stx, Eq(2));
}

TEST(TRK172Load, EtxEq3)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(TRK172_MSG), 0, 0, 0);
	ASSERT_THAT(msg.etx, Eq(3));
}

TEST(TRK172Load, CommandEq)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x00, 0, 0);
	ASSERT_THAT(msg.command[0], Eq('0' + TRK172_COM_LOAD));
}

TEST(TRK172Load, TrkNoOneDigitEqHexString)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x09, 0, 0);
	ASSERT_THAT(msg.trk_no, StartsWith("09"));
}

TEST(TRK172Load, TrkNoEqHexString)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x5D, 0, 0);
	ASSERT_THAT(msg.trk_no, StartsWith("5D"));
}

TEST(TRK172Load, PriceEqDecString)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x15, 678402, 0);
	ASSERT_THAT(msg.price, StartsWith("678402"));
}

TEST(TRK172Load, VolumeEqDecString)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x15, 0, 459321);
	ASSERT_THAT(msg.volume, StartsWith("459321"));
}

// Тесты функции trk172_start.

TEST(TRK172Start, CommandEq)
{
	TRK172_MSG msg;
	trk172_start(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.command[0], Eq('0' + TRK172_COM_START));
}

TEST(TRK172Start, SohEq1)
{
	TRK172_MSG msg;
	trk172_start(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.soh, Eq(1));
}

TEST(TRK172Start, StxEq2)
{
	TRK172_MSG msg;
	trk172_start(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.stx, Eq(2));
}

TEST(TRK172Start, EtxEq3)
{
	TRK172_MSG msg;
	trk172_start(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.etx, Eq(3));
}

TEST(TRK172Start, TrkNoOneDigitEqHexString)
{
	TRK172_MSG msg;
	trk172_start(&msg, sizeof(msg), 0x05);
	ASSERT_THAT(msg.trk_no, StartsWith("05"));
}

TEST(TRK172Start, TrkNoEqHexString)
{
	TRK172_MSG msg;
	trk172_start(&msg, sizeof(msg), 0x1A);
	ASSERT_THAT(msg.trk_no, StartsWith("1A"));
}

TEST(TRK172Start, ErrorEqZero)
{
	TRK172_MSG msg;
	trk172_start(&msg, sizeof(msg), 0);
	ASSERT_THAT(msg.error, StartsWith("00"));
}

TEST(TRK172Start, CodeEqZero)
{
	TRK172_MSG msg;
	trk172_start(&msg, sizeof(msg), 0);
	ASSERT_THAT(msg.code, StartsWith("00"));
}

// Тесты функции trk172_stop.

TEST(TRK172Stop, CommandEq)
{
	TRK172_MSG msg;
	trk172_stop(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.command[0], Eq('0' + TRK172_COM_STOP));
}

TEST(TRK172Stop, SohEq1)
{
	TRK172_MSG msg;
	trk172_stop(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.soh, Eq(1));
}

TEST(TRK172Stop, StxEq2)
{
	TRK172_MSG msg;
	trk172_stop(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.stx, Eq(2));
}

TEST(TRK172Stop, EtxEq3)
{
	TRK172_MSG msg;
	trk172_stop(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.etx, Eq(3));
}

TEST(TRK172Stop, TrkNoOneDigitEqHexString)
{
	TRK172_MSG msg;
	trk172_stop(&msg, sizeof(msg), 0x01);
	ASSERT_THAT(msg.trk_no, StartsWith("01"));
}

TEST(TRK172Stop, TrkNoEqHexString)
{
	TRK172_MSG msg;
	trk172_stop(&msg, sizeof(msg), 0x6B);
	ASSERT_THAT(msg.trk_no, StartsWith("6B"));
}

// Тесты функции trk172_reset.

TEST(TRK172Reset, CommandEq)
{
	TRK172_MSG msg;
	trk172_reset(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.command[0], Eq('0' + TRK172_COM_RESET));
}

TEST(TRK172Reset, SohEq1)
{
	TRK172_MSG msg;
	trk172_reset(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.soh, Eq(1));
}

TEST(TRK172Reset, StxEq2)
{
	TRK172_MSG msg;
	trk172_reset(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.stx, Eq(2));
}

TEST(TRK172Reset, EtxEq3)
{
	TRK172_MSG msg;
	trk172_reset(&msg, sizeof(TRK172_MSG), 0);
	ASSERT_THAT(msg.etx, Eq(3));
}

TEST(TRK172Reset, TrkNoOneDigitEqHexString)
{
	TRK172_MSG msg;
	trk172_reset(&msg, sizeof(msg), 0x03);
	ASSERT_THAT(msg.trk_no, StartsWith("03"));
}

TEST(TRK172Reset, TrkNoEqHexString)
{
	TRK172_MSG msg;
	trk172_reset(&msg, sizeof(msg), 0x7F);
	ASSERT_THAT(msg.trk_no, StartsWith("7F"));
}
