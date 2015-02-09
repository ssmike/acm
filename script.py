#!/usr/bin/python3
import os
import sys
import shutil
if len(sys.argv) != 3:
    print("usage: <path> <letter>")
    exit()
path = sys.argv[1]
letter = sys.argv[2]
for tmp in range(0, ord(letter[0]) - ord('A') + 1):
    dirLet = chr(tmp + ord('A'))
    dir = os.path.join(path, dirLet)
    if not os.path.exists(dir):
      os.makedirs(dir)
    codeLet = chr(tmp + ord('a'))
    codePath = dir + '/' + codeLet + ".cpp"
    if not os.path.exists(codePath):
      open(codePath, 'a').close()
      shutil.copy("template.cpp", codePath)
      open(dir + "/inp", 'a')
      open(dir + "/outp", 'a')
