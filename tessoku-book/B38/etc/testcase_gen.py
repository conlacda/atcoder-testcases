import random
from typing import Tuple

N_MAX = 3000

# K >= 2N - 2

def solve(n: int, s: str) -> int:
    ans = [1] * n
    b_start = -1
    for i in range(n-1):
        if s[i] == 'A':
            if b_start != -1:
                ans[b_start] = i - b_start + 1
                for j in range(b_start+1, i+1):
                    ans[j] = ans[j-1] - 1
                if b_start != 0 and ans[b_start-1] >= ans[b_start]:
                    ans[b_start] = ans[b_start-1]+1
                b_start = -1
            ans[i + 1] = ans[i] + 1
        elif b_start == -1:
            b_start = i

    if b_start != -1:
        ans[b_start] = n - b_start
        for j in range(b_start + 1, n):
            ans[j] = ans[j - 1] - 1
        if b_start != 0 and ans[b_start-1] >= ans[b_start]:
            ans[b_start] = ans[b_start-1]+1
    return sum(ans)


def generate_one() -> Tuple[str, str]:
    n = random.randint(1, 3000)
    s = []
    for i in range(n-1):
        s.append('A' if random.randint(1, 2) == 1 else 'B')
    s = ''.join(s)
    return f"{n}\n{s}\n", f'{solve(n, s)}'


def main():
    for i in range(1, 16):
        in_case, out_case = generate_one()
        case_num = ('0' + str(i))[-2:]
        case_name = f"rand_{case_num}.txt"
        with open('in/' + case_name, 'w') as f:
            f.write(in_case)
        with open('out/' + case_name, 'w') as f:
            f.write(out_case)


if __name__ == '__main__':
    main()
