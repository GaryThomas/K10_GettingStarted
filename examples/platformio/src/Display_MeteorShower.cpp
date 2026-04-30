#if defined(DISPLAY_METEOR_SHOWER)
#include "unihiker_k10.h"

volatile float startX, startY, length, endX, endY;

uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b);

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Display Meteor Shower Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.setScreenBackground(0x000000);
    k10.canvas->canvasSetLineWidth(1);
}
void loop() {
    k10.canvas->canvasClear();
    for (int index = 0; index < 15; index++) {
        startX = (random(0, 240 + 1));
        startY = (random(0, 180 + 1));
        length = (random(0, 40 + 1));
        endX = (startX + length);
        endY = (startY + length);
        k10.canvas->canvasLine(
            startX, startY, endX, endY,
            rgbToColor(round((random(128, 255 + 1))), round((random(128, 255 + 1))), round((random(128, 255 + 1)))));
    }
    k10.canvas->updateCanvas();
    delay(500);
}

uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b) {
    return (uint32_t)((((uint32_t)r << 16) | ((uint32_t)g << 8)) | (uint32_t)b);
}
#endif
