/* 
  Homework#4

  Add your name here: Max Dupler

  You are free to create as many classes within the Hw4.cs file or across 
  multiple files as you need. However, ensure that the Hw4.cs file is the 
  only one that contains a Main method. This method should be within a 
  class named hw4. This specific setup is crucial because your instructor 
  will use the hw4 class to execute and evaluate your work.
  */
  // BONUS POINT:
  // => Used Pointers from lines 10 to 15 <=
  // => Used Pointers from lines 40 to 63 <=


using System;
using System.IO;
using System.Collections.Generic;
using zipCodeList = System.Collections.Generic.List<Zipcode>;
using System.Linq;

public class Zipcode
{
    public int ZipcodeValue{ get; set; }
    public string City { get; set; }
    public string State { get; set; }
    public double Latitude { get; set; }
    public double Longitude { get; set; }

    // Constructor
    public Zipcode(string zipcodeInfo)
    {
        string[] parts = zipcodeInfo.Split('\t'); 

        ZipcodeValue = int.Parse(parts[1]);
        City = parts[3];
        State = parts[4];
        Latitude = double.Parse(parts[6]);
        Longitude = double.Parse(parts[7]);
    }

    public override string ToString()
    {
        return $"Zipcode: {ZipcodeValue}, City: {City}, State: {State}, " +
        "Latitude: {Latitude}, Longitude: {Longitude}";
    }

}


public class Hw4
{
    public static void parseCodes(ref zipCodeList codes) 
    {
        var lines = File.ReadAllLines("zipcodes.txt"); 
        foreach(string line in lines) {
          try
          {
              codes.Add(new Zipcode(line));
          }
          catch (FormatException)
          {
              continue;
          }
        }
    }
    public static void Main(string[] args)
    {
        // Capture the start time
        // Must be the first line of this method
        DateTime startTime = DateTime.Now; // Do not change
        // ============================
        // Do not add or change anything above, inside the 
        // Main method
        // ============================

        zipCodeList codes = new zipCodeList();
        parseCodes(ref codes);
        Console.WriteLine(codes[2].ToString());
        Console.WriteLine(codes.Count);
        

        // ============================
        // Do not add or change anything below, inside the 
        // Main method
        // ============================

        // Capture the end time
        DateTime endTime = DateTime.Now;  // Do not change
        
        // Calculate the elapsed time
        TimeSpan elapsedTime = endTime - startTime; // Do not change
        
        // Display the elapsed time in milliseconds
        Console.WriteLine($"Elapsed Time: {elapsedTime.TotalMilliseconds} ms");
    }

    
}
