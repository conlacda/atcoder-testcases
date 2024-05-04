#include <bits/extc++.h>

namespace pokagen {
    class splitmix64 {
        unsigned long x;
    public:
        using result_type = unsigned long;

        [[nodiscard]] static constexpr unsigned long max() {
            return std::numeric_limits<unsigned long>::max();
        }

        [[nodiscard]] static constexpr unsigned long min() {
            return std::numeric_limits<unsigned long>::min();
        }

        constexpr explicit splitmix64(unsigned long seed = 0) : x(seed) {}

        unsigned long operator()() {
            unsigned long z{x += 11400714819323198485UL};
            z = (z ^ (z >> 30UL)) * 13787848793156543929UL;
            z = (z ^ (z >> 27UL)) * 10723151780598845931UL;
            return z ^ (z >> 31UL);
        }
    };

    class xoshiro256ss {
        unsigned long state[4];
    public:
        using result_type = unsigned long;

        [[nodiscard]] static constexpr unsigned long max() {
            return std::numeric_limits<unsigned long>::max();
        }

        [[nodiscard]] static constexpr unsigned long min() {
            return std::numeric_limits<unsigned long>::min();
        }

        constexpr explicit xoshiro256ss(unsigned long seed = 0) : state() {
            splitmix64 sp{seed};
            for (auto &&i : state)i = sp();
        }

        constexpr xoshiro256ss(unsigned long seed0, unsigned long seed1, unsigned long seed2, unsigned long seed3)
                : state{
                seed0, seed1, seed2, seed3} {}

        [[nodiscard]] static constexpr unsigned long rotl(const unsigned long X, const unsigned long width) {
            return (X << width) ^ (X >> (64 - width));
        }

        unsigned long operator()() {
            const unsigned long result{rotl(state[1] * 5, 7) * 9};
            const unsigned long tmp{state[1] << 17UL};
            state[2] ^= state[0];
            state[3] ^= state[1];
            state[1] ^= state[2];
            state[0] ^= state[3];
            state[2] ^= tmp;
            state[3] = rotl(state[3], 45);
            return result;
        }
    };

    template<typename T>
    class uniform_int_distribution {
    public:
        using result_type = T;
        using param_type = std::pair<T, T>;
    private:
        result_type lower_bound, upper_bound;
    public:
        explicit uniform_int_distribution(T a = 0, T b = std::numeric_limits<T>::max()) : lower_bound(a),
                                                                                          upper_bound(b) {}

        template<typename RNG>
        result_type operator()(RNG &&rng) {
            using RT = typename std::remove_reference<RNG>::type;
            const auto diff{upper_bound - lower_bound + 1};
            static_assert(RT::min() == 0);
            assert(RT::max() >= diff);
            if (diff == 0 && RT::max() == upper_bound)return rng();
            const auto diff_t{static_cast<typename RT::result_type>(upper_bound) - lower_bound + 1};
            const auto scale{RT::max() / diff_t}, lim{diff_t * scale};
            auto ret{rng()};
            while (ret >= lim)ret = rng();
            return ret / scale + lower_bound;
        }

        template<typename RNG>
        result_type operator()(RNG &&rng, const param_type &prm) {
            using RT = typename std::remove_reference<RNG>::type;
            const auto[a, b]{prm};
            const auto diff{b - a + 1};
            static_assert(RT::min() == 0);
            assert(RT::max() >= diff);
            if (diff == 0 && RT::max() == b)return rng();
            const auto diff_t{static_cast<typename RT::result_type>(b) - a + 1};
            const auto scale{RT::max() / diff_t}, lim{diff_t * scale};
            auto ret{rng()};
            while (ret >= lim)ret = rng();
            return ret / scale + a;
        }
    };

    template<typename Function, typename RNG, typename Container, typename Container2>
    void generate_related_seq(Function &&f, RNG &&rng, const Container &from, Container2 &&to) {
        std::transform(std::cbegin(from), std::cend(from), std::begin(to),
                       [&f, &rng](const auto &x) { return f(rng, x); });
    }

