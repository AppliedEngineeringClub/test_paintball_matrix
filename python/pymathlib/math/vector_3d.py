import util
import math
import numpy as np
from vector_nd import VectorNd

class Vector3d(VectorNd):

    def __init__(self, x=0, y=0, z=0):
        super().__init__(np.array(x, y, z))

    def cross(self, other: 'Vector3d'):
        a = self.components[0]
        b = self.components[1]
        c = self.components[2]

        x = other.components[0]
        y = other.components[1]
        z = other.components[2]

        i = (b * z) - (c * y)
        j = (a * z) - (c * x)
        k = (a * y) - (b * x)

        return Vector3d(i, -j, k)

