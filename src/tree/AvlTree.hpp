#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <algorithm>

namespace vinalx {

namespace tree {

template <typename Key>
class AvlTree {
  public:
    struct Node {
        Node(const Key& data, Node* left = nullptr, Node* right = nullptr)
            : left(left), right(right), data(data) {}
        Node *left, *right;
        Key data;
        int left_height = 1;
        int right_height = 1;
    };

    ~AvlTree() {
        Clear(root_);
    }

    void Insert(const Key& key) {
        root_ = Insert(key, root_);
    }

    void Erase(const Key& key) {
        root_ = Erase(root_, key);
    }

    size_t Size() const {
        return size_;
    }

    bool Has(const Key& key) const {
        return Has(root_, key);
    }

    template <typename Func>
    void InorderTraverse(Func f) const {
        InorderTraverse(root_, f);
    }

    void Clear() {
        Clear(root_);
        root_ = nullptr;
        size_ = 0;
    }

  private:
    bool Has(Node* node, const Key& key) const {
        if (node == nullptr) {
            return false;
        }
        if (key < node->data) {
            return Has(node->left, key);
        }
        if (key > node->data) {
            return Has(node->right, key);
        }
        return true;
    }

    template <typename Func>
    void InorderTraverse(Node* node, Func f) const {
        if (node == nullptr) {
            return;
        }
        InorderTraverse(node->left, f);
        f(node->data);
        InorderTraverse(node->right, f);
    }

    Node* Insert(const Key& key, Node* node) {
        if (node == nullptr) {
            ++size_;
            return new Node(key);
        }
        if (key < node->data) {
            node->left = Insert(key, node->left);
        } else if (key > node->data) {
            node->right = Insert(key, node->right);
        } else {
            return node;
        }
        return Rebalance(node);
    }

    Node* Erase(Node* node, const Key& key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->data) {
            node->left = Erase(node->left, key);
            return Rebalance(node);
        } else if (key > node->data) {
            node->right = Erase(node->right, key);
            return Rebalance(node);
        }

        Node* temp = node;

        if (node->left == nullptr) {
            node = node->right;
        } else if (node->right == nullptr) {
            node = node->left;
        } else if (node->left->right == nullptr) {
            node->left->right = node->right;
            node->left->right_height = HeightOf(node->right) + 1;
            node = node->left;
        } else {
            Node* max_in_left = nullptr;
            node->left = GetMax(node->left, &max_in_left);
            max_in_left->left = node->left;
            max_in_left->right = node->right;
            node = max_in_left;
        }
        delete temp;
        --size_;
        return Rebalance(node);
    }

    Node* Rebalance(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        node->left_height = HeightOf(node->left) + 1;
        node->right_height = HeightOf(node->right) + 1;
        if (node->left_height - node->right_height > 1) {
            if (node->left->right_height > node->left->left_height) {
                return DoubleRotateRight(node);
            } else {
                return RotateRight(node);
            }
        }
        if (node->right_height - node->left_height > 1) {
            if (node->right->left_height > node->right->right_height) {
                return DoubleRotateLeft(node);
            } else {
                return RotateLeft(node);
            }
        }
        return node;
    }

    int HeightOf(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return std::max(node->left_height, node->right_height);
    }

    Node* RotateLeft(Node* node) {
        Node* new_root = node->right;

        node->right = new_root->left;
        node->right_height = HeightOf(node->right) + 1;

        new_root->left = node;
        new_root->left_height = HeightOf(node) + 1;

        return new_root;
    }

    Node* RotateRight(Node* node) {
        Node* new_root = node->left;

        node->left = new_root->right;
        node->left_height = HeightOf(node->left) + 1;

        new_root->right = node;
        new_root->right_height = HeightOf(node) + 1;

        return new_root;
    }

    Node* DoubleRotateLeft(Node* node) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }

    Node* DoubleRotateRight(Node* node) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    Node* GetMax(Node* node, Node** result) {
        if (node->right == nullptr) {
            *result = node;
            return node->left;
        }
        node->right = GetMax(node->right, result);
        return Rebalance(node);
    }

    void Clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        Clear(node->left);
        Clear(node->right);
        delete node;
    }

    Node* root_ = nullptr;
    size_t size_ = 0;
};

}  // namespace tree

}  // namespace vinalx

#endif  // AVL_TREE_HPP_
