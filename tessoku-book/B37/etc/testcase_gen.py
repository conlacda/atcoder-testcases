import random
from typing import Tuple

N_MAX = 10 ** 15

# K >= 2N - 2


def solve(x: int) -> int:
    s = str(x)
    n = len(s)

    ans = 0

    for i in reversed(range(n)):
        p = 10 ** (n - i - 1)
        k = int(s[i])
        for j in range(1, k):
            ans += (int('0' + s[:i]) + 1) * j * p

        ans += int('0' + s[:i]) * k * p
        ans += (int('0' + s[(i + 1):]) + 1) * k

        for j in range(k + 1, 10):
            ans += int('0' + s[:i]) * j * p

    return ans


def generate_one() -> Tuple[str, str]:
    n = random.randint(1, N_MAX)
    return f'{n}\n', f'{solve(n)}\n'


def main():
    for i in range(1, 6):
        in_case, out_case = generate_one()
        case_num = ('0' + str(i))[-2:]
        case_name = f"rand_{case_num}.txt"
        with open('in/' + case_name, 'w') as f:
            f.write(in_case)
        with open('out/' + case_name, 'w') as f:
            f.write(out_case)


if __name__ == '__main__':
    main()
