# SmartPets

@author Bijan Ghasemi Afshar (b.ghasemi-afshar@uea.ac.uk)
@author Richard Tristan Sabiers (r.sabiers@uea.ac.uk)


Control system for a smart hamster cage.
Contains GUI for controlling a smart hamster cage and is an event-based system with 3 program modes, day, night and play (which are controlled manually in the final version due to code size limit).

This software contols an STM32F746G-Discovery board which is used as a controlling system for perpherals on a hamster cage.
A Raspberry Pi acts as a perpheral, being connected to a camera. This is controlled by the Discovery board and acts as a web server transmitting image data to a web page. No other processing other than the image data is handled by the pi. Many other sensors are attached to the Discovery board using its native GPIO pins, with both digital and analogue pins being used. 




The clock system is threaded and provides the backbone for the rest of the sensors to communicate with the rest of the architecture. 

The door functionality uses mutex when closing to prevent the hamster from getting hurt, a light sensor locks the system when obstructed preventing the servo from completeing the close operation until the obstruction is cleared. 

