#pragma once
#include <algorithm>

class ResourceManager {
    char *data{nullptr};
    size_t size{0};
public:
    ResourceManager() = default;
    explicit ResourceManager(const size_t size) : data{new char[size]}, size{size} {}
    ResourceManager(const ResourceManager& other) : ResourceManager(other.size) {
        std::copy_n(other.data, size, data);
    }
    ResourceManager(ResourceManager&& other) noexcept 
        : data{other.data}, size{other.size} {
        other.data = nullptr;
        other.size = 0;
    }
    ~ResourceManager() {
        delete[] data;
    }
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            using std::swap;
            ResourceManager temp(other);
            swap(*this, temp);
        }
        return *this;
    }
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    bool operator==(const ResourceManager& other) const {
        if (size != other.size) {
            return false;
        }
        return std::equal(data, data + size, other.data, other.data + size);
    }

    [[nodiscard]] size_t show_size() const {
        return size;
    }
};