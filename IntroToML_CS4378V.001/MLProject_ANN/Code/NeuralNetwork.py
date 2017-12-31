# initializiation - to set the number of input, hidden and output nodes
# train - refind the weights after being given a training set example to learn from
# query - give an answer from the output nodes after being given an input


import numpy
import scipy.misc
import scipy.special
import matplotlib.pyplot
%matplotlib inline

##################################################
# Artificial 3 Layer Neural Network
# Purpose: Digit & Symbol Recogition
# By: Ben Hunt and Todd 
#
##################################################


class ArtificialNeuralNetwork:
    
    #initialize the neural network
    def __init__(self,inputNodes,hiddenNodes,outputNodes,learningRate):
        import numpy
        import scipy.special


        #keep track of image name
        self.imageName = 1
        self.testImageName = 1
        
		
		# Initialize Defaults
		
		
		
        # set the number of nodes in each input,hidden,ouput layer
        self.inodes = inputNodes
        self.hnodes = hiddenNodes
        self.onodes = outputNodes

        #learning rate
        self.lr = learningRate

        #--- initial weight matricies ---
        #link weight matricies, wih and who (input hidden, hidden output)
        self.wih = numpy.random.normal(0.0, pow(self.hnodes, -0.5),(self.hnodes,self.inodes))
        self.who = numpy.random.normal(0.0, pow(self.onodes, -0.5),(self.onodes,self.hnodes))

        #Put this in the constructor of the neural network.. So we can use sigmoid anywhere
        # we need it. --> (activation function is the sigmoid function)
        # We basically defined a function here using the keyword lambda, taking a parameter x.
        # it returns scipy.special.explit(x) which is the sigmoid function.
        # (anonymous function)
        self.activation_function = lambda x: scipy.special.expit(x)



        pass

    #train the neural network
    def train(self, inputs_list, targets_list):
    
        #Second part, take calculated output, compare it with the desired output and use
        #the difference to guide our updating of the network weights
        #converts inputs to 2D array & Transforms them
        
        inputs = numpy.array(inputs_list,ndmin=2).T
        targets = numpy.array(targets_list,ndmin=2).T
        
        

        #calc signals into hidden layer
        hidden_inputs = numpy.dot(self.wih,inputs)
        #calc signals emerging from hidden layer
        hidden_outputs = self.activation_function(hidden_inputs)

        #calc signals into final output layer
        final_inputs = numpy.dot(self.who,hidden_outputs)

        #calculate the singals emerging from final output layer
        final_outputs = self.activation_function(final_inputs)

        #error is the (target - acutual)
        output_errors = targets - final_outputs

        #hidden layer error is the output_errors, split by weights,
        #recombined at hidden nodes
        #Error_hidden = weightsT_hiddenoutput · errors_output
        #Have to transform the weights.
        hidden_errors = numpy.dot(self.who.T, output_errors)

        self.who += self.lr * numpy.dot((output_errors * final_outputs *
            (1.0 - final_outputs)), hidden_outputs.T)

        # update the weights for the links between the input and hiddenlayers
        self.wih += self.lr * numpy.dot((hidden_errors * hidden_outputs *
            (1.0 - hidden_outputs)), inputs.T)

        pass

    #query the neural network
    def query(self,inputs_list):

        #Converts input list to 2d array
        #Switches rows and columns
        inputs = numpy.array(inputs_list,ndmin=2).T
        
        # feed input signals to hidden layer
        hidden_inputs = numpy.dot(self.wih,inputs)
        

        # calculate the signals emerging from hidden layer
        hidden_outputs = self.activation_function(hidden_inputs)

        #calc signals into final layer
        final_inputs = numpy.dot(self.who,hidden_outputs)
        #calc signals emerging out of final layer (aka what is output of ANN)
        final_outputs = self.activation_function(final_inputs)

        #After feeding forward the signals throught the network and getting outputs
        #We need to train the network to achieve better outputs. We do this by
        #training (back propogating the error of the output through the network updating the weights)
        return final_outputs
        
        
    def testImages(self,sign):
        
    
        image_array = scipy.misc.imread("C:\\Users\\The Dough Boys\\Desktop\\MLProject\\"+sign+"\\"+repr(self.testImageName) + ".jpg", flatten=True)
        image_array = 255.0 - image_array
        matplotlib.pyplot.imshow(image_array, cmap='Greys', interpolation ='None')


        # ravel converts to 1D array
        scaled_input = (numpy.asfarray(image_array.ravel()) / 255.0 * .99) + .01

        
        
        return self.query(scaled_input)
        
        
    def trainImages(self,sign):
        image_array = scipy.misc.imread("C:\\Users\\The Dough Boys\\Desktop\\MLProject\\"+sign+"\\" + repr(self.imageName) + ".jpg", flatten=True)
        image_array = 255.0 - image_array
        matplotlib.pyplot.imshow(image_array, cmap='Greys', interpolation ='None')

        
        

        # ravel converts to 1D array
        scaled_input = (numpy.asfarray(image_array.ravel()) / 255.0 * .99) + .01


        onodes = 12 # numbers 0-9 and +
        
        targets = numpy.zeros(onodes) + 0.01
        if(sign == "PlusSigns"):
            targets[10] = 0.99
        else:
            targets[11] = 0.99
        
        
        
        self.train(scaled_input, targets)
        
    
    def printOutput(self, output_list):
    
        print("Result:")
        
        
        max = outputList[0][0]
        maxIndex = 0
        i = 0
        
        for entry in output_list:
            if(entry > max):
                max = entry
                maxIndex = i
            i += 1
            
            
        print(maxIndex)
        
        
        
    


