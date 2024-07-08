#ifndef MANAGER_H
#define MANAGER_H

#include "src/abstract/unit/loaded_unit.h"
#include "lib/trie.h"

#include <stack>
#include <memory>
#include <iostream>
using namespace std;

class manager {
protected:
    // the slots for units
    vector<unique_ptr<loaded_unit> > units;

private:
    stack<size_t> free_indexes;

    size_t generate_free_index() noexcept;

    // mapping unit's identifiers to their corresponding slot indexes
    class mapper {
        static constexpr auto assign = [](char c) -> size_t { return c - 'a'; };
        using map = trie_node<char, 26, assign, size_t>;
        map mappings;

    public:
        void add(const unit_id &path, size_t index)noexcept;

        bool exists(const unit_id &path)noexcept;

        size_t search(const unit_id &path);

        void remove(const unit_id &path)noexcept;
    } mapper;

protected:
    virtual void _start_unit_at_index(size_t in) = 0;

    virtual void _stop_unit_at_index(size_t in) = 0;

public:

    void load_unit(const unit_data &static_data)noexcept;

    void unload_unit(const unit_id &id) noexcept;

    bool unit_exists(const unit_id &id)noexcept;

    const loaded_unit& search_unit(const unit_id& id);

    void start_unit(const unit_id &id)noexcept;

    void stop_unit(const unit_id &id)noexcept;

    virtual ~manager();
};


#endif //MANAGER_H
