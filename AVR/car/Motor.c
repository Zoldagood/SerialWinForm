﻿/*
 * Motor.c
 *
 * Created: 2018-10-01 오후 7:09:22
 *  Author: kccistc
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart0.h"
#include "uart1.h"
#include "motor.h"

void motorInit()
{
	DDRB |= (1 << PORTB5) | (1 << PORTB6);										// PORTB5 = OCR1A, PORTB6 = OCR1B
	DDRE |= (1 << PORTE3) | (1 << PORTE4);										// PORTE3 = OCR3A, PORTE4 = OCR3B
	
	TCCR1A |= (1 << COM1A1)| (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0);			// 비반전출력모드
	TCCR1A |= (1 << WGM11) | (1 << WGM10); 											// 10비트 고속 PWM
	TCCR1B |= (0 << WGM13) | (1 << WGM12);
	TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);								// 분주비 256
	
	TCCR3A |= (1 << COM3A1)| (1 << COM3A0) | (1 << COM3B1) | (1 << COM3B0);			// 반전출력모드
	TCCR3A |= (1 << WGM31) | (1 << WGM30);											// 10비트 고속 PWM
	TCCR3B |= (0 << WGM33) | (1 << WGM32);
	TCCR3B |= (1 << CS32) | (0 << CS31) | (0 << CS30);								// 분주비 256
}

void print_menu(void)
{
	printf("1. idle\r\n");
	printf("2. go\r\n");
	printf("3. back\r\n");
	printf("4. left\r\n");
	printf("5. right\r\n");
	printf("6. stop\r\n");
	
}

void motor_go(void)
{
	LeftWheelGo = 400;
	LeftWheelBack = 0;
	RightWheelGo = 400;
	RightWheelBack = 0;
	_delay_ms(100);
	motro_acc();
	_delay_ms(50);
	printf("motor go\r\n");
}

void motor_back(void)
{
	LeftWheelGo = 0;
	LeftWheelBack = 400;
	RightWheelGo = 0;
	RightWheelBack = 400;
	_delay_ms(100);
	printf("motor back\r\n");
}
void motor_left(void)
{
	LeftWheelGo = 100;
	LeftWheelBack = 0;
	RightWheelGo = 400;
	RightWheelBack = 0;
	_delay_ms(100);
	printf("motor right\r\n");
}

void motor_right(void)
{
	LeftWheelGo = 400;
	LeftWheelBack = 0;
	RightWheelGo = 100;
	RightWheelBack = 0;
	_delay_ms(100);
	printf("motor left\r\n");
}

void motor_stop(void)
{
	LeftWheelGo = 0;
	LeftWheelBack = 0;
	RightWheelGo = 0;
	RightWheelBack = 0;
	printf("motor stop\r\n");
}

void motro_acc(void)
{
	if(UART1_rx_check())
	{
		char accinput;
		accinput = UART1_receive();
		switch(accinput)
		{
			case 'U':
			LeftWheelGo=LeftWheelGo+100;
			RightWheelGo=RightWheelGo+100;
			break;
			case 'D':
			LeftWheelGo=LeftWheelGo-100;
			RightWheelGo=RightWheelGo-100;
			break;
		}
	}
}