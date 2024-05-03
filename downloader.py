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
    branches = os.listdir(".git/refs/heads")
    print(branches)
    # for contest in tqdm(data.keys()):
    #     if contest in branches:
    #         continue

    #     # dl=0 -> dl=1
    #     url = data[contest][:-1] + "1"
    #     print(f"Downloading {contest} from {url}")
    #     subprocess.run(["git", "checkout", "-b", contest])
    #     download(url, f"{contest}.zip")
    #     shutil.unpack_archive(f"{contest}.zip", f"{contest}/")
    #     os.remove(f"{contest}.zip")
    #     subprocess.run(["python", "generate-list.py", contest])
    #     subprocess.run(["git", "add", "."])
    #     subprocess.run(["git", "commit", "-m", f"add {contest}"])
    #     subprocess.run(["git", "push", "origin", contest])
    #     subprocess.run(["git", "checkout", "main"])
