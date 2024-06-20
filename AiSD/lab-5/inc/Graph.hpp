#pragma once

#include <vector>
#include <random>
#include <optional>

#define FAST_RANDOM false

constexpr double INF = std::numeric_limits<double>::infinity();

class Graph
{
    public:
        Graph(const size_t size, const std::optional<double> initial = std::nullopt) : m_size{size}
        {
            #if FAST_RANDOM
                static bool seeded = false;

                if (!seeded)
                {
                    srand(time(nullptr));
                    seeded = true;
                }
            #endif
            
            m_adjMat.resize(m_size);
            // m_adjMat.resize(m_size * (m_size - 1) / 2);

            // Resize the adjacency matrix to store only the upper triangular part, no need to store [i][j] and [j][i]
            for (size_t i = 0; i < m_size; i++)
            {
                m_adjMat[i].resize(
                    m_size - i - 1
                );
            }

        #if not FAST_RANDOM
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
        #endif

            // Fill the adjacency matrix with random values (or the initial value if provided)
            for (size_t i = 0; i < m_size; i++)
                for (size_t j = i + 1; j < m_size; j++)
                    if (initial.has_value())
                        m_adjMat[i][j - i - 1] = initial.value();
                        // m_adjMat[i * (m_size - i - 1) + j - i - 1] = initial.value();
                    else
                    #if not FAST_RANDOM
                        m_adjMat[i][j - i - 1] = dis(gen);
                        // m_adjMat[i * (m_size - i - 1) + j - i - 1] = dis(gen);
                    #else
                        m_adjMat[i][j - i - 1] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
                        // m_adjMat[i * (m_size - i - 1) + j - i - 1] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
                    #endif
                        // m_adjMat[i][j - i - 1] = dis(gen);
        }

        auto size() const -> size_t
        {
            return m_size;
        }

        auto get(size_t i, size_t j) const -> double
        {
            if (i == j)
                return 0.0;

            if (i > j)
                std::swap(i, j);

            return m_adjMat[i][j - i - 1];
            // return m_adjMat[i * (m_size - i - 1) + j - i - 1];
        }

        auto set(size_t i, size_t j, double val) -> void
        {
            if (i == j)
                return;

            if (i > j)
                std::swap(i, j);

            m_adjMat[i][j - i - 1] = val;
            // m_adjMat[i * (m_size - i - 1) + j - i - 1] = val;
        }

    private:
        const size_t m_size;
        std::vector<std::vector<double>> m_adjMat;
        // std::vector<double> m_adjMat;
};
