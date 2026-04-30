#if defined(DISPLAY_DRAW_RECTANGLE)
#include "unihiker_k10.h"

volatile float offset, x, y, color;

uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b);

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Display Draw Rectangle Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.setScreenBackground(0x000000);
}
void loop() {
    for (int index = 0; index < 8; index++) {
        x = (80 - (offset / 2));
        y = (100 - (offset / 2));
        color = rgbToColor(round((random(50, 255 + 1))), round((random(50, 255 + 1))), round((random(50, 255 + 1))));
        k10.canvas->canvasRectangle(x, y, (80 + offset), (100 + offset), color, 0x0000FF, false);
        k10.canvas->updateCanvas();
        delay(10);
        offset = (offset + 20);
    }
    k10.canvas->canvasClear();
    offset = 0;
}

uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b) {
    return (uint32_t)((((uint32_t)r << 16) | ((uint32_t)g << 8)) | (uint32_t)b);
}
#endif
