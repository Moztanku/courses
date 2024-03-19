template <typename T>
class Queue
{
    public:
        Queue()
        {
            reserve(10);
        };
        ~Queue(){
            delete[] m_data;
        };

        void push(T value)
        {
            if (m_size == m_capacity) {
                bool result = reserve(m_capacity);

                if (!result) {
                    return;
                }
            }

            m_data[m_size++] = value;
        };

        T pop()
        {
            if (m_size == 0)
                return T();

            T value = m_data[0];

            for (size_t i = 0; i < m_size - 1; i++) {
                m_data[i] = m_data[i + 1];
            }

            m_size--;

            return value;
        };

        bool empty() 
        {
            return m_size == 0;
        }

        size_t size() 
        {
            return m_size;
        }

        size_t capacity() 
        {
            return m_capacity;
        }

        bool reserve(size_t size) 
        {
            size_t new_capacity = m_capacity + size;

            T* new_data = new T[new_capacity];

            if (new_data == nullptr) {
                return false;
            }

            for (size_t i = 0; i < m_size; i++) {
                new_data[i] = m_data[i];
            }

            delete[] m_data;

            m_data = new_data;
            m_capacity = new_capacity;

            return true;
        }
    private:
        T* m_data{};

        size_t m_size{};
        size_t m_capacity{};
};  // class Queue
