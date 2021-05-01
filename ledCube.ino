#include <Cube.h>
#include <arduino/ArduinoAnimator.h>
#include <Animations.h>

const int clockPin = 13;
const int dataPin = 10;
const int outputEnablePin = 11;

const int buttonPin = 2;
const unsigned long debounceThreshold = 200;
volatile unsigned long lastPress = 0;

const Animator& animator = ArduinoAnimator(outputEnablePin, dataPin, clockPin);
Cube cube(4);
AnimationRegistry& animations = AnimationRegistry::GetInstance();
volatile unsigned int animationIndex = 3;

void setup() {
    Serial.begin(9600);

    // setup button interrupt
    pinMode(buttonPin, INPUT_PULLUP);
    lastPress = millis();
    attachInterrupt(digitalPinToInterrupt(buttonPin), []() {
        unsigned long now = millis();
        if(now - lastPress < debounceThreshold) return;
        lastPress = now;
        animationIndex = (animationIndex + 1) % animations.size();
        animations.getById(animationIndex)->init(cube);
    }, FALLING);
    // end setup button interrupt

    digitalWrite(outputEnablePin, LOW);
    digitalWrite(clockPin, LOW);

    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);

    digitalWrite(outputEnablePin, HIGH);
    digitalWrite(outputEnablePin, LOW);

    Serial.println("available animations:");
    Serial.println(animations.toString().get());

    animations.getById(animationIndex)->init(cube);
}

void loop() {
    animator.play(*animations.getById(animationIndex), cube);
    if(Serial.available()) {
        animationIndex = (unsigned int) (Serial.parseInt() % animations.size());
        animations.getById(animationIndex)->init(cube);
    }
}
