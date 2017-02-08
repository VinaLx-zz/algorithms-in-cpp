#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <algorithm>
#include "BinarySearchTree.hpp"

namespace vinalx {

namespace tree {

template <typename Key>
class AvlTree {
  public:
    struct Node : BinaryNodeBase<Key> {
        Node(const Key& data, Node* left, Node* right)
            : BinaryNodeBase<Key>(data, left, right) {}
        int left_height = 1;
        int right_height = 1;
    };

    void Insert(const Key& key) {
        root_ = Insert(key, root_);
    }
    void Erase(const Key& key);

  private:
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
        if (node->left_height - node->right_height > 1) {
            if (node->left->right_height > node->left->left_height) {
                return DoubleRotateRight(node);
            } else {
                return RotateRight(node);
            }
        } else if (node->right_height - node->left_height > 1) {
            if (node->right->left_height > node->right->right_height) {
                return DoubleRotateLeft(node);
            } else {
                return RotateLeft(node);
            }
        }
        return node;
    }

        Node* root_ = nullptr;
        size_t size_ = 0;
};

}  // namespace tree

}  // namespace vinalx

#endif  // AVL_TREE_HPP_
