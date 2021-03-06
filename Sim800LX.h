/*
  Sim800LX.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2016, Alain Mollo

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Sim800LX_h
	#define Sim800LX_h

	#include <SoftwareSerial.h>

	//================================================================================
	//================================================================================
	//  Sim800LX

	// SIM800 RX and TX default pins
	#define SIM800_RX_PIN_DEFAULT 3
	#define SIM800_TX_PIN_DEFAULT 4

	// SIM800 Reset pin
	#define RESET_PIN 5

	// SIM800 Default baud rate
	#define SIM800_BAUD_RATE_DEFAULT 9600

	// SIM800 Max time out for response
	#define MAX_TIME_OUT 1000

	// Max response await
	#define RESPONSE_COUNT_OUT 2

	// Set debug mode
	// #define DEBUG_MODE_SET

	// Sim800L module class driver
	class Sim800LX : public SoftwareSerial
	{
		private:
			// Private Data buffer
			String _buffer;

			// Inner class receive pin datastore
			uint8_t _ReceivePin;

			// Private method for reading serial data incomming from Sim800L after a command
			String _readSerial(void);

			// Private factoring method SetUp
			void SetUp(long baudrate, uint8_t receivePin);

			// Set or Reset Sim800L to automatic rtc setup from cellular network
			bool AutoCellRTC(const __FlashStringHelper * command1, const __FlashStringHelper * command2, const __FlashStringHelper * command3);

			// Send carriage return on demande
			void carriageReturn(bool cr);

			// Private method for jump in buffer posititon
			void nextBuffer(void);

		public:
			struct smsReader
			{
				String WhoSend;
				String WhenSend;
				String Message;
			};

			struct dateTime
			{
				uint8_t day;
				uint8_t month;
				uint8_t year;
				uint8_t hour;
				uint8_t minute;
				uint8_t second;
			};

			// Base constructor
			Sim800LX(void);

			// Constructor with capabilities to set rx and tx pin's
			Sim800LX(uint8_t receivePin, uint8_t transmitPin);

			// Constructor with capabilities to set rx and tx pin's and also baud rate
			Sim800LX(uint8_t receivePin, uint8_t transmitPin, long baudrate);
			
			// Send command to module (optimized)
			void sendCommand(String command, bool cr = true);

			// Send command to module (optimized)
			void sendCommand(char command, bool cr = true);

			// Send command to module (optimized)
			void sendCommand(char * command, bool cr = true);

			// Send command to module (optimized)
			void sendCommand(const __FlashStringHelper * command, bool cr = true);

			// Send AT command to module (optimized)
			void sendAtCommand(const __FlashStringHelper *, bool cr = true);

			// Send AT+ command to module (optimized)
			void sendAtPlusCommand(const __FlashStringHelper *, bool cr = true);

			// Wait OK response
			bool waitOK(void);

			// Wait xxx response
			bool Sim800LX::waitResponse(const __FlashStringHelper * response);

			// Waiting for good quality signal received
			uint8_t waitSignal(void);

			// Public initialize method
			void reset(void);

			// Put module into power down mode
			void powerDownMode(void);

			// Put module into sleep mode
			void sleepMode(void);

			// Put device in phone functionality mode
			bool setPhoneFunctionality(uint8_t mode);

			// Check signal quality
			uint8_t signalQuality(void);

			// Send a Sms method
			bool sendSms(char * number, char * text);

			// Send a Sms method
			bool sendSms(String number, String text);

			// Get an index Sms
			smsReader * readSms(uint8_t index);

			// Delete Indexed Sms method
			bool delSms(uint8_t index);

			// Delete all Sms method
			bool delAllSms(void);

			// Get Rtc internal Timer in decimal and string format
			String RTCtime(dateTime * result = nullptr);

			// Setup Sim800L to automatic rtc setup from cellular network
			bool setAutoCellRTC(void);

			// Setup Sim800L to non automatic rtc setup from cellular network
			bool resetAutoCellRTC(void);

			// Save All settings in memory
			bool saveAllSettings(void);

			// Change state of module led flash
			void setOnLedFlash(void);
			void setOffLedFlash(void);

			// Return the receive (interrupt) pin choice for software communication
			uint8_t getReceivePin(void);
	};
#endif