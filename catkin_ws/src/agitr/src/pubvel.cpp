// A program that publishes random generated velocity, to the turtlesim
// From A Gentle Introduction to ROS
// Created by: Vice, 21.03.2021

#include <pubvel.hpp>

// Constructor of the publishTurtle class
publishTurtle::publishTurtle()
{

// Create a publisher object
_turtle_velocity_publish = _node_handle.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

// Seed the random number generator
srand(time(0));

// Declare a rate object - to control the speed of the loop
ros::Rate rate(2);
    
while(ros::ok()) 
{
    // Fill in the message. The other four fields, 
    // which are ignored by turtlesim, default to 0
    _msg.linear.x = double(rand())/double(RAND_MAX);
    _msg.angular.z = 2*double(rand()/double(RAND_MAX) - 1);

    // Publish the message
    _turtle_velocity_publish.publish(_msg);

    // Send the message to rosout with the details
    ROS_INFO_STREAM("Sending random velocity command:"
    << "linear=" << _msg.linear.x
    << "angular=" << _msg.angular.z);

    // Wait until it's time for another iteration.
    rate.sleep();
}

}

// De-cnstructor of the publishTurtle class
publishTurtle::~publishTurtle()
{

}

int main(int argc, char **argv) 
{

    ros::init(argc, argv, "publish_velocity");
    ros::Time::init();

    // Initialize
    publishTurtle publishTurtleBasic;

    ros::spin();

}