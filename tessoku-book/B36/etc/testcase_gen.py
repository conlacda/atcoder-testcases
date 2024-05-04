import random
from typing import Tuple


def generate_one() -> Tuple[str, str]:
    n = random.randint(200000, 300000)
    k = random.randint(0, n)
    s = []
    for i in range(n):
        s.append(str(random.randint(0, 1)))
    cnt = s.count('1')
    ans = "Yes" if cnt % 2 == k % 2 else "No"
    print(f'{n} {k} {cnt} {ans}')
    return f"{n} {k}\n{''.join(s)}\n", ans + "\n"


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
