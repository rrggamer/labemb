#include <Tone32.h>

#define BUZZER_PIN 16
#define BUZZER_CHANNEL 0

// Notes in the melody (Twinkle Twinkle Little Star)
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2
};

void setup() {}

void loop() {
  for (int i = 0; i < 14; i++) {
    int duration = 1000 / noteDurations[i];  // Convert note duration to milliseconds
    tone(BUZZER_PIN, melody[i], duration, BUZZER_CHANNEL);
    delay(duration * 1.3);  // Small pause between notes
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
  }
}
