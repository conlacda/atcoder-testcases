import sys
import os
from typing import List

# python genenrate-list.py contest_name
contest = sys.argv[1]

problems: List[str] = [p for p in os.listdir(f"./{contest}")]

# Rename file
for problem in problems:
    # input directory
    for path, subdirs, fileNames in os.walk(f"./{contest}/{problem}/in"):
        for fileName in fileNames:
            fileNameWithoutExtension = fileName.split('.')[0]
            # sometimes we have 2 files with same prefix but different extension
            if not os.path.exists(f"{path}/{fileNameWithoutExtension}"):
                os.rename(f"{path}/{fileName}", f"{path}/{fileNameWithoutExtension}")

    # output directory
    for path, subdirs, fileNames in os.walk(f"./{contest}/{problem}/out"):
        for fileName in fileNames:
            fileNameWithoutExtension = fileName.split('.')[0]
            # sometimes we have 2 files with same prefix but different extension
            if not os.path.exists(f"{path}/{fileNameWithoutExtension}"):
                os.rename(f"{path}/{fileName}", f"{path}/{fileNameWithoutExtension}")

# Generate list.txt file
for problem in problems:
    # if (os.path.exists(f"./{folder}/{problem}/list.txt")):
    #     os.remove(f"./{folder}/{problem}/list.txt")
    if not os.path.exists(f"./{contest}/{problem}/list.txt"):
        for path, subdirs, inFiles in os.walk(f"./{contest}/{problem}/in"):
            f = open(f"./{contest}/{problem}/list.txt", "a+")
            for inFile in sorted(inFiles):
                outFile = inFile
                if (inFile.endswith('.in')):
                    outFile = inFile[:-2] + "out"
                
                # missing output files will raise an error (check abc350.C on dropbox)
                # create if not exists
                if not os.path.exists(f"./{contest}/{problem}/out/{outFile}"):
                    with open(f"./{contest}/{problem}/out/{outFile}", 'w') as outf:
                        outf.write("Sorry, this output file is not provided.")

                # file_name,input_file_size_in_bytes,output_file_size_in_bytes
                inputSz = os.path.getsize(f"./{contest}/{problem}/in/{inFile}")
                outputSz = os.path.getsize(f"./{contest}/{problem}/out/{outFile}")
                commonName = inFile.split(".")[0]
                f.write(f"{commonName},{inputSz},{outputSz}\n")
            f.close()
