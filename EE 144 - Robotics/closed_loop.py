#!/usr/bin/env python3

from math import pi, sqrt, atan2, cos, sin
import numpy as np
import time

import rospy
import tf
from std_msgs.msg import Empty
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist, Pose2D
class Controller:
    def __init__(self, P=0.0, D=0.0, set_point=0):
        self.Kp = P
        self.Kd = D
        self.set_point = set_point # reference (desired value)
        self.previous_error = 0

    def update(self, current_value):
        # calculate P_term and D_term
        error = self.set_point - current_value
        P_term = self.Kp*error
        D_term = self.Kd*(error- self.previous_error)
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
        self.vel_pub = rospy.Publisher("cmd_vel", Twist, queue_size=10)
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

        try:
            self.run()
        except rospy.ROSInterruptException:
            rospy.loginfo("Action terminated.")
        finally:
            # save trajectory into csv file
            np.savetxt('trajectory.csv', np.array(self.trajectory), fmt='%f', delimiter=',')


    def run(self):
        # add your code here to adjust your movement based on 2D pose feedback
        # Use the Controller
        
        t = Controller(0.8, 0.6 , 4.0)
        c = Twist()
        
        #go straight
        c.linear.x = 0.35
        while(self.pose.x <= 4):
            if(self.pose.y >= 0.1):
                t.setPoint(-pi/6)
                c.angular.z = t.update(self.pose.theta)
            elif(self.pose.y <= -0.1):
                t.setPoint(pi/6)
                c.angular.z = t.update(self.pose.theta)
            else:
                t.setPoint(self.pose.theta)
                c.angular.z = t.update(self.pose.theta)

            self.vel_pub.publish(c)
            self.rate.sleep()
            #print(self.pose.y)
        
        c.linear.x = 0
        self.vel_pub.publish(c)
        self.rate.sleep()
        print("x:")
        print(self.pose.x)
        print("y:")
        print(self.pose.y)
        
        #turn
        t.setPoint(pi/2)
        c.angular.z = t.update(self.pose.theta)
        while(self.pose.theta < 1):
            self.vel_pub.publish(c)
            self.rate.sleep()
            #print(self.pose.theta)
        
        t.setPoint(self.pose.theta)
        c.angular.z = t.update(self.pose.theta)
        self.vel_pub.publish(c)
        self.rate.sleep()

        #go straight 2
        
        c.linear.x = 0.25
        while(self.pose.y <= 3.8):
            if(self.pose.x >= 4.1):
                t.setPoint(2)
                c.angular.z = t.update(self.pose.theta)
                #print("turn")
            elif(self.pose.x <= 3.9):
                t.setPoint(-0.1)
                c.angular.z = t.update(self.pose.theta)
            else:
                t.setPoint(self.pose.theta)
                c.angular.z = t.update(self.pose.theta)
            
            self.vel_pub.publish(c)
            self.rate.sleep()
            #print(self.pose.x)
        
        c.linear.x = 0
        self.vel_pub.publish(c)
        self.rate.sleep()
        print("x:")
        print(self.pose.x)
        print("y:")
        print(self.pose.y)

        #turn 2
        print("turning 2")
        t.setPoint(.01)
        c.angular.z = t.update(self.pose.theta)
        
        while(self.pose.theta < 2):
            self.vel_pub.publish(c)
            self.rate.sleep()

        t.setPoint(self.pose.theta)
        c.angular.z = t.update(self.pose.theta)
        self.vel_pub.publish(c)
        self.rate.sleep()
        time.sleep(.5)
        
        #straight 3
        t.setPD(1,2)
        print("going straight")
        c.linear.x = 0.35
        while(self.pose.x >= 0.1):
            if(self.pose.y > 4.1):
                t.setPoint(.01)
                c.angular.z = self.pose.theta
            elif(self.pose.y <= 3.9):
                t.setPoint(-.01)
                c.angular.z = self.pose.theta
            else:
                t.setPoint(self.pose.theta)
                c.angular.z = t.update(self.pose.theta)
            
            
            self.vel_pub.publish(c)
            self.rate.sleep()
            #print(self.pose.y)
        
        
        c.linear.x = 0
        self.vel_pub.publish(c)
        self.rate.sleep()
        print("x:")
        print(self.pose.x)
        print("y:")
        print(self.pose.y)
        
        #turn 3
        #time.sleep(1)
        t.setPD(0.8,0.6)
        for i in range(40):  
            t.setPoint(-pi/2)
            c.angular.z = t.update(self.pose.theta)
            self.vel_pub.publish(c)
            self.rate.sleep()

        t.setPoint(self.pose.theta)
        c.angular.z = t.update(self.pose.theta) 
        self.vel_pub.publish(c)
        self.rate.sleep()
        time.sleep(1)
        
        #straight 4
        t.setPD(1,2)
        print("going straight")
        c.linear.x = 0.35
        while(self.pose.y >= 0):
            if self.pose.x < -0.1:
                t.setPoint(pi/2)
                c.angular.z = t.update(self.pose.theta)
                self.rate.sleep()
            elif self.pose.x > 0.1:
                t.setPoint(-pi/2)
                c.angular.z = t.update(self.pose.theta)
                self.rate.sleep()
            c.angular.z = t.update(self.pose.theta) 
            self.vel_pub.publish(c)
            self.rate.sleep()
            #print(self.pose.y)
        
        c.linear.x = 0
        self.vel_pub.publish(c)
        self.rate.sleep()
        print("x:")
        print(self.pose.x)
        print("y:")
        print(self.pose.y)
        
        
        
    def odom_callback(self, msg):
        # get pose = (x, y, theta) from odometry topic
        quarternion = [msg.pose.pose.orientation.x,msg.pose.pose.orientation.y,\
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
            # display (x, y, theta) on the terminal
            rospy.loginfo("odom: x=" + str(self.pose.x) +\
                ";  y=" + str(self.pose.y) + ";  theta=" + str(yaw))


if __name__ == '__main__':
    whatever = Turtlebot()