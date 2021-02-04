# Digital-Stopwatch
 The Project Objective is to implement a digital stopwatch based on ATmega16 microcontroller and multiplexed 7-segments modules.
 
 #### ATmega16 Modules:
 - Timer1 CTC Mode is used to count the time for the stop watch.

 - Interrupts:
   - INT0 (Falling edge using the internal pull up) --> reset the stop watch
   - INT1 (raising edge using the external pull down) --> pause the stop watch
   - INT2 (Falling edge using the internal pull up) --> resume the stop watch.
