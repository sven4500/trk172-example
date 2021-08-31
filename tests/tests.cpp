#include <gmock/gmock.h>
#include <trk172.h>
using namespace testing; // Eq

TEST(TRK172Stat, EnomemIfBufferTooSmall)
{
	TRK172_MSG msg;
	int const error = trk172_state(&msg, 0, 0);
	ASSERT_THAT(error, Eq(ENOMEM));
}

TEST(TRK172Stat, EinvalIfBadTrk)
{
	TRK172_MSG msg;
	int const error = trk172_state(&msg, TRK172_MSG_LEN, 0x80);
	ASSERT_THAT(error, Eq(EINVAL));
}

TEST(TRK172Stat, SohEq1)
{
	TRK172_MSG msg;
	trk172_state(&msg, TRK172_MSG_LEN, 0);
	ASSERT_THAT(msg.soh, Eq(1));
}

TEST(TRK172Stat, StxEq2)
{
	TRK172_MSG msg;
	trk172_state(&msg, TRK172_MSG_LEN, 0);
	ASSERT_THAT(msg.stx, Eq(2));
}

TEST(TRK172Stat, EtxEq3)
{
	TRK172_MSG msg;
	trk172_state(&msg, TRK172_MSG_LEN, 0);
	ASSERT_THAT(msg.etx, Eq(3));
}

TEST(TRK172Stat, CommandEq34)
{
	TRK172_MSG msg;
	trk172_state(&msg, TRK172_MSG_LEN, 0);
	ASSERT_THAT(msg.command[0], Eq(TRK172_COM_STATE));
}

TEST(TRK172Stat, TrkNoMostSignificantDigit)
{
	TRK172_MSG msg;
	trk172_state(&msg, TRK172_MSG_LEN, 37);
	ASSERT_THAT(msg.trk_no[0], Eq('3'));
}

TEST(TRK172Stat, TrkNoLeastSignificantDigit)
{
	TRK172_MSG msg;
	trk172_state(&msg, TRK172_MSG_LEN, 59);
	ASSERT_THAT(msg.trk_no[1], Eq('9'));
}

TEST(TRK172Stat, TrkNoMostSignificantDigitIfLessThan10)
{
	TRK172_MSG msg;
	trk172_state(&msg, TRK172_MSG_LEN, 7);
	ASSERT_THAT(msg.trk_no[0], Eq('0'));
}

TEST(TRK172Stat, TrkNoLeastSignificantDigitIfLessThan10)
{
	TRK172_MSG msg;
	trk172_state(&msg, TRK172_MSG_LEN, 7);
	ASSERT_THAT(msg.trk_no[1], Eq('7'));
}
