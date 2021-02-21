import sys

from jsonparser.json_parser import JSONParser
from traveladvisory.travel_advisory_parser import TravelAdvisoryParser

def main():
    url = "https://www.travel-advisory.info/api"
    jsonobj = JSONParser(url)
    traveobj = TravelAdvisoryParser(jsonobj.data)
    for itr in range(1, len(sys.argv)):
        country_name = traveobj.get_country_name(sys.argv[itr])
        print(country_name, end = '\n')

if __name__ == "__main__":
    main()
