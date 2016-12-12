/**
 *
 */
#ifndef BINARY_SEARCH_TREE_HPP_
#define BINARY_SEARCH_TREE_HPP_

#include <stddef.h>

namespace vinalx {

namespace tree {

template <typename Key>
struct BinaryNodeBase {
    BinaryNodeBase(
        const Key& data, BinaryNodeBase* left = nullptr,
        BinaryNodeBase* right = nullptr)
        : left(left), right(right), data(data) {}

    BinaryNodeBase *left, *right;
    Key data;
};

template <typename Key>
class BinarySearchTree {
  public:
    struct Node : public BinaryNodeBase<Key> {
        Node(const Key& data, Node* left, Node* right)
            : BinaryNodeBase<Key>(data, left, right) {}
    };

    ~BinarySearchTree() {
        Clear(root_);
    }

    /**
     * insert a key into the tree
     */
    void Insert(const Key& key) {
        root_ = Insert(key, root_);
    }

    /**
     * erase a key from the tree
     */
    void Erase(const Key& key) {
        root_ = Erase(key, root_);
    }

    /**
     * determine whether the tree has a key
     * @return true if the tree has the key
     */
    bool Has(const Key& key) const {
        return Has(key, root_);
    }

    /**
     * clear the whole tree
     */
    void Clear() {
        Clear(root_);
        root_ = nullptr;
    }

    /**
     * number of keys in the tree
     */
    size_t Size() const {
        return size_;
    }

  private:
    /**
     * helper for clear
     */
    void Clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        Clear(node->left);
        Clear(node->right);
        delete node;
    }
    /**
     * helper function of insert;
     */
    Node* Insert(const Key& key, Node* root) {
        if (root == nullptr) {
            ++size_;
            return new Node(key);
        }
        if (key < root->data) {
            root->left = Insert(key, root->left);
        } else if (key > root->data) {
            root->right = Insert(key, root->right);
        }
        return root;
    }

    bool Has(const Key& key, Node* root) const {
        if (root == nullptr) {
            return false;
        }
        if (key < root->value) {
            return Has(key, root->left);
        }
        if (key > root->value) {
            return Has(key, root->right);
        }
        return true;
    }

    Node* Erase(const Key& key, Node* root) {
        if (root == nullptr) {
            return nullptr;
        }
        // recursively erase
        if (key < root->data) {
            root->left = Erase(key, root->left);
        } else if (key > root->data) {
            root->right = Erase(key, root->right);
        }

        // erase current node
        
        Node *temp = root;
        // connect child to the root if either is nullptr
        if (root->left == nullptr) {
            root = root->right;
        } else if (root->right == nullptr) {
            root = root->left;
        } else if (root->left->right == nullptr) {
            // if left child is the max
            root->left->right = root->right;
            root = root->left;
        } else {
            Node *max_in_left;
            root->left = GetMax(root->left, &max_in_left);
            max_in_left->left = root->left;
            max_in_left->right = root->right;
            root = max_in_left;
        }
        delete temp;
        return root;
    }

    Node *GetMax(Node *node, Node **result) {
        if (node->right == nullptr) {
            *result = node;
            return node->left;
        }
        node->right = GetMax(node->right, result);
        return node;
    }

    Node* root_ = nullptr;
    size_t size_ = 0;
};

}  // namespace tree

}  // namespace vinalx

#endif  // BINARY_SEARCH_TREE_HPP_
