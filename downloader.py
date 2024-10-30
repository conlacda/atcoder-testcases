import shutil
import subprocess
from typing import List
from requests import get
import json
import os
from tqdm import tqdm
import random


def download(url, fileName):
    with open(fileName, "wb+") as file:
        response = get(url)
        file.write(response.content)


def get_git_branches():
    # Dont use git branch -a because it will get list of branches on local. git ls-remote origin will fetch from the original source from the internet.
    result = subprocess.run(['git', 'ls-remote', 'origin'], capture_output=True, text=True)
    branches = []
    for line in result.stdout.splitlines():
        if 'refs/heads' in line:
            branch_name = line.strip().split('\t')[-1].replace('refs/heads/', '').replace('"', '')
            branches.append(branch_name)
    
    return branches

def delete_remove_branch(branch_name: str):
    subprocess.run(['git', 'push', 'origin', '–d', branch_name])


with open("./crawler/dump.json") as f:
    data: dict[str, str] = json.load(f)
    # Dont use git branch -a because it will get list of branches on local. git ls-remote origin will fetch from the original source from the internet.
    branches = get_git_branches()

    # Remove some random branches to prevent incomplete data (it should be newest branches but can not get remote branches list then sort them by created date)
    NUMBER_OF_REMOVED_BRANCHES = 3
    for i in range(3):
        abrgcBranches = list(filter(lambda branch: branch.startswith('abc') or branch.startswith('arc') or branch.startswith('agc'), branches))
        randomBranch = random.choice(abrgcBranches)
        delete_remove_branch(randomBranch)
        branches.remove(randomBranch)
    
    # Download missing testcases
    for contest in tqdm(data.keys()):
        if contest in branches:
            continue

        # dl=0 -> dl=1
        url = data[contest][:-1] + "1"
        print(f"Downloading {contest} from {url}")
        download(url, f"{contest}.zip")
        shutil.unpack_archive(f"{contest}.zip", f"{contest}/")
        os.remove(f"{contest}.zip")
        subprocess.run(["python", "generate-list.py", contest])
        subprocess.run(["git", "checkout", "-b", contest])
        subprocess.run(["git", "add", "."])
        subprocess.run(["git", "commit", "-m", f"add {contest}"])
        subprocess.run(["git", "push", "origin", contest])
        subprocess.run(["git", "checkout", "main"])
