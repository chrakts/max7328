/*
 * max7328.h
 *
 * Created: 01.01.2016 13:35:13
 *  Author: Christof
 */


#ifndef MAX7328_H_
#define MAX7328_H_

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "twi_master_driver.h"

class MAX7328
{
	private:

	TWI_MasterDriver_t *twi;
	uint8_t	oldValue;
	uint8_t	twiAddress;
	uint16_t raw_data;
	double illuminance;
	protected:
	/** Output pins values */
	volatile uint8_t _PORT;

	/** Current input pins values */
	volatile uint8_t _PIN;

	/** Pins modes values (OUTPUT or INPUT) */
	volatile uint8_t _DDR;

	/** PCF8574 I2C address */
	uint8_t _address;

	public:
  enum {INPUT=0,INPUT_PULLUP,OUTPUT};
	MAX7328();
	MAX7328(TWI_MasterDriver_t *mytwi,int address);
  void pinMode(uint8_t pin, uint8_t mode);
  void updateGPIO();
  void setOutput(uint8_t pin);
  void clearOutput(uint8_t pin);

  void newValue(uint8_t val);
  void updateValue(uint8_t val);
	uint8_t getGPIO();

};


#endif /* MAX7328_H_ */
