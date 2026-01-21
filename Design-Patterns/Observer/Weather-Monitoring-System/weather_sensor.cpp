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