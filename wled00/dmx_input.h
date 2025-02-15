#pragma once

#include "wled.h"
#include <WiFiUdp.h>
#include <mutex>

// Simple structure to hold WLED state
struct WLEDState
{
  uint8_t mode;
  uint8_t speed;
  uint8_t intensity;
  uint8_t r1, g1, b1; // Primary color
  uint8_t r2, g2, b2; // Secondary color
} __attribute__((packed));

class DMXInput
{
public:
  void init(uint8_t rxPin, uint8_t txPin, uint8_t enPin, uint8_t inputPortNum);
  void update();
  void disable();
  void enable();
  bool isConnected() const { return initialized; }

private:
  WiFiUDP udp;
  bool initialized = false;
  WLEDState state;
  std::mutex stateLock;

  void broadcastState();
  void checkAndUpdateConfig() {} // Not used in this implementation
};

#ifdef WLED_ENABLE_DMX_UDP_SYNC
extern DMXInput dmxInput; // Only declare if DMX UDP sync is enabled
#endif
