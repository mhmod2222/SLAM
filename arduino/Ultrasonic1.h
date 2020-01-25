//----------------------------Ultrasonic-------------------------//

int trig1 = 14; // attach pin 14 to Trig
int echo1 = 15; //attach pin 15 to Echo
long duration, inches, Distance_cm1;

void Get_Distance1();
long microsecondsToCentimeters(long microseconds);
//----------------------------Ultrasonic-------------------------//

void Get_Distance1(){
    pinMode(trig, OUTPUT);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);
    
    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echo,INPUT);
    duration = pulseIn(echo, HIGH);
    if (duration >= 15000){
    Serial.println("Clear!!");
    }else{
    Distance_cm1 = microsecondsToCentimeters(duration);
    Serial.print(Distance_cm1);
    Serial.print("cm");
    Serial.println();
    delay(10);
    }

}


long microsecondsToCentimeters(long microseconds){
  
    return microseconds / 29 / 2;
    
}
