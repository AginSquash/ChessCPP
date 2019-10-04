import os, sys
import shutil

### http://it.nittis.ru/python-recursive-copy.html
def copytree(src, dst, symlinks=0):
  print ("copy tree " + src)
  names = os.listdir(src)
  if not os.path.exists(dst):
    os.mkdir(dst)
  for name in names:
    srcname = os.path.join(src, name)
    dstname = os.path.join(dst, name)
    try:
      if symlinks and os.path.islink(srcname):
        linkto = os.readlink(srcname)
        os.symlink(linkto, dstname)
      elif os.path.isdir(srcname):
        copytree(srcname, dstname, symlinks)
      else:
        shutil.copy2(srcname, dstname)
    except (IOError, os.error):
      print ("Can't copy %s to %s: %s", srcname, dstname, str(IOError))

appName = "ChessCPP"

login = os.getlogin()

data_path = "/Users/" + login + "/." + appName + "/"

copytree( "resources/", data_path + "resources/")

print("All data succefull instaled into " + data_path + "\nNow you can run ChessCPP (just double-click on it).")