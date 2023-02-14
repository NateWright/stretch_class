# Requirements
This repo assumes you are using stretch with dex wrist
# Installation
```bash
cd ~/catkin_ws/src
git clone https://github.com/NateWright/stretch_class.git -b example/move-it
sudo apt install ros-noetic-moveit-planners-chomp ros-noetic-pilz-industrial-motion-planner
cd ..
catkin build
source devel/setup.bash
```

# Run Demo
```bash
# Terminal 1
roslaunch stretch_gazebo gazebo.launch
# Terminal 2
roslaunch stretch_dex_moveit_config move_group.launch
# Terminal 3
roslaunch stretch_dex_moveit_config rviz.launch
```

# Run Demo 2

```bash
# Terminal 3
rosrun simple_moveit_cpp simple_moveit_cpp_node
```
Students can take a look at cpp file located at simple_moveit_cpp/src/main.cpp to change arguments