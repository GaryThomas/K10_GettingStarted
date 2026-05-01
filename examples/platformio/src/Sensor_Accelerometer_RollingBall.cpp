#if defined(SENSOR_ACCLEROMETER_ROLLING_BALL)
#include "unihiker_k10.h"

volatile float accx, accy, moveX, moveY;

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Sensor Accelerometer Rolling Ball Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.setScreenBackground(0xFFFFFF);
}

void loop() {
    accx = (k10.getAccelerometerX());
    accy = (k10.getAccelerometerY());
    moveX = (120 + (accx / 3));
    moveY = (160 + (accy / 3));
    k10.canvas->canvasCircle(moveX, moveY, 8, 0x00FF00, 0x00FF00, true);
    k10.canvas->updateCanvas();
    k10.canvas->canvasCircle(moveX, moveY, 9, 0xFFFFFF, 0xFFFFFF, true);
}
#endif
