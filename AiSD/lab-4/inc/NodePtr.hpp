#pragma once

#include <memory>

class NodePtr_Base
{
    public:
        static auto get_stats()
        {
            struct {
                int reads;
                int changes;
            } stats;

            stats.reads = reads;
            stats.changes = changes;

            return stats;
        }

        static void reset_stats()
        {
            reads = 0;
            changes = 0;
        }
    protected:
        static int reads;
        static int changes;
};

int NodePtr_Base::reads = 0;
int NodePtr_Base::changes = 0;

// Uses std::shared_ptr<Node> under the hood, counts number of reads and changes
template <typename Node>
class NodePtr : public NodePtr_Base
{
    public:
        NodePtr(std::shared_ptr<Node> node = nullptr)
            : node(node)
        {
        }

        auto operator=(const NodePtr<Node>& other) -> NodePtr<Node>&
        {
            ++changes;
            node = other.node;

            return *this;
        }

        auto operator=(std::shared_ptr<Node> node)
        {
            ++changes;
            this->node = node;

            return *this;
        }

        auto operator==(const NodePtr<Node>& other) const -> bool
        {
            ++reads;
            return node == other.node;
        }

        auto operator==(Node* other) const -> bool
        {
            ++reads;
            return node.get() == other;
        }

        // operator std::shared_ptr<Node>() const
        // {
        //     return node;
        // }

        // operator std::shared_ptr<Node>&()
        // {
        //     return node;
        // }

        operator bool() const
        {
            ++reads;
            return node != nullptr;
        }

        auto operator->() -> std::shared_ptr<Node>
        {
            ++reads;
            return node;
        }

        auto operator->() const -> std::shared_ptr<Node>
        {
            ++reads;
            return node;
        }

        auto operator!() const -> bool
        {
            ++reads;
            return !node;
        }
    private:
        std::shared_ptr<Node> node{nullptr};
};
