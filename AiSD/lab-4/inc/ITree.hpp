#pragma once

#include <memory>

struct ITree {
    virtual ~ITree() = default;

    virtual auto insert(int key) -> void = 0;
    virtual auto remove(int key) -> void = 0;
    virtual auto height() const -> int = 0;

    virtual auto print() const -> void final{
        print(m_root, 0, ' ');
    };

    protected:
        struct Node;
        using NodePtr = std::shared_ptr<Node>;

        struct Node {
            int key;
            NodePtr l{nullptr};
            NodePtr r{nullptr};
            NodePtr p{nullptr};
        };

        NodePtr m_root{nullptr};

    private:
        static auto print(NodePtr root, int depth, char prefix) -> void{};
};


