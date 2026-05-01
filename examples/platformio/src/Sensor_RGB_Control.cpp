#if defined(SENSOR_RGB_CONTROL)
#include "unihiker_k10.h"

volatile float mind_n_brightness;

UNIHIKER_K10 k10;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Sensor RGB Control Example");
    k10.begin();
    mind_n_brightness = 0;
    k10.rgb->brightness(round(mind_n_brightness));
    k10.rgb->write(-1, 0x0000FF);
}

void loop() {
    while (!(mind_n_brightness == 9)) {
        k10.rgb->brightness(round(mind_n_brightness));
        k10.rgb->write(-1, 0x0000FF);
        delay(200);
        mind_n_brightness += 1;
    }
    while (!(mind_n_brightness == 0)) {
        k10.rgb->brightness(round(mind_n_brightness));
        k10.rgb->write(-1, 0x0000FF);
        delay(200);
        mind_n_brightness -= 1;
    }
}
#endif
