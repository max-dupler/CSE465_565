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

  This code was assisted by ChatGPT, an AI language model developed by OpenAI.
  Specific help from ChatGPT includes:
    * fixing compilation and runtime errors
    * help with list comprehension
    * comment generation
    * improving runtime
"""

# Function to write city states to a file
def city_states(codes):
    city_states_dict = {}
    
    # Initialize city_states_dict with cities from the file
    with open("cities.txt", "r") as file:
        for line in file:
            city = line.strip().lower()  # Convert city to lowercase
            city_states_dict[city] = set()  # Initialize empty set for each city
    
    # Populate city_states_dict with states for each city
    for code in codes:
        city = code.city.lower()  # Convert city to lowercase
        if city in city_states_dict:
            city_states_dict[city].add(code.state)
    
    # Write city states to the output file
    with open("CityStates.txt", "w") as output_stream:
        for city, states in city_states_dict.items():
            output_stream.write(" ".join(sorted(states)) + "\n")



# Function to write latitude and longitude to a file
def lat_lon(codes):
    # Create a dictionary for faster lookup
    codes_dict = {code.code: code for code in codes}
    
    with open("zips.txt", "r") as zip_stream, open("LatLon.txt", "w") as lat_lon_stream:
        for line in zip_stream:
            zip_code = line.strip()
            if zip_code in codes_dict:
                code = codes_dict[zip_code]
                lat_lon_stream.write(f"{code.lat} {code.lon}\n")


# Function to write common city names to a file
def common_cities(codes):
    with open("CommonCityNames.txt", "w") as output_stream:
        for city in get_common_cities(codes):
            output_stream.write(str(city) + "\n")

# Generator function to find common cities
def get_common_cities(codes):
    state_dict = dict()

    # get state names into a dict with each state name declared as a key
    # each key has a set that will be populated with city names
    with open("states.txt", "r") as state_input:
        state_dict.update({line.strip(): set() for line in state_input})
    
    # add all city names from a state into its set in the dictionary
    for code in codes:
        state_dict[code.state].add(code.city) if code.state in state_dict else None
    
    # get a list of values from each state
    cities = list(state_dict.values())

    # filter to find common cities
    common_cities = sorted(list(filter(lambda x : x in cities[0], cities[1])))
    
    for city in common_cities:
        yield city

# Function to create a Zipcode object from a line of text
def create_zip_code(line):
    toks = line.strip().split('\t')
    try:
        code = ZC(toks[1], toks[3], toks[4], toks[6], toks[7])
        return code
    except Exception:
        return None

def parse_codes():
    with open("zipcodes.txt", "r") as input_stream:
        yield from (create_zip_code(line) for line in input_stream)

# Main block of code
if __name__ == "__main__": 
    start_time = time.perf_counter()  # Start measuring program runtime

    codes = list(parse_codes())
    city_states(codes)
    lat_lon(codes)
    common_cities(codes)

    end_time = time.perf_counter()  # Stop measuring program runtime
    # Calculate the runtime in milliseconds
    runtime_ms = (end_time - start_time) * 1000
    print(f"The runtime of the program is {runtime_ms} milliseconds.")  # Print program runtime


    