#number of input,hidden and output nodes
input_nodes = 784
hidden_nodes = 100
output_nodes = 12

#learning rate is 0.01
learning_rate = .3

#make instance of neural network
ann = ArtificialNeuralNetwork(input_nodes,hidden_nodes,output_nodes,learning_rate)

#Reads in the data... data_file is like FileInputStream
# data_list is an array of lines from the .csv file
# data_file.close closes the stream
data_file = open("C:\\Users\\The Dough Boys\\Desktop\\MLProject\\mnist_train60000.csv", 'r')
trainingData = data_file.readlines()
data_file.close()

#len(data_list)
#print(data_list[0])

epochs = 1 # number of total times the neural network gets trained


for n in range(epochs):
	for record in trainingData:
		#split the data along the commas, comma is the delimiter
		all_values = record.split(',')
		# [1:]  this takes all but the first element in the list (how we ignore the
		# label). numpy.asfarray is a function to convert strings to numbers
		# last part converts it to a 28x28 array (matrix) .. & greyscale
		image_array = numpy.asfarray(all_values[1:]).reshape((28,28))
		#matplotlib.pyplot.imshow(image_array, cmap='Greys', interpolation ='None')

		#Preprocessing
		#Rescale our input between .01 - 1.0 (.01 to avoid 0 errors)
		# divide by 255 to bring in range of 0-1, multiply by .99 to bring in range
		# of 0-.99, then add .01 to get .01 - 1.0
		scaled_input = (numpy.asfarray(all_values[1:]) / 255.0 * .99) + .01
		#print(scaled_input)

		# We need target matrix that has optimal values
		onodes = 12 # numbers 0-9
		targets = numpy.zeros(onodes) + 0.01
		targets[int(all_values[0])] = 0.99


		#input layer, output expected
		ann.train(scaled_input,targets)
		pass
    

# load the mnist test data CSV file into a list
test_data_file = open("C:\\Users\\The Dough Boys\\Desktop\\MLProject\\test100.csv",'r')
testingData = test_data_file.readlines()
test_data_file.close()

for n in range(epochs):
    # train the images
    ann.imageName = 1 # reset
    for n in range(80):
        ann.trainImages("PlusSigns")
        ann.trainImages("MinusSigns")
        ann.imageName += 1

# For testing
totalCorrect = 0
totalLabels = 0
sum = 0



for record in testingData:

	all_values = record.split(',')

	image_array = numpy.asfarray(all_values[1:]).reshape((28,28))

	scaled_input = (numpy.asfarray(all_values[1:]) / 255.0 * .99) + .01

	onodes = 12 # numbers 0-9
	targets = numpy.zeros(onodes) + 0.01
	targets[int(all_values[0])] = 0.99

	predictList = ann.query(scaled_input)
	
	# for entry in predictList:
		# print("%.5f" % entry)
	# print("--------------")

	#find accuracys
	max = predictList[0][0] #start with max at first index
	maxIndex = 0
	for n in range(onodes):
		if(predictList[n][0] > max):
			max = predictList[n][0]
			maxIndex = n

	# sum up the correct predictions, for ex .96 + .78 + ...ect.
	if(maxIndex == int(all_values[0])):
		sum += max
		totalCorrect += 1

	totalLabels +=1 # sum of total tests

	#print ("Should be: " + repr(int(all_values[0])) + " but was: " + repr(maxIndex) + " with accuracy: " + repr(max))

	#matplotlib.pyplot.imshow(image_array, cmap='Greys', interpolation ='None')

	pass



print("Average prediction: "  + repr(sum/totalCorrect))
print("Correct: "  + repr(totalCorrect/totalLabels))
print("Epochs: " +  repr(epochs))
print("Learning Rate: " + repr(learning_rate))
print("Hidden Layer Nodes: " + repr(hidden_nodes))




testSize = 20
totalLabels = testSize
totalCorrect = 0
sum = 0
max = 0
for n in range (testSize):
    predictList = ann.testImages("TestPlus")
    ann.testImageName += 1
    #find accuracys
    max = predictList[0][0] #start with max at first index
    maxIndex = 0

    for n in range(output_nodes):
        if(predictList[n][0] > max):
            max = predictList[n][0]
            maxIndex = n

    # sum up the correct predictions, for ex .96 + .78 + ...ect.
    if(maxIndex == 10):
        sum += max
        totalCorrect += 1

    totalLabels +=1 # sum of total tests

print("Average prediction: "  + repr(sum/totalCorrect))
print("Correct: "  + repr(totalCorrect/totalLabels))
print("Epochs: " +  repr(epochs))
print("Learning Rate: " + repr(learning_rate))
print("Hidden Layer Nodes: " + repr(hidden_nodes))

ann.testImageName = 1
totalLabels = testSize
totalCorrect = 0
sum = 0
max = 0
for n in range (testSize):
    predictList = ann.testImages("TestMinus")
    ann.testImageName += 1
    #find accuracys
    max = predictList[0][0] #start with max at first index
    maxIndex = 0

    for n in range(output_nodes):
        if(predictList[n][0] > max):
            max = predictList[n][0]
            maxIndex = n

    # sum up the correct predictions, for ex .96 + .78 + ...ect.
    if(maxIndex == 11):
        sum += max
        totalCorrect += 1

    totalLabels +=1 # sum of total tests

print("Average prediction: "  + repr(sum/totalCorrect))
print("Correct: "  + repr(totalCorrect/totalLabels))
print("Epochs: " +  repr(epochs))
print("Learning Rate: " + repr(learning_rate))
print("Hidden Layer Nodes: " + repr(hidden_nodes))