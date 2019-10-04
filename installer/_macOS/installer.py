import os
import shutil

appName = "ChessCPP"

login = os.getlogin()
print(login)
data_path = "/Users/" + login + "/.projects/" + appName + "/resources"
shutil.copytree( "resources/", data_path)

print("All data succefull instaled into " + data_path + "\nNow you can run ChessCPP (just double-click on it).")