# Define the Location class
class Location:
    def __init__(self, **args):
        # Initialize attributes based on keyword arguments
        self.city = args.get("city")
        self.state = args.get("state")
        self.lat = args.get("lat")
        self.lon = args.get("lon") 

# Define the Zipcode class, inheriting from Location
class Zipcode(Location):
    def __init__(self, code, city, state, lat, lon):
        # Call the superclass constructor with specified keyword arguments
        super().__init__(city=city, state=state, lat=lat, lon=lon)
        self.code = code

    # Override the equality operator
    def __eq__(self, other):
        # Check if the other object is an instance of Zipcode class
        if isinstance(other, Zipcode):
            # Compare the code attribute for equality
            return self.code == other.code
        return False  # Return False if other object is not a Zipcode instance
    
    # Override the string representation method
    def __str__(self):
        return f"Zipcode: {self.code}, City: {self.city}, State: {self.state}"
