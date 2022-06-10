#include <Arduino.h>
#include "OneWireNg_CurrentPlatform.h"

#define OW_PIN          14

static OneWireNg *ow = NULL;


static void printId(const OneWireNg::Id& id) {
  Serial.print(id[0], HEX);
  for (size_t i = 1; i < sizeof(OneWireNg::Id); i++) {
    Serial.print(':');
    Serial.print(id[i], HEX);
  }
  Serial.println();
}

void setup() {
  
  ow = new OneWireNg_CurrentPlatform(OW_PIN, false);
  Serial.begin(115200);
}

void loop() {
  OneWireNg::Id id;
  int before = micros();
  ow->searchReset();
  while (ow->search(id) == OneWireNg::EC_MORE) {
    printId(id); 
    int after = micros();
    int time = after - before;
    Serial.println(time);   
  }
}
