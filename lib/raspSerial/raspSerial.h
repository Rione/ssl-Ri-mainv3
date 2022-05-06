#ifndef _RASPSERIAL_
#define _RASPSERIAL_

#include "mbed.h"
#include "RobotInfo.h"

class raspSerial {
  public:
    raspSerial(PinName TX, PinName RX);
    void receiveRx();
    void put(int val);
    void get(float &a, int num);
    void print(float val);
    void syncFromRasp(RobotInfo &_info);

  private:
    static const int8_t BUFFER_SIZE = 7;
    //ここ元々intだったのですが8bitの変数しか扱えない空間でint(32bit)はアウトなのでuint8_tにしておきます。
    uint8_t buffer[64];
    RawSerial device;
    int8_t bufferCount;

    RobotInfo info;
};

#endif