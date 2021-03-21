#ifndef ACQUISITION_HPP
#define ACQUISITION_HPP

// Header with standard ROS classes
#include <ros/ros.h>
// Message type recognized by the turtle
#include <geometry_msgs/Twist.h>
// Recquired for rand() and RAND_MAX
#include <stdlib.h> 

class publishTurtle 
{
private:
    // Declare necessary ROS objects
    ros::NodeHandle _node_handle;

    // Declare a publisher object
    ros::Publisher _turtle_velocity_publish;

    // Declare a message to publish turtle speed
    geometry_msgs::Twist _msg;

public:
    publishTurtle();

    ~publishTurtle();

}; 

#endif