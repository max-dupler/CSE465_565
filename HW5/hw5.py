import time 
import threading
from zipcode import Zipcode as ZC 

"""
  Homework#5

  Add your name here: Max Dupler

  You are free to create as many classes within the hw5.py file or across 
  multiple files as you need. However, ensure that the hw5.py file is the 
  only one that contains a __main__ method. This specific setup is crucial 
  because your instructor will run the hw5.py file to execute and evaluate 
  your work.

  This code was assisted by ChatGPT, an AI language model developed by OpenAI.
  Specific help from ChatGPT includes:
    * fixing compilation and runtime errors
    * help with list comprehension
    * comment generation
    * improving runtime
"""

# Function to write city states to a file
def city_states(codes):
    cities = list()
    with open("cities.txt", "r") as file:
        for line in file:
            cities.append(line.strip())
    
    with open("CityStates.txt", "w") as outputStream:
        for city in cities:
            states = sorted(set(code.state for code in codes if code.city.lower() == city.lower()))
            outputStream.write(" ".join(states) + "\n")

# Function to write latitude and longitude to a file
def lat_lon(codes):
    zips = list()
    with open("zips.txt", "r") as zipStream:
        for line in zipStream:
            zips.append(line.strip())
    
    with open("LatLon.txt", "w") as latLonStream:
        for zip in zips:
            code = list((filter(lambda x : x.code == zip, codes)))
            latLonStream.write(f"{code[0].lat} {code[0].lon}\n")

# Function to write common city names to a file
def common_cities(codes):
    with open("CommonCityNames.txt", "w") as outputStream:
        for city in get_common_cities(codes):
            outputStream.write(str(city) + "\n")

# Generator function to find common cities
def get_common_cities(codes):
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

# Function to create a Zipcode object from a line of text
def create_zip_code(line):
    toks = line.strip().split('\t')
    try:
        code = ZC(toks[1], toks[3], toks[4], toks[6], toks[7])
        return code
    except Exception:
        return None

# Function to parse codes from a file
def parse_codes():
    inputStream = open("zipcodes.txt", "r")
    return list(map(create_zip_code, inputStream))

# Main block of code
if __name__ == "__main__": 
    start_time = time.perf_counter()  # Start measuring program runtime
    
    codesLst = parse_codes()

    # create threads for each different operation

    common_cities(codesLst)
    lat_lon(codesLst)
    city_states(codesLst)

    end_time = time.perf_counter()  # Stop measuring program runtime
    # Calculate the runtime in milliseconds
    runtime_ms = (end_time - start_time) * 1000
    print(f"The runtime of the program is {runtime_ms} milliseconds.")  # Print program runtime


    

