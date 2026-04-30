#if defined(DISPLAY_QR_CODE)
#include "unihiker_k10.h"

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.canvasDrawCode("https://www.unihiker.com");
    k10.canvas->updateCanvas();
}
void loop() {}
#endif
