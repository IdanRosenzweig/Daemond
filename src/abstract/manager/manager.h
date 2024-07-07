#ifndef MANAGER_H
#define MANAGER_H

#include "loaded_unit.h"
#include "../../../lib/trie.h"

#include <stack>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

class manager {
protected:
    // the slots for units
    vector<unique_ptr<loaded_unit> > units;

private:
    stack<size_t> free_indexes;

    size_t generate_free_index() {
        size_t in;
        if (!free_indexes.empty()) {
            in = free_indexes.top();
            free_indexes.pop();
        } else {
            in = units.size();
            units.push_back(nullptr);
        }
        return in;
    }

    // mapping unit's identifiers to their corresponding slot indexes
    class mapper {
        static constexpr auto assign = [](char c) -> size_t { return c - 'a'; };
        using map = trie_node<char, 26, assign, size_t>;
        map mappings;

    public:
        void add(const unit_id &path, size_t index) {
            if (exists(path)) return;
            map::add_word(&mappings, path.name)->data = index;
        }

        bool exists(const unit_id &path) {
            return map::contains_word(&mappings, path.name);
        }

        size_t search(const unit_id &path) {
            if (!exists(path)) throw "path not found";
            return map::search(&mappings, path.name)->data;
        }

        void remove(const unit_id &path) {
            if (!exists(path)) return;
            map::remove_word(&mappings, path.name);
        }
    } mapper;

protected:
    virtual void _start_unit_at_index(size_t in) = 0;

    virtual void _stop_unit_at_index(size_t in) = 0;

public:
    void load_unit(const unit_data &static_data) {
        if (unit_exists(static_data.id)) {
            cerr << "unit is already loaded" << endl;
            return;
        }

        unique_ptr<loaded_unit> ptr(factory_generate_unit());
        ptr->data = static_data;
        ptr->runtime = {NOT_RUNNING};

        size_t in = generate_free_index();

        units[in] = std::move(ptr);
        mapper.add(static_data.id, in);

        // special attributes
        if (units[in]->data.attr.autostart_on_load) {
            _start_unit_at_index(in);
        }
    }

    void unload_unit(const unit_id &id) {
        if (!mapper.exists(id)) {
            cerr << "can't find the requested unit to unload" << endl;
            return;
        }

        size_t in = mapper.search(id);

        _stop_unit_at_index(in);

        units[in] = nullptr;
        mapper.remove(id);
        free_indexes.push(in);
    }

    bool unit_exists(const unit_id &id) {
        return mapper.exists(id);
    }

    const loaded_unit& search_unit(const unit_id& id) {
        if (!unit_exists(id)) throw "no such unit";
        return *units[mapper.search(id)];
    }

    void start_unit(const unit_id &id) {
        if (!mapper.exists(id)) {
            cerr << "can't find the requested unit to start" << endl;
            return;
        }

        size_t in = mapper.search(id);

        switch (units[in]->runtime.status) {
            case NOT_RUNNING: {
                _start_unit_at_index(in);
                break;
            }
            case RUNNING: {
                cerr << "unit is already running" << endl;
                break;
            }
        }
    }

    void stop_unit(const unit_id &id) {
        if (!mapper.exists(id)) {
            cerr << "can't find the requested unit to stop" << endl;
            return;
        }

        size_t in = mapper.search(id);

        switch (units[in]->runtime.status) {
            case RUNNING: {
                _stop_unit_at_index(in);
                break;
            }
            default: {
                cerr << "unit is not running" << endl;
                break;
            }
        }
    }


    virtual ~manager() {
        for (size_t in = 0; in < units.size(); in++) {
            if (units[in] == nullptr) continue;
            // stop_unit(in);
            units[in] = nullptr;
        }
    }
};


#endif //MANAGER_H
