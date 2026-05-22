#include <avr/pgmspace.h>

// =======================
//        NOTE DEFINES
// =======================
#define NOTE_E4  330
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_G5  784
#define REST 0

// =======================
//        پایه‌ها
// =======================
const int button1Pin = 13;
const int button2Pin = 8;
const int ledWhite   = 11;
const int ledRed1    = 12;
const int ledRed2    = 9;
const int buzzer     = 10;

// =======================
//        ملودی هیجانی
// =======================
int tempo = 140;

const int melody[] PROGMEM = {
  NOTE_E4,8, NOTE_G4,8, NOTE_A4,8, NOTE_B4,8,
  NOTE_C5,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
  NOTE_E4,8, NOTE_G4,8, NOTE_A4,8, NOTE_C5,8,
  NOTE_B4,4, REST,8,

  NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,
  NOTE_A4,8, NOTE_G4,8, NOTE_A4,8, NOTE_C5,8,
  NOTE_B4,4, REST,8
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;

int wholenote;
int divider = 0;
int noteDuration = 0;
int thisNote = 0;
unsigned long noteStartTime = 0;
bool musicPlaying = true;

// =======================
//      وضعیت بازی
// =======================
bool gameStarted = false;
bool gameFinished = false;
bool falseStart = false;

unsigned long randomDelayTime = 0;

void setup() {

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(ledWhite, OUTPUT);
  pinMode(ledRed1, OUTPUT);
  pinMode(ledRed2, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(ledWhite, LOW);
  digitalWrite(ledRed1, LOW);
  digitalWrite(ledRed2, LOW);

  randomSeed(analogRead(A0));

  wholenote = (60000 * 4) / tempo;

  startNewRound();
}

void loop() {

  playBackgroundMusic();

  // اگر قبل از روشن شدن چراغ سفید دکمه بزنند = باخت
  if (!gameStarted && !gameFinished) {

    if (digitalRead(button1Pin) == LOW) lose(1);
    if (digitalRead(button2Pin) == LOW) lose(2);

    if (millis() >= randomDelayTime) {
      digitalWrite(ledWhite, HIGH);
      tone(buzzer, 1500, 150); // صدای شروع
      gameStarted = true;
    }
  }

  if (gameStarted && !gameFinished) {

    if (digitalRead(button1Pin) == LOW) win(1);
    if (digitalRead(button2Pin) == LOW) win(2);
  }
}

// =======================
//        برنده
// =======================
void win(int player) {

  gameFinished = true;
  digitalWrite(ledWhite, LOW);

  if (player == 1)
    digitalWrite(ledRed1, HIGH);
  else
    digitalWrite(ledRed2, HIGH);

  // ملودی برد
  tone(buzzer, 2000, 200);
  delay(250);
  tone(buzzer, 2500, 200);
  delay(250);
  tone(buzzer, 3000, 300);
  delay(1000);

  startNewRound();
}

// =======================
//        باخت (تقلب)
// =======================
void lose(int player) {

  gameFinished = true;

  // چشمک سریع اخطار
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledRed1, HIGH);
    digitalWrite(ledRed2, HIGH);
    tone(buzzer, 400, 100);
    delay(100);
    digitalWrite(ledRed1, LOW);
    digitalWrite(ledRed2, LOW);
    delay(100);
  }

  startNewRound();
}

// =======================
//      شروع راند جدید
// =======================
void startNewRound() {

  digitalWrite(ledWhite, LOW);
  digitalWrite(ledRed1, LOW);
  digitalWrite(ledRed2, LOW);

  gameStarted = false;
  gameFinished = false;

  randomDelayTime = millis() + random(2000, 6000);
}

// =======================
//    پخش نرم موسیقی
// =======================
void playBackgroundMusic() {

  if (millis() - noteStartTime >= noteDuration) {

    if (thisNote >= notes * 2) thisNote = 0;

    divider = pgm_read_word_near(melody + thisNote + 1);

    noteDuration = wholenote / divider;

    int pitch = pgm_read_word_near(melody + thisNote);

    if (pitch == REST)
      noTone(buzzer);
    else
      tone(buzzer, pitch, noteDuration * 0.95); // بدون قطع ناگهانی

    noteStartTime = millis();
    thisNote += 2;
  }
}