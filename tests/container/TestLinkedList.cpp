

typedef struct Node
{
    int m_data;
    Node *m_next;
}Node;


class LinkedList
{

public:

    //LinkedList() = default;
    ~LinkedList() = default;

    LinkedList()
    {
        m_current->m_data = 0;
        m_current = nullptr;
    }


    void Insert(int value)
    {
        m_current->m_data = value;
        m_current = m_current->m_next;
    }

    //decltype(m_current->m_data)
    int Last()
    {
        if (m_current)
        {
            //std::throw("");
            return 0;
        }
        return m_current->m_data;
    }

private:

    Node *m_current;


};



