#include <Animations.h>
#include <Cube.h>
#include <arduino/ArduinoAnimator.h>

#define LED_READY_PIN 11
#define LED_OUT_PIN 10
#define CLOCK_PIN 13

#define MIN(a,b) ((((a) < (b))) ? (a) : (b))

const Animator& animator = ArduinoAnimator(LED_READY_PIN, LED_OUT_PIN, CLOCK_PIN);
Cube cube(4);
Cube cube2(4);

Cube& screenCube = cube;
Cube& offscreenCube = cube2;
volatile int readBytes = 0;

void customAnimation(const Painter& painter, Cube& cube) {
    for(unsigned int z = 0; z < 4; ++z) { 
        for(unsigned int y = 0; y < 4; ++y) { 
            for(unsigned int x = 0; x < 4; ++x) { 
                cube.setPixel(x, y, z, true);
                painter.paintCube(cube);
            }
        }
    }
    for(unsigned int z = 4; z > 0; z--) { 
        for(unsigned int y = 4; y > 0; y--) { 
            for(unsigned int x = 4; x > 0; x--) { 
                cube.setPixel(x-1, y-1, z-1, false);
                painter.paintCube(cube);
            }
        }
    }
}

void serialAnimation(const Painter& painter, Cube& cube) {
    painter.paintCube(screenCube, 50);
}

void serialEvent() {
    int availableData = Serial.available();
    Serial.println();
    Serial.print("Data ready: ");
    Serial.println(availableData);
    for(int i = 0; i < availableData; ++i) {
        offscreenCube.getBuffer()[readBytes] = (unsigned char)Serial.read();
        ++readBytes;
        Serial.print(offscreenCube.getBuffer()[readBytes], HEX);
        Serial.print(" ");
        if(readBytes == offscreenCube.getSize()) {
            Serial.println();
            Serial.println("switching cube");
            Cube& tmp = screenCube;
            screenCube = offscreenCube;
            offscreenCube = tmp;
            readBytes = 0;
        }
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(Serial.available() > 0) Serial.read();
}

void loop() {
  animator.play(serialAnimation, cube);
}

