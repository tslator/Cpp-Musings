#include <chrono>
#include <random>
#include <thread>
#include <vector>

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

void do_weather_station2() {
    WeatherSensor2 sensor{1, 2};

    auto temperature_subscription = sensor.subscribe_raii([](const WeatherSensor2& sensor, WeatherSensor2::Property property) {
        if (property == WeatherSensor2::Property::Temperature) {
            fmt::println("Temp now {}", sensor.temperature());
        }
    });

    auto subscription_id = sensor.subscribe([](const WeatherSensor2& sensor, WeatherSensor2::Property property) {
        if (property == WeatherSensor2::Property::Humidity) {
            fmt::println("Humidity now {}", sensor.humidity());
        }
    });

    sensor.temperature(10.f);
    sensor.humidity(20.f);

    auto result = sensor.unsubscribe(subscription_id);
    fmt::println("Unsubscribed result: {}", result);

    sensor.temperature(10.f);
}

void do_weather_station2_threaded() {
    WeatherSensor2 sensor{15.f, 45.f};

    std::vector<std::thread> threads;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_real_distribution<float> temperature_distribution(20.f, 30.f);
    std::uniform_real_distribution<float> humidity_distribution(30.f, 80.f);
    std::uniform_int_distribution<int> delay_distribution(100, 500);

    // Temperature Subscription
    auto temperature_subscription = sensor.subscribe_raii([](const WeatherSensor2& sensor, WeatherSensor2::Property property) {
        if (property == WeatherSensor2::Property::Temperature) {
            fmt::println("[Observer 1] Temperature: {:.1f}°C", sensor.temperature());
        }
    });

    // Humidity Subscription
    auto humidity_subscription = sensor.subscribe_raii([](const WeatherSensor2& sensor, WeatherSensor2::Property property) {
        if (property == WeatherSensor2::Property::Humidity) {
            fmt::println("[Observer 2] Humidity: {:.1f}%", sensor.humidity());
        }
    });

    threads.emplace_back([&sensor, &generator, &temperature_distribution, &delay_distribution]() {
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(30)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_distribution(generator)));
            sensor.temperature(temperature_distribution(generator));
        }
    });

    threads.emplace_back([&sensor, &generator, &humidity_distribution, &delay_distribution]() {
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(30)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_distribution(generator)));
            sensor.humidity(humidity_distribution(generator));
        }
    });

    threads.emplace_back([&sensor, &delay_distribution, &generator]() {
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(30)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_distribution(generator)));
            fmt::println("[Dynamic Observer] Subscribing...");
            auto id = sensor.subscribe([](const WeatherSensor2& sensor, WeatherSensor2::Property property) {
                fmt::println("[Dynamic Observer] Event Detected");
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_distribution(generator)));
            auto success = sensor.unsubscribe(id);
            fmt::println("[Dynamic Observer] Unsubscribed ({})", success ? "success" : "failure");
        }
    });

    fmt::println("Running threaded waether station for 30 seconds...\n");

    for (auto& thread : threads) {
        thread.join();
    }

    fmt::println("\nThreaded test completed!");

}

int main() {
    //do_weather_station();
    //do_weather_station2();
    do_weather_station2_threaded();
    return 0;
}