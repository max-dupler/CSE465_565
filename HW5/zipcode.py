class Location:
    def __init__(self, **args):
        self.city = args.get("city")
        self.state = args.get("state")
        self.lat = args.get("lat")
        self.lon = args.get("lon")

class Zipcode(Location):
    def __init__(self, code, city, state, lat, lon):
        super().__init__(city = city, state = state, lat = lat, lon = lon)
        self.code = code

    def __eq__(self, other):
        if isinstance(other, Zipcode):
            return self.code == other.code
        return False
    
    def __str__(self):
        return f"Zipcode: {self.code}, City: {self.city}, State: {self.state}"

    