#include "gtest/gtest.h"
extern "C" {
  #include "LedDriver.h"
}

namespace {

class LedDriverTest : public ::testing::Test
{
protected:
  uint16_t virtualLeds;

  virtual void SetUp()
  {
    LedDriverCreate(&virtualLeds);
  }
  virtual void TearDown()
  {
  }
};

TEST_F(LedDriverTest, LedMemoryIsNotReadable)
{
  virtualLeds = 0xffff;

  LedDriverTurnOn(8);
  EXPECT_EQ(0x80, virtualLeds);
}

TEST_F(LedDriverTest, LedsOffAfterCreate)
{
  uint16_t virtualLeds = 0xffff;

  LedDriverCreate(&virtualLeds);
  EXPECT_EQ(0x0, virtualLeds);
}

TEST_F(LedDriverTest, TurnOnLedOne)
{
  LedDriverTurnOn(1);
  EXPECT_EQ(0x1, virtualLeds);
}

TEST_F(LedDriverTest, TurnOffLedOne)
{
  LedDriverTurnOn(1);
  LedDriverTurnOff(1);
  EXPECT_EQ(0x0, virtualLeds);
}

TEST_F(LedDriverTest, TurnOnMultipleLeds)
{
  LedDriverTurnOn(9);
  LedDriverTurnOn(8);
  EXPECT_EQ(0x0180, virtualLeds);
}

TEST_F(LedDriverTest, TurnOffMultipleLeds)
{
  LedDriverTurnAllOn();
  LedDriverTurnOff(9);
  LedDriverTurnOff(8);
  EXPECT_EQ((~0x0180)&0xffff, virtualLeds);
}

TEST_F(LedDriverTest, AllOn)
{
  LedDriverTurnAllOn();
  EXPECT_EQ(0xffff, virtualLeds);
}

TEST_F(LedDriverTest, AllOff)
{
  LedDriverTurnAllOn();
  LedDriverTurnAllOff();
  EXPECT_EQ(0x0, virtualLeds);
}

TEST_F(LedDriverTest, TurnOffAnyLed)
{
  LedDriverTurnAllOn();
  LedDriverTurnOff(8);
  EXPECT_EQ(0xff7f, virtualLeds);
}

TEST_F(LedDriverTest, UpperAndLowerBounds)
{
  LedDriverTurnOn(1);
  LedDriverTurnOn(16);
  EXPECT_EQ(0x8001, virtualLeds);
}

TEST_F(LedDriverTest, OutOfBoundsTurnOnDoesNoHarm)
{
  LedDriverTurnOn(-1);
  LedDriverTurnOn(0);
  LedDriverTurnOn(17);
  LedDriverTurnOn(3141);
  EXPECT_EQ(0x0, virtualLeds);
}

TEST_F(LedDriverTest, OutOfBoundsTurnOffDoesNoHarm)
{
  LedDriverTurnAllOn();
  LedDriverTurnOff(-1);
  LedDriverTurnOff(0);
  LedDriverTurnOff(17);
  LedDriverTurnOff(3141);
  EXPECT_EQ(0xffff, virtualLeds);
}

TEST_F(LedDriverTest, IsOn)
{
  EXPECT_FALSE(LedDriverIsOn(11));
  LedDriverTurnOn(11);
  EXPECT_TRUE(LedDriverIsOn(11));
}

TEST_F(LedDriverTest, OutOfBoundsLedsAreAlwaysOff)
{
  EXPECT_FALSE(LedDriverIsOn(0));
  EXPECT_FALSE(LedDriverIsOn(17));
  EXPECT_TRUE(LedDriverIsOff(0));
  EXPECT_TRUE(LedDriverIsOff(17));
}

TEST_F(LedDriverTest, IsOff)
{
  LedDriverTurnAllOn();
  EXPECT_FALSE(LedDriverIsOff(11));
  LedDriverTurnOff(11);
  EXPECT_TRUE(LedDriverIsOff(11));
}

} // namespace
