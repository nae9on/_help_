from jsonparser import JSONParser
from traveladvisory.travel_advisory_parser import TravelAdvisoryParser

url = "https://www.travel-advisory.info/api"

jsonobj = JSONParser(url)

traveobj = TravelAdvisoryParser(jsonobj.data)

class Menu:
    def __init__(self):
        self.choices = {
                "1" : self.show_travel_score,
                "2" : self.show_travel_message,
                "3" : self.quit
                }
    
    def display_menu(self):
        print("""
              1. Trvael score
              2. Travel message
              3. Quit
              """)
        
    def run(self):
        while True:
            self.display_menu()
            choice = input("Enter an option ")
            action = self.choices.get(choice)
            if action:
                Status = action() # call necessary action
                if not Status:
                    break                    
            else:
                print("Invalid choice")
                
    def show_travel_score(self):
        code = input("Enter country code ")
        print(traveobj.get_travel_score(code))
        return True
        
    def show_travel_message(self):
        code = input("Enter country code ")
        print(traveobj.get_travel_message(code))
        return True
        
    def quit(self):
        print("Quit")
        return False
        
if __name__ == "__main__": # False when module is imported
    Menu().run()