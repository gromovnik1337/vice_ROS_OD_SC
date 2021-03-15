// Livox Mid-40 data acquisition program
// Created by: Vice, 15.03.2021

// Header with standard ROS classes
#include <ros/ros.h>

int main(int argc, char **argv) {
    // Initialize ROS system
    ros::init(argc, argv, "acquisition");

    // Establish this program as a ROS node, creates an NodeHandle object
    ros::NodeHandle nh;

    // Announce the start of the process
    ROS_INFO_STREAM("Data acquistion initiate!");

    ros::Subscriber cloudSubscriber;
    
    //TODO change the topic?
    // How to figure our the name of the topic from the custom msg? Shall I run the node and do rostopic list?
    cloudSubscriber = nodeHandle.subscribe<sensor_msgs::PointCloud2>('livox/cloud', 1, &CargoHold::topicCallBack, this); 

    void CargoHold::topicCallBack(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
    /*
    Callback for the subscriber to the topic:
    * Input parameters:
        - msg: It is the pointer to the cloud sent by the publisher.
    */
    ROS_DEBUG_STREAM("CARGO HOLD: Listening to the LOAM topic...");
    // Transform the message to a pcl::PCLPointCloud2
    pcl::PCLPointCloud2 pointCloud2;
    pcl_conversions::toPCL(*msg, pointCloud2);
    // Add the pointcloud to the buffer
    pointCloudCircularBuffer.push_back(pointCloud2);
    // Save last time stamp received
    lastCloudTimeStamp = msg->header.stamp;
    // Let the other thread work when the buffer is full
    if (pointCloudCircularBuffer.full()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    }
}

}