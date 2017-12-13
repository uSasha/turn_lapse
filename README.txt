Hi there,
purpose of this project is to make small box that can turn photo camera and make it shot 
according to user defined values,such as:
- whole time of lapse
- turn angle
- exposure time
- communication between box and DSLR is done via IR LED

The main challenge for me was to design robust menu with clear defined transitions between states.
This was the time I discovered FSMs :)

Everithing is managed in Main.c and sate_machine.c
Also I implemented simple drivers for camera, encoder and brush motor (/drivers)
The most fun part was to debug DSLR driver, because communication interface is based on microsecond delays and is not documented properly.

Current hardware is:
- XMC1100 ARM Cortex M0 MCU,
- Nokia 5110 BW 84x48 display
- simple brushed motor
- IR diode to communicate with camera

IDE is DAVE(Eclipse + GCC)
