'''
Requirements:
Use of Object-Oriented Programming :
○ Lambda. This must be a part of your solution. 
○ Filter. This must be a part of your solution.
○ Proper use of Data Structures from python library. This must be a part of your solution.
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
    print(len(codesLst))
    print(codesLst[1])

    # code = ZC(12345, "Oxford", "OH", 1.4567, 4.5667)
    # code2 = ZC(12345, "Oxford", "OH", 1.4567, 4.5667)
    # code3 = ZC(12390, "Oxford", "OH", 1.4567, 4.5667)
    # print(code)
    # print(code == code2)
    # print(code == code3)


    '''
    Inside the __main__, do not add any codes after this line.
    ----------------------------------------------------------
    '''
    end_time = time.perf_counter()
    # Calculate the runtime in milliseconds
    runtime_ms = (end_time - start_time) * 1000
    print(f"The runtime of the program is {runtime_ms} milliseconds.")  
    

