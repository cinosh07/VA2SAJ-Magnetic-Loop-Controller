void playBeep() {
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(500);
        noTone(buzzer);
}
void playBeepBeep() {
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(250);
        noTone(buzzer);
        delay(250);
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(250);
        noTone(buzzer);
}
void playShortBeep() {
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(250);
        noTone(buzzer);
}
void playAlarmSWR() {

        int toneOne = 2000;
        int toneTwo = 1000;
        int toneDelay = 50;
        int repeat = 20;

        for (int i = 0; i < repeat; i++) {
                tone(buzzer, toneOne); // Send 2KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);
                tone(buzzer, toneTwo); // Send 1KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);

        }
}
void playAlarmNOSD() {
        int toneOne = 2000;
        int toneTwo = 1000;
        int toneDelay = 50;
        int repeat = 3;

        for (int i = 0; i < repeat; i++) {
                tone(buzzer, toneOne); // Send 2KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);
                tone(buzzer, toneTwo); // Send 1KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);

        }
}
void playAlarmNONETWORK() {
        int toneOne = 2000;
        int toneTwo = 1000;
        int toneDelay = 50;
        int repeat = 6;

        for (int i = 0; i < repeat; i++) {
                tone(buzzer, toneOne); // Send 2KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);
                tone(buzzer, toneTwo); // Send 1KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);

        }
}
void playAlarmNOCLOUD() {
        int toneOne = 2000;
        int toneTwo = 1000;
        int toneDelay = 50;
        int repeat = 9;

        for (int i = 0; i < repeat; i++) {
                tone(buzzer, toneOne); // Send 2KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);
                tone(buzzer, toneTwo); // Send 1KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);

        }
}
