#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node* prev;
    Node* next;
};  // struct Node

template <typename T>
class List
{
    public:
        List() = default;
        ~List()
        {

        }

        void insert(T value)
        {
            Node<T>* node = new Node<T>{};

            if (node == nullptr)
                return;

            node->data = value;

            if (m_tail == nullptr)
            {
                m_tail = node;
                m_tail->next = m_tail;
                m_tail->prev = m_tail;
            }

            Node<T>* temp = m_tail->prev;

            node->next = m_tail;
            node->prev = temp;

            m_tail->prev = node;
            temp->next = node;

            m_size++;
        }

        size_t size() const
        {
            return m_size;
        }

        T& operator[](size_t index)
        {
            return 
                index < 0 ? searchBackward(index) :
                index > m_size ? searchForward(index) :
                index < m_size / 2 ? searchForward(index) :
                    searchBackward(index);
        }

        friend void insert(List<T>& list, T value)
        {
            list.insert(value);
        }

        friend void merge(List<T>& list1, List<T>& list2)
        {
            if (list2.m_tail == nullptr)
                return;

            Node<T>* tail = list2.m_tail;
            Node<T>* head = list2.m_tail->prev;
            size_t size = list2.m_size;

            list2.m_tail = nullptr;
            list2.m_size = 0;

            list1.getHead()->next = tail;
            list1.m_tail->prev = head;

            tail->prev = list1.getHead();
            head->next = list1.m_tail;

            list1.m_size += size;
        }
    private:
        Node<T>* m_tail{};
        size_t m_size{};

        Node<T>* getHead()
        {
            return m_tail->prev;
        }

        T& searchForward(size_t index)
        {
            static size_t last = 0;
            static Node<T>* current = m_tail;

            if (index < last)
            {
                current = m_tail;
                last = 0;
            }

            for (size_t i = last; i < index; i++)
                current = current->next;

            last = index % m_size;
            return current->data;
        }

        T& searchBackward(size_t index)
        {
            static size_t last = m_size - 1;
            static Node<T>* current = m_tail->prev;

            if (index > last)
            {
                current = m_tail->prev;
                last = m_size - 1;
            }

            for (size_t i = last; i > index; i--){
                current = current->prev;
            }

            last = index % m_size;

            return current->data;
        }
};  // class List