import os
import string
import sys

def main():
    if(len(sys.argv) != 2):
        print("usage: python3 .\stripper.py path_to_file")
        return
    fileName = sys.argv[1]

    savedFileName = os.path.splitext(fileName)[0]+"_stripped.txt"
    data = []
    with open(fileName, "r") as f:
        data = f.read().splitlines()
    f.close()

    with open(savedFileName, "w") as s:
        for d in data:
            if(d[0] in string.digits):
                s.write(d+"\n")
    s.close()




main()