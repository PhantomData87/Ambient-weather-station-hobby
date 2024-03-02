"""
  ******************************************************************************
    @file     analyzeTest
    @author   Alonzo Ortiz-Sanchez
    @version  V1.0.0
    @made     01-March-2024
    @modified 01-March-2024
    @brief    To take in my test data and give me averages, alongside standard deviation.
"""
sumOfVarOne = 0
sumOfVarTwo = 0
countVarOne = 0
countVarTwo = 0
switch = True

# Read file for average
with open("dump", "r") as dump:
	for line in dump:
		if switch:
			sumOfVarOne += float(line)
			countVarOne += 1
		else:
			sumOfVarTwo += float(line)
			countVarTwo += 1
		switch = not switch
varOneAverage = sumOfVarOne / countVarOne
varTwoAverage = sumOfVarTwo / countVarTwo

print(f"Results of var one average: {varOneAverage}")
print(f"Results of var two average: {varTwoAverage}")

# Redo reading for proper calculations for Standard Deviation
devOfVarOne = 0
devOfVarTwo = 0
switch = True
with open("dump", "r") as dump:
	for line in dump:
		if switch:
			devOfVarOne += (float(line) - varOneAverage)**2
		else:
			devOfVarTwo += (float(line) - varTwoAverage)**2
		switch = not switch
varOneDeviation = (devOfVarOne / countVarOne) ** 0.5
varTwoDeviation = (devOfVarTwo / countVarTwo) ** 0.5

print(f"Results of var one standard deviation: {varOneDeviation}")
print(f"Results of var two standard deviation: {varTwoDeviation}")