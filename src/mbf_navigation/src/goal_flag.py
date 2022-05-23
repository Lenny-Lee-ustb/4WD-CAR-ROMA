#!/usr/bin/env python3
from geometry_msgs.msg import PoseStamped,Pose
'''
class count_time():
    def __init__(self):
        self.
if __name__ == '__main__':
    rospy.init_node=("counttime")
    count_time()
'''

import rospy
import string
import math
import time
import sys
from nav_msgs.msg import Odometry
from std_msgs.msg import String
from move_base_msgs.msg import MoveBaseActionResult
from actionlib_msgs.msg import GoalStatusArray
from geometry_msgs.msg import PoseStamped

class MultiGoals:
    def __init__(self, goalListX, goalListY, retry, map_frame):
        self.retry=1
        if(self.retry==1):
            #self.sub = rospy.Subscriber('move_base/result', MoveBaseActionResult, self.statusCB, queue_size=1)
            self.pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=10)
            self.pose_ekf = rospy.Subscriber('/odometry/filtered',Odometry,self.getPose_ekf,queue_size=10)
        # params & variables
            self.goalListX = goalListX
            self.goalListY = goalListY
            self.goalListW = goalListW
            self.goalListZ = goalListZ
            self.kx=0
            self.ky=0
            self.gx=0
            self.gy=0
            self.flag=1
            self.MIN_DISTANCE=0.8 #min distance of the judge between the goal and odometrypose
            #self.retry = retry
            self.LONG=len(self.goalListX)
            self.goalId = 0
            self.count = 0
            self.goalMsg = PoseStamped()
            self.goalMsg.header.frame_id = map_frame
            #self.goalMsg.pose.orientation.z = 0.0
            #self.goalMsg.pose.orientation.w = 0.5
        # Publish the first goal
            time.sleep(1)
            self.goalMsg.header.stamp = rospy.Time.now()
            self.goalMsg.pose.position.x = self.goalListX[self.goalId]
            self.goalMsg.pose.position.y = self.goalListY[self.goalId]
            self.goalMsg.pose.orientation.z = self.goalListZ[self.goalId]
            self.goalMsg.pose.orientation.w = self.goalListW[self.goalId]
            self.pub.publish(self.goalMsg)
            self.start_time=rospy.get_time()
            rospy.loginfo("Initial goal published! Goal ID is: %d", self.goalId)
            self.goalId = self.goalId + 1

    def statusCB(self):
        self.gx=self.goalListX[self.goalId-1] if (self.count!=self.LONG-1) else self.goalListX[self.goalId]
        self.gy=self.goalListY[self.goalId-1] if (self.count!=self.LONG-1) else self.goalListY[self.goalId]
        #print(self.gx)
        self.dist=self.distance(self.kx,self.ky,self.gx,self.gy)
	#print(self.dist)
        #print(data.status.status)
        #if (data.status.status == 3 and self.flag==1) or self.dist<self.MIN_DISTANCE: # reached and not the final goal
        if self.dist<self.MIN_DISTANCE and self.flag==1:
	    #print("here")
            finish_time = rospy.get_time()
            # interval=rospy.Time()
            interval = finish_time - self.start_time
            print(interval)
            self.goalMsg.header.stamp = rospy.Time.now()
            self.goalMsg.pose.position.x = self.goalListX[self.goalId]
            self.goalMsg.pose.position.y = self.goalListY[self.goalId]
            self.goalMsg.pose.orientation.z = self.goalListZ[self.goalId]
            self.goalMsg.pose.orientation.w = self.goalListW[self.goalId]
            self.pub.publish(self.goalMsg)
            rospy.loginfo("Initial goal published! Goal ID is: %d", self.goalId)
            rospy.loginfo("intostatusCB")
            self.count=self.count+1
            print(self.count)
            #print(len(self.goalListX))
            if self.count==len(self.goalListX):
                print("gg")
                self.flag=0
            if self.goalId < (len(self.goalListX)-1):
                self.goalId = self.goalId + 1

    def getPose_ekf(self,data):
        self.kx=data.pose.pose.position.x
        self.ky=data.pose.pose.position.y
        self.statusCB()


    def distance(self,kx,ky,gx,gy):
        try:
            return math.sqrt((kx-gx)**2+(ky-gy)**2)
	                       #return kx-gx
        except:
            return None

if __name__ == "__main__":
    try:
        # ROS Init
        rospy.init_node('multi_goals', anonymous=True)
        retry=1
        # Get params
        goalListX = rospy.get_param('~goalListX', '[11.3,0.0]')
        goalListY = rospy.get_param('~goalListY', '[0.05,2.0]')
        goalListZ = rospy.get_param('~goalListZ', '[0,1]')
        goalListW = rospy.get_param('~goalListW', '[1,0]')
        map_frame = rospy.get_param('~map_frame', 'map' )
        #retry = rospy.get_param('~retry', '1')
        #retry = int(retry)
        #print(type(retry))
        goalListX = goalListX.replace("[","").replace("]","")
        goalListY = goalListY.replace("[","").replace("]","")
        goalListZ = goalListZ.replace("[","").replace("]","")
        goalListW = goalListW.replace("[","").replace("]","")

        goalListX = [float(x) for x in goalListX.split(",")]
        goalListY = [float(y) for y in goalListY.split(",")]
        goalListZ = [float(z) for z in goalListZ.split(",")]
        goalListW = [float(w) for w in goalListW.split(",")]

        if len(goalListX) == len(goalListY) & len(goalListY) >=1 :
            # Constract MultiGoals Obj
            rospy.loginfo("Multi Goals Executing...")
            mg = MultiGoals(goalListX, goalListY, retry, map_frame)
            rospy.spin()
        else:
            rospy.loginfo("Lengths of goal lists are not the same")
    except KeyboardInterrupt:
        print("shutting down")
