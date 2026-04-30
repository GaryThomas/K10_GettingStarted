#if defined(DISPLAY_SHOWING_TEXT)

#include "unihiker_k10.h"
UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Display Showing Text Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.setScreenBackground(0xFFFFFF);
    k10.canvas->canvasText("UNIHIKER", 1, 0x0000FF);
    k10.canvas->updateCanvas();
    delay(1000);
    k10.canvas->canvasText("UNIHIKER", 2, 0xFF0000);
    k10.canvas->updateCanvas();
    delay(1000);
    k10.canvas->canvasText("UNIHIKER", 3, 0x00FF00);
    k10.canvas->updateCanvas();
    delay(1000);
    k10.canvas->canvasText("UNIHIKER", 4, 0x000000);
    k10.canvas->updateCanvas();
    delay(1000);
}
void loop() {}
#endif
