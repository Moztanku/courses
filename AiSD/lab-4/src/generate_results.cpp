#include <iostream>
#include <format>

#include <span>
#include <string>
#include <vector>
#include <ranges>
#include <random>
#include <unordered_map>

#include "Key.hpp"
#include "NodePtr.hpp"

#include "ITree.hpp"
#include "BSTree.hpp"
#include "RBTree.hpp"
#include "SplayTree.hpp"

auto generate_sorted_values(std::span<int> arr) -> void
{
    std::iota(arr.begin(), arr.end(), 1);
}

auto generate_random_values(std::span<int> arr) -> void
{
    generate_sorted_values(arr);

    static std::random_device rd;
    static std::mt19937 g(rd());
    
    std::shuffle(arr.begin(), arr.end(), g);
}

std::unique_ptr<ITree> get_tree(const std::string& name)
{
    if (name == "BSTree")
        return std::make_unique<BSTree>();
    else if (name == "RBTree")
        return std::make_unique<RBTree>();
    else if (name == "SplayTree")
        return std::make_unique<SplayTree>();
    else
        return nullptr;
}

struct Result
{
    int64_t total_cmp{};
    int64_t total_reads{};
    int64_t total_writes{};

    int64_t max_cmp_per_operation{};
    int64_t max_reads_per_operation{};
    int64_t max_writes_per_operation{};

    int64_t tree_height{};

    auto operator+=(const Result& other) -> Result&
    {
        total_cmp += other.total_cmp;
        total_reads += other.total_reads;
        total_writes += other.total_writes;

        max_cmp_per_operation += other.max_cmp_per_operation;
        max_reads_per_operation += other.max_reads_per_operation;
        max_writes_per_operation += other.max_writes_per_operation;

        tree_height += other.tree_height;

        return *this;
    }

    auto operator/=(int n) -> Result&
    {
        total_cmp = std::round(static_cast<double>(total_cmp) / n);
        total_reads = std::round(static_cast<double>(total_reads) / n);
        total_writes = std::round(static_cast<double>(total_writes) / n);

        max_cmp_per_operation = std::round(static_cast<double>(max_cmp_per_operation) / n);
        max_reads_per_operation = std::round(static_cast<double>(max_reads_per_operation) / n);
        max_writes_per_operation = std::round(static_cast<double>(max_writes_per_operation) / n);

        tree_height = std::round(static_cast<double>(tree_height) / n);

        return *this;
    }
};

auto get_reset_stats()
{
    auto key_stats = Key::get_stats();
    Key::reset_stats();

    auto node_stats = NodePtr_Base::get_stats();
    NodePtr_Base::reset_stats();

    return std::make_pair(key_stats, node_stats);
}

auto fill_result(Result& result) -> void
{
    auto [key_stats, node_stats] = get_reset_stats();

    result.total_cmp += key_stats.comparison_count;
    result.total_reads += node_stats.reads;
    result.total_writes += node_stats.changes;

    result.max_cmp_per_operation = std::max(
        result.max_cmp_per_operation, static_cast<int64_t>(key_stats.comparison_count)
    );
    result.max_reads_per_operation = std::max(
        result.max_reads_per_operation, static_cast<int64_t>(node_stats.reads)
    );
    result.max_writes_per_operation = std::max(
        result.max_writes_per_operation, static_cast<int64_t>(node_stats.changes)
    );

    // result.tree_height = std::max(result.tree_height, tree_height);
}

auto test_tree(std::unique_ptr<ITree> tree, std::span<int> values) -> Result
{
    Result result{};

    Key::reset_stats();
    NodePtr_Base::reset_stats();

    for (auto v : values)
    {
        tree->insert(v);
        fill_result(result);
    }

    result.tree_height = tree->height();

    generate_random_values(values);
    for (auto v : values)
    {
        tree->remove(v);
        fill_result(result);
    }

    return result;
}

auto main() -> int
{
    constexpr uint K = 20;
    // constexpr uint K = 1;

    constexpr uint n_min  =  10000;
    constexpr uint n_step =  10000;
    constexpr uint n_max  = 100000;

    auto Ns = std::views::iota(n_min / n_step, (n_max + n_step) / n_step)
            | std::views::transform([n_step](auto i) { return n_step * i; });

    std::unordered_map<
        std::string,std::vector<std::pair<uint, Result>>
    > results{};

    const std::vector<std::string> TREE_NAMES =
        {"BSTree", "RBTree", "SplayTree"};

    for (auto N : Ns)
    {
        std::clog << "Running tests for N = " << N << "\n";
        std::vector<int> values(N);

        for (const auto& tree_name : TREE_NAMES)
        {
            Result avg_result{};

            for (auto _ = 0; _ < K; _++)
            {
                std::unique_ptr<ITree> tree = get_tree(tree_name);

                // generate_sorted_values(values);
                generate_random_values(values);

                const auto result = test_tree(std::move(tree), values);

                avg_result += result;
            }
            
            avg_result /= K;
            results[tree_name].push_back({N, avg_result});
        }

    }

    for (auto const& [tree_name, results] : results)
    {
        std::cout << "#" << tree_name << "\n";
        for (auto const& [N, result] : results)
        {
            std::cout << std::format(
                "{} {} {} {} {} {} {} {}\n",
                N, result.total_cmp, result.total_reads, result.total_writes,
                result.max_cmp_per_operation, result.max_reads_per_operation,
                result.max_writes_per_operation, result.tree_height
            );
        }
    }

    return 0;
}