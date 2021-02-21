import requests
import json

class JSONParser:
    
    def __init__(self, url_or_file):
        self._url = None
        self._file = None
        self.data = None
        self.configure(url_or_file)
        
    def configure(self, url_or_file):
        if url_or_file.startswith("https://"):
            self._url = url_or_file
            self._get_data_from_url()
        elif url_or_file.endswith(".json"):
            self._file = url_or_file
            self._get_data_from_jsonfile()
        
    def _get_data_from_url(self):
        response = requests.get(self._url)
        self.data = response.json()
        
    def _get_data_from_jsonfile(self):
        with open(self._file) as json_file:
            self.data = json.load(json_file)
            
    def write_json_file(self, path):
        text = json.dumps(self.data, sort_keys=True, indent=4)
        with open(path, "w") as text_file:
            text_file.write(text)