# Overview

UniversalDHT is an Arduino library that supports DHT11 and DHT22 with the same code.


Usage example:

```
#include "UniversalDHT.h"

// Works with either a DHT11 or a DHT22 connected to pin D3
UniversalDHT dht(D3);
float temperature, humidity = 0;

void setup() {
  Serial.begin();
}

void loop() {
  UniversalDHT::Response response = dht.read(&temperature, &humidity);
  if(response.error) {
    Serial.printf("Read DHTxx failed t=%d err=%d\n", response.time, response.error);
  } else {
    Serial.printf("Sample OK: %0.1f *C, %0.1f RH%%\n", temperature, humidity);
  }
  delay(2000);
}
```

# Caveats

Querying the DHTxx sensors too often will result in failures. The following sampling rates are supported:

* DHT11: 1hz
* DHT22: 0.5hz

# See also

* DHT22 data sheet: https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf
* DHT11 data sheet: https://akizukidenshi.com/download/ds/aosong/DHT11.pdf
