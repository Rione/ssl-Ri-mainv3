#ifndef _MODEMAIN_
#define _MODEMAIN_

#include "setup.h"

Timeout dribTimeout;

void dribleOff() {
    // タイマー割り込みでドリブルをオフにする
    dribler.write(0.0);
}

void actuatorTests() {
    // dribler test
    if (swDrible.read() == false) {
        dribTimeout.attach(dribleOff, 1);
        dribler.write(1.0);
    }
    // kicker test
    if (swKicker.read() == false) {
        kicker.Kick();
    }
}

void before_main() {
    // bodyを実行する直前に1度だけ実行する関数
    pc.printf("before main\r\n");
}

// モードのメインプログラムを書く関数.この関数がループで実行されます
void body_main() {
    actuatorTests();
    info.photoSensor = ballPhoto.read();
    info.isHoldBall = (info.photoSensor < BALL_DETECT_VALUE);
    raspBallDetectSig = LED = info.isHoldBall;
    rasp.syncFromRasp(info);
    MD.setVelocity(info);
    pc.printf("working\r\n");
}

void after_main() {
    // モードが切り替わり、bodyが実行し終えた直後に1度だけ実行する関数
    pc.printf("after main\r\n");
    dribler.write(0);
}

// モード登録
const RIMode modeTest = {
    modeName : "mode_test", //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : 'M', //モード実行のコマンド
    before : callback(before_main),
    body : callback(body_main),
    after : callback(after_main)
};

#endif