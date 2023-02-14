#include <moveit/move_group_interface/move_group_interface.h>
#include <ros/ros.h>
int main(int argc, char** argv) {
    ros::init(argc, argv, "moveit_pub");
    ros::NodeHandle n;
    ros::AsyncSpinner s(1);
    s.start();

    moveit::planning_interface::MoveGroupInterface move_group_arm("stretch_arm");
    move_group_arm.setGoalTolerance(0.01);
    move_group_arm.setPlanningTime(20.0);
    move_group_arm.setMaxVelocityScalingFactor(1.0);
    move_group_arm.setPlanningTime(5);

    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    moveit::core::RobotStatePtr current_state = move_group_arm.getCurrentState();
    const moveit::core::JointModelGroup* joint_model_group = move_group_arm.getCurrentState()->getJointModelGroup("stretch_arm");
    std::vector<double> joint_group_positions;
    current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

    joint_group_positions.at(0) = 0.4;  // Lift position
    double dist = 0.5 / 4;              // Arm Extension / 4
    for (int i = 1; i < 5; i++) {
        joint_group_positions.at(i) = dist;
    }
    joint_group_positions.back() = 0;  // Gripper Yaw

    move_group_arm.setJointValueTarget(joint_group_positions);
    move_group_arm.plan(my_plan);
    move_group_arm.execute(my_plan);

    return 0;
}
