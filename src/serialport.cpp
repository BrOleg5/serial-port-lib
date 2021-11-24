#include "serialport.hpp"

void CloseComPort(HANDLE& port)
{
  PurgeComm(port, PURGE_RXABORT | PURGE_TXABORT | PURGE_RXCLEAR | PURGE_TXCLEAR);
  if(port != INVALID_HANDLE_VALUE) // if comm port is not closed
    CloseHandle(port);
  else
    printf("Communication is closed with errors\n");
  port = INVALID_HANDLE_VALUE;
}

bool ComPortSettings(unsigned baud)
{
  DCB PortDCB = { 0 };
  // Get the default port setting information.
  PortDCB.DCBlength = sizeof (DCB);
  if (!GetCommState (hPort, &PortDCB)) {
    printf("Unable to configure the serial port\n");
    return false;
  }

  // Change the DCB structure settings.
  // Current baud 
  PortDCB.BaudRate = baud;
  // Binary mode
  // PortDCB.fBinary = TRUE;
  // Number of bits/byte, 4-8 
  PortDCB.ByteSize = 8;
  // 0-4 = no,odd,even,mark,space
  PortDCB.Parity = NOPARITY; 
  // 0,1,2 = 1, 1.5, 2
  PortDCB.StopBits = ONESTOPBIT; 

  if (!SetCommState (hPort, &PortDCB))
  {
    CloseComPort(hPort);
    printf("Unable to configure the serial port\n");
    return false;
  }
  else return true;
}

bool ComPortTimeouts(void)
{
  COMMTIMEOUTS CommTimeouts = { 0 };

  GetCommTimeouts (hPort, &CommTimeouts);
  CommTimeouts.ReadIntervalTimeout = MAXDWORD; // aproximativelly 50 days
  CommTimeouts.ReadTotalTimeoutMultiplier = 0;
  CommTimeouts.ReadTotalTimeoutConstant = 0;
  CommTimeouts.WriteTotalTimeoutMultiplier = 0;
  CommTimeouts.WriteTotalTimeoutConstant = 0;

  if (!SetCommTimeouts (hPort, &CommTimeouts))
  {
  CloseComPort(hPort);
  printf("Unable to set the timeout parameters\n");
  return false;
  }
  else return true;
}

bool OpenComPort(const char* name, unsigned baud)
{
  hPort=CreateFile(static_cast<LPCSTR>(name), GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if (hPort != INVALID_HANDLE_VALUE) // if comm port is opened
    if(
        ComPortSettings(baud) /*&&   // setting DCB structure
        ComPortTimeouts()     &&   // setting commtimouts structure
        SetCommMask(hPort, EV_RXCHAR)*/ // init RX event
      )
    {
      // execute comm port settings
      printf("Serial Port will be opened successfully\n");
      return true;
    }
  // error settings
  printf("Serial PORT hasn't been initialized or does not exist \n");
  return false;
}

void SendByte(const char& send)
{
  /**
   * In function WriteFile:
   * @param &send address of byte to be sent
   * @param 1 the number of bytes to send
   * @param &tBytes variable address that store information about number sent bytes
   */
  if(!WriteFile(hPort,&send,1,&tBytes,NULL))
  {
    printf("error\n");
    PurgeComm(hPort, PURGE_TXABORT );
  }
}

void ReceiveByte(char& byte)
{
  /**
   * In function ReadFile: 
   * @param &byte byte address to write received byte
   * @param 1 the number of bytes to receive
   * @param &rBytes variable address that store information about number sent bytes
   */
  if(!ReadFile(hPort,&byte, 1,&rBytes, NULL))
  {
    if(GetLastError() != ERROR_IO_PENDING) {
      std::cout << "Error in communications." << std::endl;
    }
    printf("error\n");
    PurgeComm(hPort, PURGE_RXABORT );
  }
}