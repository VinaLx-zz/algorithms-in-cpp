#ifndef TRIE_H_
#define TRIE_H_

#include <cstdint>
#include <memory> // std::unique_ptr
#include <string>
#include <utility> // std::pair

namespace vinalx {

class TRIE {
  private:
    struct Node {
        static constexpr int32_t kCharSize = 256;
        std::unique_ptr<Node> leaves[kCharSize];
        bool flag = false;
        int children = 0;
    };
    std::unique_ptr<Node> root_ = std::make_unique<Node>();
    int size_ = 0;
    static bool Insert(Node *node, const std::string &s, int index) {
        if (index == s.size()) {
            bool ret = not node->flag;
            node->flag = true;
            return ret;
        }
        if (node->leaves[s[index]] == nullptr) {
            node->leaves[s[index]] = std::make_unique<Node>();
            ++node->children;
        }
        return Insert(node->leaves[s[index]].get(), s, index + 1);
    }
    static bool Find(Node *node, const std::string &s, int index) {
        if (index == s.size()) {
            return node->flag;
        }
        if (node->leaves[s[index]] == nullptr) {
            return false;
        }
        return Find(node->leaves[s[index]].get(), s, index + 1);
    }
    static std::pair<bool, bool>
    Erase(Node *node, const std::string &s, int index) {
        if (index == s.size()) {
            bool success = node->flag;
            node->flag = false;
            return {success, node->children == 0};
        }
        if (node->leaves[s[index]] == nullptr) {
            return {false, false};
        }
        auto bs = Erase(node->leaves[s[index]].get(), s, index + 1);
        if (not bs.first) {
            return {false, false};
        }
        if (bs.second) {
            node->leaves[s[index]].reset();
            --node->children;
        }
        return {bs.first, node->children == 0 and not node->flag};
    }

  public:
    void Insert(const std::string &s) {
        if (Insert(root_.get(), s, 0)) {
            ++size_;
        }
    }
    /**
     * @return true if s is deleted, false if s is not found
     */
    bool Erase(const std::string &s) {
        if (Erase(root_.get(), s, 0).first) {
            --size_;
            return true;
        }
        return false;
    }
    bool Find(const std::string &s) const {
        return Find(root_.get(), s, 0);
    }
    int Size() const {
        return size_;
    }
};

} // namespace vinalx

#endif // TRIE_H_