//----------------------------Ultrasonic-------------------------//

int trig1 = 10; // attach pin 10 to Trig
int echo1 = 11; //attach pin 11 to Echo
long duration, inches, Distance_cm3;

void Get_Distance3();
long microsecondsToCentimeters(long microseconds);
//----------------------------Ultrasonic-------------------------//

void Get_Distance3(){
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
    Distance_cm3 = microsecondsToCentimeters(duration);
    Serial.print(Distance_cm3);
    Serial.print("cm");
    Serial.println();
    delay(10);
    }

}


long microsecondsToCentimeters(long microseconds){
  
    return microseconds / 29 / 2;
    
}
