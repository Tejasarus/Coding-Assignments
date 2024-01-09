import numpy as np
from math import pi, cos, sin, atan, atan2, sqrt, acos

def inverse_kinematics(position):
    # input: the position of end effector [x, y, z]
    # output: joint angles [joint1, joint2, joint3]
    # add your code here to complete the computation

    link1z = 0.065
    link2z = 0.039
    link3x = 0.050
    link3z = 0.150
    link4x = 0.150
    x = position[0]
    y = position[1]
    z = position[2]

    # Calculate joint1
    joint1 = atan2(y, x)

    # Calculate joint2
    L2 = sqrt(x**2 + y**2) - link1z
    L3 = z - link3z
    d = sqrt(L2**2 + L3**2)
    alpha = acos((link2z**2 + d**2 - link4x**2) / (2 * link2z * d))
    beta = atan2(L3, L2)
    joint2 = pi/2 - alpha - beta

    gamma = acos((link4x**2 + d**2 - link2z**2) / (2 * link4x * d))
    joint3 = pi - gamma

    return [joint1, joint2, joint3]

j = inverse_kinematics((0.20000,0.00000,0.25391))
print(j)