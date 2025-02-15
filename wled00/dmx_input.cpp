#include "wled.h"

#ifdef WLED_ENABLE_DMX_UDP_SYNC
#pragma message "WLED UDP sync enabled"

#include "dmx_input.h"

DMXInput dmxInput; // Define the global instance only in this file

void DMXInput::init(uint8_t rxPin, uint8_t txPin, uint8_t enPin, uint8_t inputPortNum)
{
  if (!initialized)
  {
    udp.begin(DMX_UDP_PORT);
    initialized = true;
    USER_PRINTLN(F("WLED UDP Sync Initialized"));
  }
}

void DMXInput::update()
{
  if (!initialized)
    return;

  const std::lock_guard<std::mutex> lock(stateLock);

  // Get current segment
  uint8_t mainSegId = strip.getMainSegmentId();
  Segment &mainseg = strip.getSegment(mainSegId);

  // Update state
  state.mode = mainseg.mode;
  state.speed = mainseg.speed;
  state.intensity = mainseg.intensity;

  // Primary color
  uint32_t color1 = mainseg.colors[0];
  state.r1 = (color1 >> 16) & 0xFF;
  state.g1 = (color1 >> 8) & 0xFF;
  state.b1 = color1 & 0xFF;

  // Secondary color
  uint32_t color2 = mainseg.colors[1];
  state.r2 = (color2 >> 16) & 0xFF;
  state.g2 = (color2 >> 8) & 0xFF;
  state.b2 = color2 & 0xFF;

  broadcastState();
}

void DMXInput::broadcastState()
{
  udp.beginPacket("255.255.255.255", DMX_UDP_PORT);
  udp.write((uint8_t *)&state, sizeof(WLEDState));
  udp.endPacket();
}

void DMXInput::disable()
{
  if (initialized)
  {
    udp.stop();
    initialized = false;
  }
}

void DMXInput::enable()
{
  if (!initialized)
  {
    udp.begin(DMX_UDP_PORT);
    initialized = true;
  }
}

#endif