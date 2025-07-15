// Please support Youtube Channel ADSP
// https://www.youtube.com/channel/UCaFqpdENcVNK2Zn4qY-vOzQ
// VIDEO TUTOR: https://youtu.be/W-hMcpSHhUg
// GITHUB: https://github.com/adsp17/Project-3

#include <HID-Project.h>  // Library HID Project: https://github.com/NicoHood/HID
#include <HID-Settings.h>

const int pinCLK = 2;  // Sinyal A
const int pinDT  = 3;  // Sinyal B
const int pinSW  = 4;  // Tombol tekan (opsional)

int lastCLKState;
bool isMuted = false;

void setup() {
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);
  pinMode(pinSW, INPUT_PULLUP);  // Tombol biasanya aktif LOW

  lastCLKState = digitalRead(pinCLK);

  // Mulai komunikasi HID
  Consumer.begin();
}

void loop() {
  int currentCLKState = digitalRead(pinCLK);

  // Deteksi perubahan putaran
  if (currentCLKState != lastCLKState && currentCLKState == LOW) {
    int dtState = digitalRead(pinDT);
    if (dtState != currentCLKState) {
      // Putaran ke kanan - volume up
      Consumer.write(MEDIA_VOLUME_UP);
    } else {
      // Putaran ke kiri - volume down
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
  }
  lastCLKState = currentCLKState;

  // Tombol tekan encoder untuk mute/unmute
  if (digitalRead(pinSW) == LOW) {
    delay(50);  // debounce
    if (digitalRead(pinSW) == LOW) {
      Consumer.write(MEDIA_VOLUME_MUTE);
      delay(300);  // biar ga spam
    }
  }
}
