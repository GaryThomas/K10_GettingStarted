#if defined(SENSOR_ACCELEROMETER_DIRECTIONS)
#include "unihiker_k10.h"
UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Sensor Accelerometer Directions Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.initSDFile();
}
void loop() {
    if ((k10.isGesture(TiltForward))) {
        k10.canvas->canvasDrawImage(0, 0, "S:/forward.png");
        k10.canvas->updateCanvas();
        Serial.println("TiltForward");
        sleep(1);
    } else if ((k10.isGesture(TiltBack))) {
        k10.canvas->canvasDrawImage(0, 0, "S:/back.png");
        k10.canvas->updateCanvas();
        Serial.println("TiltBack");
        sleep(1);
    } else if ((k10.isGesture(TiltLeft))) {
        k10.canvas->canvasDrawImage(0, 0, "S:/left.png");
        k10.canvas->updateCanvas();
        Serial.println("TiltLeft");
        sleep(1);
    } else if ((k10.isGesture(TiltRight))) {
        k10.canvas->canvasDrawImage(0, 0, "S:/right.png");
        k10.canvas->updateCanvas();
        Serial.println("TiltRight");
        sleep(1);
    }
    k10.canvas->canvasRectangle(0, 0, 240, 320, 0xFFFFFF, 0xFFFFFF, true);
    k10.canvas->updateCanvas();
}
#endif
