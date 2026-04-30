
#if defined(DISPLAY_DRAW_POINT)
#include "unihiker_k10.h"

uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b);

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Display Draw Point Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.setScreenBackground(0x000000);
}
void loop() {
    for (int index = 0; index < 50; index++) {
        k10.canvas->canvasPoint(
            (random(0, 240 + 1)), (random(0, 320 + 1)),
            rgbToColor(round((random(128, 255 + 1))), round((random(128, 255 + 1))), round((random(128, 255 + 1)))));
        k10.canvas->updateCanvas();
    }
    k10.canvas->canvasClear();
}

uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b) {
    return (uint32_t)((((uint32_t)r << 16) | ((uint32_t)g << 8)) | (uint32_t)b);
}
#endif
