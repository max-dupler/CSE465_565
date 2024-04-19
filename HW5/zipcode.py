class Location:
    def __init__(self, city, state, lat, lon):
        self.city = city
        self.state = state
        self.lat = lat
        self.lon = lon

class Zipcode(Location):
    def __init__(self, code, city, state, lat, lon):
        super().__init__(city, state, lat, lon)
        self.code = code

    