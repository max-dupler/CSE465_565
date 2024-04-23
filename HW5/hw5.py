'''
○ Use of Object-Oriented Programming :
i. Design a logical and practical hierarchy of classes with at least one superclass
and a subclass. This must be a part of your solution.
ii. Override an operator, which could be either a logical operator, or a
mathematical operator. This does not have to be a part of your solution.
iii. Override a method. This does not have to be a part of your solution.
○ Lambda. This must be a part of your solution. 
○ Map. This must be a part of your solution.
○ Filter. This must be a part of your solution.
○ List Comprehension. This must be a part of your solution.
○ Proper use of Data Structures from python library. This must be a part of your solution.
○ Variable Positional Argument. This must be a part of your solution.
○ Yield. Does not have to be a part of your solution.
'''
import time
from zipcode import Zipcode as ZC

"""
  Homework#5

  Add your name here: Max Dupler

  You are free to create as many classes within the hw5.py file or across 
  multiple files as you need. However, ensure that the hw5.py file is the 
  only one that contains a __main__ method. This specific setup is crucial 
  because your instructor will run the hw5.py file to execute and evaluate 
  your work.
"""

def latLon(codes):
    zips = list()
    with open("zips.txt", "r") as zipStream:
        for line in zipStream:
            zips.append(line.strip())
    
    with open("LatLon.txt", "w") as latLonStream:
        for zip in zips:
            code = list((filter(lambda x : x.code == zip, codes)))
            latLonStream.write(f"{code[0].lat} {code[0].lon}\n")

def commonCities(codes):
    with open("CommonCityNames.txt", "w") as outputStream:
        for city in getCommonCities(codes):
            outputStream.write(str(city) + "\n")


def getCommonCities(codes):
    stateDict = dict()
    # get state names into a dict with each state name declared as a key
    # each key has a set that will be populated with city names
    with open("states.txt", "r") as stateInput:
        stateDict.update({line.strip(): set() for line in stateInput})
    
    # add all city names from a state into its set in the dictionary
    for code in codes:
        stateDict[code.state].add(code.city) if code.state in stateDict else None
    
    # get a list of values from each state
    cities = list(stateDict.values())
    # filter to find common cities
    commonCities = sorted(list(filter(lambda x : x in cities[0], cities[1])))
    
    for city in commonCities:
        yield city
    
def createZipCode(line):
    toks = line.strip().split('\t')
    try:
        code = ZC(toks[1], toks[3], toks[4], toks[6], toks[7])
        return code
    except Exception:
        return None

def parseCodes():
    inputStream = open("zipcodes.txt", "r")
    return list(map(createZipCode, inputStream))


if __name__ == "__main__": 
    start_time = time.perf_counter()  # Do not remove this line
    '''
    Inisde the __main__, do not add any codes before this line.
    -----------------------------------------------------------
    '''

    codesLst = parseCodes()
    commonCities(codesLst)
    latLon(codesLst)

    '''
    Inside the __main__, do not add any codes after this line.
    ----------------------------------------------------------
    '''
    end_time = time.perf_counter()
    # Calculate the runtime in milliseconds
    runtime_ms = (end_time - start_time) * 1000
    print(f"The runtime of the program is {runtime_ms} milliseconds.")  
    

