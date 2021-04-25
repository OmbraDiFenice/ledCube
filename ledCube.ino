#include <Cube.h>
#include <arduino/ArduinoAnimator.h>
#include <Animations.h>

const int clockPin = 13;
const int dataPin = 10;
const int outputEnablePin = 11;

const Animator& animator = ArduinoAnimator(outputEnablePin, dataPin, clockPin);
Cube cube(4);
AnimationRegistry& animations = AnimationRegistry::GetInstance();
unsigned int animationIndex = 3;

class Remote : public Animation {
    public:
        Remote() : Animation("remote") {}; 
        void run(const Painter& painter, Cube& cube) override {
            Serial.readBytes(cube.getBuffer(), cube.getSize());
            painter.paintCube(cube, 50);
        };
};

void setup() {
    Serial.begin(9600);

    digitalWrite(outputEnablePin, LOW);
    digitalWrite(clockPin, LOW);

    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);

    digitalWrite(outputEnablePin, HIGH);
    digitalWrite(outputEnablePin, LOW);

    Serial.println("available animations:");
    Serial.println(animations.toString().get());
}

void loop() {
    animator.play(*animations.getById(animationIndex), cube);
    if(Serial.available()) {
        //animationIndex = (animationIndex + 1) % animations.size();
        animationIndex = (unsigned int) (Serial.parseInt() % animations.size());
        animations.getById(animationIndex)->init(cube);
    }
}
