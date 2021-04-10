// This script acquires the Livox Mid 40 data and subsequently visualizes them using PCL viewer
// Created by: Vice, 09.04.2021

#include <pcl_view_lidar.hpp>

customVisualizer::customVisualizer(std::string label) : _v(new pcl::visualization::PCLVisualizer(label))
{
    //_v (new pcl::visualization::PCLVisualizer(label));
}

customVisualizer::~customVisualizer()
{
}

/*
void customVisualizer::addPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
  _v->addPointCloud<pcl::PointXYZ>(cloud);
  _v->spin();

}

*/

getAndView::getAndView()
{

    visualizeIt =  customVisualizer("visualizer");
    _cloud_subscriber = _node_handle.subscribe<sensor_msgs::PointCloud2>("/livox/lidar", 1, &getAndView::lidarRawDataCallback, this);
    
}

getAndView::~getAndView()
{
}


void getAndView::lidarRawDataCallback(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
   
    // Transform the message to a pcl::PCLPointCloud2
    pcl::PCLPointCloud2 pointCloud2;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZ>);
    pcl_conversions::toPCL(*msg, pointCloud2);

    ROS_INFO_STREAM("Data acquired");
    
    // Converto to plc cloud
    pcl::fromPCLPointCloud2(pointCloud2, *cloud_out);

    visualizeIt->addPointCloud<pcl::PointCloudXYZ>(*cloud_out, "sample cloud");
    
}


int main(int argc, char **argv) {

    ros::init(argc, argv, "pcl_view_lidar");
    ros::Time::init();

    // Announce the start of the process
    ROS_INFO_STREAM("Data acquisition and visualization initiated!");

    // Initialize
    getAndView getAndViewBasic;
    

    ros::spin();

}