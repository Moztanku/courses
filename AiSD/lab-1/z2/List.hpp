template <typename T>
struct Node
{
    T data;
    Node* next;
};   // struct Node

template <typename T>
class List
{
    public:
        List() = default;
        ~List()
        {
            Node<T>* current = m_tail;
            
            for (size_t i = 0; i < m_size; i++)
            {
                Node<T>* next = current->next;
                delete current;
                current = next;
            }
        }

        void insert(T value)
        {
            Node<T>* node = new Node<T>{value, m_tail};

            if (node == nullptr)
                return;

            if (m_tail == nullptr)
                m_tail = node;

            getHead()->next = node;

            m_size++;
        }

        size_t size() const
        {
            return m_size;
        }

        T& operator[](size_t index)
        {
            static size_t last = 0;
            static Node<T>* current = m_tail;

            if (index < last){
                current = m_tail;
                last = 0;
            }

            for (size_t i = last; i < index; i++)
                current = current->next;

            last = index;
            return current->data;
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
            Node<T>* head = list2.getHead();
            size_t size = list2.m_size;

            list2.m_tail = nullptr;
            list2.m_size = 0;

            list1.getHead()->next = tail;
            head->next = list1.m_tail;

            list1.m_size += size;
        }
    private:
        Node<T>* m_tail{};
        size_t m_size{};

        Node<T>* getHead()
        {
            Node<T>* current = m_tail;

            for (size_t i = 1; i < m_size; i++)
                current = current->next;

            return current;
        }
};   // class List
