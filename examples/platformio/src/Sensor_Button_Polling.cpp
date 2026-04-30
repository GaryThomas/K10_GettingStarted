#if defined(SENSOR_BUTTON_POLLING)
#include "unihiker_k10.h"

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Sensor Button Polling Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
}
void loop() {
    if ((k10.buttonA->isPressed())) {
        k10.canvas->canvasRectangle(10, 100, 110, 100, 0xFF6666, 0x0000FF, true);
        k10.canvas->updateCanvas();
    } else if ((k10.buttonB->isPressed())) {
        k10.canvas->canvasCircle(180, 150, 50, 0xFF6666, 0x0000FF, true);
        k10.canvas->updateCanvas();
    } else if ((k10.buttonAB->isPressed())) {
        k10.canvas->canvasClear();
        k10.canvas->updateCanvas();
    }
}
#endif
