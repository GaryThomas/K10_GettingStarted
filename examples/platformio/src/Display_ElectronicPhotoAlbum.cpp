#if defined(DISPLAY_PHOTO_ALBUM)
#include "unihiker_k10.h"

void onButtonAPressed();
void onButtonBPressed();

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Display Electronic Photo Album Example");
    k10.begin();
    k10.initScreen(screen_dir);
    k10.initBgCamerImage();
    k10.setBgCamerImage(false);
    k10.creatCanvas();
    k10.buttonA->setPressedCallback(onButtonAPressed);
    k10.initSDFile();
    k10.buttonB->setPressedCallback(onButtonBPressed);
    k10.setBgCamerImage(true);
}
void loop() {}

void onButtonAPressed() { k10.photoSaveToTFCard("S:/photo.bmp"); }
void onButtonBPressed() { k10.canvas->canvasDrawImage(0, 0, "S:/photo.bmp"); }
#endif
