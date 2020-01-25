float AnalogValue=0;
float AnalogVoltage=0;
float CurrentBatVoltage=0;
float AlarmLED = 34;
void VoltageSense(float OrigBatVolt);

void VoltageSense(float OrigBatVolt, float ResRat){
    AnalogValue = analogRead(A0);
    AnalogVoltage = (AnalogValue/1024.0)*5.0;
    CurrentBatVoltage = AnalogVoltage*ResRat;
    
    if (CurrentBatVoltage < (OrigBatVolt - 1) ){
        digitalWrite(34, HIGH);
        Serial.println("Battery LOW!");
        delay(1000);
    }
    if (CurrentBatVoltage > (OrigBatVolt - 1) ){
        digitalWrite(34, LOW);
        
    }
}
