#include <utility>
#include <algorithm>

namespace avl
{

template <typename T>
class AvlTree
{
public:
    AvlTree();
    explicit AvlTree(T key);
    AvlTree(const AvlTree<T> &other);
    AvlTree<T> &operator=(const AvlTree<T> &other);
    ~AvlTree();

    const T *insert(T key);
    const T *find(const T &key) const;
    const T min() const;
    const T max() const;
    void erase(const T &key);
    int size() const;
    int height() const;

private:
    struct Node
    {
        T key;
        int height;
        Node *left{}, *right{}, *parent{};
    };
    Node *root;
    int n;

    Node *insert(Node *node, T key);
    Node *find(Node *node, const T &key) const;
    Node *minNode(Node *node) const;
    Node *nextLarger(Node *node);
    Node *deleteNode(Node *node);
    int getHeight(Node *node) const;
    void updateHeight(Node *node);
    void leftRotate(Node *node);
    void rightRotate(Node *node);
    void rebalance(Node *node);
    void copy(Node **dest, Node *src);
    void deleteSubtree(Node *node);
};

template <typename T>
AvlTree<T>::AvlTree() : root{nullptr}, n{0}
{}

template <typename T>
AvlTree<T>::AvlTree(T key) : n{1}
{
    root = new Node;
    root->key = std::move(key);
    root->height = 0;
}

template <typename T>
AvlTree<T>::AvlTree(const AvlTree<T> &other) : n{other.n}
{
    copy(&root, other.root);
}

template <typename T>
AvlTree<T> &AvlTree<T>::operator=(const AvlTree<T> &other)
{
    if (root != nullptr)
        deleteSubtree(root);
    copy(&root, other.root);
    n = other.n;
    return *this;
}

template <typename T>
AvlTree<T>::~AvlTree()
{
    deleteSubtree(root);
}

template <typename T>
void AvlTree<T>::copy(AvlTree<T>::Node **dest, AvlTree<T>::Node *src)
{
    *dest = new Node{*src};
    (*dest)->parent = nullptr;

    if (src->left != nullptr)
    {
        copy(&(*dest)->left, src->left);
        (*dest)->left->parent = *dest;
    }
    if (src->right != nullptr)
    {
        copy(&(*dest)->right, src->right);
        (*dest)->right->parent = *dest;
    }
}

template <typename T>
void AvlTree<T>::deleteSubtree(AvlTree<T>::Node *node)
{
    if (node->left != nullptr)
        deleteSubtree(node->left);
    if (node->right != nullptr)
        deleteSubtree(node->right);
    if (node->parent != nullptr)
    {
        if (node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
    }
    delete node;
    --n;
}

template <typename T>
const T *AvlTree<T>::insert(T key)
{
    if (root == nullptr)
    {
        root = new Node;
        root->key = std::move(key);
        root->height = 0;
        return &(root->key);
    }
    auto *node = insert(root, std::move(key));
    rebalance(node);
    ++n;
    return &node->key;
}

template <typename T>
const T *AvlTree<T>::find(const T &key) const
{
    auto *node = find(root, key);
    if (node == nullptr)
        return nullptr;
    return &node->key;
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::find(AvlTree<T>::Node *node, const T &key) const
{
    if (key < node->key)
    {
        if (node->left != nullptr)
            return find(node->left, key);
        else
            return nullptr;
    }
    else if (key > node->key)
    {
        if (node->right != nullptr)
            return find(node->right, key);
        else
            return nullptr;
    }
    else // key == node->key
        return node;
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::nextLarger(AvlTree<T>::Node *node)
{
    if (node->right != nullptr)
        return minNode(node->right);
    while ((node->parent != nullptr) && (node == node->parent->right))
        node = node->parent;
    return node->parent;
}

template <typename T>
const T AvlTree<T>::min() const
{
    auto *node = root;
    while (node->left != nullptr)
        node = node->left;
    return node->key;
}

template <typename T>
const T AvlTree<T>::max() const
{
    auto *node = root;
    while (node->right != nullptr)
        node = node->right;
    return node->key;
}

template <typename T>
void AvlTree<T>::erase(const T &key)
{
    auto *node = find(root, key);
    if (node != nullptr)
    {
        auto *temp = deleteNode(node);
        if (temp != nullptr)
            rebalance(temp);
    }
}

template <typename T>
int AvlTree<T>::size() const
{
    return n;
}

template <typename T>
int AvlTree<T>::height() const
{
    return getHeight(root) + 1;
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::insert(AvlTree::Node *node, T key)
{
    if (key < node->key)
    {
        if (node->left == nullptr)
        {
            node->left = new Node;
            node->left->key = std::move(key);
            node->left->parent = node;
            return node->left;
        }
        else
            return insert(node->left, std::move(key));
    }
    else
    {
        if (node->right == nullptr)
        {
            node->right = new Node;
            node->right->key = std::move(key);
            node->right->parent = node;
            return node->right;
        }
        else
            return insert(node->right, std::move(key));
    }
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::minNode(AvlTree<T>::Node *node) const
{
    auto *minimum = node;
    while (minimum->left != nullptr)
        minimum = minimum->left;
    return minimum;
}

template <typename T>
int AvlTree<T>::getHeight(AvlTree<T>::Node *node) const
{
    return node != nullptr ? node->height : -1;
}

template <typename T>
void AvlTree<T>::updateHeight(AvlTree<T>::Node *node)
{
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <typename T>
void AvlTree<T>::leftRotate(AvlTree<T>::Node *node)
{
    auto *temp = node->right;
    temp->parent = node->parent;
    if (node->parent == nullptr)
        this->root = temp;
    else
    {
        if (node->parent->left == node)
            node->parent->left = temp;
        else
            node->parent->right = temp;
    }

    node->right = temp->left;
    if (node->right != nullptr)
        node->right->parent = node;
    
    temp->left = node;
    node->parent = temp;

    updateHeight(node);
    updateHeight(temp);
}

template <typename T>
void AvlTree<T>::rightRotate(AvlTree<T>::Node *node)
{
    auto *temp = node->left;
    temp->parent = node->parent;
    if (node->parent == nullptr)
        this->root = temp;
    else
    {
        if (node->parent->left == node)
            node->parent->left = temp;
        else
            node->parent->right = temp;
    }

    node->left = temp->right;
    if (node->left != nullptr)
        node->left->parent = node;
    
    temp->right = node;
    node->parent = temp;

    updateHeight(node);
    updateHeight(temp);
}

template <typename T>
void AvlTree<T>::rebalance(AvlTree<T>::Node *node)
{
    do
    {
        updateHeight(node);
        if (getHeight(node->left) > getHeight(node->right) + 1)
        {
            if (getHeight(node->left->left) >= getHeight(node->left->right))
                rightRotate(node);
            else
            {
                leftRotate(node->left);
                rightRotate(node);
            }
        }
        else if (getHeight(node->right) > getHeight(node->left) + 1)
        {
            if (getHeight(node->right->right) >= getHeight(node->right->left))
                leftRotate(node);
            else
            {
                rightRotate(node->right);
                leftRotate(node);
            }
        }
        node = node->parent;
    }
    while(node != nullptr);
}

template<typename T>
typename AvlTree<T>::Node *AvlTree<T>::deleteNode(AvlTree<T>::Node *node)
{
    Node *temp;
    if ((node->left != nullptr) && (node->right == nullptr))
        temp = node->left;
    else if ((node->left == nullptr) && (node->right != nullptr))
        temp = node->right;
    else if ((node->left == nullptr) && (node->right == nullptr))
    {
        temp = node->parent;
        deleteSubtree(node);
        return temp;
    }
    else
    {
        temp = nextLarger(node);
        std::swap(node->key, temp->key);
        return deleteNode(temp);
    }

    temp->parent = node->parent;
    if (temp->parent != nullptr)
    {
        if (node->parent->left == node)
            temp->parent->left = temp;
        else
            temp->parent->right = temp;
    }
    else
        root = temp;
    
    temp = node->parent;
    delete node;
    --n;
    return temp;
}

} // namespace avl
