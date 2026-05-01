#if defined(AUDIO_PLAY_MUSIC)
#include "unihiker_k10.h"

void onButtonAPressed();
void onButtonBPressed();

UNIHIKER_K10 k10;
Music music;

void setup() {
    Serial.begin(115200);
    sleep(3);
    Serial.println("\n\n\nUNIHIKER K10 Audio Play Music Example");
    k10.begin();
    k10.buttonA->setPressedCallback(onButtonAPressed);
    k10.buttonB->setPressedCallback(onButtonBPressed);
}
void loop() {}

void onButtonAPressed() { music.playMusic(DADADADUM); }

void onButtonBPressed() {
    music.stopPlayTone();
    music.playTone(131, 8000);
    music.playTone(131, 8000);
    music.playTone(196, 8000);
    music.playTone(196, 8000);
    music.playTone(220, 8000);
    music.playTone(220, 8000);
    music.playTone(196, 8000);
}
#endif
