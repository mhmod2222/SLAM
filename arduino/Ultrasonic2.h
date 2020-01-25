//----------------------------Ultrasonic-------------------------//

int trig1 = 12; // attach pin 12 to Trig
int echo1 = 13; //attach pin 13 to Echo
long duration, inches, Distance_cm2;

void Get_Distance2();
long microsecondsToCentimeters(long microseconds);
//----------------------------Ultrasonic-------------------------//

void Get_Distance2(){
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
    Distance_cm2 = microsecondsToCentimeters(duration);
    Serial.print(Distance_cm2);
    Serial.print("cm");
    Serial.println();
    delay(10);
    }

}


long microsecondsToCentimeters(long microseconds){
  
    return microseconds / 29 / 2;
    
}
