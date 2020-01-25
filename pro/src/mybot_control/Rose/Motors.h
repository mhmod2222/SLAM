#define encoder_pulse   13 //encoder integrated in motor
#define gear_ratio      120
#define wheel_diameter  0.069   //m
#define wheel_width     0.027   //m
#define track_width     0.276   //m
#define MAX_RPM         58
#define pi              3.1415926
#define two_pi          6.2831853

#define Motor1_Enable 4
#define Motor2_Enable 5
#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25

//------------------------------------Function Init-------------------------------------------//

void Motor1(int Pulse_Width1);
void Motor2(int Pulse_Width2);
void Motor3(int Pulse_Width3);
void Motor4(int Pulse_Width4);



//------------------------------------Motor1-------------------------------------------//
void Motor1(int Pulse_Width1){
  
  if (Pulse_Width1 > 0){
      analogWrite(Motor1_Enable, Pulse_Width1);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
  }
  if (Pulse_Width1 < 0){
      Pulse_Width1=abs(Pulse_Width1);
      analogWrite(Motor1_Enable, Pulse_Width1);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
  }
  if (Pulse_Width1 == 0){
      analogWrite(Motor1_Enable, Pulse_Width1);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
  }
      
}

//------------------------------------Motor2-------------------------------------------//

void Motor2(int Pulse_Width2){
  if (Pulse_Width2 > 0){
      analogWrite(Motor2_Enable, Pulse_Width2);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
  }
  if (Pulse_Width2 < 0){
      Pulse_Width2=abs(Pulse_Width2);
      analogWrite(Motor2_Enable, Pulse_Width2);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
  }
  if (Pulse_Width2 == 0){
      analogWrite(Motor2_Enable, Pulse_Width2);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
  }
}

