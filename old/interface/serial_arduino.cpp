#include "serial_arduino.hpp"
#include <Arduino.h>

void SerialArduino::setup(int32_t bitrate)
{
    switch(bitrate)
    {
    case 300: case 1200: case 2400: case 4800: case 9600:
    case 14400: case 19200: case 28800: case 38400: case 57600: case 115200:
        Serial.begin(bitrate);
        break;
    default:
        break;
    };
}

//int SerialArduino::read(uint8_t* data, int size)
//{
//    return Serial.read();
//}

int SerialArduino::write(const uint8_t* data, int size)
{
    return Serial.write(data, size);
}

int SerialArduino::printf(const char* format, ...)
{
    char buffer[128];
    va_list ap;
    int len;
    va_start(ap, format);
    len = vsprintf(buffer, format, ap);
    va_end(ap);
    return Serial.write((uint8_t*)buffer, len);

    ////Serial.println(len);
    ////浮動小数の数をカウント
    //int flNum = 0;
    //char format2[128];
    //for(int i = 0; i < len; i++)
    //{
    //    Serial.print(i);
    //    Serial.println(format[i]);
    //    if(i < len - 1 && format[i] == '%' && format[i+1] == 'f')
    //    {
    //        flNum++;
    //    }

    //    //ついでにコピー
    //    format2[i] = format[i];
    //}

    ////Serial.print("flNum: ");
    ////Serial.println(flNum);

    //if(flNum == 0)
    //{
    //    return Serial.write((uint8_t*)buffer, len);
    //}
    //else
    //{
    //    /* code */
    //    char buf[flNum+1][128];
    //    int bufPos = 0;
    //    char* bufTmp;
    //    for(int i = 0; i < len; i++)
    //    {
    //        if(i < len-1 && format2[i] == '%' && format2[i+1] == 'f')
    //        {
    //            format2[i] = '\0';

    //            int cnt = 0;
    //            while(*(bufTmp + cnt))
    //            {
    //                buf[bufPos][cnt] = bufTmp[cnt];
    //                cnt++;
    //                Serial.println(cnt);
    //            }

    //            //次
    //            bufPos++;
    //            bufTmp = &format2[i+2];
    //            Serial.println(bufTmp);
    //        }
    //    }
    //}
    
    //return 0;
}
