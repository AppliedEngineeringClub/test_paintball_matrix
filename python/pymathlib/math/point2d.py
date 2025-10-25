import util
import math
import numpy as np
from vector_nd import VectorNd

class Point2d(VectorNd):

    def __init__(self, x=0, y=0):
        components = np.array((x, y))
        super.__init__(components)

    def from_native(x, y):
        coords = util.native_to_cartesian(x, y)
        return Point2d(coords[0], coords[1])
    
    def get_native(self):
        coords = util.cartesian_to_native(self.x, self.y)
        return Point2d(coords[0], coords[1])

    def get_native_x(self):
        return self.get_native().get(0)

    def get_native_y(self):
        return self.get_native().get(1)

    def is_out_of_bounds(self, w=util.width, h=util.width):
        x = self.get(0)
        y = self.get(1)

        if(x > w / 2 or x < -w / 2):
            return True
        if(y > h / 2 or y < -h / 2):
            return True
        
        return False
