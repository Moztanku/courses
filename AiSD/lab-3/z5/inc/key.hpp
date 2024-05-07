#pragma once

#include <ostream>

class Key {
    public:
        Key(int value = 0) : m_value{value} {};
        Key& operator=(const int value) {
            assignment_count++;
            m_value = value; return *this;
        }
        Key& operator=(const Key& other) {
            assignment_count++;
            m_value = other.m_value; return *this;
        }
        operator int() const { return m_value; }

        void swap(Key& other)
        {
            assignment_count+=3;
            swap_count++;
            std::swap(m_value, other.m_value);
        }

        friend auto operator<=>(const Key& lhs, const Key& rhs)
        {
            comparison_count++;
            return lhs.m_value <=> rhs.m_value;
        }

        friend std::ostream& operator<<(std::ostream& os, const Key& key)
        {
            return os << (key.m_value < 10 ? "0" : "") << key.m_value;
        }

        static auto get_stats()
        {
            struct {
                int comparison_count;
                int assignment_count;
                int swap_count;
            } stats;

            stats.comparison_count = comparison_count;
            stats.assignment_count = assignment_count;
            stats.swap_count = swap_count;

            return stats;
        }

        static void reset_stats()
        {
            comparison_count = 0;
            assignment_count = 0;
            swap_count = 0;
        }
    private:
        int m_value;

        static int comparison_count;
        static int assignment_count;
        static int swap_count;
};

int Key::comparison_count = 0;
int Key::assignment_count = 0;
int Key::swap_count = 0;