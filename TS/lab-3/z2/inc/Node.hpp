#pragma once

#include <vector>
#include <string>
#include <random>
#include <deque>

#include <format>

int randomInt(int min, int max) noexcept
{
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

class Node;

struct Packet
{
    enum class Type : int
    {
        Data = 0,
        Jam = 1
    };

    Type type;
    Node* sender;
    Node* receiver;
};

struct Buffer
{
    Buffer(size_t max_size = 10) : max_size(max_size) {}

    size_t max_size;
    std::deque<std::string> data{};

    auto operator<<(std::string str) -> Buffer&
    {
        data.push_back(str);

        if (data.size() > max_size)
            data.pop_front();

        return *this;
    }
};

class Node
{
    public:
        Node(std::string name, int interval) : m_name(name), m_interval(interval) {}

        void update()
        {
            m_timer++;

            if (m_jamming)
            {
                if (m_timer >= randomInt(20, 40))
                {
                    m_jamming = false;
                    m_timer = 0;
                }

                return;
            }

            // Produce packets at a fixed interval
            if (m_timer >= m_interval)
            {
                Packet packet = produce_packet();

                buffer << std::format(
                    "{} produced a {} packet for {}\n",
                    m_name,
                    packet.type == Packet::Type::Data ? "data" : "jam",
                    packet.receiver->m_name
                );

                m_timer = 0;

                m_packets.push_back(packet);
            }

            // Consume packets that are meant for this node
            auto it = m_packets.begin();
            while (it != m_packets.end())
            {
                if (it->receiver == this)
                {
                    int same_packets = 0;
                    for (auto& packet : m_packets)
                        if (packet.sender == it->sender && packet.type == it->type)
                            same_packets++;
                    consume_packet(*it);
                    it = m_packets.erase(it);
                } else {
                    it++;
                }
            }

            it = m_packets.begin();
            while (it != m_packets.end())
            {
                if (it->type == Packet::Type::Jam)
                {
                    m_jamming = true;
                    m_timer = 0;

                    Node* prev = find_next(it->sender);
                    consume_packet(*it);

                    // Forward the jam packet
                    if (prev == m_left && m_right != nullptr)
                    {
                        Packet jam_packet{Packet::Type::Jam, this, nullptr};
                        m_right->m_packets.push_back(jam_packet);
                    } else if (prev == m_right && m_left != nullptr) {
                        Packet jam_packet{Packet::Type::Jam, this, nullptr};
                        m_left->m_packets.push_back(jam_packet);
                    }

                    m_packets.clear();
                    break;
                } else {
                    it++;
                }
            }

            // Try to forward packets
            for (auto& packet : m_packets)
            {
                Node* next = find_next(packet.receiver);

                if (next->scan_collision(this))
                {
                    // Collision detected
                    m_jamming = true;
                    m_timer = 0;

                    Packet jam_packet{Packet::Type::Jam, this, nullptr};

                    if (m_left != nullptr)
                        m_left->m_packets.push_back(jam_packet);

                    if (m_right != nullptr)
                        m_right->m_packets.push_back(jam_packet);

                    break;
                } else {
                    // Forward the packet
                    next->m_packets.push_back(packet);
                }
            }

            m_packets.clear();
        }

        void connect(Node* left, Node* right)
        {
            m_left = left;
            m_right = right;
        }

        const std::vector<Packet>& packets() const
        {
            return m_packets;
        }

        const std::string& name() const
        {
            return m_name;
        }

        bool is_jamming() const
        {
            return m_jamming;
        }

        static Buffer buffer;
    private:
        const std::string m_name;

        int m_timer{0};
        bool m_jamming{false};
        const int m_interval;

        std::vector<Packet> m_packets{};

        Node* m_left;
        Node* m_right;

        bool scan_collision(Node* node)
        {
            for (auto& packet : m_packets)
                if (packet.receiver == node)
                    return true;

            return false;
        }

        Node* find_next(Node* node)
        {
            for (Node* n = m_left; n != nullptr; n = n->m_left)
                if (n == node)
                    return m_left;

            for (Node* n = m_right; n != nullptr; n = n->m_right)
                if (n == node)
                    return m_right;

            return nullptr;
        }

        Packet produce_packet()
        {
            int nodes_left = 0;
            int nodes_right = 0;

            for (Node* n = m_left; n != nullptr; n = n->m_left)
                nodes_left++;

            for (Node* n = m_right; n != nullptr; n = n->m_right)
                nodes_right++;

            int node_idx = randomInt(0, nodes_left + nodes_right - 1);

            if (node_idx >= nodes_left)
            {
                node_idx -= nodes_left;

                for (Node* n = m_right; n != nullptr; n = n->m_right)
                    if (node_idx-- == 0)
                        return Packet{Packet::Type::Data, this, n};
            } else {
                for (Node* n = m_left; n != nullptr; n = n->m_left)
                    if (node_idx-- == 0)
                        return Packet{Packet::Type::Data, this, n};
            }

            return Packet{};
        };

        void consume_packet(Packet packet)
        {
            // Do something with the packet
            buffer << std::format(
                "{} received a {} packet from {}\n",
                m_name,
                packet.type == Packet::Type::Data ? "data" : "jam",
                packet.sender->m_name
            );
        }
};

Buffer Node::buffer = Buffer(100);