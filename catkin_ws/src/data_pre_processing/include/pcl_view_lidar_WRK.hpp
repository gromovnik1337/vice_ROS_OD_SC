#ifndef PCL_VIEW_HPP
#define PCL_VIEW_HPP

// Include necessary libraries
//ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
// PCL
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/visualization/pcl_visualizer.h> 


class customVisualizer
{
private:
    // Smart pointer to the visualizer
    pcl::visualization::PCLVisualizer::Ptr _v;

public:
    customVisualizer(std::string label);
    ~customVisualizer();

    //void addPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

};

class getAndView
{
private:
    // Create necessary ROS objects
    ros::NodeHandle _node_handle;

    // Create a subscriber
    ros::Subscriber _cloud_subscriber;

    customVisualizer visualizeIt;

public:
    getAndView();

    ~getAndView();

    void lidarRawDataCallback(const sensor_msgs::PointCloud2::ConstPtr& msg);

};

#endif 