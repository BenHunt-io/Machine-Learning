# Using Numpy library for math functions and array manipulation
# Arrays/Matricies useful for feeding signals forward and errors backwards through a network
# import matplotlib.pyplot - import graphics plotting ability

# Basic Printing

print("Hello World!")

x = 10
print(x)
print(x + 5)


list(range(10)) # List from 0 - 9


#Basic loop n = 0
for n in range (10):
	print(n)
	pass
print("done")


# function that takes 2 numbers as input
# and outputs their average
def avg(x,y):
	print("first input is", x)
    print("second input is", y) 
    a = (x + y) / 2.0
    print("average is", a)
    return a


# using numpy and 2D arrays
a = numpy.zeros( [3,2] )
print(a)


a[0,0] = 1
a[0,1] = 2
a[1,0] = 9
a[2,1] = 12
print(a)

%matplotlib inline #to plot in the same window

#instruction to create plot is imShow, a is the array
matplotlib.pyplot.imshow(a,interpolation = "nearest")



#classes/objects


# class for a dog object
class Dog:
 
	# dogs can bark()
	def bark(self):
		print("woof!")
		pass
     
	pass
	
sizzles = Dog()
sizzles.bark()

#Updated dog class
class Dog:

	# constructor
	# initialisation method with internal data
	def __init__(self, petname, temp):
		self.name = petname;
		self.temperature = temp;

	# get status
	def status(self):
		print("dog name is ", self.name)
		print("dog temperature is ", self.temperature)
		pass

	# set temperature
	
	def setTemperature(self,temp):
		self.temperature = temp;
		pass
     
	# dogs can bark()
	def bark(self):
		print("woof!")
		pass
     
	pass
