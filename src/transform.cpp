#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/String.h"
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>

class Parrot
{
public:
  Parrot()
  {
    pose_pub = n_.advertise<geometry_msgs::PoseWithCovarianceStamped>("/robot_pose_with_covariance", 10);

    sub_ = n_.subscribe("/odom_plugin", 1, &Parrot::callback, this);
  }

  void callback(const nav_msgs::Odometry::ConstPtr& input)
  {
    geometry_msgs::PoseWithCovarianceStamped output;

    output.header = input->header;
    output.pose.pose = input->pose.pose;
    output.pose.covariance = input->pose.covariance;
    output.header.stamp = input->header.stamp;    

    tf::Transform map;

    static tf::TransformBroadcaster br;

    tf::poseMsgToTF(input->pose.pose, map);

    br.sendTransform(tf::StampedTransform(map, ros::Time::now(), "map", "base_link"));

    ROS_WARN_ONCE("Map transform is publishing now...");

    pose_pub.publish(output);

  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pose_pub;
  ros::Subscriber sub_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "parrot");

  ROS_INFO_ONCE("Node initialized...");

  Parrot SAPObject;

  ros::spin();

  return 0;
}

