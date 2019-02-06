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
		
		pub = nh.advertise<PointCloud> ("mocap_transformed", 1);
		sub = nh.subscribe<PointCloud>("mocap_point_cloud", 1, &SubscribeAndPublish::callback, this);
	}
    void callback(const PointCloud::ConstPtr& msg)
  	{
  		
    	
    	pcl::transformPointCloud (msg, *transformed_cloud, transform_2);
    	transformed_cloud->header.frame_id = "base";
  		pcl_conversions::toPCL(ros::Time::now(), transformed_cloud->header.stamp);
    	pub_.publish(transformed_cloud);
  	}

		
private:
	ros::NodeHandle nh;
	ros::Publisher pub;
	ros::Subscriber sub;
	pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
	
}
	
int
main (int argc, char** argv)
{
	ros::init(argc, argv, "sub_pcl");
	
	PhasespaceTransformer Transformer;

	ros::spin();
	return 0
	
}
