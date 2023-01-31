# Part 1
Open Gazebo
```bash
# Terminal 1
roslaunch stretch_gazebo gazebo.launch
```
Run rviz
```bash
# Terminal 2
roslaunch stretch_tf navigation_gazebo.launch
```
```bash
# Terminal 3
rostopic echo /clicked_point
```
Now use RVIZ publish point tool to click somewhere on the pointcloud. Terminal 3 should have a point with a frame_id of "camera_depth_optical_frame". This is a point relative to the depth camera. Now we will lookup the transform between the camera and the map. Terminal 3 can be closed but make sure to save the xyz values of the point.
```bash
# Terminal 3
rosrun tf tf_echo /camera_depth_optical_frame /map
```
This will give us two pieces of information the translation and rotation between our source frame camera_depth_optical_frame and our target frame map.

This can then be used to find where the point we clicked on is located on the map.
Perform necessary math operations to transform the point to the map coordinates.
```bash
# Terminal 3 publish the command change position x y to calculated points x and y. z will be discarded because the robot only travels in xy plane
rostopic pub /move_base/goal move_base_msgs/MoveBaseActionGoal "header:
  seq: 0
  stamp:
    secs: 0
    nsecs: 0
  frame_id: ''
goal_id:
  stamp:
    secs: 0
    nsecs: 0
  id: ''
goal:
  target_pose:
    header:
      seq: 0
      stamp:
        secs: 0
        nsecs: 0
      frame_id: 'map'
    pose:
      position:
        x: 0.0
        y: 0.0
        z: 0.0
      orientation:
        x: 0.0
        y: 0.0
        z: 0.0
        w: 1.0"
```
# Part 2
Perform the same operation for finding a point and for finding the transform but this time transform the point to "link_wrist_yaw". Find the angle the wrist would need to rotate to be pointing at the point you selected.