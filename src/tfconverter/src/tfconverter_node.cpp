#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point.h>
#include <tf/transform_listener.h>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    sub = n.subscribe("/input", 1, &SubscribeAndPublish::read_input, this);
    pub = n.advertise<geometry_msgs::Point>("/output", 1);
  }

  void read_input(const geometry_msgs::PointStamped::ConstPtr& point_stamped)
  {
    geometry_msgs::PointStamped new_point_stamped;
    listener.transformPoint("core_frame", *point_stamped, new_point_stamped);
    pub.publish(new_point_stamped.point);
  }

private:
  ros::NodeHandle n;
  ros::Publisher pub;
  ros::Subscriber sub;
  tf::TransformListener listener;
}; // End of class SubscribeAndPublish


int main(int argc, char **argv)
{
  ros::init(argc, argv, "tfconverter_node");
  SubscribeAndPublish SAPObject;
  ros::spin();
  return 0;
}
