#include "manager.h"

size_t manager::generate_free_index() noexcept {
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

void manager::mapper::add(const unit_id &path, size_t index) noexcept{
    if (exists(path)) return;
    map::add_word(&mappings, path.name)->data = index;
}

bool manager::mapper::exists(const unit_id &path)noexcept {
    return map::contains_word(&mappings, path.name);
}

size_t manager::mapper::search(const unit_id &path) {
    if (!exists(path)) throw "path not found";
    return map::search(&mappings, path.name)->data;
}

void manager::mapper::remove(const unit_id &path)noexcept {
    if (!exists(path)) return;
    map::remove_word(&mappings, path.name);
}

void manager::load_unit(const unit_data &static_data) noexcept {
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

void manager::unload_unit(const unit_id &id) noexcept {
    if (!mapper.exists(id)) {
        cerr << "can't find the requested unit to unload" << endl;
        return;
    }

    size_t in = mapper.search(id);;

    switch (units[in]->runtime.status) {
        case RUNNING: {
            _stop_unit_at_index(in);
            break;
        }
    }

    units[in] = nullptr;
    mapper.remove(id);
    free_indexes.push(in);
}

bool manager::unit_exists(const unit_id &id) noexcept {
    return mapper.exists(id);
}

const loaded_unit & manager::search_unit(const unit_id &id) {
    if (!unit_exists(id)) throw "no such unit";
    return *units[mapper.search(id)];
}

void manager::start_unit(const unit_id &id) noexcept {
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

void manager::stop_unit(const unit_id &id) noexcept {
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

manager::~manager() {
    for (size_t in = 0; in < units.size(); in++) {
        if (units[in] == nullptr) continue;
        // stop_unit(in);
        units[in] = nullptr;
    }
}
