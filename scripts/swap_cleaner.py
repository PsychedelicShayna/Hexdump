import os, time, sys, json, threading
import pythoncom
import pyttsx3 as ptts

arguments = sys.argv

speech_queries:list = []

def speech_job():
    global speech_queries
    pythoncom.CoInitialize()

    tts = ptts.init()
            
    while True:
        while len(speech_queries) > 0:
            if(len(speech_queries) > 1):
                tts.say("Deleted %s swaps" % str(len(speech_queries)))
                speech_queries.clear()
            else:
                tts.say(speech_queries.pop(-1))
            
            tts.setProperty("rate", 200)
            tts.runAndWait()
            
        time.sleep(1)        

target_folders:list = [
    "\\..\\source",
    "\\..\\source\\headers",
    "\\..\\scripts",
    "\\..\\source\\deprecated",
    "\\.."
]

def get_folders():
    folders:list = []
    with open("folders.json", "r") as io:
        folders = json.loads(io.read())
        io.close()

    return folders

def deleteCaches(folders:list):
    baseDir = os.path.dirname(__file__)
    
    for folder in folders:
        fullpaths = [baseDir+folder+"\\"+file for file in os.listdir(baseDir+folder)]
        fullpaths = [file for file in fullpaths if os.path.isfile(file)]
        fullpaths = [file for file in fullpaths if file.endswith("~")]
       
        for file in fullpaths:
            os.remove(file)
            
            print("Deleted swap: " + file)
            speech_queries.append("Deleted swap: " + os.path.basename(file))
            
speech_worker = threading.Thread(target=speech_job, daemon=True)
speech_worker.start()

if "-loop" in arguments:
    while True:
        try: deleteCaches(get_folders())
        except Exception as exception:
            print("Failed to delete caches")
            print("Exception: " + str(exception))
        
        time.sleep(1)
else:
    try: deleteCaches(get_folders())
    except Exception as exception: 
        print("Failed to delete caches")
        print("Exception: " + str(exception))