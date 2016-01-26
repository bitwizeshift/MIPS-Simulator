# MIPS-Simulator
A small pet-project that I wrote that executes MIPS binary and can print out registers.

I originally wrote this in 2013 after reading [Computer Organization and Design: The Hardware-Software Interface](http://www.amazon.com/Computer-Organization-Design-Fourth-Edition/dp/0123744938). The book introduced the MIPS assembly language, and I figured the best way to learn it would be to write a simulator for the language -- which could be a fun project to write in C++.

After finding my original code for it, I decided to extend it and to attempt to implement an assembler for the language as well -- so that this program can serve as both an assembler and a simulator at the same time.


Currently, only the main code for the simulator exists, but is not directly callable -- though I hope to change that in the following weeks. 

Right now I still need to implement the coprocessor and exception handling, both of which are relatively hard to find concrete information on. Coprocessor0 is especially important, as it has registers that contain important information with regards to exceptions.