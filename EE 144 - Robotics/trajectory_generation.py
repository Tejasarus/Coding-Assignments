
#!/usr/bin/env python

from math import pi, sqrt, atan2, cos, sin,tanh
import numpy as np

import rospy
import tf
from std_msgs.msg import Empty
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist, Pose2D

class Theta_Controller:
	def __init__(self, P=0.0, D=0.0, set_point=0):
		self.Kp = P
		self.Kd = D
		self.set_point = set_point # reference (desired value)
		self.previous_error = 0

	def update(self, current_value):
		# calculate P_term and D_term
		error = self.set_point - current_value
		if error > pi:
			error -= 2 * pi
		elif error < -pi:
			error += 2 * pi
		P_term = self.Kp * error
		D_term = self.Kd * (error - self.previous_error)
		self.previous_error = error
		return P_term + D_term

	def setPoint(self, set_point):
		self.set_point = set_point
		self.previous_error = 0
		
	def setPD(self, P=0.0, D=0.0):
		self.Kp = P
		self.Kd = D

class Linear_Controller:
	def __init__(self, P=0.0, D=0.0, set_point=0):
		self.Kp = P
		self.Kd = D
		self.set_point = set_point # reference (desired value)
		self.previous_error = 0

	def update(self, current_value):
		# calculate P_term and D_term
		error = self.set_point - current_value
		P_term = self.Kp * error
		D_term = self.Kd * (error - self.previous_error)
		self.previous_error = error
		return P_term + D_term

	def setPoint(self, set_point):
		self.set_point = set_point
		self.previous_error = 0
		
	def setPD(self, P=0.0, D=0.0):
		self.Kp = P
		self.Kd = D

class Turtlebot():
    def __init__(self):
        rospy.init_node("turtlebot_move")
        rospy.loginfo("Press Ctrl + C to terminate")
        self.vel_pub = rospy.Publisher("cmd_vel_mux/input/navi", Twist, queue_size=10)
        self.rate = rospy.Rate(10)

        # reset odometry to zero
        self.reset_pub = rospy.Publisher("mobile_base/commands/reset_odometry", Empty, queue_size=10)
        for i in range(10):
            self.reset_pub.publish(Empty())
            self.rate.sleep()
        
        # subscribe to odometry
        self.pose = Pose2D()
        self.logging_counter = 0
        self.trajectory = list()
        self.odom_sub = rospy.Subscriber("odom", Odometry, self.odom_callback)

        self.vel = Twist()

        try:
            self.run()
        except rospy.ROSInterruptException:
            rospy.loginfo("Action terminated.")
        finally:
            # save trajectory into csv file
            np.savetxt('trajectory.csv', np.array(self.trajectory), fmt='%f', delimiter=',')


    def run(self):
        waypoints = [[0.5, 0], [0.5, -0.5], [1, -0.5], [1, 0], [1, 0.5],\
                      [1.5, 0.5], [1.5, 0], [1.5, -0.5], [1, -0.5], [1, 0],\
                      [1, 0.5], [0.5, 0.5], [0.5, 0], [0, 0], [0, 0]]
        for i in range(len(waypoints)-1):
            self.move_to_point(waypoints[i], waypoints[i+1])


    def move_to_point(self, current_waypoint, next_waypoint):
        # generate polynomial trajectory and move to current_waypoint
        # next_waypoint is to help determine the velocity to pass current_waypoint
        coef_x = self.polynomial_time_scaling_3rd_order(0, 0,0,0,2)
        coef_y = self.polynomial_time_scaling_3rd_order(current_waypoint[1],.5,next_waypoint[1],.5,2)
        pd_controller = Linear_Controller()
        pd_controller.setPD(0.8, 0.5)
        pd_controller_theta = Theta_Controller()
        pd_controller_theta.setPD(0.8, 0.5)
        
        for t in range(200):
            a0,a1,a2,a3 = coef_x
            V_x_t = a1 + 2*a2*t + 3*a3*(t**2)
            P_x_t = a0 + a1*t + a2 * (t**2) + a3 * (t**3)
            a0,a1,a2,a3 = coef_y
            V_y_t = a1 + 2*a2*t + 3*a3*(t**2)
            P_y_t = a0 + a1*t + a2 * (t**2) + a3 * (t**3)

            v_t = sqrt(V_x_t **2 + V_y_t**2)
            self.vel.linear.x = v_t

            tar_theta = atan2(V_y_t, V_x_t)

            if tar_theta <= 0 and self.pose.theta >= 8 and self.pose.theta -tar_theta >= pi:
                tar_theta += 2 * pi
            elif tar_theta > 0 and self.pose.theta < 0 and tar_theta - self.pose.theta > pi:
                tar_theta -= 2* pi
            else:
                pass
            pd_controller.setPoint(tar_theta)
           # use PD controller to set angle
            self.vel.angular.z = pd_controller_theta.update(self.pose.theta)
       
            self.vel_pub.publish(self.vel)
            self.rate.sleep
            
        pass


    def polynomial_time_scaling_3rd_order(self, p_start, v_start, p_end, v_end, T):
        # input: p,v: position and velocity of start/end point
        #        T: the desired time to complete this segment of trajectory (in second)
        # output: the coefficients of this polynomial
        PolyList = np.matrix([[0, 0, 0, 1],
                              [pow(T, 3), pow(T, 2), T, 1],
                              [0, 0, 1, 0],
                              [3 * pow(T, 2), 2 * T, 1, 0]])
        
        x = np.matrix([[p_start],
                      [p_end],
                      [v_start],
                      [v_end]])
        
        PolyInverse = np.linalg.inv(PolyList)

        a = PolyInverse * x

        return a
        pass


    def odom_callback(self, msg):
        # get pose = (x, y, theta) from odometry topic
        quarternion = [msg.pose.pose.orientation.x, msg.pose.pose.orientation.y,\
                    msg.pose.pose.orientation.z, msg.pose.pose.orientation.w]
        (roll, pitch, yaw) = tf.transformations.euler_from_quaternion(quarternion)
        self.pose.theta = yaw
        self.pose.x = msg.pose.pose.position.x
        self.pose.y = msg.pose.pose.position.y

        # logging once every 100 times (Gazebo runs at 1000Hz; we save it at 10Hz)
        self.logging_counter += 1
        if self.logging_counter == 100:
            self.logging_counter = 0
            self.trajectory.append([self.pose.x, self.pose.y])  # save trajectory
            rospy.loginfo("odom: x=" + str(self.pose.x) +\
                ";  y=" + str(self.pose.y) + ";  theta=" + str(yaw))


if __name__ == '__main__':
    whatever = Turtlebot()