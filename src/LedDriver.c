#include <stdio.h>
#include "LedDriver.h"

enum{ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
enum{FIRST_LED = 1, LAST_LED = 16};
static uint16_t *ledsAddress;
static uint16_t ledsImage;

static uint16_t convertLedNumberToBit (uint16_t ledNumber)
{
  return (uint16_t)(1 << (ledNumber - 1));
}

static void updateHardware(void)
{
  *ledsAddress = ledsImage;
}

static bool IsLedOutOfBounds(uint16_t ledNumber)
{
  return (ledNumber < FIRST_LED) || (ledNumber > LAST_LED);
}

static void setLedImageBit (uint16_t ledNumber)
{
  ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit (uint16_t ledNumber)
{
  ledsImage &= ~(convertLedNumberToBit(ledNumber));
}

void LedDriverCreate(uint16_t *addr)
{
  ledsAddress = addr;
  ledsImage = ALL_LEDS_OFF;
  updateHardware();
}

void LedDriverTurnOn(uint16_t ledNumber)
{
  if (IsLedOutOfBounds(ledNumber))
  {
    return;
  }

  setLedImageBit(ledNumber);
  updateHardware();
}

void LedDriverTurnAllOn(void)
{
  ledsImage = ALL_LEDS_ON;
  updateHardware();
}

void LedDriverTurnAllOff(void)
{
  ledsImage = ALL_LEDS_OFF;
  updateHardware();
}

void LedDriverTurnOff(uint16_t ledNumber)
{
  if (IsLedOutOfBounds(ledNumber))
  {
    return;
  }

  clearLedImageBit(ledNumber);
  updateHardware();
}

bool LedDriverIsOn (uint16_t ledNumber)
{
  if(IsLedOutOfBounds(ledNumber))
  {
    return false;
  }
  return 0 != (ledsImage & convertLedNumberToBit(ledNumber));
}

bool LedDriverIsOff (uint16_t ledNumber)
{
  return !LedDriverIsOn(ledNumber);
}
