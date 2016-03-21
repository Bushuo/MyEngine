#include <gtest\gtest.h>
#include <Timing\Clock.h>
#include <qt\qtest.h>
#include <Qt\qdebug.h>
#include <iostream>

using Timing::Clock;

TEST(Clock, Initialize)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	EXPECT_TRUE(clock.shutdown());
}

TEST(Clock, FrameTimeMeasuring)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());

	QTest::qSleep(1000);
	clock.newFrame();
	float timedTime = clock.timeElapsedLastFrame();
	EXPECT_TRUE(0.9f < timedTime);
	EXPECT_TRUE(timedTime < 1.1f);
	clock.newFrame();

	QTest::qSleep(500);
	clock.newFrame();
	timedTime = clock.timeElapsedLastFrame();
	EXPECT_TRUE(0.4f < timedTime);
	EXPECT_TRUE(timedTime < 0.6f);
	
	const int NUM_TESTS = 10 + rand() % 100;
	const float THRESHOLD = 0.01f;
	for (unsigned int i = 0; i < NUM_TESTS; i++)
	{
		std::cout << ".";
		int thisTestTimeMilliseconds = rand() % 10000;
		float thisTestTimeSeconds = thisTestTimeMilliseconds / 1000.0f;
		clock.newFrame();
		QTest::qSleep(thisTestTimeMilliseconds);
		clock.newFrame();
		float elapsedSeconds = clock.timeElapsedLastFrame();
		EXPECT_TRUE((thisTestTimeSeconds - THRESHOLD) < elapsedSeconds);
		EXPECT_TRUE(elapsedSeconds < (thisTestTimeSeconds + THRESHOLD));
	}
	clock.newFrame();
	clock.timeElapsedLastFrame();
	EXPECT_TRUE(clock.shutdown());
}