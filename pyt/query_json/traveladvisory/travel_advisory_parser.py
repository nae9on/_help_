class TravelAdvisory:
    def __init__(self, Advisory):
        self.score = Advisory['score']
        self.message = Advisory['message']
            
class TravelAdvisoryParser:
    
    def __init__(self, data):
        self.data = data
    
    def get_country_data(self, country_code):
        all_data = self.data['data']
        country_data = all_data[country_code]
        return country_data
    
    def get_country_name(self, country_code):
        country_data = self.get_country_data(country_code)
        countryname = country_data['name']
        return countryname
    
    def get_travel_advisory(self, country_code):
        country_data = self.get_country_data(country_code)
        country_travel_advisory = country_data['advisory']
        return TravelAdvisory(country_travel_advisory)
    
    def get_travel_score(self, country_code):
        country_travel_advisory = self.get_travel_advisory(country_code)
        return country_travel_advisory.score
    
    def get_travel_message(self, country_code):
        country_travel_advisory = self.get_travel_advisory(country_code)
        return country_travel_advisory.message
        
      
            
            