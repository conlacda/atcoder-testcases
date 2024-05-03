import shutil
import subprocess
from typing import List
from requests import get
import json
import os
from tqdm import tqdm


def download(url, fileName):
    with open(fileName, "wb+") as file:
        response = get(url)
        file.write(response.content)


with open("./crawler/dump.json") as f:
    data: dict[str, str] = json.load(f)
    output = subprocess.run(["git", "ls-remote", "origin"], capture_output = True)
    print(output.stdout)
    # output = subprocess.run(["git", "branch", "-a"], capture_output = True)
    # branches = str(output.stdout)
    # for contest in tqdm(data.keys()):
    #     if contest in branches:
    #         continue

    #     # dl=0 -> dl=1
    #     url = data[contest][:-1] + "1"
    #     print(f"Downloading {contest} from {url}")
    #     download(url, f"{contest}.zip")
    #     shutil.unpack_archive(f"{contest}.zip", f"{contest}/")
    #     os.remove(f"{contest}.zip")
    #     subprocess.run(["python", "generate-list.py", contest])
    #     subprocess.run(["git", "checkout", "-b", contest])
    #     subprocess.run(["git", "add", "."])
    #     subprocess.run(["git", "commit", "-m", f"add {contest}"])
    #     subprocess.run(["git", "push", "origin", contest])
    #     subprocess.run(["git", "checkout", "main"])
