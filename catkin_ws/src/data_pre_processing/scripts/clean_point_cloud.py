#!/usr/bin/evn python3
import os
import sys
curr_dir = os.path.dirname(os.path.realpath(__file__))
os.chdir("..")
data_dir = os.getcwd() + "/data"
sys.path.append(data_dir)
os.chdir(curr_dir)

# Import dependencies
import open3d as o3d
import numpy as np

# Load the point cloud data
point_cloud_in = o3d.io.read_point_cloud(data_dir + "/lidar_screenshot_test.pcd", print_progress = True)

# Convert to numpy 
point_cloud_in = np.asarray(point_cloud_in.points)

point_cloud_clean = np.empty([0, 3])

for i in range(np.shape(point_cloud_in)[0]):
    if point_cloud_in[i, 0]!=0 and point_cloud_in[i, 1]!=0 and point_cloud_in[i, 2]!=0:
        point_cloud_clean = np.append(point_cloud_clean, [point_cloud_in[i, :]], axis=0)


point_cloud_out = o3d.geometry.PointCloud()
point_cloud_out.points = o3d.utility.Vector3dVector(point_cloud_clean)
o3d.io.write_point_cloud(data_dir + "/lidar_screenshot_clean.pcd", point_cloud_out, write_ascii = True)