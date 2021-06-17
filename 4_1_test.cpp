#include <iostream>
#include <queue>
using std::cin;
using std::cout;
using std::endl;
using std::queue;

/*
4_1. Солдаты.
В одной военной части решили построить в одну шеренгу по росту.
Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие.
За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.

Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.

Требования: скорость выполнения команды - O(log n).
*/

class CompareElements
{
public:
    CompareElements() {}
    const bool operator()(const int& a, const int& b);
};

const bool CompareElements::operator()(const int& a, const int& b)
{
    return a > b;
}

template<class T>
struct Node
{
    T key;
    int height;
    Node<T>* right;
    Node<T>* left;
    explicit Node(const T& _key);
};

template<class T, class Comparator>
class AVLTree
{
public:
    explicit AVLTree();
    AVLTree(const AVLTree& _tree) = delete;
    AVLTree& operator=(const AVLTree& _tree) = delete;
    ~AVLTree();

    int Insert(const T& key);
    void Delete(int position);

private:

    Comparator compare;
    Node<T>* root;

    int height(Node<T>* node) const;
    int balanceFactor(Node<T>* node) const;
    void fixHeight(Node<T>* node);

    Node<T>* rotateRight(Node<T>* node);
    Node<T>* rotateLeft(Node<T>* node);
    Node<T>* balance(Node<T>* node);
    Node<T>* removeMin(Node<T>* node, Node<T>** foundNode);
    Node<T>* remove(Node<T>* node, int& position);
    void insert(Node<T>*& node, const T& key, int& position);
};

template<class T, class Comparator>
AVLTree<T, Comparator>::AVLTree() : root(nullptr) {}

template<class T, class Comparator>
AVLTree<T, Comparator>::~AVLTree()
{
    if (root == nullptr)
    {
        return;
    }
    queue<Node<T>*> elements;
    elements.push(root);
    while (!elements.empty())
    {
        Node<T>* node = elements.front();
        elements.pop();
        if (node->right != nullptr)
        {
            elements.push(node->right);
        }
        if (node->left != nullptr)
        {
            elements.push(node->left);
        }
        delete node;
    }
}

template<class T, class Comparator>
int AVLTree<T, Comparator>::Insert(const T& key)
{
    int position = 0;
    insert(root, key, position);
    return height(root) - position - 1;
}

template<class T, class Comparator>
void AVLTree<T, Comparator>::Delete(int position)
{
    position = height(root) - position - 1;
    root = remove(root, position);
}

template<class T, class Comparator>
int AVLTree<T, Comparator>::height(Node<T>* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

template<class T, class Comparator>
int AVLTree<T, Comparator>::balanceFactor(Node<T>* node) const
{
    return height(node->right) - height(node->left);
}

template<class T, class Comparator>
void AVLTree<T, Comparator>::fixHeight(Node<T>* node)
{
    node->height = height(node->right) + height(node->left) + 1;
}

template<class T, class Comparator>
Node<T>* AVLTree<T, Comparator>::rotateRight(Node<T>* node)
{
    Node<T>* nodeLeft = node->left;
    node->left = nodeLeft->right;
    nodeLeft->right = node;
    fixHeight(node);
    fixHeight(nodeLeft);
    return nodeLeft;
}

template<class T, class Comparator>
Node<T>* AVLTree<T, Comparator>::rotateLeft(Node<T>* node)
{
    Node<T>* nodeRight = node->right;
    node->right = nodeRight->left;
    nodeRight->left = node;
    fixHeight(node);
    fixHeight(nodeRight);
    return nodeRight;
}

template<class T, class Comparator>
Node<T>* AVLTree<T, Comparator>::balance(Node<T>* node)
{
    fixHeight(node);

    if (balanceFactor(node) == 2)
    {
        if (balanceFactor(node->right) < 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    if (balanceFactor(node) == -2)
    {
        if (balanceFactor(node->left) > 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    return node;
}

template<class T, class Comparator>
void AVLTree<T, Comparator>::insert(Node<T>*& node, const T& key, int& position)
{
    if (node == nullptr)
    {
        node = new Node<T>(key);
        return;
    }
    if (key == node->key || compare(key, node->key))
    {
        position += height(node) - height(node->right);
        insert(node->right, key, position);
    }
    else
    {
        insert(node->left, key, position);
    }
    node = balance(node);
}

template<class T, class Comparator>
Node<T>* AVLTree<T, Comparator>::removeMin(Node<T>* node, Node<T>** foundNode)
{
    if (node->left == nullptr)
    {
        *foundNode = node;
        return node->right;
    }
    node->left = removeMin(node->left, foundNode);
    return balance(node);
}

template<class T, class Comparator>
Node<T>* AVLTree<T, Comparator>::remove(Node<T>* node, int& position)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (!compare(position, height(node->left)) && position != height(node->left))
    {
        node->left = remove(node->left, position);
    }
    else if (compare(position, height(node->left)))
    {
        position -= (height(node->left) + 1);
        node->right = remove(node->right, position);
    }
    else
    {
        Node<T>* left = node->left;
        Node<T>* right = node->right;
        delete node;
        if (!right) return left;

        Node<T>* tmpNode;
        Node<T>* tmpSideNode = removeMin(right, &tmpNode);
        tmpNode->right = tmpSideNode;
        tmpNode->left = left;
        return balance(tmpNode);
    }
    return balance(node);
}

template<class T>
Node<T>::Node(const T& _key) : key(_key), right(nullptr), left(nullptr), height(1) {}

enum Command
{
    ADD = 1,
    DEL = 2
};

int main()
{
    AVLTree<int, CompareElements> tree;

    int n = 0;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int command = 0, value = 0;

        cin >> command >> value;

        switch (command)
        {
        case ADD:
            cout << tree.Insert(value) << endl;
            break;
        case DEL:
            tree.Delete(value);
            break;
        }
    }

    return 0;
}