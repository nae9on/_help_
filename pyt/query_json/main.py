import requests
import json
import sys

def getdata_from_jsonfile(file = 'data.json'):
    with open(file) as json_file:
        data = json.load(json_file)
    return data

def getdata_from_url(url = "https://www.travel-advisory.info/api"):
    response = requests.get(url)
    return response.json()

def createjsonfile_from_url(url = "https://www.travel-advisory.info/api"):
    data = getdata_from_url(url)
    text = json.dumps(data, sort_keys=True, indent=4)
    return text
    
def getcountryname(jsondict, countrycode):
    alldata = jsondict['data']
    countrydata = alldata[countrycode]
    countryname = countrydata['name']
    return countryname

def main():
    data = getdata_from_jsonfile()
    for itr in range(1, len(sys.argv)):
        countryname = getcountryname(data, sys.argv[itr])
        print(countryname, end = '\n')

if __name__ == "__main__":
    main()
