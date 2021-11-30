#ifndef VIS_FUNCTIONS
#define VIS_FUNCTIONS

#include <ros/ros.h>
#include <pp_local_planner/pp_ds.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <base_local_planner/local_planner_util.h>

namespace vis_functions{

    void publish_circle_(const std::pair<double, double> &cc_, const double &r_, ros::Publisher &circle_pub_, base_local_planner::LocalPlannerUtil &planner_util_, ros::NodeHandle &nh_){

            visualization_msgs::Marker marker;
            marker.header.frame_id = planner_util_.getGlobalFrame();
            marker.header.stamp = ros::Time();
            marker.ns = nh_.getNamespace() + "_circle_";
            marker.id = 0;

            marker.type = visualization_msgs::Marker::CYLINDER;
            marker.action = visualization_msgs::Marker::ADD;

            marker.pose.position.x = cc_.first;
            marker.pose.position.y = cc_.second;
            marker.pose.position.z = 1;

            marker.pose.orientation.x = 0.0;
            marker.pose.orientation.y = 0.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 1.0;

            marker.scale.x = 2.0 * r_;
            marker.scale.y = 2.0 * r_;
            marker.scale.z = 0.2;

            marker.color.a = 1.0; // Don't forget to set the alpha!

            marker.color.r = 0.0;
            marker.color.g = 1.0;
            marker.color.b = 0.0;

            circle_pub_.publish(marker);
    }

    void publish_unfilled_circle_(const std::pair<double, double> &cc_, const double &r_, ros::Publisher &unfilled_circle_pub_, base_local_planner::LocalPlannerUtil &planner_util_, ros::NodeHandle &nh_){

            visualization_msgs::MarkerArray marker_array;
            
            int num_markers_ = 50;
            double theta_i_ = 0 ;
            double del_theta_ = (2 * 3.14)/(1.0 * num_markers_);

            int marker_id_ =0 ; 

            for(int i =0 ; i < num_markers_ ; i++) {

                double theta_ = theta_i_ + (i * del_theta_);
                
                visualization_msgs::Marker marker;

                marker.header.frame_id = planner_util_.getGlobalFrame();
                marker.header.stamp = ros::Time();
                marker.ns = nh_.getNamespace() + "unfilled_circle_";
                marker.id = marker_id_++;

                marker.type = visualization_msgs::Marker::CYLINDER;
                marker.action = visualization_msgs::Marker::ADD;

                marker.pose.position.x = cc_.first + (r_ * cos(theta_));
                marker.pose.position.y = cc_.second + (r_ * sin(theta_));
                marker.pose.position.z = 1;

                marker.pose.orientation.x = 0.0;
                marker.pose.orientation.y = 0.0;
                marker.pose.orientation.z = 0.0;
                marker.pose.orientation.w = 1.0;

                marker.scale.x = 0.02;
                marker.scale.y = 0.02;
                marker.scale.z = 1.0;

                marker.color.a = 1.0; // Don't forget to set the alpha!

                marker.color.r = 0.0;
                marker.color.g = 1.0;
                marker.color.b = 0.0;

                marker_array.markers.push_back(marker);

            }
            
            unfilled_circle_pub_.publish(marker_array);
    }

    void publish_point_(const std::pair<double, double> &pt_, ros::Publisher &point_pub_, base_local_planner::LocalPlannerUtil &planner_util_, ros::NodeHandle &nh_){

            visualization_msgs::Marker marker;
            marker.header.frame_id = planner_util_.getGlobalFrame();
            marker.header.stamp = ros::Time();
            marker.ns = nh_.getNamespace() + "_point_";
            marker.id = 0;

            marker.type = visualization_msgs::Marker::CUBE;
            marker.action = visualization_msgs::Marker::ADD;

            marker.pose.position.x = pt_.first;
            marker.pose.position.y = pt_.second;
            marker.pose.position.z = 1;
            marker.pose.orientation.x = 0.0;
            marker.pose.orientation.y = 0.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 1.0;

            marker.scale.x = 0.2;
            marker.scale.y = 0.2;
            marker.scale.z = 0.0;

            marker.color.a = 1.0; // Don't forget to set the alpha!

            marker.color.r = 0.0;
            marker.color.g = 0.0;
            marker.color.b = 1.0;

            point_pub_.publish(marker);
    }

    void publish_la_pose_line();

    void publish_ct_error_line(const int &closest_pt_idx, const pp_ds::Plan_ &global_plan_, const double &la_dis_, const double &alpha_, ros::Publisher &crosstrack_error_pub_, base_local_planner::LocalPlannerUtil &planner_util_, ros::NodeHandle &nh_){
        
        visualization_msgs::MarkerArray marker_array;
            
        int marker_id_ =0 ; 
        
        geometry_msgs::PoseStamped closest_stamped_pose_ = global_plan_.at(closest_pt_idx);
        std::pair<double,double> closest_pose_ = {closest_stamped_pose_.pose.position.x, closest_stamped_pose_.pose.position.y};

        for(double len_ = 0; len_ <= la_dis_ ; len_ += 0.1){
                
                visualization_msgs::Marker marker;

                double y_ = closest_pose_.first +  la_dis_ * cos(alpha_); 
                double x_ = closest_pose_.second  + len_ * sin(alpha_);

                std::pair<double, double> pt_ = {x_, y_};

                

                marker.header.frame_id = planner_util_.getGlobalFrame();
                marker.header.stamp = ros::Time();
                marker.ns = nh_.getNamespace() + "_ct_error_";
                marker.id = marker_id_++;

                marker.type = visualization_msgs::Marker::CYLINDER;
                marker.action = visualization_msgs::Marker::ADD;

                marker.pose.position.x = x_;
                marker.pose.position.y = y_;
                marker.pose.position.z = 1;

                marker.pose.orientation.x = 0.0;
                marker.pose.orientation.y = 0.0;
                marker.pose.orientation.z = 0.0;
                marker.pose.orientation.w = 1.0;

                marker.scale.x = 0.02;
                marker.scale.y = 0.02;
                marker.scale.z = 1.0;

                marker.color.a = 1.0; // Don't forget to set the alpha!

                marker.color.r = 1.0;
                marker.color.g = 0.0;
                marker.color.b = 0.0;

                marker_array.markers.push_back(marker);

        }

        crosstrack_error_pub_.publish(marker_array);

    }


};

#endif

