#if defined(DISPLAY_DRAW_CIRCLE)
#include "unihiker_k10.h"

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Display Draw Circle Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.canvas->canvasCircle(120, 120, 40, 0xFFCC33, 0xFFCC33, true);
    k10.canvas->canvasCircle(160, 160, 40, 0xFFCC33, 0xFFCC33, true);
    k10.canvas->canvasCircle(120, 200, 40, 0xFFCC33, 0xFFCC33, true);
    k10.canvas->canvasCircle(80, 160, 40, 0xFFCC33, 0xFFCC33, true);
    k10.canvas->canvasCircle(120, 160, 40, 0xFFFF00, 0xFFFF00, true);
    k10.canvas->updateCanvas();
}
void loop() {}
#endif
