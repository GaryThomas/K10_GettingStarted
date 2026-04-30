#if defined(DISPLAY_DRAW_LINE)
#include "unihiker_k10.h"

volatile float startX, endX;

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Display Draw Line Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.canvas->canvasSetLineWidth(1);
    startX = 0;
    endX = 240;
}
void loop() {
    while (!(startX == 240)) {
        k10.canvas->canvasLine(startX, 0, endX, 320, 0xFF0000);
        k10.canvas->updateCanvas();
        startX += 3;
        endX -= 3;
    }
}
#endif
