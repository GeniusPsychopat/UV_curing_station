# Open-source UV curing station project

## the What?
UV curing station, made from cheap, "off-the-shelf" parts. Held together by bad soldering, plastic welding and my hopes and prayers. Fully open-source of course, but that isn't always a good thing is it?


## Why?
I am planning on getting a SLA 3d printer and I'm way too cheap to pay for an additional curing station. So I'm making my own open-source, jank filled, mess with a buggy code. With hookers!.. and blackjack!


## How?
I used to play with arduino when I was a bit younger, so I'm trying to coax an off-brand Nano into running my code. All the frame parts + the gearbox are made from FDM 3D printer (that's the one that uses plastic filament to fill our seas with plastic). And so far all the electronics have been from AliExpress. God help us all.

I will try to include all the code, sketches/diagrams, .stl files, and anything else I can think of, so that someone could (no idea why) make himself his own.


## When?
In my free time mostly.. I do have a day job, plus wayyy to many responsibilities to make any promises to keep, but if I'm in the mood I'm gonna make some goddamn commits. I would like to finish by the end of September 25', cuz that's when I want to get the printer, but I may make updatese from time to time afterwards.

## Part list
In no particular order:
1. Arduino Nano - The brains of this operation, pretty sure any Arduino could work with some little changes to the code
2. LCD screen - I am using a 16x2 variant, because it came free with my learners kit of Ardui
3. Normal Open Button x2 - Normal, run-of-the-mill button, allows you to control this 'thing'
4. Stepper motor - Any could do, I am using the smallest NEMA knock-off I could find on AliExpress
5. A4988 stepper driver - Could do without this, but numbers are hard. Is used to control the servo
6. Stepper driver expansion shield - Again, could do without this, but numbers are hard, and apparently this uses less cables or whatever
7. 24V Fan - Used to cool down this circus, any voltage could work as long as you are willing to work for it
8. Transformer - used to reduce your wall power AC to 24DC for the electronics
9. LM2596 - DC to DC buck converter, used to reduce the voltage from 24V to 5V for the Ardui
10. 24 LEDs and 24 60ohm resistors - The reason why am I doing all this

I believe this is everything, will fix if I find something I missed
