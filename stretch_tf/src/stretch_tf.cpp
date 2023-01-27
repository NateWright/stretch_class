#include <stretch_tf/stretch_tf.hpp>
Stretch_tf::Stretch_tf(ros::NodeHandlePtr nh) : nh_(nh) {
    clickHandlerSub_ = nh_->subscribe("/clicked_point", 30, &Stretch_tf::clickHandlerCallback, this);

    tfListener_ = new tf2_ros::TransformListener(tfBuffer_);
}

Stretch_tf::~Stretch_tf() {
    delete tfListener_;
}

void Stretch_tf::clickHandlerCallback(const geometry_msgs::PointStampedPtr& msg) {
    try {
        ROS_INFO_STREAM("\nOriginal Message\n"
                        << *msg);

        auto newMsg = tfBuffer_.transform(*msg, "base_link", ros::Duration(0.1));
        ROS_INFO_STREAM("\nNew Message\n"
                        << newMsg);
    } catch (...) {
        ROS_ERROR_STREAM("Unable to perform Transform");
    }
}