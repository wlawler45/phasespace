#include <ros/ros.h>
#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/common/transforms.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

class PhasespaceTransformer
{
public:
	PhasespaceTransformer(){
		
        pub = nh.advertise<PointCloud>("mocap_transformed", 1);
        sub = nh.subscribe<PointCloud>("mocap_point_cloud", 1, &PhasespaceTransformer::callback, this);
        transform_1 (0,0) = 0.9978439525214857;
        transform_1 (0,1) = 0.009325973887858344;
        transform_1 (0,2) = 0.06496516472188765;
        transform_1 (0,3) = -0.6951269888410334;
        transform_1 (1,0) = 0.06502531006439705;
        transform_1 (1,1) = 0.9978637437432095;
        transform_1 (1,2) = -0.006297457726367262;
        transform_1 (1,3) = -0.562901040445272;
        transform_1 (2,0) = -0.008896935839267175;
        transform_1 (2,1) = -0.006890304452225736;
        transform_1 (2,2) = 0.9999366821140364;
        transform_1 (2,3) = -3.3780828942330037;
        //transformed_cloud=(new pcl::PointCloud<pcl::PointXYZ> ());
	}
    void callback(const PointCloud::ConstPtr& msg)
  	{
  		
    	
        pcl::transformPointCloud (*msg, *transformed_cloud, transform_1);
        transformed_cloud->header.frame_id = "/base";
  		pcl_conversions::toPCL(ros::Time::now(), transformed_cloud->header.stamp);
        pub.publish(*transformed_cloud);
  	}

		
private:
	ros::NodeHandle nh;
	ros::Publisher pub;
	ros::Subscriber sub;
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud;
    Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();

};
	
int main (int argc, char** argv)
{
	ros::init(argc, argv, "sub_pcl");
	
	PhasespaceTransformer Transformer;

	ros::spin();
    return 0;
	
}
