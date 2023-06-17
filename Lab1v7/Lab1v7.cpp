#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool has_item_in_vec(vector<int> vector, int value)
{
    for (auto i = 0; i < vector.size(); i++)
    {
        if (value == vector[i])
        {
            return true;
        }
    }
    
    return false;
}

vector<int> get_max_sequence(vector<string>& words, vector<int> used)
{
    vector<int> max_sequence = used;
    auto last_word_index =  used.back();
    auto last_word = words[last_word_index];

    for (auto i = 0; i < words.size(); i++)
    {
        // Если слово использовалось ранее - пропускаем его
        if (has_item_in_vec(used, i))
        {
            continue;
        }
        
        // Проверяем, подходит ли слово в качестве продолжения кроссворда
        if (words[i].front() == last_word.back())
        {
            
            auto sequence = vector<int>(used);
            sequence.push_back(i);
            // Находим максимальную длину для оставшейся последовательности
            auto max_length = get_max_sequence(words, sequence);
            if (max_sequence.size() < max_length.size())
            {
                max_sequence = max_length;
            }
        }
    }

    return max_sequence;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    int n;
    cout << "Введите количество слов: ";
    cin >> n;

    vector<string> words(n);
    cout << "Введите слова: ";
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    auto max_count = vector<int> {};

    for (auto i = 0; i < n; i++)
    {
        vector<int> used = {i}; 
        auto count = get_max_sequence(words, used);
        if (count.size() > max_count.size())
        {
            max_count = count;
        }
    }

    cout << "Максимальная длина возможного кроссворда: " << max_count.size() << endl;

    for (int i : max_count)
    {
        cout << words[i] << " ";
    }
    
    return 0;
}