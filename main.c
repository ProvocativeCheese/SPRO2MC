/*
 * test222.c
 *
 * Created: 3/21/2019 9:44:16 AM
 * Author : jonas
 */ 
#define F_CPU 16e6
#include <avr/io.h>
#include <util/delay.h>
#include "i2cmaster.h"
#include "PCA9685.h"


void motor_set1438_controlpin(unsigned char pin_adr, unsigned char level);
void motor_set_state(unsigned char motor_number, unsigned char state);
void motor_set_pwm(unsigned char motor_number, unsigned int on_value, unsigned int off_value);
void motor_init_pwm(unsigned char frequency);

void solenoid(int value); // if value is 0 then solenoid is off, otherwise 1 is on
void motors(unsigned char motorNr, unsigned char movment, unsigned int speed );
void motor_speed(int delay2, unsigned char motor_nr, unsigned char movement, int speed);

unsigned char motorNr;
unsigned char movment;
unsigned int speed;


int main(void)
{
	i2c_init();
	
	DDRD = 0b11111101;
	PORTD = 0b00000010;
	
	motor_init_pwm(PWM_FREQUENCY_1500);
	
	motor_set_state(M1, STOP);
	motor_set_state(M2, STOP);
	
		
	//motor_set_state(M1, CCW); // CCW - counter clockwise CW - clockwise 
	//motor_set_pwm(M1, 0, 0xfff); // 0xFFF is the highest value 
	
	motors(M1,CW,0xfff);
	
	
	while(1)
	{		
		if(PIND == 0b0000010 ) motor_set_state(M1, STOP); // When PIN2 is grounded the motor M1 turns off
		else  motors(M1,CW,0xfff);
		
		solenoid(1);
		_delay_ms(5);
		solenoid(0);
		_delay_ms(5);
	}

}


void solenoid(int value)
{
	if(value == 1) // turn the solenoid on
	{
		motor_set_state(M3, HIGH);
		motor_set_pwm(M3, 0, 0xfff);
	}
	if(value == 0) // turn the solenoid off
	{
		motor_set_state(M3, STOP);
		motor_set_pwm(M3, 0, 0);
	}
	
}
void motors(unsigned char motorNr, unsigned char movment, unsigned int speed )
{
	motor_set_state(motorNr, movment); // CCW - Counter-clock wise
	motor_set_pwm(motorNr, 0, speed); // 0x1ff - slow speed
}
