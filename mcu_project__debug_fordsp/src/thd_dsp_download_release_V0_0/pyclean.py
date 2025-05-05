#encoding=utf8
import sys,os
import shutil
import platform
from os import listdir
def cleanSrc(plat, dir, typeName):
    for root, dirs, files in os.walk(dir):
        for file_name in files:
            if file_name.endswith(typeName):
                os.remove(os.path.join(root, file_name))
plat = platform.system().lower()
if plat == 'windows':
    print('windows system')
elif plat == 'linux':
    print('linux system')
scriptPath = os.getcwd()
rootPath = os.path.dirname(scriptPath)
cleanSrc(plat, rootPath, '.o')
if len(sys.argv) > 1:
    cleanSrc(plat, scriptPath, '.map')
    print('clean finish')
