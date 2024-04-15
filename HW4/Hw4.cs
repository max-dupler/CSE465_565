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

public class Zipcode
{
    public int RecordNumber { get; set; }
    public int ZipcodeValue { get; set; }
    public string ZipCodeType { get; set; }
    public string City { get; set; }
    public string State { get; set; }
    public string LocationType { get; set; }
    public double Latitude { get; set; }
    public double Longitude { get; set; }
    public double XAxis { get; set; }
    public double YAxis { get; set; }
    public double ZAxis { get; set; }
    public string WorldRegion { get; set; }
    public string Country { get; set; }
    public string LocationText { get; set; }
    public string Location { get; set; }
    public bool Decommissioned { get; set; }
    public int TaxReturnsFiled { get; set; }
    public int EstimatedPopulation { get; set; }
    public int TotalWages { get; set; }
    public string Notes { get; set; }

    // Constructor
    public Zipcode(string zipcodeInfo)
    {
        string[] parts = zipcodeInfo.Split('\t'); // Assuming tab-separated values

        // Populate properties from parts array
        RecordNumber = int.Parse(parts[0]);
        ZipcodeValue = int.Parse(parts[1]);
        ZipCodeType = parts[2];
        City = parts[3];
        State = parts[4];
        LocationType = parts[5];
        Latitude = double.Parse(parts[6]);
        Longitude = double.Parse(parts[7]);
        XAxis = double.Parse(parts[8]);
        YAxis = double.Parse(parts[9]);
        ZAxis = double.Parse(parts[10]);
        WorldRegion = parts[11];
        Country = parts[12];
        LocationText = parts[13];
        Location = parts[14];
        Decommissioned = bool.Parse(parts[15]);
        TaxReturnsFiled = int.Parse(parts[16]);
        EstimatedPopulation = int.Parse(parts[17]);
        TotalWages = int.Parse(parts[18]);
        Notes = parts[19];
    }
}


public class Hw4
{
    public static void Main(string[] args)
    {
        // Capture the start time
        // Must be the first line of this method
        DateTime startTime = DateTime.Now; // Do not change
        // ============================
        // Do not add or change anything above, inside the 
        // Main method
        // ============================





        // TODO: your code goes here




        

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
