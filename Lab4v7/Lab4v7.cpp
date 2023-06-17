#include <iostream>
#include <fstream>
#include <random>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

/** Функция заполнения файла случайно сгенерироваными числами */
void create_file()
{
    // Открываем файл
    ofstream output;
    output.open("file.bin", ios::out | ios::trunc);

    cout << "Введите количество чисел";

    // Инициализируем генератор
    random_device rd;
    mt19937 generator(rd());
    const std::uniform_int_distribution<int> distribution(-100, 100);


    int n;
    cin >> n;

    // Заполняем файл
    cout << "Содержимое файла: " << endl;
    for (auto i = 0; i < n; i++)
    {
        int random_int = distribution(generator);
        output.write(reinterpret_cast<char*>(&random_int), sizeof(int));
        cout << random_int << " ";
    }

    output.close();
    cout << endl;
}

/** Функция для добавления нового элемента в список */
void insert(Node** head, int data)
{
    auto new_node = new Node();
    new_node->data = data;
    new_node->next = nullptr;

    if (*head == nullptr)
    {
        *head = new_node;
    }
    else
    {
        Node* current = *head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

/** Функция для печати списка */
void print_list(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

/**
 * Функция для освобождения памяти, занятой списком
 * */
void delete_list(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// Функция для разделения списка на положительные и отрицательные числа
void split_list(Node* head, Node** positive_head, Node** negative_head)
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next_node = current->next;
        if (current->data >= 0)
        {
            current->next = *positive_head;
            *positive_head = current;
        }
        else
        {
            current->next = *negative_head;
            *negative_head = current;
        }
        current = next_node;
    }
}

/**
 * \brief Функция для сортировки списка по возрастанию 
 * \param head Начало списка 
 */
void sort_list(Node** head)
{
    if (*head == nullptr || (*head)->next == nullptr)
    {
        return;
    }

    Node* sorted_list = nullptr;
    Node* current = *head;
    while (current != nullptr)
    {
        Node* next_node = current->next;
        Node* sorted_current = sorted_list;
        Node* sorted_prev = nullptr;

        while (sorted_current != nullptr && sorted_current->data < current->data)
        {
            sorted_prev = sorted_current;
            sorted_current = sorted_current->next;
        }

        if (sorted_prev == nullptr)
        {
            current->next = sorted_list;
            sorted_list = current;
        }
        else
        {
            current->next = sorted_current;
            sorted_prev->next = current;
        }

        current = next_node;
    }

    *head = sorted_list;
}

/**
 * \brief Функция чтения файла и разделения на положительные и отрицательные числа
 */
void read_and_separate_file()
{
    std::ifstream input_file("file.bin", std::ios::binary);
    if (!input_file)
    {
        std::cout << "Ошибка открытия файла." << std::endl;
        return;
    }

    Node* positive_head = nullptr;
    Node* negative_head = nullptr;

    int num;
    while (input_file.read(reinterpret_cast<char*>(&num), sizeof(int)))
    {
        // Определяем список для вставки по условию и вставляем число в нужный список
        insert(num >= 0 ? &positive_head : &negative_head, num);
    }

    input_file.close();

    // Сортировка списков
    sort_list(&positive_head);
    sort_list(&negative_head);

    // Вывод списков
    std::cout << "Положительные числа: ";
    print_list(positive_head);

    std::cout << "Отрицательные числа: ";
    print_list(negative_head);

    // Освобождение памяти
    delete_list(positive_head);
    delete_list(negative_head);
}

/**
 * \brief Функция простого чтения файла
 * \return Числа в виде списка
 */
Node* read_file()
{
    Node* head = nullptr;

    std::ifstream input_file("file.bin", std::ios::binary);
    if (!input_file)
    {
        std::cout << "Ошибка открытия файла." << std::endl;
        return nullptr;
    }

    int num;
    while (input_file.read(reinterpret_cast<char*>(&num), sizeof(int)))
    {
        insert(&head, num);
    }

    input_file.close();

    return head;
}


/**
 * \brief Функция чтения файла и вывода содержимого на экран
 */
void read_and_print_file()
{
    auto head = read_file();
    print_list(head);
    delete_list(head);
}

int main()
{
    while (true)
    {
        cout << "Выберите режим работы:" << endl
            << "1 - Сгенерировать новый файл" << endl
            << "2 - Прочитать файл и вывести сначала положительные, затем - отрицательные числа" << endl
            << "3 - Прочитать файл и вывести результат на экран" << endl;

        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            create_file();
            break;
        case 2:
            read_and_separate_file();
            break;
        case 3:
            read_and_print_file();
            break;
        default:
            return 0;
        }
        cout << endl << endl;
    }
}
