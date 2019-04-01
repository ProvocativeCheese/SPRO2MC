# SPRO2MC
**_SWING SWING SWING THE APE GENTLY DOWN THE RAIL. HOPE IT WON'T FALL, HOPE IT WON'T FALL OR ELSE WE'LL ALL JUST FAIL_** 


**TO CONTROL THE SOLENOID**
- The solenoid function works with inputing a 1 or a 0 in the function **_solenoid()_** 
- solenoid(1) means the solenoid will be turned **ON** and solenoid(0) is for turning the solenoid **OFF**
  
 **TO CONTROL THE MOTORS**
 - Use the custom function created called: **_motors()_** 
 - This is what the *PROTOTYPE* function looks like **_void motors(unsigned char motorNr, unsigned char movment, unsigned int speed )_**
 > - Unsigned char motoNr = assign the motor number such as M1, M2, M3 or M4
 > - Unsigned char movement defines how the motor will spin - CCW (Counterclockwise) CW (Clockwise)
 > - Unsigned char speed = defines the *speed* of the motor **_LOWEST** value 0, **_HIGHEST** - 0xfff (4095 in BINARY)
 - To **STOP** a motor use motor_set_state(motor nr, STOP), replacing the motor nr with the motor you want to stop. (M1, M2, M3 or M4)
