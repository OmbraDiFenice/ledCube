# Install arduino-cli

```
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```

This whill download the `arduino-cli` executable in a `bin` folder inside the current directory.
Copy this executable in a location in your PATH to have it available from any position.

You can also setup the bash completion for it with 

```
arduino-cli completion bash > arduino-cli.sh
sudo mv arduino-cli.sh /etc/bash_completion.d/
```

For other shells refer to https://arduino.github.io/arduino-cli/0.16/command-line-completion/

# Initialize the cli

```
arduino-cli config init
arduino-cli core install arduino:avr
arduino-cli core update-index
```

# Create a new sketch

```
arduino-cli sketch new ledCube
```

From now on any arduino-cli command working with the sketch will have to use the name `ledCube`.

# Compile and upload

Use the script `flash.sh`

# Serial monitor

You can use `screen` to connect to the serial monitor.

    IMPORTANT: as long as screen is keeping the connection to the serial device opened you won't be able to flash anything on the Arduino.
    You'll have to close screen in order to upload a new sketch.

## Open serial monitor

```
screen /dev/ttyUSB0 115200
```

## Close serial monitor

To close the screen session use the key combination `Ctrl-a` followed by `\\`, then confirm on the prompt with `y`.

