/*
 * CPPFile1.cpp
 *
 * Created: 01.01.2016 13:31:08
 *  Author: Christof
 */


#include "max7328.h"


MAX7328::MAX7328(void)
{
}

MAX7328::MAX7328(TWI_MasterDriver_t *mytwi,int address)
{
	twi = mytwi;
	twiAddress = address;
	getGPIO();
	_PIN = 0;
	_PORT = 0;
	_DDR = 0;
}

void MAX7328::setOutput(uint8_t pin)
{
  _PORT |= (1 << pin);
}

void MAX7328::clearOutput(uint8_t pin)
{
  _PORT &= ~(1 << pin);
}


void MAX7328::pinMode(uint8_t pin, uint8_t mode)
{
	/* Switch according mode */
	switch (mode) {
	case INPUT:
		_DDR &= ~(1 << pin);
		_PORT &= ~(1 << pin);
		break;

	case INPUT_PULLUP:
		_DDR &= ~(1 << pin);
		_PORT |= (1 << pin);
		break;

	case OUTPUT:
		_DDR |= (1 << pin);
		_PORT &= ~(1 << pin);
		break;

	default:
		break;
	}

	/* Update GPIO values */
	updateGPIO();
}

void MAX7328::updateGPIO()
{

	/* Read current GPIO states */
	//readGPIO(); // Experimental

	/* Compute new GPIO states */
	//uint8_t value = ((_PIN & ~_DDR) & ~(~_DDR & _PORT)) | _PORT; // Experimental
	//uint8_t value = ( _PIN & (~_DDR) ) | _PORT;
	uint8_t value =  _PORT;

	/* Start communication and send GPIO values as byte */
	//twi->beginTransmission(_address);
	//twi->writeData(value);
	//I2CWRITE(value);
	//twi->endTransmission();
	TWI_MasterWrite(twi,twiAddress,&value,1);
}

void MAX7328::newValue(uint8_t val)
{
  TWI_MasterWrite(twi,twiAddress,&val,1);
  oldValue = val;
}

void MAX7328::updateValue(uint8_t val)
{
  if(val!=oldValue)
    TWI_MasterWrite(twi,twiAddress,&val,1);
  oldValue=val;
}

uint8_t MAX7328::getGPIO()
{
	TWI_MasterRead(twi,twiAddress,1);

	while (twi->status != TWIM_STATUS_READY) {
		/* Wait until transaction is complete. */
	}
	return( twi->readData[0] );
}
