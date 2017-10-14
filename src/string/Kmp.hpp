#ifndef KMP_H_
#define KMP_H_

#include <cstdint>
#include <string>
#include <vector>

namespace vinalx {

class Kmp {
  private:
    /**
     * match table of the pattern
     */
    std::vector<int64_t> table_;

    /**
     * build the match table for the pattern
     * @param pattern the pattern string
     */
    void BuildTable(const std::string &pattern) {
        table_ = std::vector<int64_t>(pattern.size());
        table_[0] = -1;
        table_[1] = 0;
        for (size_t substr_size(0), position(2); position < pattern.size();) {
            if (pattern[position - 1] == pattern[substr_size]) {
                table_[position++] = ++substr_size;
            } else if (substr_size > 0) { // try to find the previous substring
                substr_size = table_[substr_size];
            } else {
                table_[position++] = 0; // next one
            }
        }
    }

    /**
     * do the search according to the table
     * @param text    the text string
     * @param pattern the pattern string
     * @return index where the match start, string::npos if not found
     */
    size_t Search(const std::string &text, const std::string &pattern) {
        size_t text_pos(0), pattern_pos(0);
        for (; text_pos + pattern_pos < text.size();) {
            if (pattern[pattern_pos] == text[text_pos + pattern_pos]) {
                if (pattern_pos == pattern.size() - 1) {
                    return text_pos;
                }
                ++pattern_pos;
            } else if (pattern_pos != 0) {
                text_pos = text_pos + pattern_pos - table_[pattern_pos];
                pattern_pos = table_[pattern_pos];
            } else {
                ++text_pos;
            }
        }
        return std::string::npos;
    }

  public:
    /**
     * search for the pattern in the text
     * @param text    the text string
     * @param pattern the pattern string
     * @return index where the match start, string::npos if not found
     */
    size_t Find(const std::string &text, const std::string &pattern) {
        if (pattern.empty() or text.empty()) {
            return std::string::npos;
        } else if (pattern.size() == 1) {
            return text.find(pattern[0]);
        }
        BuildTable(pattern);
        return Search(text, pattern);
    }
}; // Kmp

} // namespace vinalx

#endif // KMP_H_
