#pragma once

#include "Node.hpp"

#include <thread>
#include <chrono>
#include <iostream>

#include <ncurses.h>
#include <locale.h>

class Simulation
{
    public:
        Simulation(size_t size, double ms_per_update) : m_ms_per_update(ms_per_update)
        {
            // m_nodes.reserve(size);
            // for (size_t i = 0; i < size - 1; i++)
            //     m_nodes.emplace_back(generate_name(), 10000000);
            // m_nodes.emplace_back(generate_name(), 10);

            for (size_t i = 0; i < size; i++)
                m_nodes.emplace_back(generate_name(), randomInt(10, 40));

            m_nodes[0].connect(nullptr, &m_nodes[1]);

            for (size_t i = 1; i < size - 1; i++)
                m_nodes[i].connect(&m_nodes[i - 1], &m_nodes[i + 1]);

            m_nodes[size - 1].connect(&m_nodes[size - 2], nullptr);

            init_ncurses();
        }

        ~Simulation()
        {
            end_ncurses();
        }

        void simulate(size_t iterations)
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> start;

            for (size_t _ = 0; _ < iterations; _++)
            {
                start = std::chrono::high_resolution_clock::now();

                for (auto& node : m_nodes)
                    node.update();
                
                draw();

                auto elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();

                if (elapsed < m_ms_per_update)
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(m_ms_per_update - elapsed)));
            }
        }

    private:
        std::vector<Node> m_nodes{};

        double m_ms_per_update{};

        void draw()
        {
            clear();

            const auto& buffer = Node::buffer.data;


            constexpr size_t table_h = 6;
            constexpr size_t padding_h = 1;

            int height, width;
            getmaxyx(stdscr, height, width);


            const size_t columns = width / 50;

            int text_height = height - table_h - padding_h;
            int text_width = width / columns;

            // Drawing the graph

            const int node_width = 12;

            const int begin_x = 1;
            const int begin_y = 1;

            for (size_t i = 0; i < m_nodes.size(); i++)
            {
                if (i * node_width + begin_x >= width)
                    break;

                mvprintw(begin_y - 1, i * node_width + begin_x, "┌───────┐");
                mvprintw(begin_y, i * node_width + begin_x, "| %s |", m_nodes[i].name().c_str());
                mvprintw(begin_y + 1, i * node_width + begin_x, "└───────┘");

                if (i != m_nodes.size() - 1)
                {
                    mvprintw(begin_y, i * node_width + begin_x + node_width - 3, "┅┅┅");
                }

                if (m_nodes[i].is_jamming())
                {
                    mvprintw(begin_y + 2, i * node_width + begin_x + node_width / 2 - 3, "⚠️");
                }
            }

            // Drawing the logs
            auto rit = buffer.rbegin();
            for (int col = 0; col < columns; col++)
            {
                for (int i = 0; i < text_height && rit != buffer.rend(); i++, rit++)
                {
                    mvprintw(i + table_h + padding_h, col * text_width, " %s", rit->c_str());
                }

                // Draw vertical lines
                for (int i = 0; i < text_height; i++)
                    if (col != 0)
                        mvprintw(i + table_h + padding_h, col * text_width, "|");
            }

            // Draw horizontal lines
            for (int i = 0; i < width; i++)
                mvprintw(table_h, i, "-");

            refresh();
        }

        static void init_ncurses()
        {
            setlocale(LC_ALL, "");
            initscr();
        }

        static void end_ncurses()
        {
            endwin();
        }

        static std::string generate_name()
        {
            // constexpr std::string_view alphabet = "abcdefghijklmnopqrstuvwxyz";

            // auto to_upper = [](char c) -> char
            // {
            //     return c - 32;
            // };

            // std::string name = std::string(randomInt(5, 10), ' ');

            // for (auto& c : name)
            //     c = alphabet[randomInt(0, alphabet.size() - 1)];
            // name[0] = to_upper(name[0]);

            static int counter = 0;

            counter++;
            std::string name = "PC_" + ((counter < 10) ? "0" + std::to_string(counter) : std::to_string(counter));

            return name;
        }
};