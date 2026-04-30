#if defined(SENSOR_ACCELEROMETER_PEDOMETER)
#include "unihiker_k10.h"

volatile float step;

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

static void showPedometer() {
    step += 1;
    k10.canvas->canvasText((String("Pedometer: ") + String(step)), 1, 0x0000FF);
    k10.canvas->updateCanvas();
}

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Sensor Accelerometer Pedometer Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    step = 0;
    showPedometer();
}

void loop() {
    if (((k10.getStrength()) > 1050)) {
        step += 1;
        showPedometer();
        delay(1000);
    }
}
#endif
