/**
 * Source @link http://we.easyelectronics.ru/electro-and-pc/rs232-vzglyad-iznutri.html
 */

#ifndef SERIALPORT_HPP
#   define SERIALPORT_HPP 

#include <windows.h>
#include <cstdlib>
#include <iostream>

// Object that controls serial port
static HANDLE hPort;
// Variable that contains information about serial port interruption
static DWORD dwMask;
// Variables that store received/transmitted bytes
static DWORD rBytes,tBytes;

/**
 * Close serial port.
 * 
 * @param port object that controls serial port
 */
void CloseComPort(HANDLE& port);

/**
 * Set serial port settings.
 * 
 * @param baud baud rate
 */
bool ComPortSettings(unsigned baud);

/**
 * Determine serail port timeouts.
 */
bool ComPortTimeouts(void);

/**
 * Open serial port.
 * 
 * @param name serail port name from COM1 to COM7
 * @param baud baud rate
 */
bool OpenComPort(const char* name, unsigned baud);

/**
 * Send byte in serial port.
 * 
 * @param send byte to be sent
 */
void SendByte(const char& send);

/**
 * Receive byte.
 * 
 * @param byte received byte
 */
void ReceiveByte(char& byte);

#endif