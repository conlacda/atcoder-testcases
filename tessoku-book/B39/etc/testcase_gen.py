import heapq
import random

N_MAX_SUBTASK1 = 2000
N_MAX = 200000
Y_MAX = 10 ** 6


def solve(n: int, d: int, xy: list[tuple[int, int]]):
    h = []
    ls = [[] for _ in range(d)]

    for x, y in xy:
        ls[x - 1].append(y)

    ans = 0
    for i in range(d):
        for k in ls[i]:
            heapq.heappush(h, -k)
        if len(h) == 0:
            continue
        ans -= heapq.heappop(h)

    return ans


def generate_one() -> tuple[str, str]:
    n = random.randint(N_MAX_SUBTASK1+1, N_MAX)
    d = random.randint(300, 365)
    case = [f'{n} {d}']
    xy = []
    for i in range(n):
        x = random.randint(1, d)
        y = random.randint(1, Y_MAX)
        case.append(f'{x} {y}')
        xy.append((x, y))
    case.append('')

    return '\n'.join(case), f'{solve(n, d, xy)}\n'


def main():
    for i in range(1, 7):
        in_case, out_case = generate_one()
        case_num = ('0' + str(i))[-2:]
        case_name = f"rand_{case_num}.txt"
        with open('in/' + case_name, 'w') as f:
            f.write(in_case)
        with open('out/' + case_name, 'w') as f:
            f.write(out_case)


if __name__ == '__main__':
    main()