    template<class RandomAccessIterator, class UniformRandomBitGenerator>
    void shuffle(RandomAccessIterator first, RandomAccessIterator last, UniformRandomBitGenerator &&g) {
        if (first == last) return;

        using distance_type = typename std::iterator_traits<RandomAccessIterator>::difference_type;
        using unsigned_type = typename std::make_unsigned<distance_type>::type;
        using distribute_type = typename pokagen::uniform_int_distribution<unsigned_type>;
        using param_type = typename distribute_type::param_type;

        distribute_type d;
        for (auto it = first + 1; it != last; ++it)
            std::iter_swap(it, first + d(g, param_type(0, it - first)));
    }
}

class testcase {
public:
    std::string name;
    unsigned long N, T;
    std::vector<std::pair<unsigned long, unsigned long>> edges;

    template<class NGen, class TGen, class EdgeGen, class RNG>
    testcase(std::string &&_name, NGen &&N_generator, TGen &&T_generator, EdgeGen &&edge_generator, RNG &&rng) : name(
            _name), N(), T(), edges() {
        N = N_generator(rng);
        T = T_generator(rng, N);
        edges = edge_generator(rng, N, T);
    }

    testcase(std::string &&_name,
             std::pair<unsigned long, std::vector<std::pair<unsigned long, unsigned long>>> &&_t_edges)
            : name(_name), N(_t_edges.second.size() + 1), T(_t_edges.first), edges(_t_edges.second) {}

    [[nodiscard]] std::string to_string() const {
        using std::endl;
        std::stringstream cout;
        cout << N << " " << T << endl;
        for (const auto[A, B] : edges)cout << A << " " << B << endl;
        return cout.str();
    }

    [[nodiscard]] std::string head(unsigned long lines = 5) const {
        using std::endl;
        std::stringstream cout;
        cout << N << " " << T << endl;
        unsigned long cnt{};
        for (const auto[A, B] : edges) {
            cout << A << " " << B << endl;
            ++cnt;
            if (cnt >= lines)break;
        }
        return cout.str();
    }
};

class constraint_condition {
public:
    virtual bool operator()(const testcase &) const = 0;
};

template<class Condition>
class free_condition : public constraint_condition {
    Condition cond;
    std::string name;
public:
    free_condition(Condition &&_c, std::string &&_name) : cond(_c), name(_name) {}

    bool operator()(const testcase &test) const override {
        if (!cond(test)) {
            std::cerr << "constraint violation : " << name << std::endl;
            return false;
        }
        return true;
    }
};

template<class Condition>
std::unique_ptr<free_condition<Condition>> make_free_condition(Condition &&_c, std::string &&_name) {
    return std::make_unique<free_condition<Condition>>(std::forward<Condition>(_c), std::forward<std::string>(_name));
}

template<class Getter, class T>
class inequation_condition : public constraint_condition {
    Getter getter;
    std::string name;
    T lower, upper;
public:
    inequation_condition(Getter &&_g, std::string &&_name, T &&_lower, T &&_upper) : getter(_g), name(_name),
                                                                                     lower(_lower), upper(_upper) {}

    bool operator()(const testcase &test) const override {
        const T value{getter(test)};
        if (!(lower <= value && value <= upper)) {
            std::cerr << "constraint violation : constraint is " << lower << " <= " << name << " <= " << upper
                      << " but actual " << name << " = " << value << std::endl;
            return false;
        }
        return true;
    }
};

template<class Getter, class T>
std::unique_ptr<inequation_condition<Getter, T>> make_inequation_condition(Getter &&_g, std::string &&_name, T &&_lower,
                                                                           T &&_upper) {
    return std::make_unique<inequation_condition<Getter, T>>(std::forward<Getter>(_g), std::forward<std::string>(_name),
                                                             std::forward<T>(_lower), std::forward<T>(_upper));
}

template<class Getter>
class unique_condition : public constraint_condition {
    Getter getter;
    std::string name;
public:
    unique_condition(Getter &&_g, std::string &&_name) : getter(_g), name(_name) {}

    bool operator()(const testcase &test) const override {
        const auto &value{getter(test)};
        std::set<std::pair<unsigned long, unsigned long>> check{value.begin(), value.end()};
        if (size(check) != size(value)) {
            std::cerr << "constraint violation : there is multiple element in " << name << std::endl;
            return false;
        }
        return true;
    }
};

