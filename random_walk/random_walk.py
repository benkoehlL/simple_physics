from random import choice
import matplotlib.pyplot as plt

import numpy as np

class RandomWalk():
   """A class to generate random walks"""

   def __init__(self, num_points=5000):
      """Initialise attributes of a walk."""
      self.num_points = num_points

      # all movements start at (0,0).
      self.x_values = [0]
      self.y_values = [0]
   
   def fill_walk(self):
      """Calculates all the points in the walk"""
   
      # do steps until path has appropriate length
      while len(self.x_values) < self.num_points:
      
         # choose direction of the next steps
         x_direction = choice([1,-1])
         y_direction = choice([1,-1]) 
         x_distance = choice([0,1,2,3,4])
         y_distance = choice([0,1,2,3,4])
         x_step = x_direction*x_distance
         y_step = y_direction*y_distance
      
         # reject steps that do not change the current position
         if x_step == 0 and y_step == 0:
            continue

         # calculate the next value of x and y
         next_x = self.x_values[-1] + x_step
         next_y = self.y_values[-1] + y_step

         self.x_values.append(next_x)
         self.y_values.append(next_y)

while True: 
   # create a random walk and plot the points in a diagram
   rw = RandomWalk(5000000)
   rw.fill_walk()
   point_numbers = list(range(rw.num_points))
   
   # determine distance from the origin 
   distance = [np.sqrt(rw.x_values[i]**2+rw.y_values[i]**2) for i in range(len(rw.x_values))]  
   
   plt.figure("distance vs. time")
   plt.xlabel("time")
   plt.ylabel("distance")
   plt.plot([4*np.sqrt(i) for i in range(len(rw.x_values))])
   plt.plot(distance)
   
   plt.figure("real space position")
   plt.scatter(rw.x_values, rw.y_values, c=point_numbers, cmap=plt.cm.Blues, edgecolor='none', s=1)
   
   #highlight the first and last point of the walk
   plt.scatter(0,0, c='green', edgecolors='none', s=100)
   plt.scatter(rw.x_values[-1],rw.y_values[-1], c='red', edgecolors='none', s=100)
   
   #remove the axes
   plt.axes().get_xaxis().set_visible(False)
   plt.axes().get_yaxis().set_visible(False)

   plt.show()
   
   keep_running = input("Make another walk? (y/n): ")
   if keep_running == 'n':
       break
   
   
