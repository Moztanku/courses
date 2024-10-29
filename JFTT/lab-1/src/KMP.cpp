/**
 * @file KMP.cpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief Implementation of Knuth-Morris-Pratt algorithm for pattern searching
 */
#include <print>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string_view>

auto create_lps(std::string_view pat) -> std::vector<int>
{
    std::vector<int> lps(pat.size());

    // Length of the previous longest prefix-suffix
    int prev_len = 0;

    // The first element of the lps is always 0
    lps[0] = 0;
    
    // Calculate the lps for the rest of the pattern
    for (int i = 1; i < pat.size(); i++)
    {
        // If the current character matches the character at the previous longest prefix-suffix
        if (pat[i] == pat[prev_len])
        {
            prev_len++;
            lps[i] = prev_len;
        }
        else
        {
            // If the current character does not match the character at the previous longest prefix-suffix
            if (prev_len != 0)
            {
                // We try to find a shorter prefix-suffix
                prev_len = lps[prev_len - 1];
                i--;
            }
            else
            {
                // If we cannot find a shorter prefix-suffix then the lps is 0
                lps[i] = 0;
            }
        }
    }

    return lps;
}

auto search(std::string_view pat, std::string_view text) -> std::vector<int>
{
    std::vector<int> matches;

    // Generate the longest prefix-suffix table
    const std::vector<int> lps = create_lps(pat);

    int i = 0; // Index for the text
    int j = 0; // Index for the pattern

    // Traverse the text
    while (i < text.size())
    {
        // If the current character in the text matches the current character in the pattern
        if (text[i] == pat[j])
        {
            i++;
            j++;
        }

        // If we found a match
        if (j == pat.size())
        {
            matches.push_back(i - j);
            j = lps[j - 1];
        }
        // If the current character in the text does not match the current character in the pattern
        else if (i < text.size() && text[i] != pat[j])
        {
            // If we are not at the beginning of the pattern
            if (j != 0)
            {
                // We try to find a shorter prefix-suffix
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return matches;
}

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

    const std::string text = read_file(argv[2]);

    const std::vector<int> matches = search(pattern, text);

    for (int i : matches)
        std::println("Match found at index: {}", i);

    return 0;
}
