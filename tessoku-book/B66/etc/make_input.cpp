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

class testcase_pre {
public:
    std::string name;
    unsigned long N, Q;
    std::vector<std::tuple<unsigned long, unsigned long, unsigned long>> queries;

    template<class NGen, class QGen, class QueryGen, class RNG>
    testcase_pre(std::string &&_name, NGen &&N_generator, QGen &&Q_generator, QueryGen &&query_generator, RNG &&rng)
            : name(
            _name), N(), Q(), queries() {
        N = N_generator(rng);
        Q = Q_generator(rng, N);
        queries = query_generator(rng, N, Q);
    }

    testcase_pre(std::string &&_name,
                 std::pair<unsigned long, std::vector<std::tuple<unsigned long, unsigned long, unsigned long>>> &&_n_edges)
            : name(
            _name), N(_n_edges.first), Q(size(_n_edges.second)), queries(_n_edges.second) {}

    [[nodiscard]] std::string to_string() const {
        using std::endl;
        std::stringstream cout;
        cout << N << " " << Q << endl;
        for (const auto[t, u, v] : queries)cout << t << " " << u << " " << v << endl;
        return cout.str();
    }

    [[nodiscard]] std::string head(unsigned long lines = 5) const {
        using std::endl;
        std::stringstream cout;
        cout << N << " " << Q << endl;
        unsigned long cnt{};
        for (const auto[t, u, v] : queries) {
            cout << t << " " << u << " " << v << endl;
            ++cnt;
            if (cnt >= lines)break;
        }
        return cout.str();
    }
};

class testcase {
public:
    std::string name;
    unsigned long N, M, Q;
    std::vector<std::pair<unsigned long, unsigned long>> edges;
    std::vector<std::tuple<unsigned long, unsigned long, unsigned long>> queries;

    template<class NGen, class MGen, class QGen, class EdgeGen, class QueryGen, class RNG>
    testcase(std::string &&_name, NGen &&N_generator, MGen &&M_generator, QGen &&Q_generator, EdgeGen &&edge_generator,
             QueryGen &&query_generator, RNG &&rng) : name(
            _name), N(), M(), Q(), edges(), queries() {
        N = N_generator(rng);
        M = Q_generator(rng, N);
        Q = Q_generator(rng, N, M);
        edges = edge_generator(rng, N, M, Q);
        queries = query_generator(rng, N, M, Q, edges);
    }

    testcase(std::string &&_name,
             std::tuple<unsigned long, std::vector<std::pair<unsigned long, unsigned long>>, std::vector<std::tuple<unsigned long, unsigned long, unsigned long>>> &&_n_edges_queries)
            : name(_name), N(std::get<0>(_n_edges_queries)), M(std::get<1>(_n_edges_queries).size()),
              Q(std::get<2>(_n_edges_queries).size()), edges(std::get<1>(_n_edges_queries)),
              queries(std::get<2>(_n_edges_queries)) {}

    template<class RNG>
    testcase(testcase_pre &&_tk, RNG &&rng) : name(_tk.name), N(_tk.N), M(), Q(), edges(), queries() {
        std::vector<std::pair<unsigned long, unsigned long>> edges_tmp;
        for (const auto[t, u, v] : _tk.queries) {
            if (t == 1) {
                edges_tmp.emplace_back(u, v);
                queries.emplace_back(t, size(edges_tmp), 0);
            } else {
                queries.emplace_back(t, u, v);
            }
        }
        M = size(edges_tmp);
        Q = size(queries);
        std::vector<unsigned long> edge_index(M + 1);
        std::iota(edge_index.begin(), edge_index.end(), 0UL);
        pokagen::shuffle(edge_index.begin() + 1, edge_index.end(), rng);
        for (auto&&[t, u, v] : queries)if (t == 1)u = edge_index[u];
        std::reverse(queries.begin(), queries.end());
        edges.resize(M);
        for (unsigned long i{1}; i <= M; ++i)edges[edge_index[i] - 1] = edges_tmp[i - 1];
    }

    [[nodiscard]] std::string to_string() const {
        using std::endl;
        std::stringstream cout;
        cout << N << " " << M << endl;
        for (const auto[u, v] : edges)cout << u << " " << v << endl;
        cout << Q << endl;
        for (const auto[t, u, v] : queries)
            if (t == 1)cout << t << " " << u << endl;
            else cout << t << " " << u << " " << v << endl;
        return cout.str();
    }

