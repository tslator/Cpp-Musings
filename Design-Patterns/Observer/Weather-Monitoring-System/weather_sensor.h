#pragma once
#include <cstdint>
#include <set>
#include <mutex>
#include <unordered_map>
#include <vector>
#include "observer.h"


class WeatherSensor {
public:
    enum Property {
        Temperature,
        Humidity,
    };

    using WeatherSensorObserver = Observer<WeatherSensor, Property>;

    explicit WeatherSensor(const float temperature, const float humidity)
        : temperature_(temperature), humidity_(humidity) {}

    bool attach(WeatherSensorObserver* observer);
    bool detach(WeatherSensorObserver* observer);

    void notify(Property property);

    void temperature(float value);
    void humidity(float value);

    [[nodiscard]] float temperature() const { return temperature_; }
    [[nodiscard]] float humidity() const { return humidity_; }

private:
    float temperature_{};
    float humidity_{};

    std::set<WeatherSensorObserver*> observers_{};
};

class WeatherSensor2 {
public:
    enum class Property {
        Temperature,
        Humidity,
    };

    using Callback = std::function<void(const WeatherSensor2&, Property)>;
    using SubscriptionId = std::uint64_t;

    class Subscription {
    public:
        Subscription() = default;
        Subscription(WeatherSensor2& sensor, SubscriptionId id) : sensor_(&sensor), id_(id) {}

        Subscription(const Subscription&) = delete;
        Subscription& operator=(const Subscription&) = delete;

        Subscription(Subscription&& other) noexcept { *this = std::move(other); };
        Subscription& operator=(Subscription&& other) noexcept {
            if (this != &other) {
                reset();
                sensor_ = other.sensor_;
                id_ = other.id_;
                other.sensor_ = nullptr;
                other.id_ = 0;
            }
            return *this;
        }

        ~Subscription() {reset();}

        void reset() {
            if (sensor_) {
                auto _ = sensor_->unsubscribe(id_);
                sensor_ = nullptr;
                id_ = 0;
            }
        }

    private:
        WeatherSensor2* sensor_{nullptr};
        SubscriptionId id_{0};
    };

    explicit WeatherSensor2(float temperature, float humidity) : temperature_(temperature), humidity_(humidity) {}

    SubscriptionId subscribe(Callback callback);
    Subscription subscribe_raii(Callback callback) {
        return Subscription{*this, subscribe(std::move(callback))};
    }

    [[nodiscard]] bool unsubscribe(SubscriptionId id);

    void temperature(float value);
    void humidity(float value);

    [[nodiscard]] float temperature() const {return temperature_;}
    [[nodiscard]] float humidity() const {return humidity_;}

private:
    void notify(Property property);
    float temperature_{};
    float humidity_{};

    std::mutex m_{};
    SubscriptionId next_id_{0};
    std::unordered_map<SubscriptionId, Callback> callbacks_{};
};