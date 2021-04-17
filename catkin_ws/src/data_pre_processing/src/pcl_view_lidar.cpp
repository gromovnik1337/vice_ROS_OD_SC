// This script acquires the Livox Mid 40 data and subsequently visualizes them in a continuos stream using PCL viewer
// Created by: Vice, 17.04.2021

#include <pcl_view_lidar.hpp>



getAndView::getAndView()
{
    
    
    //pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer("Viewer"));
    _cloud_subscriber = _node_handle.subscribe<sensor_msgs::PointCloud2>("/livox/lidar", 1, &getAndView::lidarRawDataCallback, this);  

}

getAndView::~getAndView()
{
}

void getAndView::simpleVis (pcl::visualization::PCLVisualizer::Ptr _v, pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{

    _v->setBackgroundColor (0, 0, 0);
    _v->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
    _v->addCoordinateSystem (1.0);
    //_v->initCameraParameters ();
    _v->spin();
    //_v->spinOnce (100);
    //return (_v);
    
}

pcl::PointCloud<pcl::PointXYZ>::Ptr getAndView::lidarRawDataCallback(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
   
    // Transform the message to a pcl::PCLPointCloud2
    pcl::PCLPointCloud2 pointCloud2;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZ>);
    pcl_conversions::toPCL(*msg, pointCloud2);

    ROS_INFO_STREAM_ONCE("Lidar data acquired!");
    
    // Conver to plc cloud
    pcl::fromPCLPointCloud2(pointCloud2, *cloud_out);

    //pcl::visualization::PCLVisualizer::Ptr viewer;
    //viewer = simpleVis(cloud_out);
    return(cloud_out);
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
