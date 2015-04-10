// Change this if required if not using a 16MHz board
#ifndef F_CPU
#define F_CPU 16000000UL 
#endif

#include <avr/io.h>
#include <util/delay.h>

/*

This is a stripped down version that simply outputs same fades to DMX channel 1

This uses the hardware serial pins 0 and 1 (technically just 1), do not call Serial.begin() in this sketch.

*/




// If you need to output less than 512 channels, you can reduce this number to save memory. 
// If you don't need to save memory, I recommend keeping it here.
#ifndef CHANNELS
#define CHANNELS 512
#endif

// Start low-level DMX stuff -- DO NOT MODIFY
uint8_t volatile universe[CHANNELS + 1];
uint16_t volatile num_channels;
uint16_t volatile start_address;
uint16_t volatile channel = 0;
uint8_t volatile need_break = 0; 
uint8_t volatile start_packet = 0;
uint8_t volatile ptr = 0;


// Sets address to value, range checks.
void DMXput(uint16_t address, uint8_t value)
{
	if(address >= start_address && address < start_address + num_channels)
	{
		universe[address - start_address] = value;
	}
}

void dmx_break(void) 
{
	// Disable TXD0 and pull low PD1
	PORTD = 0b11111100;
	UCSR0B = 0b00000000;
	_delay_us(20);
        _delay_us(20);
        _delay_us(20);
        _delay_us(20);
        _delay_us(20);
        _delay_us(20);

        _delay_us(20); // DMX-512 defines minimum break as 92us, we need to add 20us for the last slot to finish transmitting after we disable the TX.
}

void dmx_mab(void)
{
	PORTD = 0b11111110; // pull high
	_delay_us(11); // DMX-512 defines minimum mab as 12us, we get 2us as the TX enables.
	UCSR0B = 0b00101000; // re-enable TXD0
}

// Initalizes start address and number of channels
void DMXinit(uint16_t address, uint16_t number) {

  DDRD = 0b00000010; /* set PD2 to output */
  PORTD = 0b11111100; // Set low, so we get a low value when TX is disabled. Magic.


	cli();
	UBRR0L = (F_CPU / 0x3d0900) - 1; 
	UBRR0H = 0;
	UCSR0C = 0b00001110;
	UCSR0B = 0b10101000; // enabled value, disabled value is UCSR0B = 0b00000000;
	UCSR0A = 0x00;
	
	sei();
	
	start_address = address;
	if(number <= CHANNELS)
	{
		num_channels = number;
	}
	else
	{
		num_channels = CHANNELS;
	}
      
        
}

// Interrupt handler for each sent data packet.    
ISR(USART_UDRE_vect)
{
	if(need_break)
	{
               
		dmx_break();
		dmx_mab();
		need_break = 0;
               
	}

	if(channel == 0 && start_packet == 0)
	{
		UDR0 = 0x00;
		start_packet = 1;
		return;
	}
	
	channel++;
	if(channel > 512)
	{
		channel = 0;
		start_packet = 0;
		need_break = 1;
		return;
	}
	
	if(channel < start_address || channel > start_address+num_channels)
	{
		UDR0 = 0x00;
	}
	else
	{
		UDR0 = universe[channel - start_address];
	}
	
	return;
}

// END Low-level stuff, feel free to modify below this line

bool pinInputs[3];

void setup()
{
  DMXinit(1,512); // Initializes DMX output with all 512 slots and starting with 1
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(13,OUTPUT); // LED for status
  
}

// We have an Interrupt handler that takes care of outputting the DMX universe
// So all we have to do is called DMXput() and it'll update in the next update.
// DMXput(channel, level);  -- this is the absolute channel number.

void fadeLoop(int firstDelay, int secondDelay)
{
    int x; // Just a variable so we can do fades
  
  for(x = 0; x < 255; x++)
  {
    if (pinInputs[0] == HIGH) {
    DMXput(1,x);  // Fade channel 1 from 0-255
    DMXput(2,x);
    DMXput(3,x);
    }
    if (pinInputs[1] == HIGH) {
    DMXput(4,x);
    DMXput(5,x);
    DMXput(6,x);
    }
    if (pinInputs[2] == HIGH) {
    DMXput(7,255-x);
    DMXput(8,255-x);
    DMXput(9,255-x);
    }
    delay(firstDelay); // Take 2.55 seconds (2550 milliseconds) to execute fade 
  }
  
  
  for(x = 255; x > 0; x--)
  {
    if (pinInputs[0] == HIGH) {
    DMXput(1,x);  // Fade channel 1 from 255-0
    DMXput(2,x);
    DMXput(3,x);
    }
    if (pinInputs[1] == HIGH) {
    DMXput(4,x);
    DMXput(5,x);
    DMXput(6,x);
    }
    if (pinInputs[2] == HIGH) {
    DMXput(7,255-x);
    DMXput(8,255-x);
    DMXput(9,255-x);
    }
    delay(secondDelay); // Take 2.55 seconds (2550 milliseconds) to execute fade 
  }
  delay(300);
}

bool toggled = false;

void loop()
{

  pinInputs[0] = digitalRead(2);
  pinInputs[1] = digitalRead(3);
  pinInputs[2] = digitalRead(4);
  if (pinInputs[0] || pinInputs[1] || pinInputs[2]) {
    fadeLoop(1,4);
 //   fadeLoop(1,4);
 //   fadeLoop(1,4);
  }
  
  delay(10);
}



