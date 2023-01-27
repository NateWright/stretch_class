#pragma once
#include <geometry_msgs/PointStamped.h>
#include <ros/ros.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

class Stretch_tf {
   private:
    ros::NodeHandlePtr nh_;

    ros::Subscriber clickHandlerSub_;

    void clickHandlerCallback(const geometry_msgs::PointStampedPtr& msg);

    tf2_ros::Buffer tfBuffer_;
    tf2_ros::TransformListener* tfListener_;

   public:
    explicit Stretch_tf(ros::NodeHandlePtr nh);
    ~Stretch_tf();
};
