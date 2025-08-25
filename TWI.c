/*
 * TWI.c
 *
 * Created: 25.08.2025 16:10:08
 * Author : didlox1
 */ 
#define F_CPU 16000000  //16Mhz Clock freq for atmega328p MCU. You can comment it to make it 8Mhz default defined in delay.h header file
#define SLAVE_ADDR 0x27

#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

void TWI_Start(){
	// Set SCL to 100kHz (for 16MHz CPU)
	TWSR = 0x00;								 // Prescaler = 1
	TWBR = 72;
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);  //Send START signal
	while(!(TWCR & (1<<TWINT))); 				 //WAIT for the shift register to end sending data to SDA bus
}

void TWI_Stop(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);		 //Send STOP signal
	_delay_us(100);								 // Wait for STOP to complete
}

void TWI_Write(uint8_t data){
	TWDR = data;								 //Send DATA to SLAVE (display setup data)
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));				 //WAIT
}

int main(void)
{
	uint8_t data = 0x00;						 //Bits that will be sent through TWI interface
	TWI_Start();								 //Starting TWI interface
	TWI_Write((SLAVE_ADDR << 1) | TW_WRITE	);	 //Make a Master as a transmitter and SLAVE a receiver
	TWI_Write(data);							 //Sends data to the SLAVE
	TWI_Stop();
}

