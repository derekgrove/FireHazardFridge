# FireHazardFridge
An open source fridge that cost too much money and took 50+ hours to build! Also it's very energy inefficient

## Disclaimers!
By no means is this a "good fridge", this was a challenge and an exercise for myself. I built it out of love and the humor of it all. Yes, the fridge really is a fire hazard, the frame is wood in my build (although you are welcome to make a different frame or box or whatever). 

Some suggested improvements: if you want a pretty legit homemade minifridge, build a metal frame somehow. Would likely cost an arm and leg, alghough maybe one could be built from those aluminum extrusions like what a 3D printer is made from. I'm actually sad I didn't have this idea sooner, I most definitely would've went that route. Wood was more accessible and easier to cut for me, the aluminum extrusions would need cut to whatever dimensions you need for your fridge.

Anyways, the more interesting part is the electronics. My arduino source code files can be found in this repo. The arduino code is relatively simple as far as arduino code goes. The arduino is the heart of the project, it controls everything and I have tried to program it in such a way that if it were to die then the fridge bricks itself. I've done this by using MOSFETS, so if the arduino isn't sending PWM's to the MOSFETs then no device is getting any sort of power. 

I have also put a couple other saftey measures in place, if the temperature monitor on the heat sink detects "too high of a temp" (tbd what that temp is) then it sets the PWM to the peltiers to 0 duty cycle and loops infinitely like that. Should also display on the screen a warning that it was too hot! This then is your indication to turn off and back on the fridge after its had enough time to cool down. If it happens routinely, it's likely there is a problem, either the water pump isn't working, the fans on the radiator aren't running, or the water is too warm (or not enough water, thus it gets too warm too fast).
