import requests
import json

response = requests.get("https://www.travel-advisory.info/api")
text = json.dumps(response.json(), sort_keys=True, indent=4)
pythondict = json.loads(text)
print(list(pythondict.keys()))
mydata = pythondict['data']
#print(mydata)
print(list(mydata.keys()))
ad_data = mydata['AD']
print(list(ad_data.keys()))
ad_data['name']
