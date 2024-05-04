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
    unsigned long N, M;
    std::vector<std::pair<unsigned long, unsigned long>> edges;

    template<class NGen, class MGen, class EdgeGen, class RNG>
    testcase(std::string &&_name, NGen &&N_generator, MGen &&M_generator, EdgeGen &&edge_generator, RNG &&rng) : name(
            _name), N(), M(), edges() {
        N = N_generator(rng);
        M = M_generator(rng, N);
        edges = edge_generator(rng, N, M);
    }

    [[nodiscard]] std::string to_string() const {
        using std::endl;
        std::stringstream cout;
        cout << N << " " << M << endl;
        for (const auto[A, B] : edges)cout << A << " " << B << endl;
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
            std::cerr << "constraint violation :" << name << std::endl;
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
                std::cerr << i << "-th testcases violates constraints" << std::endl;
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
    manager.add_condition(make_inequation_condition([](auto &&i) { return i.M; }, "M"s, 1UL, 100000UL));
    manager.add_condition(make_free_condition([](auto &&i) {
        const auto N{i.N};
        return all_of(begin(i.edges), end(i.edges),
                      [&N](auto &&i) { return 1 <= i.first && i.first < i.second && i.second <= N; });
    }, "condition is 1 <= vertex index <= N but it is not satisfied"s));
    manager.add_condition(make_unique_condition([](auto &&i) { return i.edges; }, "edge"s));
    manager.add_condition(make_no_self_loop_condition([](auto &&i) { return i.edges; }));

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
    const auto constant{[](auto N) { return [N](auto...) { return N; }; }};
    manager.add_testcase(testcase(
            "sample00",
            constant(5),
            constant(4),
            constant(vector<pair<unsigned long, unsigned long>>{{1, 2},
                                                                {2, 3},
                                                                {3, 4},
                                                                {3, 5}}),
            rng
    ));
    manager.add_testcase(testcase(
            "sample01",
            constant(15),
            constant(30),
            [&uid, &shuffle_edge](auto &&rng, auto N, auto M) {
                vector<vector<unsigned long>> v(N, vector<unsigned long>(N));
                fill(begin(v[0]) + 1, end(v[0]), 1);
                for (unsigned long i{1}; i < N; ++i)v[i][0] = 1;
                unsigned long edge_cnt{N - 1};
                while (edge_cnt < M) {
                    unsigned long U{uid(rng, {1, N - 1})};
                    unsigned long V{uid(rng, {1, N - 1})};
                    if (V >= U)++V;
                    if (V < U)swap(U, V);
                    if (!v[U][V])++edge_cnt;
                    v[U][V] = v[V][U] = 1;
                }
                vector<pair<unsigned long, unsigned long>> ret;
                for (unsigned long i{}; i < N; ++i)
                    for (unsigned long j{}; j < i; ++j)
                        if (v[i][j])
                            ret.emplace_back(i + 1, j + 1);
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "00",
            constant(100),
            [](auto &&rng, auto &&N) { return N * (N - 1) / 2; },
            [](auto &&rng, auto N, auto M) {
                vector<pair<unsigned long, unsigned long>> ret;
                for (unsigned long i{1}; i <= N; ++i)for (unsigned long j{i + 1}; j <= N; ++j)ret.emplace_back(i, j);
                return ret;
            },
            rng
    ));
    manager.add_testcase(testcase(
            "01",
            constant(100),
            [](auto &&rng, auto &&N) { return N * (N - 1) / 2; },
            [&shuffle_edge](auto &&rng, auto N, auto M) {
                vector<pair<unsigned long, unsigned long>> ret;
                for (unsigned long i{1}; i <= N; ++i)for (unsigned long j{i + 1}; j <= N; ++j)ret.emplace_back(i, j);
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "02",
            constant(447),
            [](auto &&rng, auto &&N) { return N * (N - 1) / 2; },
            [&shuffle_edge](auto &&rng, auto N, auto M) {
                vector<pair<unsigned long, unsigned long>> ret;
                for (unsigned long i{1}; i <= N; ++i)for (unsigned long j{i + 1}; j <= N; ++j)ret.emplace_back(i, j);
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "03",
            [&uid](auto &&rng) { return uid(rng, {50, 10000}); },
            [&uid](auto &&rng, auto &&N) { return uid(rng, {N, min(N * (N - 1) / 2, 100000UL)}); },
            [&uid, &shuffle_edge](auto &&rng, auto N, auto M) {
                set<pair<unsigned long, unsigned long>> st;
                vector<pair<unsigned long, unsigned long>> ret;
                while (size(ret) < M) {
                    unsigned long u{uid(rng, {1, N - 1})};
                    unsigned long v{uid(rng, {1, N - 1})};
                    if (v >= u)++v;
                    if (v < u)swap(u, v);
                    if (st.count(make_pair(u, v)))continue;
                    st.emplace(u, v);
                    ret.emplace_back(u, v);
                }
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "04",
            [&uid](auto &&rng) { return uid(rng, {50000, 100000}); },
            [](auto &&rng, auto &&N) { return N; },
            [&shuffle_edge](auto &&rng, auto N, auto M) {
                vector<pair<unsigned long, unsigned long>> ret;
                for(unsigned long i{}; i < N; ++i)ret.emplace_back(i + 1, (i + 1) % N + 1);
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "05",
            constant(2),
            constant(1),
            [&uid, &shuffle_edge](auto &&rng, auto N, auto M) {
                set<pair<unsigned long, unsigned long>> st;
                vector<pair<unsigned long, unsigned long>> ret;
                while (size(ret) < M) {
                    unsigned long u{uid(rng, {1, N - 1})};
                    unsigned long v{uid(rng, {1, N - 1})};
                    if (v >= u)++v;
                    if (v < u)swap(u, v);
                    if (st.count(make_pair(u, v)))continue;
                    st.emplace(u, v);
                    ret.emplace_back(u, v);
                }
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "05",
            [&uid](auto &&rng) { return uid(rng, {50000, 100000}); },
            [&uid](auto &&rng, auto &&N) { return uid(rng, {50, 100}); },
            [&uid, &shuffle_edge](auto &&rng, auto N, auto M) {
                set<pair<unsigned long, unsigned long>> st;
                vector<pair<unsigned long, unsigned long>> ret;
                while (size(ret) < M) {
                    unsigned long u{uid(rng, {1, N - 1})};
                    unsigned long v{uid(rng, {1, N - 1})};
                    if (v >= u)++v;
                    if (v < u)swap(u, v);
                    if (st.count(make_pair(u, v)))continue;
                    st.emplace(u, v);
                    ret.emplace_back(u, v);
                }
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "06",
            constant(100000),
            constant(100000),
            [&uid, &shuffle_edge](auto &&rng, auto N, auto M) {
                set<pair<unsigned long, unsigned long>> st;
                vector<pair<unsigned long, unsigned long>> ret;
                while (size(ret) < M) {
                    unsigned long u{uid(rng, {1, N - 1})};
                    unsigned long v{uid(rng, {1, N - 1})};
                    if (v >= u)++v;
                    if (v < u)swap(u, v);
                    if (st.count(make_pair(u, v)))continue;
                    st.emplace(u, v);
                    ret.emplace_back(u, v);
                }
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));
    manager.add_testcase(testcase(
            "07",
            constant(100000),
            constant(100000),
            [&uid, &shuffle_edge](auto &&rng, auto N, auto M) {
                set<pair<unsigned long, unsigned long>> st;
                vector<pair<unsigned long, unsigned long>> ret;
                while (size(ret) < M) {
                    unsigned long u{uid(rng, {1, N - 1})};
                    unsigned long v{uid(rng, {1, N - 1})};
                    if (v >= u)++v;
                    if (v < u)swap(u, v);
                    if (st.count(make_pair(u, v)))continue;
                    st.emplace(u, v);
                    ret.emplace_back(u, v);
                }
                return shuffle_edge(N, ret, rng);
            },
            rng
    ));

    manager.make_input();
    return 0;
}