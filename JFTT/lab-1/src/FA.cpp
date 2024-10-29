/**
 * @file KMP.cpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief Implementation of Finite Automaton algorithm for pattern searching
 */
#include <print>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string_view>

class FA
{
    constexpr static int alphabet_size = std::numeric_limits<char>::max() + 1;

    public:
        FA(std::string_view pattern)
            : m_pat_size(pattern.size())
        {
            // Number of states is equal to the size of the pattern plus one
            const int states_cnt   = m_pat_size + 1;

            m_table.resize(states_cnt * alphabet_size);

            // Fill the table with the next state for each state and symbol
            for (int state = 0; state < states_cnt; state++)
                for (int symbol = 0; symbol < alphabet_size; symbol++)
                    m_table[state * alphabet_size + symbol] = get_next_state(pattern, state, symbol);
        }

        auto search(std::string_view text) const -> std::vector<int>
        {
            std::vector<int> matches;

            int state = 0;

            // Traverse the text
            for (int i = 0; i < text.size(); i++)
            {
                state = m_table[state * alphabet_size + text[i]];

                // We found a match
                if (state == m_pat_size)
                    matches.push_back(i - m_pat_size + 1);
            }

            return matches;
        }

    private:
        std::vector<int> m_table;
        const int        m_pat_size;

        auto get_next_state(std::string_view pat, int st, int sy) -> int
        {
            // If the symbol is the same as the next character in the pattern then we move to the next state
            if (st < pat.size() && sy == pat[st])
                return st + 1;

            // Otherwise we need to find the longest prefix of the pattern that is also a suffix of the pattern
            for (int ns = st; ns > 0; ns--)
            {
                if (pat[ns - 1] == sy)
                {
                    int i = 0;
                    for (; i < ns; i++)
                    {
                        if (pat[i] != pat[st - ns + 1 + i])
                            break;
                    }

                    if (i == ns)
                        return ns;
                }
            }

            return 0;
        }
};

auto read_file(std::string_view path) -> std::string
{
    std::ifstream ifs(path.data());
    std::ostringstream oss;
    oss << ifs.rdbuf();

    return oss.str();
}

auto main(int argc, char** argv) -> int
{
    if (argc != 3)
    {
        std::println("Usage: {} <pattern> <file-path>", argv[0]);

        return 1;
    }

    std::string_view pattern = argv[1];

    const FA fa(pattern);

    const std::string text = read_file(argv[2]);

    const std::vector<int> matches = fa.search(text);

    for (int i : matches)
        std::println("Match found at index: {}", i);

    return 0;
}