template<class Getter>
std::unique_ptr<unique_condition<Getter>> make_unique_condition(Getter &&_g, std::string &&_name) {
    return std::make_unique<unique_condition<Getter>>(std::forward<Getter>(_g), std::forward<std::string>(_name));
}

template<class Getter>
class no_self_loop_condition : public constraint_condition {
    Getter getter;
    std::string name{"self loop"};
public:
    explicit no_self_loop_condition(Getter &&_g) : getter(_g) {}

    bool operator()(const testcase &test) const override {
        for (const auto[a, b] : getter(test))
            if (a == b) {
                std::cerr << "constraint violation : there is self loop" << std::endl;
                return false;
            }
        return true;
    }
};

template<class Getter>
std::unique_ptr<no_self_loop_condition<Getter>> make_no_self_loop_condition(Getter &&_g) {
    return std::make_unique<no_self_loop_condition<Getter>>(std::forward<Getter>(_g));
}

class testcase_manager {
    std::vector<testcase> testcases;
    std::vector<std::unique_ptr<constraint_condition>> constraints;

public:
    void add_testcase(testcase &&_testcase) {
        testcases.emplace_back(_testcase);
    }

    void add_condition(std::unique_ptr<constraint_condition> &&_condition) {
        constraints.push_back(move(_condition));
    }

    bool check_constraint() {
        bool ret{true};
        for (unsigned long i{}, i_upto{size(testcases)}; i < i_upto; ++i) {
            if (std::any_of(constraints.begin(), constraints.end(),
                            [this, &i](auto &&cond) { return !cond->operator()(this->testcases[i]); })) {
                std::cerr << i << "-th testcase(" << testcases[i].name << ") violates constraints" << std::endl;
                ret &= 0;
            }
        }
        return ret;
    }

    void make_input() {
        if (!check_constraint()) {
            std::cerr << "constraints violation remains!\nfix it first." << std::endl;
            return;
        }
        for (const auto &t : testcases) {
            std::ofstream ofs{"../in/" + t.name + ".txt"};
            ofs << t.to_string() << std::flush;
        }
    }

    void print_input() {
        if (!check_constraint()) {
            std::cerr << "constraints violation remains!\nfix it first." << std::endl;
            return;
        }
        for (const auto &t : testcases) {
            std::cout << t.name << std::string(30, '-') << std::endl;
            std::cout << t.to_string() << std::endl;
        }
    }

    void print_summary(bool force = false) {
        if (!check_constraint()) {
            std::cerr << "constraints violation remains!\nfix it first." << std::endl;
            if (!force)return;
        }
        for (const auto &t : testcases) {
            std::cout << t.name << std::string(30, '-') << std::endl;
            std::cout << t.head() << std::endl;
        }
    }
};

template<class T, int N>
constexpr T pow_ten = 10 * pow_ten<T, N - 1>;
template<class T>
constexpr T pow_ten<T, 0> = 1;

