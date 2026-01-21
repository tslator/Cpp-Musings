# Challenge #2 — Observer Pattern (Modern C++ Edition)
## Problem Statement

You are designing a **Weather Monitoring System**. You have a WeatherSensor that tracks temperature and humidity. Multiple "displays" (e.g., a CurrentConditionsDisplay, a StatisticsDisplay, and a Logger) need to be notified immediately whenever the sensor's data changes so they can update their output.

The system must be extensible: you should be able to add or remove displays at runtime without modifying the WeatherSensor code.

## Design Pattern to Apply

**Observer Pattern** — focusing on the intent of "one-to-many dependency" and "push-based notification."

**Requirements & Constraints (Modern Perspective)**
- **Avoid "Inheritance Overkill"**: Do not feel forced to create a class IObserver with a virtual update() method if you can achieve the same goal using std::function, signals/slots, or type erasure.
- **Ownership & Lifetime**: Consider how the sensor knows if a display still exists. Use smart pointers (std::shared_ptr / std::weak_ptr) or a registration ID system to prevent "dangling observers."
- **Efficiency**: Use std::string_view or pass-by-reference where appropriate to avoid unnecessary copies during notification.
- **Thread Safety (Optional but encouraged)**: Think about what happens if a display is added while a notification is in progress (though a single-threaded solution is fine for the core pattern).