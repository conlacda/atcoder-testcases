import random
from collections import Counter
from typing import List

N_MAX = 1000
A_MAX = 100


def solve(n: int, a: List[int]):
    counter = Counter(map(lambda k: k % 100, a))
    ans = 0
    for i in range(1, 50):
        ans += counter.get(i, 0) * counter.get(100 - i, 0)
    ans += counter.get(50, 0) * (counter.get(50, 0) - 1) // 2
    ans += counter.get(0, 0) * (counter.get(0, 0) - 1) // 2
    return ans


def generate_one() -> tuple[str, str]:
    n = random.randint(N_MAX * 9 // 10, N_MAX)
    a = [random.randint(1, A_MAX) for _ in range(n)]
    # a = [50]
    # for i in range(1, 50):
    #     a.append(i)
    #     a.append(i)
    # random.shuffle(a)
    # n = len(a)
    return f"{n}\n{' '.join(map(str, a))}\n", f'{solve(n, a)}\n'


def main():
    for i in range(1, 14):
        in_case, out_case = generate_one()
        case_num = ('0' + str(i))[-2:]
        case_name = f"rand_{case_num}.txt"
        with open('in/' + case_name, 'w') as f:
            f.write(in_case)
        with open('out/' + case_name, 'w') as f:
            f.write(out_case)


if __name__ == '__main__':
    main()
