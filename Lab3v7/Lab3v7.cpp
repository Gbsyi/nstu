#include <iostream>
#include <queue>

using namespace std;

struct TreeNode
{
    int value;
    TreeNode* left;
    TreeNode* right;
};

void tree_insert_left(TreeNode* node, int value)
{
    auto new_node = TreeNode{
        value,
        nullptr,
        nullptr
    };

    node->left = &new_node;
}

void tree_insert_right(TreeNode* node, int value)
{
    auto new_node = TreeNode{
        value,
        nullptr,
        nullptr
    };

    node->right = &new_node;
}


/**
 * \brief Функция для определения максимальной длины дерева (Обход в глубину)
 * \param node Текущий элемент
 * \return Максимальная длина
 */
int get_max_tree_len(const TreeNode* node)
{
    // Проверяем, является ли текущий узел пустым
    if (node == nullptr)
    {
        // Если узел пуст, возвращаем 0 (базовый случай)
        return 0;
    }

    // Рекурсивно вычисляем максимальную длину левого поддерева
    const auto max_left_len = get_max_tree_len(node->left) + 1;

    // Рекурсивно вычисляем максимальную длину правого поддерева
    const auto max_right_len = get_max_tree_len(node->right) + 1;

    // Возвращаем максимальную длину между левым и правым поддеревьями,
    // сравнивая длины и выбирая большую из них
    return max_left_len > max_right_len
               ? max_left_len
               : max_right_len;
}

void print_Tree(TreeNode* p, int level)
{
    if (p)
    {
        print_Tree(p->left, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->value << endl;
        print_Tree(p->right, level + 1);
    }
}

int main()
{
    auto root = TreeNode{
        1,
        new TreeNode{
            3,
            new TreeNode{
                4,
                nullptr,
                nullptr
            },
            new TreeNode{
                5,
                new TreeNode{
                    8,
                    nullptr,
                    nullptr
                },
                new TreeNode{
                    6,
                    nullptr,
                    nullptr
                }
            }
        },
        new TreeNode{
            2,
            new TreeNode{
                7,
                nullptr,
                nullptr
            },
            nullptr
        }
    };

    cout << "" << get_max_tree_len(&root) << endl;

    print_Tree(&root, 0);

    return 0;
}
