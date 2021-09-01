#include <gmock/gmock.h>
#include <trk172.h>
using namespace testing; // Eq

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

TEST(TRK172Load, CommandEq)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x00, 0);
	ASSERT_THAT(msg.command[0], Eq('0' + TRK172_COM_LOAD));
}

TEST(TRK172Load, TrkNoOneDigitEqHexString)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x09, 0);
	ASSERT_THAT(msg.trk_no, StartsWith("09"));
}

TEST(TRK172Load, TrkNoEqHexString)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x5D, 0);
	ASSERT_THAT(msg.trk_no, StartsWith("5D"));
}

TEST(TRK172Load, VolumeEqDecString)
{
	TRK172_MSG msg;
	trk172_load(&msg, sizeof(msg), 0x15, 459321);
	ASSERT_THAT(msg.volume, StartsWith("459321"));
}
