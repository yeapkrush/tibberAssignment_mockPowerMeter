#include <Arduino.h>
#include <stdio.h>
#include <string.h>

#include "../lib/Variables.h"

char readBuff[1024] = {0};
int pos = 0;

void clearBuff()
{
  Serial.print(readBuff);
  for (int i = 0; i <= pos + 1; i++)
    *(&readBuff[0] + i) = 0;
  pos = 0;
}

// void clearBuff()
// {
//   for (int i = 0; i <= pos + 1; i++)
//   {
//     Serial.print(*(&readBuff[0] + i));
//     *(&readBuff[0] + i) = 0;
//   }

//   pos = 0;
// }
char str[1024];

bool sendId = false;
bool sendData = false;
bool updateBaudrate = false;
int baud = 300;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(300, SERIAL_7E1, 4, 5);
  Serial.println("Power Meter Restarted");
  delay(100);
  Serial2.setTimeout(50);

  strcpy(str, i0);
  strcat(str, i1);
  strcat(str, i2);
  strcat(str, i3);
  strcat(str, i4);
  strcat(str, i5);
  strcat(str, i6);
  strcat(str, i7);
  strcat(str, i8);
  strcat(str, i9);
  strcat(str, i10);
  strcat(str, i11);
  strcat(str, i12);
  strcat(str, i13);
  strcat(str, i14);
  strcat(str, i15);
  strcat(str, i16);
  strcat(str, i17);
  strcat(str, i18);
  strcat(str, i19);
  strcat(str, i20);
  strcat(str, i21);
  strcat(str, i22);
  strcat(str, i23);
  strcat(str, i24);
  strcat(str, i25);
}

void loop()
{
  if (updateBaudrate)
  {
    if (Serial2.available())
      int input = Serial2.read();
    Serial.print("Baudrate: ");
    Serial.println(baud);
    updateBaudrate = false;
    Serial2.updateBaudRate(baud);
    if (Serial2.available())
      int input = Serial2.read();
    delay(50);
    // Serial2.end();
    // delay(50);
    // Serial2.begin(baud, SERIAL_7E1, 4, 5);
    // delay(50);
  }
  else if (sendId)
  {
    if (Serial2.available())
      int input = Serial2.read();
    sendId = false;
    Serial2.write(devId);
  }
  else if (sendData)
  {
    if (Serial2.available())
      int input = Serial2.read();
    sendData = false;
    Serial2.write(str);
    Serial2.flush();

    baud = 300;
    updateBaudrate = true;
  }
  else if (Serial2.available())
  {
    while (Serial2.available())
    {
      int input = Serial2.read();
      *(&readBuff[0] + pos) = (char)input;
      pos++;

      bool clearFlag = false;
      if (input == 10)
        clearFlag = true;

      if (strcmp(readBuff, "/?!\r\n") == 0)
        sendId = true;
      else if (strcmp(readBuff, ack) == 0)
      {
        baud = 4800;
        updateBaudrate = true;
        sendData = true;
      }

      if (clearFlag)
        clearBuff();
    }
  }

  delay(50);
}