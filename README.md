# Requirements
This repo assumes you are using stretch with dex wrist and aws house
# Installation
```bash
cd ~/catkin_ws/src
git clone https://github.com/NateWright/stretch_class.git -b example/open-cv
cd ..
catkin build
source devel/setup.bash
```

# Objectives
Familiarize yourself using cv_bridge as well as using classes with publishers and subscribers

# Run Demo
```bash
# Terminal 1
roslaunch stretch_gazebo gazebo.launch
# Terminal 2
roslaunch opencv_example rviz.launch
# Terminal 3
rosrun  opencv_example opencv_example_node
```
Look at the code and change between the different Sobel edge detection methods on line 44-46

# Run Demo 2
Modify the callback function to the code below make sure to rebuild and resource after modifying code

```c++
    cv_bridge::CvImagePtr cv_ptr;
    cv_bridge::CvImage output;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    Mat hsvImage, mask;
    // Converts RGB image to HSV image
    cv::cvtColor(cv_ptr->image, hsvImage, CV_RGB2HSV);
    // Filters blue into a mask which will be mono
    cv::inRange(hsvImage, cv::Scalar(60, 35, 140), cv::Scalar(180, 255, 255), mask);

    // Using original message header as header for converted image
    output.header = msg->header;
    // Set encoding type to MONO8
    output.encoding = sensor_msgs::image_encodings::MONO8;
    // Set image to the mask
    output.image = mask;
    // Publishes image
    pub_.publish(output.toImageMsg());
```
What do you notice happens in the code?

How can you make the code filter other colors?