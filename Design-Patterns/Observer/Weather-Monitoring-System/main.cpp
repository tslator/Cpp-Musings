#include <fmt/core.h>

#include "observer.h"
#include "weather_sensor.h"


void do_weather_station() {
    using Display = Observer<WeatherSensor, WeatherSensor::Property>;

    auto reporter = [](std::string display_name, WeatherSensor const& sensor, WeatherSensor::Property const& changed_property) {
        if (changed_property == WeatherSensor::Temperature) {
            fmt::println("{} received new temperature: {}", display_name, sensor.temperature());
        } else if (changed_property == WeatherSensor::Humidity) {
            fmt::println("{} received new humidity: {}", display_name, sensor.humidity());
        }
    };

    WeatherSensor weatherSensor(1, 2);
    Display currentConditionsDisplay([display_name = "Current Conditions Display", reporter](WeatherSensor const& sensor, WeatherSensor::Property changed_property) {
        reporter(display_name, sensor, changed_property);
    });

    Display statisticsDisplay([display_name = "Statistics Display", reporter](WeatherSensor const& sensor, WeatherSensor::Property changed_property) {
        reporter(display_name, sensor, changed_property);
    });

    Display logger([display_name = "Logger", reporter](WeatherSensor const& sensor, WeatherSensor::Property changed_property) {
        reporter(display_name, sensor, changed_property);
    });

    weatherSensor.attach(&currentConditionsDisplay);
    weatherSensor.attach(&statisticsDisplay);
    weatherSensor.attach(&logger);

    fmt::println("Current temperature: {}", weatherSensor.temperature());
    fmt::println("Current humidity: {}", weatherSensor.humidity());

    weatherSensor.temperature(2);
    weatherSensor.humidity(3);
}

int main() {
    do_weather_station();
    return 0;
}