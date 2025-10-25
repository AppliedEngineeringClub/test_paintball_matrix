import math
import numpy as np
import util

class VectorNd:

    def __init__(self, n: int =None, components: np.ndarray =None):

        if(n != None and components == None):
            self.n = n
            self.components = np.zeros(n)

        elif(components != None and n == None):
            self.n = components.size
            self.components = components
        else:
            raise ValueError("Expected either n or components given, got none.")
    
    def get_vector(self):
        return self
    
    def get(self, index):
        return self.components[index]
    
    def get_dimension(self):
        return self.n

    def copy(self):
        return VectorNd(self.components)
    
    def set_point(self, other: 'VectorNd'):
        self.components = other.components
        return self

    def set(self, components):
        self.components = components
        return self
    
    def set_value_at_index(self, index, value):
        self.components[index] = value
        return self
    
    def with_value_at_index(self, index, value):
        copy = self.components
        copy[index] = value
        return VectorNd(components=copy)
    
    def get_magnitude(self):
        squared_sums = 0.0

        for i in range(self.n):
            squared_sums += (self.components[i] * self.components[i])

        return math.sqrt(squared_sums)

    def get_unit_vector(self):
        mag = self.get_magnitude()

        copy = self.components

        for i in range(self.n):
            copy[i] / mag

        return VectorNd(copy)

    def with_magnitude(self, magnitude):
        return self.get_unit_vector().times(magnitude)
    
    def plus(self, other: 'VectorNd'):
        copy = self.components

        for i in range(self.n):
            copy[i] += other[i]

        return VectorNd(copy)
    
    def plus_at_index(self, index, value):
        copy = self.components

        copy[index] += value

        return VectorNd(copy)
    
    def minus(self, other: 'VectorNd'):
        return self.plus(other.times(-1))
    
    def minus_at_index(self, index, value):
        return self.plus_at_index(index, -value)
    
    def times(self, scalar):
        copy = self.components

        for i in range(self.n):
            copy[i] *= scalar

        return VectorNd(copy)
    
    def times_at_index(self, index, scalar):
        copy = self.components

        copy[index] *= scalar

        return VectorNd(copy)

    def divided_by(self, scalar):
        return self.times(1 / scalar)
    
    def divided_at_index(self, index, scalar):
        return self.times_at_index(index, 1 / scalar)

    def dot(self, other: 'VectorNd'):
        sum_of_products = 0

        for i in range(self.n):
            sum_of_products += self.components[i] * other.components[i]

        return sum_of_products

    def equals(self, other: 'VectorNd'):
        components_equal = True

        for i in range(self.n):
            if self.components[i] != other.components[i]:
                components_equal = False

        return components_equal


    



