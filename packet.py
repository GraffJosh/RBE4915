# traj start=3
# traj cont =2
# traj stop =1
class point:
    x = 0
    y = 0
    z = 0
    r = 0
    p = 0
    t = 0

    def __init__(self,in_x,in_y,in_z,in_r,in_p,in_t):
        self.x = in_x
        self.y = in_y
        self.z = in_z
        self.r = in_r
        self.p = in_p
        self.y = in_t

    def __str__(self):
        return str(self.x)+","+str(self.y)+","+str(self.z)+","+str(self.r)+","+str(self.p)+","+str(self.t)


class packet:
    status  = 0
    robot   = 0
    speed   = 0
    data    = 0

    def __init__(self,in_status,in_robot,in_speed,in_data):
        self.status  = in_status
        self.robot   = in_robot
        self.speed   = in_speed
        self.data    = in_data
    def __str__(self):
        return str(self.status)+","+str(self.robot)+","+str(self.speed)+","+str(self.data)