    [[nodiscard]] std::string head(unsigned long lines = 5) const {
        using std::endl;
        std::stringstream cout;
        cout << N << " " << M << endl;
        unsigned long cnt{};
        for (const auto[u, v] : edges) {
            cout << u << " " << v << endl;
            ++cnt;
            if (cnt >= lines)return cout.str();
        }
        cout << Q << endl;
        ++cnt;
        if (cnt >= lines)return cout.str();
        for (const auto[t, u, v] : queries) {
            if (t == 1)cout << t << " " << u << endl;
            else cout << t << " " << u << " " << v << endl;
            ++cnt;
            if (cnt >= lines)return cout.str();
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
        std::set<typename std::remove_reference_t<decltype(value)>::value_type> check{value.begin(), value.end()};
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
        for (const auto[a, b, c] : getter(test))
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
    manager.add_condition(make_inequation_condition([](auto &&i) { return i.M; }, "M"s, 1UL, 100000UL));
    manager.add_condition(make_inequation_condition([](auto &&i) { return i.Q; }, "Q"s, 1UL, 100000UL));
    manager.add_condition(
            make_free_condition([](auto &&i) { return size(i.edges) == i.M; }, "number of edge must be M"s));
    manager.add_condition(make_free_condition([](auto &&i) {
        const auto N{i.N};
        return all_of(begin(i.edges), end(i.edges),
                      [&N](auto &&i) { return 1 <= i.first && i.first < i.second && i.second <= N; });
    }, "condition is 1 <= u < v <= N but it is not satisfied"s));
    manager.add_condition(make_unique_condition([](auto &&i) { return i.edges; }, "there are multiple edges"s));
    manager.add_condition(make_unique_condition([](auto &&i) {
        vector<unsigned long> xs;
        for (const auto[t, u, v] : i.queries)if (t == 1)xs.emplace_back(u);
        return xs;
    }, "there are multiple queries to erase same edge"s));
    manager.add_condition(
            make_free_condition([](auto &&i) { return size(i.queries) == i.Q; }, "number of query must be Q"s));
    manager.add_condition(make_free_condition([](auto &&i) {
        return all_of(begin(i.queries), end(i.queries), [](auto &&i) { return get<0>(i) == 1 || get<0>(i) == 2; });
    }, "condition is t in {1, 2} but it is not satisfied"s));
    manager.add_condition(make_free_condition([](auto &&i) {
        const auto M{i.M};
        return all_of(begin(i.queries), end(i.queries), [&M](auto &&i) {
            return get<0>(i) != 1 || (get<2>(i) == 0 && 1 <= get<1>(i) && get<1>(i) <= M);
        });
    }, "query format `1 x` (1 <= x <= M) is not satisfied"s));
    manager.add_condition(make_free_condition([](auto &&i) {
        const auto N{i.N};
        return all_of(begin(i.queries), end(i.queries), [&N](auto &&i) {
            return get<0>(i) != 2 || (1 <= get<1>(i) && get<1>(i) < get<2>(i) && get<2>(i) <= N);
        });
    }, "query format `2 u v` (1 <= u < v <= N) is not satisfied"s));

    const auto shuffle_query{[](unsigned long N, auto &&query, auto &&rng) {
        vector<unsigned long> index(N + 1);
        iota(begin(index), end(index), 0UL);
        pokagen::shuffle(begin(index) + 1, end(index), rng);
        for (auto&&[t, u, v] : query) {
            u = index[u];
            v = index[v];
            if (u >= v)swap(u, v);
        }
        return query;
    }};
    const auto make_random_query{[&uid, &shuffle_query](auto &&rng, auto N, auto Q) {
        vector<vector<unsigned long>> group(N);
        for (unsigned long i{}; i < N; ++i)group[i].emplace_back(i);
        vector<unsigned long> group_inv(N);
        __gnu_pbds::tree<unsigned long, __gnu_pbds::null_type, less<>, __gnu_pbds::splay_tree_tag, __gnu_pbds::tree_order_statistics_node_update> not_single_groups;
        iota(begin(group_inv), end(group_inv), 0UL);
        set<pair<unsigned long, unsigned long>> st;
        vector<tuple<unsigned long, unsigned long, unsigned long>> ret;
        const auto unite{[&group, &group_inv, &not_single_groups, &ret](unsigned long i, unsigned long j) {
            ret.emplace_back(1, i + 1, j + 1);
            unsigned long i_g{group_inv[i]};
            unsigned long j_g{group_inv[j]};
            if (i_g == j_g)return;
            if (size(group[i_g]) < size(group[j_g]))swap(i_g, j_g);
            if (size(group[j_g]) > 1)not_single_groups.erase(j_g);
            if (size(group[i_g]) <= 1)not_single_groups.insert(i_g);
            for (const auto g_j_g : group[j_g])group_inv[g_j_g] = i_g;
            group[i_g].insert(end(group[i_g]), begin(group[j_g]), end(group[j_g]));
        }};
        for (unsigned long i{}; i < Q; ++i) {
            const auto t{uid(rng, {1, 2})};
            if (t == 1) {
                unsigned long u{}, v{};
                do {
                    u = uid(rng, {0, N - 1});
                    v = uid(rng, {0, N - 1});
                } while (u == v || st.count(minmax(u, v)));
                if (u > v)swap(u, v);
                unite(u, v);
                st.emplace(u, v);
            } else {
                unsigned long u{}, v{};
                if (size(group[group_inv[0]]) == N || not_single_groups.empty()) {
                    do {
                        u = uid(rng, {0, N - 1});
                        v = uid(rng, {0, N - 1});
                    } while (u == v);
                    if (u > v)swap(u, v);
                } else if (uid(rng, {0, 1})) {
                    const auto gp{*not_single_groups.find_by_order(uid(rng, {0, size(not_single_groups) - 1}))};
                    do {
                        u = uid(rng, {0, size(group[gp]) - 1});
                        v = uid(rng, {0, size(group[gp]) - 1});
                    } while (u == v);
                    u = group[gp][u];
                    v = group[gp][v];
                    if (u > v)swap(u, v);
                } else {
                    do {
                        u = uid(rng, {0, N - 1});
                        v = uid(rng, {0, N - 1});
                    } while (group_inv[u] == group_inv[v]);
                    if (u > v)swap(u, v);
                }
                ret.emplace_back(t, u + 1, v + 1);
            }
        }
        return shuffle_query(N, ret, rng);
    }};
    const auto constant{[](auto N) { return [N](auto...) { return N; }; }};
    manager.add_testcase(testcase(testcase_pre(
            "sample00",
            make_pair(3UL, vector<tuple<unsigned long, unsigned long, unsigned long>>{{1, 1, 2},
                                                                                      {2, 1, 3},
                                                                                      {1, 2, 3},
                                                                                      {2, 2, 3}})
    ), rng));
    manager.add_testcase(testcase(testcase_pre(
            "sample01",
            make_pair(12UL, vector<tuple<unsigned long, unsigned long, unsigned long>>{{2, 9,  11},
                                                                                       {1, 1,  7},
                                                                                       {1, 1,  4},
                                                                                       {2, 3,  6},
                                                                                       {1, 3,  5},
                                                                                       {2, 3,  5},
                                                                                       {1, 10, 12},
                                                                                       {1, 4,  8},
                                                                                       {1, 8,  11},
                                                                                       {2, 10, 12},
                                                                                       {1, 5,  9},
                                                                                       {2, 6,  8}})
    ), rng));
    manager.add_testcase(testcase(
            "sample02",
            make_tuple(4UL, vector<pair<unsigned long, unsigned long>>{{1, 2}, {2, 3}, {3, 4}}, vector<tuple<unsigned long, unsigned long, unsigned long>>{{2, 1, 2}, {2, 1, 3}, {2, 1, 4}, {1, 2, 0}, {2, 1, 2}, {2, 1, 3}, {2, 1, 4}})
    ));
    manager.add_testcase(testcase(testcase_pre(
            "00",
            [&shuffle_query, &uid, &rng] {
                vector<tuple<unsigned long, unsigned long, unsigned long>> query;
                [dfs_impl{[&query](auto &&f, unsigned long l, unsigned long r) -> void {
                    if (l + 1 == r)return;
                    unsigned long n{r - l};
                    query.emplace_back(1, l, l + n / 2);
                    f(f, l, l + n / 2);
                    f(f, l + n / 2, r);
                }}] { dfs_impl(dfs_impl, 1, 50001); }();
                reverse(begin(query), end(query));
                for (unsigned long i{}; i < 50000; ++i) {
                    unsigned long u, v;
                    do {
                        u = uid(rng, {1, 100000});
                        v = uid(rng, {1, 100000});
                    } while (u == v);
                    query.emplace_back(2, u, v);
                }
                return make_pair(100000, shuffle_query(100000, query, rng));
            }()
    ), rng));
    manager.add_testcase(testcase(testcase_pre(
            "01",
            [&shuffle_query, &rng] {
                vector<tuple<unsigned long, unsigned long, unsigned long>> query;
                for (unsigned long i{}; i < 50000; ++i)query.emplace_back(1, i + 1, i + 2);
                for (unsigned long i{}; i < 50000; ++i)query.emplace_back(2, 1, i + 2);
                return make_pair(100000, shuffle_query(100000, query, rng));
            }()
    ), rng));
    manager.add_testcase(testcase(testcase_pre(
            "02",
            [&uid, &shuffle_query, &rng] {
                vector<tuple<unsigned long, unsigned long, unsigned long>> query;
                for (unsigned long i{}; i < 50000; ++i)query.emplace_back(1, i + 1, i + 2);
                for (unsigned long i{}; i < 50000; ++i) {
                    unsigned long u, v;
                    do {
                        u = uid(rng, {1, 100000});
                        v = uid(rng, {1, 100000});
                    } while (u == v);
                    query.emplace_back(2, u, v);
                }
                return make_pair(100000, shuffle_query(100000, query, rng));
            }()
    ), rng));
    manager.add_testcase(testcase(testcase_pre(
            "03",
            constant(100000),
            constant(100000),
            make_random_query,
            rng
    ), rng));
    manager.add_testcase(testcase(testcase_pre(
            "04",
            [] {
                return make_pair(2UL, vector<tuple<unsigned long, unsigned long, unsigned long>>{{2, 1, 2},
                                                                                                 {1, 1, 2},
                                                                                                 {2, 1, 2}});
            }()
    ), rng));
    manager.add_testcase(testcase(testcase_pre(
            "05",
            [&uid](auto &&rng) { return uid(rng, {50000, 100000}); },
            [&uid](auto &&rng, auto &&N) { return uid(rng, {50000, 100000}); },
            make_random_query,
            rng
    ), rng));
    manager.add_testcase(testcase(testcase_pre(
            "06",
            [&uid](auto &&rng) { return uid(rng, {50000, 100000}); },
            [&uid](auto &&rng, auto &&N) { return uid(rng, {50000, 100000}); },
            make_random_query,
            rng
    ), rng));
    manager.add_testcase(testcase(
            "07",
            constant(100000),
            constant(100000),
            constant(100000),
            [&uid](auto &&rng, auto N, auto M, auto Q) {
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
                vector<pair<unsigned long, unsigned long>> ret;
                set<pair<unsigned long, unsigned long>> s;
                while (size(ret) + 1 < N) {
                    unsigned long u{uid(rng, {1, N})};
                    unsigned long v{uid(rng, {1, N})};
                    if (find(u - 1) == find(v - 1))continue;
                    ret.emplace_back(minmax(u, v));
                    s.emplace(minmax(u, v));
                    unite(u - 1, v - 1);
                }
                unsigned long u, v;
                do {
                    u = uid(rng, {1, N});
                    v = uid(rng, {1, N});
                } while (u == v || s.count(minmax(u, v)));
                ret.emplace_back(minmax(u, v));
                pokagen::shuffle(begin(ret), end(ret), rng);
                return ret;
            },
            [&uid](auto &&rng, auto N, auto M, auto Q, auto &&edge) {
                vector<unsigned long> erasable(M);
                iota(begin(erasable), end(erasable), 1UL);
                pokagen::shuffle(begin(erasable), end(erasable), rng);
                vector<tuple<unsigned long, unsigned long, unsigned long>> queries(Q);
                for (auto&&[t, u, v] : queries) {
                    t = uid(rng, {1, 2});
                    if (t == 1) {
                        u = erasable.back();
                        erasable.pop_back();
                    } else
                        do {
                            u = uid(rng, {1, N});
                            v = uid(rng, {1, N});
                            if (u >= v)swap(u, v);
                        } while (u == v);
                }
                return queries;
            },
            rng
    ));

    manager.print_summary();
    manager.make_input();
    return 0;
}