int main() {
    using namespace std;
    pokagen::xoshiro256ss rng{pokagen::splitmix64{259}()};
    pokagen::uniform_int_distribution<unsigned long> uid{};

    testcase_manager manager;
    manager.add_condition(make_inequation_condition([](auto &&i) { return i.N; }, "N"s, 2UL, 100000UL));
    manager.add_condition(make_free_condition([](auto &&i) {
        return 1 <= i.T && i.T <= i.N;
    }, "condition is 1 <= T <= N but it is not satisfied"s));
    manager.add_condition(
            make_free_condition([](auto &&i) { return size(i.edges) + 1 == i.N; }, "number of edge must be N - 1"s));
    manager.add_condition(make_free_condition([](auto &&i) {
        const auto N{i.N};
        return all_of(begin(i.edges), end(i.edges),
                      [&N](auto &&i) { return 1 <= i.first && i.first < i.second && i.second <= N; });
    }, "condition is 1 <= vertex index <= N but it is not satisfied"s));
    manager.add_condition(make_unique_condition([](auto &&i) { return i.edges; }, "edge"s));
    manager.add_condition(make_no_self_loop_condition([](auto &&i) { return i.edges; }));
    manager.add_condition(make_free_condition([](auto &&i) {
        const auto N{i.N};
        vector<unsigned long> uf(N), sz(N, 1);
        iota(begin(uf), end(uf), 0UL);
        const auto find{[&uf](auto i) {
            while (i != uf[i])i = uf[i] = uf[uf[i]];
            return i;
        }};
        const auto unite{[&uf, &sz, &find](auto i, auto j) {
            i = find(i);
            j = find(j);
            if (i == j)return;
            if (sz[i] < sz[j])swap(i, j);
            sz[i] += sz[j];
            uf[j] = i;
        }};
        for (auto[u, v] : i.edges)unite(u - 1, v - 1);
        return sz[find(0)] == N;
    }, "graph is not connected"s));

    const auto shuffle_edge{[](unsigned long N, auto &&edge, auto &&rng) {
        vector<unsigned long> index(N + 1);
        iota(begin(index), end(index), 0UL);
        pokagen::shuffle(begin(index) + 1, end(index), rng);
        pokagen::shuffle(begin(edge), end(edge), rng);
        for (auto&&[A, B] : edge) {
            A = index[A];
            B = index[B];
            if (A >= B)swap(A, B);
        }
        return edge;
    }};
    const auto make_random_tree{[&uid, &shuffle_edge](auto &&rng, auto N, auto T) {
        vector<pair<unsigned long, unsigned long>> ret;
        vector<unsigned long> uf(N + 1), sz(N + 1, 1);
        iota(begin(uf), end(uf), 0UL);
        const auto find{[&uf](auto i) {
            while (i != uf[i])i = uf[i] = uf[uf[i]];
            return i;
        }};
        const auto unite{[&uf, &sz, &find](auto i, auto j) {
            i = find(i);
            j = find(j);
            if (i == j)return;
            if (sz[i] < sz[j])swap(i, j);
            sz[i] += sz[j];
            uf[j] = i;
        }};
        const auto same{[&find](auto i, auto j) { return find(i) == find(j); }};
        while (size(ret) + 1 < N) {
            unsigned long u{uid(rng, {1, N - 1})};
            unsigned long v{uid(rng, {1, N - 1})};
            if (v >= u)++v;
            if (v < u)swap(u, v);
            if (same(u, v))continue;
            ret.emplace_back(u, v);
            unite(u, v);
        }
        return shuffle_edge(N, ret, rng);
    }};
    const auto constant{[](auto N) { return [N](auto...) { return N; }; }};
    manager.add_testcase(testcase(
            "sample00",
            make_pair(1UL, vector<pair<unsigned long, unsigned long>>{{1, 2},
                                                                      {1, 3},
                                                                      {3, 4},
                                                                      {2, 5},
                                                                      {4, 6},
                                                                      {4, 7}})
    ));
    manager.add_testcase(testcase(
            "sample01",
            make_pair(1UL, vector<pair<unsigned long, unsigned long>>{{1,  2},
                                                                      {2,  3},
                                                                      {1,  4},
                                                                      {1,  5},
                                                                      {1,  6},
                                                                      {6,  7},
                                                                      {2,  8},
                                                                      {6,  9},
                                                                      {9,  10},
                                                                      {10, 11},
                                                                      {6,  12},
                                                                      {12, 13},
                                                                      {13, 14},
                                                                      {12, 15}})
    ));
    manager.add_testcase(testcase(
            "00",
            [&uid, &rng] {
                vector<pair<unsigned long, unsigned long>> par(99999);
                for (unsigned long i{}; i < 99999; ++i)par[i] = {i + 1, i + 2};
                return make_pair(1, par);
            }()
    ));
    manager.add_testcase(testcase(
            "01",
            [&uid, &rng] {
                vector<pair<unsigned long, unsigned long>> par(99999);
                for (unsigned long i{}; i < 99999; ++i)par[i] = {i / 2 + 1, i + 2};
                return make_pair(uid(rng, {1, 100000}), par);
            }()
    ));
    manager.add_testcase(testcase(
            "02",
            [&uid, &rng, &shuffle_edge] {
                vector<pair<unsigned long, unsigned long>> par(99999);
                for (unsigned long i{}; i < 99999; ++i)par[i] = {i / 2 + 1, i + 2};
                return make_pair(uid(rng, {1, 100000}), shuffle_edge(100000, par, rng));
            }()
    ));
    manager.add_testcase(testcase(
            "03",
            constant(100000),
            [&uid](auto &&rng, auto &&N) { return uid(rng, {1, N}); },
            [&uid, &shuffle_edge](auto &&rng, auto &&N, auto &&T) {
                vector<pair<unsigned long, unsigned long>> ret;
                vector<unsigned long> uf(N + 1), sz(N + 1, 1);
                iota(begin(uf), end(uf), 0UL);
                const auto find{[&uf](auto i) {
                    while (i != uf[i])i = uf[i] = uf[uf[i]];
                    return i;
                }};
                const auto unite{[&uf, &sz, &find](auto i, auto j) {
                    i = find(i);
                    j = find(j);
                    if (i == j)return;
                    if (sz[i] < sz[j])swap(i, j);
                    sz[i] += sz[j];
                    uf[j] = i;
                }};
                const auto same{[&find](auto i, auto j) { return find(i) == find(j); }};
                for (unsigned long i{}, p{1}; i < N / 3; ++i) {
                    unsigned long u{uid(rng, {1, N})};
                    if (same(p, u))continue;
                    ret.emplace_back(minmax(p, u));
                    swap(p, u);
                    unite(p, u);
                }
                while (size(ret) + 1 < N) {
                    unsigned long u{uid(rng, {1, N - 1})};
                    unsigned long v{uid(rng, {1, N - 1})};
                    if (v >= u)++v;
                    if (v < u)swap(u, v);
                    if (same(u, v))continue;
                    ret.emplace_back(u, v);
                    unite(u, v);
                }
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "04",
            make_pair(1UL, vector<pair<unsigned long, unsigned long>>{{1, 2}})
    ));
    manager.add_testcase(testcase(
            "05",
            [&uid](auto &&rng) { return uid(rng, {50000, 100000}); },
            [&uid](auto &&rng, auto &&N) { return uid(rng, {1, N}); },
            [&uid, &shuffle_edge](auto &&rng, auto &&N, auto &&T) {
                vector<pair<unsigned long, unsigned long>> ret;
                vector<unsigned long> uf(N + 1), sz(N + 1, 1);
                iota(begin(uf), end(uf), 0UL);
                const auto find{[&uf](auto i) {
                    while (i != uf[i])i = uf[i] = uf[uf[i]];
                    return i;
                }};
                const auto unite{[&uf, &sz, &find](auto i, auto j) {
                    i = find(i);
                    j = find(j);
                    if (i == j)return;
                    if (sz[i] < sz[j])swap(i, j);
                    sz[i] += sz[j];
                    uf[j] = i;
                }};
                const auto same{[&find](auto i, auto j) { return find(i) == find(j); }};
                for (unsigned long i{}, p{1}; i < N / 3; ++i) {
                    unsigned long u{uid(rng, {1, N})};
                    if (same(p, u))continue;
                    ret.emplace_back(minmax(p, u));
                    swap(p, u);
                    unite(p, u);
                }
                while (size(ret) + 1 < N) {
                    unsigned long u{uid(rng, {1, N - 1})};
                    unsigned long v{uid(rng, {1, N - 1})};
                    if (v >= u)++v;
                    if (v < u)swap(u, v);
                    if (same(u, v))continue;
                    ret.emplace_back(u, v);
                    unite(u, v);
                }
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "06",
            [&uid](auto &&rng) { return uid(rng, {50000, 100000}); },
            [&uid](auto &&rng, auto &&N) { return uid(rng, {1, N}); },
            make_random_tree,
            rng
    ));
    manager.add_testcase(testcase(
            "07",
            constant(100000),
            [&uid](auto &&rng, auto&& N) { return uid(rng, {50000, 100000}); },
            make_random_tree,
            rng
    ));

    manager.print_summary();
    manager.make_input();
    return 0;
}