# IO Buttons Addition
 - Task 0: Display port B LEDs one by one from right to left. Each LED has 1 second, it blinks 5 times.
 - Task 1: Display port B LEDs from center to edges, i.e., they should be turned on in this order: xxxooxxx, xxoxxoxx, xoxxxxox, oxxxxxxo, and repeat.
 - Task 2: Use both port A and B as output port, and flush the 16 LEDs from left to right with an interval of 200ms of each LED.
 - Task 3: Improve task 2 by acceleration. It means the interval between LEDs is getting smaller and smaller. The first interval is 1000ms, the next
is 950, then 900, ….
 - Task 4: Use Port B to control LEDs, use Port D as button input ports. Let each button controls 1 LED: when PD7 is pressed, it will toggle LED on
PB7. The program starts with all LEDs are OFF.
 - Task 5: Use Port B to control LEDs, and Port D as button inputs. When program starts, it blinks PB7 at 0.1Hz. When any button(s) is/are pressed, the program blinks PB7 at 10Hz.
