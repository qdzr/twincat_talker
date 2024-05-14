#include "AdsLib.h"
#include "AdsNotification.h"
#include "AdsVariable.h"
#include "ros/ros.h"
#include "iostream"

using namespace std;

int main(int argc, char *argv[]) {
  // ROS node init
  ros::init(argc, argv, "tctalker");
  ros::NodeHandle n;

  ROS_INFO_STREAM("running good");

  //static const AmsNetId remoteNetId{5, 67, 39, 56, 1, 1};
  //static const char remoteIpV4[] = "10.180.30.49";
  static const AmsNetId remoteNetId{192, 168, 0, 231, 1, 1};
  static const char remoteIpV4[] = "114.213.237.49";

  AdsDevice route{remoteIpV4, remoteNetId, AMSPORT_R0_PLC_TC3};
    AdsVariable<double> lumbar_position{route, "MAIN.pos_axis1"};
    AdsVariable<double> big_arm_position{route, "MAIN.pos_axis2"};
    AdsVariable<double> small_arm_position{route, "MAIN.pos_axis3"};
    AdsVariable<double> wrist_position{route, "MAIN.pos_axis4"};
    AdsVariable<double> hand_position{route, "MAIN.pos_axis5"};
    AdsVariable<double> finger_position{route, "MAIN.pos_axis6"};

  //AdsVariable<bool> variable_to_write{route, "MAIN.read_do"};

  ros::Rate loop_rate(10);

  while (ros::ok()) {
    // variable_to_write = true;
    double value = lumbar_position / 180.0;
    cout<<value<<endl;
    ROS_INFO_STREAM("changed variable on sps");
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
