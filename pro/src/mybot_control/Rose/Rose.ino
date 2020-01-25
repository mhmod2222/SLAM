#include "SoftI2CMaster.h"
#include "I2Cdev.h"
#include "Wire.h"
#include "Motors.h"

//ROS headers
#include <ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>
#include <sensor_msgs/LaserScan.h>


#define encodPinA1      3        		// encoder 1 pin A
#define encodPinA2      2	      		// encoder 2 pin A
#define LOOPTIME        100      		// PID loop time(ms)
#define SMOOTH      	   10

#define sign(x) (x > 0) - (x < 0)

unsigned long lastMilli = 0;     		// loop timing 
unsigned long lastMilliPub = 0;
double rpm_req1 = 0;             		//required rpm for wheels
double rpm_req2 = 0;
double rpm_act1 = 0;             		//actual rpm for wheels
double rpm_act2 = 0; 
double rpm_req1_smoothed = 0;
double rpm_req2_smoothed = 0;

int PWM_val1 = 0;
int PWM_val2 = 0;
volatile long count1 = 0;          		// rev counter
volatile long count2 = 0;
long countAnt1 = 0;			   	// previous count1 "i-1"
long countAnt2 = 0;			   	// previous count2
float Kp =   0.5;
float Kd =   0;
float Ki =   0;
ros::NodeHandle nh;


void handle_cmd( const geometry_msgs::Twist& cmd_msg) {
  double vx = cmd_msg.linear.x;
  double wz = cmd_msg.angular.z;
  if (wz == 0) {     				// go straight
    						// convert m/s to rpm
    rpm_req1 = vx*60/(pi*wheel_diameter); 	//first motor
    rpm_req2 = rpm_req1; 			// second motor
  }
  else if (vx == 0) { 				//rotate only
    						// convert rad/s to rpm
    rpm_req2 = wz*track_width*60/(wheel_diameter*pi*2);
    rpm_req1 = -rpm_req2;
  }
  else { 					//move and rotate
    rpm_req1 = vx*60/(pi*wheel_diameter)-wz*track_width*60/(wheel_diameter*pi*2);
    rpm_req2 = vx*60/(pi*wheel_diameter)+wz*track_width*60/(wheel_diameter*pi*2);
  }
}


ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", handle_cmd);
geometry_msgs::Vector3Stamped rpm_msg;
ros::Publisher rpm_pub("rpm", &rpm_msg);
ros::Time current_time;
ros::Time last_time;


void setup() {
 count1 = 0;
 count2 = 0;
 countAnt1 = 0;
 countAnt2 = 0;
 rpm_req1 = 0;
 rpm_req2 = 0;
 rpm_act1 = 0;
 rpm_act2 = 0;
 PWM_val1 = 0;
 PWM_val2 = 0;
 nh.initNode();
 nh.getHardware()->setBaud(57600);
 nh.subscribe(sub);
 nh.advertise(rpm_pub);
  
 pinMode(encodPinA1, INPUT);  
 digitalWrite(encodPinA1, HIGH);    		// turn on pullup resistor
 attachInterrupt(1, encoder1, RISING);		//1 means pin3 on mega"A1"
 pinMode(encodPinA2, INPUT); 
 digitalWrite(encodPinA2, HIGH);     		// turn on pullup resistor
 attachInterrupt(0, encoder2, RISING);		//0 means pin2 on mega"A2"
 
//stopping motors when deploying code for first time !!
 Motor1(0);
 Motor2(0);

}


void loop() {
  nh.spinOnce();
  unsigned long time = millis();

    if(time-lastMilli>= LOOPTIME){      	// enter tmed loop
     
     	getMotorData(time-lastMilli);
     	PWM_val1 = updatePid(1, PWM_val1, rpm_req1, rpm_act1);
     	PWM_val2 = updatePid(2, PWM_val2, rpm_req2, rpm_act2);

     	Motor1(PWM_val1);
     	Motor2(PWM_val2); 

	publishRPM(time-lastMilli);
    	lastMilli = time;
    }
  	
     if(time-lastMilliPub >= LOOPTIME){
  	
	// publishRPM(time-lastMilliPub);
    	lastMilliPub = time;
     }
    
    nh.spinOnce();

}

/////////////////
//*************//
/////////////////

void getMotorData(unsigned long time)  {
 
 rpm_act1 = double((count1-countAnt1)*60*1000)/double(time*encoder_pulse*gear_ratio);
 rpm_act2 = double((count2-countAnt2)*60*1000)/double(time*encoder_pulse*gear_ratio);
 
 countAnt1 = count1;
 countAnt2 = count2;
}

int updatePid(int id, int command, double targetValue, double currentValue) {
  double pidTerm = 0;                           // PID correction
  double error = 0;
  double new_pwm = 0;
  double new_cmd = 0;
  static double last_error1 = 0;
  static double last_error2 = 0;
  static double int_error1 = 0;
  static double int_error2 = 0;
  
  error = targetValue-currentValue;
  if (id == 1) {
    int_error1 += error;
    pidTerm = Kp*error + Kd*(error-last_error1) + Ki*int_error1;
    last_error1 = error;
  }
  else {
    int_error2 += error;
    pidTerm = Kp*error + Kd*(error-last_error2) + Ki*int_error2;
    last_error2 = error;
  }
  new_pwm = constrain(double(command)*MAX_RPM/4095.0 + pidTerm, -MAX_RPM, MAX_RPM);
  new_cmd = 4095.0*new_pwm/MAX_RPM;
  return int(new_cmd);
}

void publishRPM(unsigned long time) {
  rpm_msg.header.stamp = nh.now();
  rpm_msg.vector.x = rpm_act1;
  rpm_msg.vector.y = rpm_act2;
  rpm_msg.vector.z = double(time)/1000;
  rpm_pub.publish(&rpm_msg);
  nh.spinOnce();
}

void encoder1() {
  if (digitalRead(encodPinA1) == digitalRead(encodPinB1)) count1++;
  else count1--;
}

void encoder2() {
  if (digitalRead(encodPinA2) == digitalRead(encodPinB2)) count2--;
  else count2++;
}
