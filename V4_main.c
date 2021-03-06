#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PCA9685.h"
#include "i2cmaster.h"

void motor_set1438_controlpin(unsigned char pin_adr, unsigned char level);
void motor_set_state(unsigned char motor_number, unsigned char state);
void motor_set_pwm(unsigned char motor_number, unsigned int on_value, unsigned int off_value);
void motor_init_pwm(unsigned char frequency);

void solenoid(int value); // if value is 0 then solenoid is off, otherwise 1 is on
void motors(unsigned char motorNr, unsigned char movment, unsigned int speed );
void motor_speed(int delay2, unsigned char motor_nr, unsigned char movement, int speed);
void start_switch(void);
void setup();
void initialize_motors();

unsigned char motorNr;
unsigned char movment;
unsigned int speed;
volatile unsigned char shutdown=1;



int main (void)
{
	i2c_init();
	initialize_motors(); // Sets all the inputs/outputs and sets the motor frequency etc
	
	while(1)
	{
		while ( shutdown == 0 ){ // When the robot is setup correctly
			//motor_set_state(M1, STOP);
			motor_set_state(M2, STOP);
			motor_set_state(M3, STOP);
			
			if ((~PIND) & (1<<PIND6)){ // If Button 6  is pressed it starts
				_delay_ms(2000); // wait 2 seconds until the griper starts to fall
				start_switch();
			shutdown = 31;}
		}
		
		if (!((~PINB) & (1<<PINB0))) { // Switch is pressed - close the gripper
			motor_set_state(M1,STOP);
			motors(M3,CCW,0xFFF);
			_delay_ms(400);
		motor_set_state(M3, STOP); }
		
		
		while ( shutdown == 1 )	setup();
	}
}

void start_switch(void)
{
	motors(M3,CW,0xFFF); // gripper
	motors(M1, CCW, 0xFFF);
	_delay_ms(300);
	motor_set_state(M3,STOP);
	_delay_ms(300);
	motors(M1, CCW, 0xFFF);
	motor_set_state(M1, STOP);
	motors(M3,CCW,0xFFF);
	motor_set_state(M3,STOP);
}

void motors(unsigned char motorNr, unsigned char movment, unsigned int speed )
{
	motor_set_state(motorNr, movment); // CCW - Counter-clock wise
	motor_set_pwm(motorNr, 0, speed); // 0x1ff - slow speed
}

void setup(){
	// LEFT Arm & Gripper (Right looking from the button)
	while ((~PINC) & (1<<PINC0)) // Button 1
	{	//ARM
		if ((~PINC) & (1<<PINC3)) motors(M1,CCW,0xFFF);// Button 4 - CCW
		if ((~PINC) & (1<<PINC2)) motors(M1,CW,0xFFF);// Button 3 - CW
		
		//GRIPPER
		if ((~PIND) & (1<<PIND7)) motors(M3,CCW,0xFFF);// Button 5 - CLOSE
		if ((~PIND) & (1<<PIND6)) motors(M3,CW,0xFFF);// Button 6 - Open
	}
	
	// RIGHT Arm & Gripper (Left looking from the button)
	while ((~PINC) & (1<<PINC1)) // Button 2
	{	//ARM (Red next to ground )
		if ((~PINC) & (1<<PINC3)) motors(M2,CCW,0xFFF);// Button 4 - CCW
		if ((~PINC) & (1<<PINC2)) motors(M2,CW,0xFFF);// Button 3 - CW
		
		//GRIPPER ( Black next to ground )
		if ((~PIND) & (1<<PIND7)) motors(M4,CCW,0xFFF);// Button 5 - CLOSE
		if ((~PIND) & (1<<PIND6)) motors(M4,CW,0xFFF);// Button 6 - OPEN
	}

	if ((~PINC) & (1<<PINC3)) shutdown = 0; // Button 3 makes it ready for start
	
	motor_set_state(M1, STOP);
	motor_set_state(M2, STOP);
	motor_set_state(M3, STOP);
	motor_set_state(M4, STOP);
}

void initialize_motors(){
	DDRD = 0x00; //I/O board:PD4-7 as outputs, for LEDs
	DDRC = 0x00; //I/O board PC0-3 as inputs, for buttons
	DDRB = 0x00; // Make PB5 as output (LED on the NANO)
	PORTC = 0xFF; // 3: for temp sensor; F: Enable internal pull at for buttons
	PORTD = 0xFF; // Set output LEDs to off
	PORTB = 0xFF;
	
	motor_init_pwm(PWM_FREQUENCY_1500);
	motor_set_state(M1, STOP);
	motor_set_state(M2, STOP);
	motor_set_state(M3, STOP);
	motor_set_state(M4, STOP);
}
