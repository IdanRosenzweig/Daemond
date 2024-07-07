#ifndef TRIE_H
#define TRIE_H

#include <string>
using namespace std;

template<typename T,
    size_t RANGE, // max number of children
    size_t (*ASSIGN_INDEX)(T val), // function that assigns indexes in the range [0, RANGE) to values
    typename DATA
>
struct trie_node { // a trie node
    bool marked = false;
    trie_node *children[RANGE] = {nullptr};
    size_t child_count = 0;

    DATA data;

    virtual ~trie_node() {
        remove_all_children(this);
    }

    static trie_node *get_child(trie_node *node, T val) {
        if (node == nullptr) return nullptr;
        return node->children[ASSIGN_INDEX(val)];
    }

    static trie_node *create_child(trie_node *node, T val) {
        if (node == nullptr) return nullptr;

        size_t in = ASSIGN_INDEX(val);

        if (node->children[in] != nullptr) return node->children[in]; // child already exists

        node->children[in] = new trie_node;
        ++node->child_count;

        return node->children[in];
    }

    static void remove_child(trie_node *node, T val) {
        if (node == nullptr) return;

        size_t in = ASSIGN_INDEX(val);

        if (node->children[in] == nullptr) return; // no such child

        delete node->children[in]; // deconstructor will call child->remove_all_children()
        node->children[in] = nullptr;
        --node->child_count;
    }

    static void remove_all_children(trie_node *node) {
        if (node == nullptr) return;

        for (size_t i = 0; i < RANGE; i++) {
            trie_node *child = node->children[i];
            if (child == nullptr) return; // child doesn't exists

            delete child; // deconstructor will call child->remove_all_children()
        }
    }

    static trie_node *search(trie_node *node, const basic_string<T> &str) {
        if (node == nullptr) return nullptr;

        trie_node *curr_node = node;
        for (char c: str) {
            trie_node *child = get_child(curr_node, c);
            if (child == nullptr) return nullptr; // word doesn't exists

            curr_node = child;
        }

        return curr_node;
    }

    static trie_node *add_word(trie_node *node, const basic_string<T> &str) {
        if (node == nullptr) return nullptr;
        if (str.empty()) return nullptr;

        trie_node *curr_node = node;
        for (char c: str) {
            trie_node *child = get_child(curr_node, c);
            if (child == nullptr) child = create_child(curr_node, c); // node should be added

            curr_node = child;
        }

        curr_node->marked = true;
        return curr_node;
    }

    static void remove_word(trie_node *node, const basic_string<T> &str) {
        if (node == nullptr) return;
        if (str.empty()) return;

        // we would want to remove the final node representing the entire word,
        // and any other node on the path contributes only to the removed word
        trie_node *lowest_ans_par = node;
        // represents the parent of the lowest ancestor which contributes only to the removed word
        char lowest_ans_val = str[0]; // represents the value that points from lowest_ans_par to our ancestor

        trie_node *curr_node = node;
        for (char c: str) {
            trie_node *child = get_child(curr_node, c);
            if (child == nullptr) return; // word doesn't exists

            if (curr_node->marked || curr_node->child_count > 1) {
                // this node contributes to other words besides ours
                lowest_ans_par = curr_node;
                lowest_ans_val = c;
            }

            curr_node = child;
        }

        if (!curr_node->marked) return; // word doesn't exists

        remove_child(lowest_ans_par, lowest_ans_val); // remove our lowest valid ancestor
    }

    // does the trie contain this word
    static bool contains_word(trie_node *node, const basic_string<T> &str) {
        if (node == nullptr) return false;
        trie_node *word = search(node, str);
        return word != nullptr && word->marked;
    }

    // does the trie contain some word which has this prefix
    static bool is_prefix(trie_node *node, const basic_string<T> &str) {
        if (node == nullptr) return false;
        return search(node, str) != nullptr;
    }

    // does the trie contain some word which is a prefix of str
    static bool contains_prefix(trie_node *node, const basic_string<T> &str) {
        if (node == nullptr) return false;

        trie_node *curr_node = node;
        for (char c: str) {
            trie_node *child = get_child(curr_node, c);
            if (child == nullptr) return false;

            curr_node = child;
            if (curr_node->marked) return true; // prefix exists
        }

        return false;
    }
};



#endif //TRIE_H
