#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

Node* createNode(int data)
{
    auto newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

void insertAtEnd(Node*& head, int data)
{
    if (head == nullptr)
    {
        head = createNode(data);
    }
    else
    {
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = createNode(data);
    }
}

/**
 * \brief
 * Функция нахождения максимального элемента списка
 * \param head Указатель на начало списка
 * \return Максимальный элемент списка
 */
Node* findMaxElement(Node* head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node* maxNode = head;
    Node* temp = head->next;
    // Проходим по списку
    while (temp != nullptr)
    {
        // Сравниваем максимальный элемент с текущим
        if (temp->data > maxNode->data)
        {
            maxNode = temp;
        }
        temp = temp->next;
    }
    return maxNode;
}

/**
 * \brief
 * Функция вставки L2 в список L1 после первого вхождения элемента E
 * \return Длина итогового списка
 */
int insertAfterFirstOccurrence(Node*& L1, int E, Node* L2)
{
    int length = 0;
    Node* temp = L1;
    Node* tempAfterE = L1;
    // Проходим по списку L1 пока не дойдём до конца или не встретим элемент E
    while (temp != nullptr && temp->data != E)
    {
        length++;
        temp = temp->next;
        tempAfterE = tempAfterE->next;
    }

    // Если элемент найден
    if (temp != nullptr)
    {
        // Сохраняем указатель на продолжение списка после E
        tempAfterE = tempAfterE->next;
        // Прикрепляем список L2 к элементу списка со значением E
        temp->next = L2;
        // Доходим до конца получившегося списка
        while (temp->next != nullptr)
        {
            length++;
            temp = temp->next;
        }
        // Прикрепляем продолжение списка L1 после элемента E
        temp->next = tempAfterE;
    }
    else
    {
        cout << "Элемент E со значением " << E << " не найден в списке L1" << endl;
    }

    // Доходим до конца списка и заканчиваем подсчёт длины
    while (temp != nullptr)
    {
        length++;
        temp = temp->next;
    }
    return length;
}

void print_list(Node* head)
{
    Node* temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void clearList(Node*& head)
{
    Node* temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    Node* L1 = nullptr;
    Node* L2 = nullptr;

    // Ввод списков с клавиатуры
    int n1, n2, value;
    cout << "Введите количество элементов списка L1: ";
    cin >> n1;
    cout << "Введите элементы списка L1: ";
    for (int i = 0; i < n1; i++)
    {
        cin >> value;
        insertAtEnd(L1, value);
    }

    cout << "Введите количество элементов списка L2: ";
    cin >> n2;
    cout << "Введите элементы списка L2: ";
    for (int i = 0; i < n2; i++)
    {
        cin >> value;
        insertAtEnd(L2, value);
    }

    // Найти максимальный элемент списка, вернуть адрес
    Node* maxNode = findMaxElement(L1);
    if (maxNode != nullptr)
    {
        cout << "Максимальный элемент списка L1: " << maxNode->data << ", адрес: " << maxNode << endl;
    }
    else
    {
        cout << "Список L1 пуст." << endl;
    }

    // Добавить в список L1 за первым вхождением элемента E все элементы списка L2, вернуть длину нового списка
    int E;
    cout << "Введите элемент E: ";
    cin >> E;
    int newLength = insertAfterFirstOccurrence(L1, E, L2);
    cout << "Итоговый список L1:" << endl;
    print_list(L1);
    cout << "Длина нового списка L1: " << newLength << endl;

    // Очистка списков L1 и L2 (тк в списке L1 находится L2, то отдельно L2 не нужно очищать)
    clearList(L1);

    return 0;
}
