// Range image tutorial from PCL
// https://pointclouds.org/documentation/tutorials/range_image_creation.html
#include <pcl/range_image/range_image.h>
#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/range_image_visualizer.h>



pcl::visualization::PCLVisualizer::Ptr simpleVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
    pcl::visualization::PCLVisualizer::Ptr _v (new pcl::visualization::PCLVisualizer("Point Cloud Viewer"));
    _v->setBackgroundColor (0, 0, 0);
    _v->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
    _v->addCoordinateSystem (1.0);
    _v->spin();
    return (_v);    
}  

int main(int argc, char **argv) {

    ros::init(argc, argv, "Range_image");
    ros::NodeHandle nh;
 
    pcl::PointCloud<pcl::PointXYZ> point_cloud_for_image;
    
    /* 
    // Generate the data
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud (new pcl::PointCloud<pcl::PointXYZ>); // boost shared pointer

    for (float y=-0.5f; y<=0.5f; y+=0.01f) {
        for (float z=-0.5f; z<=0.5f; z+=0.01f) {
        pcl::PointXYZ point;
        point.x = 2.0f - y;
        point.y = y;
        point.z = z;
        point_cloud->points.push_back(point);
        }
    }
    point_cloud->width = point_cloud->size();
    point_cloud->height = 1;

    pcl::io::savePCDFileASCII ("./test_pcd.pcd", *point_cloud);

    pcl::PCDReader reader;
    reader.read ("test_pcd.pcd", point_cloud_for_image);
    */

    pcl::PCDReader reader;
    reader.read ("lidar_screenshot.pcd", point_cloud_for_image);
    ROS_INFO_STREAM("Here:\n");

    // We now want to create a range image from the above point cloud, with a 1deg angular resolution
    float angularResolution = (float) (  1.0f * (M_PI/180.0f));  //   1.0 degree in radians
    float maxAngleWidth     = (float) (360.0f * (M_PI/180.0f));  // 360.0 degree in radians
    float maxAngleHeight    = (float) (180.0f * (M_PI/180.0f));  // 180.0 degree in radians
    Eigen::Affine3f sensorPose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);
    pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;
    float noiseLevel=0.00;
    float minRange = 0.0f;
    int borderSize = 1;

    pcl::RangeImage range_image;
    range_image.createFromPointCloud(point_cloud_for_image, angularResolution, maxAngleWidth, maxAngleHeight,
                                    sensorPose, coordinate_frame, noiseLevel, minRange, borderSize);
   
    /*
    // Visualize the cloud
    pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
    viewer.showCloud (point_cloud_lidar);
    while (!viewer.wasStopped ())
    {
    }

    
    pcl::visualization::PCLVisualizer::Ptr viewer;
    viewer = simpleVis(point_cloud_lidar);
    */
    pcl::visualization::RangeImageVisualizer range_image_widget ("Range image");
    range_image_widget.showRangeImage (range_image);
    range_image_widget.spin();

    ROS_INFO_STREAM("Image data: " << range_image << "\n");
}