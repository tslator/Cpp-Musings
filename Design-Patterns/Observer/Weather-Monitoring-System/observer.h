#pragma once

#include <functional>

template<typename Subject, typename StateTag>
class Observer {
    public:
    using OnUpdate = std::function<void(const Subject&, StateTag)>;

    explicit Observer(OnUpdate onUpdate) : onUpdate_{ std::move(onUpdate) } {}

    void update(const Subject& subject, StateTag property) {
        onUpdate_(subject, property);
    }

    private:
    OnUpdate onUpdate_{};
};
