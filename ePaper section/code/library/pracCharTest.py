import math

class printTest:
	def __init__(self):
		print("Started")
		self.width = 0
		self.height = 0
		self.radius = 0
		self.invert = False
		self.filled = False
		self.xRotation = False
		self.yRotation = False
		self.maxHeight = 200
		self.maxWidth = 200
		self.image = [
		" ",1,1,1," "," "," "," "," ",
		" ",1,1,1,1,1,1,1," ",
		" "," "," ",1,1,1,1," "," ",
		" "," ",1,1,1," "," "," "," ",
		1,1,1,1,1,1,1,1,1
		]
		self.charBuff = [
		" "," ",1," "," ",
		" ",1," ",1," ",
		" ",1," ",1," ",
		" ",1,1,1," ",
		" ",1," ",1," ",
		1," "," "," ",1,
		1," "," "," ",1,
		
		1,1,1," "," ",
		1," "," ",1," ",
		1,1,1,1," ",
		1,1,1,1," ",
		1," "," ",1," ",
		1," "," ",1," ",
		1,1,1,1," ",
		
		" "," ",1," "," ",
		" ",1," ",1," ",
		" ",1," ",1," ",
		" ",1,1,1," ",
		1,1," ",1,1,
		1," "," "," ",1,
		1," "," "," ",1,
		
		1,1,1," "," ",
		1," "," ",1," ",
		1,1,1,1," ",
		1,1,1,1," ",
		1," "," ",1," ",
		1," "," ",1," ",
		1,1,1,1," ",
		
		" ",1,1,1," ",
		1,1," "," ",1,
		1," "," "," "," ",
		1," "," "," "," ",
		1," "," "," "," ",
		1,1," "," ",1,
		" ",1,1,1," "
		]
		
	def printCircle(self):
		self.radius = 3 # At zero, only the center point is considered
		additionalThickness = 5 # Will add more "pixels" to its width by increasing the radius that was normally considered.

		#Proper drawing inspiration
		# Inspired initially from: https://stackoverflow.com/questions/38843226/how-to-draw-a-circle-with-stars-in-c
		# Proper circle drawing for filling & interior https://stackoverflow.com/questions/70722545/draw-circle-in-console-using-python
		for j in range(-self.radius-additionalThickness, self.radius+1+additionalThickness, 1):
			for i in range(-self.radius-additionalThickness, self.radius+1+additionalThickness, 1):
				thing = "*" if (self.radius-1 <= math.sqrt(math.pow(j,2)+math.pow(i,2)) <= self.radius+additionalThickness) else " " # For normal circle drawing
				thing = "*" if (self.filled and int(math.sqrt(math.pow(j,2)+math.pow(i,2))) <= self.radius-1) else thing # For filling in circle
				if self.invert:
					if thing == " ":
						thing = "*"
					else:
						thing = " "
				print(thing, end="")
			print("")
		print("@@@@@")
	
	def printRectangle(self):
		# Setup for the test
		self.width = 25
		self.height = 7
		self.nortSouth = False
		
		# Setup for rotation and the such
		xCounter = 1
		xStart = 0
		xEnd = self.width
		if self.xRotation:
			xCounter = -1
			xStart = self.width - 1
			xEnd = -1
		
		yCounter = 1
		yStart = 0
		yEnd = self.height
		if self.yRotation:
			yCounter = -1
			yStart = self.height - 1
			yEnd = -1

		#Proper drawing
		for j in range(yStart, yEnd, yCounter):
			northSouth = True if (j==0 or j==self.height-1) else False
			for i in range(xStart, xEnd, xCounter):
				thing = "*" if (northSouth or self.filled or i==0 or i==self.width-1) else " "
				if self.invert:
					if thing == " ":
						thing = "*"
					else:
						thing = " "
				print(thing, end="")
			print("")
		print("@@@@@")
	
	def printString(self):
		# Setup for test
		self.charAmount = 5
		self.charWidth = 5
		self.width = 25
		self.height = 7
		offsetArea = self.height * self.charWidth
		
		# Setup for rotation and the such
		xCounter = 1
		xStart = 0
		xEnd = self.width
		if self.xRotation:
			xCounter = -1
			xStart = self.width - 1
			xEnd = -1
		
		yCounter = 1
		yStart = 0
		yEnd = self.height
		if self.yRotation:
			yCounter = -1
			yStart = self.height - 1
			yEnd = -1

		for j in range(yStart, yEnd, yCounter):
			areaCount = self.charWidth - 1 if self.xRotation else 0
			charCount = self.charWidth - 1 if self.xRotation else 0
			for i in range(xStart, xEnd, xCounter):
				thing = self.charBuff[offsetArea * areaCount + charCount + j * self.charWidth]
				if self.invert:
					if thing == " ":
						thing = 1
					else:
						thing = " "
				# Since our array isn't nice to do with. We need to count this
				charCount += xCounter
				if (charCount == self.charWidth and not self.xRotation) or (charCount < 0 and self.xRotation):
					charCount = self.charWidth - 1 if self.xRotation else 0
					areaCount += xCounter
				print(thing, end="")
			print("")
		print("@@@@@")
	
	def printImage(self):
		# Setup for test
		self.width = 9
		self.height = 5
		
		# Setup for rotation and the such
		xCounter = 1
		xStart = 0
		xEnd = self.width
		if self.xRotation:
			xCounter = -1
			xStart = self.width - 1
			xEnd = -1
		
		yCounter = 1
		yStart = 0
		yEnd = self.height
		if self.yRotation:
			yCounter = -1
			yStart = self.height - 1
			yEnd = -1

		for j in range(yStart, yEnd , yCounter):
			for i in range(xStart, xEnd, xCounter):
				thing = self.image[i + j * self.width]
				if self.invert:
					if thing == " ":
						thing = 1
					else:
						thing = " "
				print(thing, end="")
			print("")
		print("@@@@@")

a = printTest()
print("_________")
print("Original")
a.printCircle()
a.filled = True
a.printCircle()
a.filled = False
a.invert = True
a.printCircle()
a.invert = False
print("_________")
print("Original")
a.printRectangle()
a.filled = True
a.printRectangle()
a.filled = False
a.xRotation = True
a.printRectangle()
a.xRotation = False
a.yRotation = True
a.printRectangle()
a.yRotation = False
a.invert = True
a.printRectangle()
a.invert = False
print("_________")
print("Original")
a.printString()
a.xRotation = True
a.printString()
a.xRotation = False
a.yRotation = True
a.printString()
a.yRotation = False
a.invert = True
a.printString()
a.invert = False
print("_________")
print("Original")
a.printImage()
a.xRotation = True
a.printImage()
a.xRotation = False
a.yRotation = True
a.printImage()
a.yRotation = False
a.invert = True
a.printImage()
print("End")
