#if defined(DISPLAY_BACKGROUND_COLOR)
#include "unihiker_k10.h"

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Display Background Color Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
}

void loop() {
    k10.setScreenBackground(0xFFFFFF);
    delay(2000);
    k10.setScreenBackground(0xFF0000);
    delay(2000);
    k10.setScreenBackground(0x00FF00);
    delay(2000);
    k10.setScreenBackground(0x0000FF);
    delay(2000);
    k10.setScreenBackground(0x000000);
    delay(2000);
}
#endif
