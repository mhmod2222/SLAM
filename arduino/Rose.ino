#include "SoftI2CMaster.h"
#include "Motors.h"
#include "Ultrasonic1.h"
#include "Ultrasonic2.h"
#include "Ultrasonic3.h"
#include "VoltageSense.h"
#include "MPU6050_.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
void setup(){
    Serial.begin(115200);
    MPU_6050_init();
    Serial.println(" ");
    Serial.println("Start Yaw Calibration! (Send any char)");
    while (!Serial.available());
    while (Serial.available() && Serial.read());
    MPU_6050_Yaw_Calibration();
    while (!Serial.available());
    while (Serial.available() && Serial.read());
    Serial.println("Let's go!");
}

void loop(){
    Key = Serial.read();
    if (Key == '2'){
        Serial.println("Forward");     
         Motor1(200);
         Motor2(200); 
    }
    if (Key == '5'){
        Serial.println("Backward");
        Motor1(-200);
        Motor2(-200);
    }
    if (Key == '4'){
        Serial.println("TURN LEFT");
        Motor1(-255);
        Motor2(255);
        delay(100);
        Motor1(0);
        Motor2(0);
    }
    if (Key == '6'){
        Serial.println("TURN RIGHT");
        Motor1(255);
        Motor2(-255);
        delay(100);
        Motor1(0);
        Motor2(0);
    }
    
    if (Key == '0'){
        Serial.println("STOP");
        Motor3(0);
        Motor4(0);
    }
    MPU_6050();
}


