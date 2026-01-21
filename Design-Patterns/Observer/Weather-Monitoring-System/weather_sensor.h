#pragma once
#include <set>
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

    // TODO: Include a GUID for unique id
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