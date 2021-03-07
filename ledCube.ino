#include <Animations.h>
#include <Cube.h>
#include <arduino/ArduinoAnimator.h>

#define LED_READY_PIN 11
#define LED_OUT_PIN 10
#define CLOCK_PIN 13

void customAnimation(const Painter& painter, Cube& cube) {
    for(unsigned int z = 0; z < 4; ++z) { 
        for(unsigned int y = 0; y < 4; ++y) { 
            for(unsigned int x = 0; x < 4; ++x) { 
                Serial.print(x);
                Serial.print(" ");
                Serial.print(y);
                Serial.print(" ");
                Serial.println(z);
                cube.setPixel(x, y, z, true);
                painter.paintCube(cube);
            }
        }
    }
    Serial.println();
    for(unsigned int z = 4; z > 0; z--) { 
        for(unsigned int y = 4; y > 0; y--) { 
            for(unsigned int x = 4; x > 0; x--) { 
                Serial.print(x-1);
                Serial.print(" ");
                Serial.print(y-1);
                Serial.print(" ");
                Serial.println(z-1);
                cube.setPixel(x-1, y-1, z-1, false);
                painter.paintCube(cube);
            }
        }
    }
}

const Animator& animator = ArduinoAnimator(LED_READY_PIN, LED_OUT_PIN, CLOCK_PIN);
Cube cube(4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  animator.play(customAnimation, cube);
}

