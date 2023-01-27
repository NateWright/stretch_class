#include <ros/ros.h>

#include <stretch_tf/stretch_tf.hpp>

int main(int argc, char **argv) {
    /* code */
    ros::init(argc, argv, "Camera_Node");
    ros::NodeHandlePtr nh(new ros::NodeHandle());
    Stretch_tf tfNode(nh);
    ros::spin();
    return 0;
}
