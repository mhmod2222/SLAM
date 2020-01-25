#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

const int num = 4;
double sonar_frequency = 40; //Hz
double ranges[num];
double intensities[num];
    
    int main(int argc, char** argv){
      ros::init(argc, argv, "laser_scan_publisher");
    
      ros::NodeHandle n;
      ros::Publisher sonar_pub = n.advertise<sensor_msgs::LaserScan>("/mybot/laser/scan", 50);

     ros::Rate r(1.0);
     while(n.ok()){
       //generate some fake data for our laser scan
       for(unsigned int i = 0; i < num; ++i){
         ranges[i] = 0;
         intensities[i] = 0;
       }
       ros::Time scan_time = ros::Time::now();
   
       //populate the LaserScan message
       sensor_msgs::LaserScan sonar;
       sonar.header.stamp = scan_time;
       sonar.header.frame_id = "hokuyo";
       sonar.angle_min = -0.1308997;
       sonar.angle_max = 0.1308997;
       sonar.angle_increment = 3.14 / num;
       sonar.time_increment = (1 / sonar_frequency) / (num);
       sonar.range_min = 0.02;
       sonar.range_max = 3.5;

       sonar.ranges.resize(num);
       sonar.intensities.resize(num);
       
       for(unsigned int i = 0; i < num; ++i){
         sonar.ranges[i] = ranges[i];
         sonar.intensities[i] = intensities[i];
       }
   
       sonar_pub.publish(sonar);
       //ROS_INFO("range is %f \n",sonar.ranges[0]);
       //std::cout << "range is " << sonar.ranges[0] << std::endl;
       r.sleep();
      }
   }
