#include "weather_sensor.h"

bool WeatherSensor::attach(WeatherSensorObserver* observer) {
    auto [pos, success] = observers_.insert(observer);
    return success;
}

bool WeatherSensor::detach(WeatherSensorObserver* observer) {
    return (observers_.erase(observer) > 0U);
}

void WeatherSensor::notify(Property property) {
    for (auto iter=begin(observers_); iter!=end(observers_);) {
        auto const pos = iter++;
        (*pos)->update(*this, property);
    }
}

void WeatherSensor::temperature(float value) {
    temperature_ = value;
    notify(Property::Temperature);
}

void WeatherSensor::humidity(float value) {
    humidity_ = value;
    notify(Property::Humidity);
}

WeatherSensor2::SubscriptionId WeatherSensor2::subscribe(Callback callback) {
    std::scoped_lock lock(m_);
    const auto id = ++next_id_;
    callbacks_.emplace(id, std::move(callback));
    return id;
}

bool WeatherSensor2::unsubscribe(SubscriptionId id) {
    std::scoped_lock lock(m_);
    return callbacks_.erase(id) > 0;
}

void WeatherSensor2::notify(Property property) {
    std::vector<Callback> snapshot;
    {
        std::scoped_lock lock(m_);
        snapshot.reserve(callbacks_.size());
        for (auto const& [_, callback] : callbacks_) {
            snapshot.push_back(callback);
        }
        for (auto& callback : snapshot) {
            callback(*this, property);
        }
    }
}

void WeatherSensor2::temperature(float value) {
    temperature_ = value;
    notify(Property::Temperature);
}

void WeatherSensor2::humidity(float value) {
    humidity_ = value;
    notify(Property::Humidity);
}