#include <stdint.h>
#include <stdbool.h>

void LedDriverCreate(uint16_t *addr);
void LedDriverTurnOn(uint16_t ledNumber);
void LedDriverTurnAllOn(void);
void LedDriverTurnAllOff(void);
void LedDriverTurnOff(uint16_t ledNumber);
bool LedDriverIsOn(uint16_t ledNumber);
bool LedDriverIsOff(uint16_t ledNumber);
