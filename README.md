# SPRO2MC
**_SWING SWING SWING THE APE GENTLY DOWN THE RAIL. HOPE IT WON'T FALL, HOPE IT WON'T FALL OR ELSE WE'LL ALL JUST FAIL_** 

 **TO CONTROL THE MOTORS**
 - Use the custom function created called: **_motors()_** 
 - This is what the *PROTOTYPE* function looks like **_void motors(unsigned char motorNr, unsigned char movment, unsigned int speed )_**
 > - Unsigned char motoNr = assign the motor number such as M1, M2, M3 or M4
 > - Unsigned char movement defines how the motor will spin - CCW (Counterclockwise) CW (Clockwise)
 > - Unsigned char speed = defines the *speed* of the motor **LOWEST** value 0, **HIGHEST** - 0xfff (4095 in BINARY)
 - To **STOP** a motor use **motor_set_state(motor nr, STOP)**, replacing the variable *motor nr* with the motor you want to stop. (M1, M2, M3 or M4)

Calculate the RPM and HEX values for Motors:
https://docs.google.com/spreadsheets/d/1jSR5PAT4rw37uSOZTdlW205r7602VoMGzFZtLPvw88U/edit#gid=0
