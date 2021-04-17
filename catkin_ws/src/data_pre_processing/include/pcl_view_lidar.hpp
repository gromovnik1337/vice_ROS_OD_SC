#ifndef PCL_VIEW_HPP
#define PCL_VIEW_HPP

// Include necessary libraries
#include <boost/circular_buffer.hpp>
#include <thread>
#include <chrono>

//ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
// PCL
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/visualization/pcl_visualizer.h> 


class getAndView
{
private:
    // Create necessary ROS objects
    ros::NodeHandle _node_handle;

    // Create a subscriber
    ros::Subscriber _cloud_subscriber;

    // Create a visualizer
    pcl::visualization::PCLVisualizer::Ptr viewer;

    // Circular buffer for Livox data
    boost::circular_buffer<pcl::PCLPointCloud2> _livox_data_circular_buffer;

    std::thread _data_processed_thread;

private:
    pcl::PointCloud<pcl::PointXYZ>::Ptr lidarRawDataCallback(const sensor_msgs::PointCloud2::ConstPtr& msg);    

public:
    getAndView();

    ~getAndView();

    void simpleVis (pcl::visualization::PCLVisualizer::Ptr _v, pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);
};

#endif 