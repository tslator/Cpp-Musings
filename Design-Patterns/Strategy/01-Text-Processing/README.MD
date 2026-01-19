# Strategy Pattern (Modern C++ Edition)
## Problem Statement
You’re building a small text‑processing tool. Depending on user preference, the text should be transformed in different ways:

- convert to uppercase
- convert to lowercase
- capitalize each word

Your task is to design this system so the transformation algorithm can be swapped at runtime without modifying the calling code.

## Design Pattern to Apply
Strategy Pattern — using modern C++ features (e.g., std::unique_ptr, lambdas, concepts if useful).

## Requirements & Constraints
- Define a common interface for text‑transformation strategies.
- Provide at least three concrete strategy implementations (uppercase, lowercase, capitalize).
- The caller should hold a strategy object and be able to replace it at runtime.
- Avoid raw owning pointers.
- Favor value semantics where reasonable, but unique ownership of polymorphic strategies is fine.
- Demonstrate usage in a simple main().