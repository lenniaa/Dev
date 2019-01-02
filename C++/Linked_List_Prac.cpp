#include <iostream>

/**
 *  * 필요할 때마다 Node를 생성해 데이터를 저장하고 이들을 서로 연결한다.
 *  * Good_Notes -> 낙서 p.27
 *  TODO search function implement
 */

using namespace std;

template <typename T>
class Link;

template <typename T>
class Node
{
    friend class Link<T>;

    Node()
    {
        next = nullptr;
        data = -1; // 기본 초기화 값
    }

  private:
    T data;
    Node *next;
};

template <typename T>
class Link
{
  public:
    void printNode()
    {
        print(head->next);
        cout << endl;
    }

    bool isEmpty()
    {
        if (head->next == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void insert(T val)
    {
        insertNode(val);
    }

    void deleteNode(T val)
    {
        Node<T> *temp = head->next;
        Node<T> *prev = nullptr;
        while (temp->data != val)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == head->next)
        {
            // 가장 앞에 노드를 삭제하는 경우
            head->next = temp->next;
        }
        else if (temp == tail->next)
        {
            //가장 마지막 노드를 삭제하는 경우
            tail->next = prev;
            prev->next = nullptr; // 삭제한 노드의 이전노드의 포인터 변수를 null로 초기화 해줘야함 그렇게 하지 않으면 쓰레기값을 가리키게 되어 print시 쓰레기값 출력
        }
        else
        {
            prev->next = temp->next;
        }

        cout << temp->data << " deleted" << endl;
        delete temp;
        Count--;
    }

    int size()
    {
        return Count;
    }

    Link()
    {
        head->next = nullptr;
        tail->next = nullptr;
    }

    // TODO check this to exactly active
    ~Link()
    {
        Node<T> *temp = head;
        while (temp->next != nullptr)
        {
            Node<T> *temp1 = temp->next;
            delete temp;
            temp = temp1->next;
        }
        delete tail;
    }

  private:
    Node<T> *head = new Node<T>();
    Node<T> *tail = new Node<T>();
    int Count;

    void print(Node<T> *current)
    {
        while (current->next != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << current->data << " ";
    }

    void insertNode(T data)
    {
        // Node<T> *temp = getHead()->next; // temp : 제일 첫번째 값이 들어가있는 노드
        Node<T> *temp = head;

        //  다음을 가리키는 포인터가 비어있는 노드를 반복문을 돌며 찾는다
        while (temp->next != nullptr)
        {
            temp = temp->next;
            Count++;
        }

        Node<T> *newNode = new Node<T>();
        newNode->data = data;
        temp->next = newNode;
        tail->next = newNode;
    }
};

int main(int argc, char const *argv[])
{
    Link<int> *link = new Link<int>();

    link->insert(8);
    link->insert(9);
    link->insert(10);

    cout << "Value in List : ";
    link->printNode();

    cout << "List Size : " << link->size() << endl;
    link->isEmpty();

    link->deleteNode(9);
    cout << link->size() << endl;
    link->printNode();
    return 0;
}