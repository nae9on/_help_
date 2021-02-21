class TravelAdvisory:
    def __init__(self, Advisory):
        self.score = Advisory['score']
        self.message = Advisory['message']
            
class TravelAdvisoryParser:
    
    def __init__(self, api_data):
        self.data = api_data['data']
        self.name_id_map = {self.data[key]['name']:key for key in self.data.keys()}
    
    def get_country_data(self, country_code_or_name):
        if len(country_code_or_name) == 2:
            country_code = country_code_or_name
        else:
            country_code = self.name_id_map[country_code_or_name]
        country_data = self.data[country_code]
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
        
      
            
            