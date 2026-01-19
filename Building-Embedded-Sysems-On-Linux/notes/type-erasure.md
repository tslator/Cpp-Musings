# Type Erasure for NMEA Messages

```cpp
#pragma once
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

class AnyNmeaSentence
{
    public:
    AnyNmeaSentence() = default;

    template <
        typename T, 
        class Decayed = std::decay_t<T>, 
        std::enable_if_t<
            not std::is_same<Decayed, AnyNmeaSentence>::value, int> = 0>
    AnyNmeaSentence(T&& sentence) 
        : self_(std::make_unique<Model<Decayed>>(std::forward<T>(sentence)))
    {}

    AnyNmeaSentence(const AnyNmeaSentence& other)
        : self_(other.self_ ? other.self_->clone() : nullptr)
    {}

    AnyNmeaSentence& operator=(const AnyNmeaSentence& other) 
    {
        // Q: Is this check required?  I read somewhere that copy swap was safe without this check
        if (this != &other)
        {
            self_ other.self_ ? other.self_->clone() : nullptr;
        }
        return *this;
    }

    AnyNmeaSentence(AnyNmeaSentence&&) noexcept = default;
    AnyNmeaSentence& operator=(AnyNmeaSentence&&) noexcept = default;

    bool hasValue() const noexcept
    {
        return static_cast<bool>(self_);
    }

    explicit operator bool() const noexcept
    {
        return hasValue();
    }

    std::string_view talker() const
    {
        return self_ ? self_->talker() : std::string_view{};
    }

    std::string_view sentenceType() const
    {
        return self_ ? self_->sentenceType() : std::string_view{};
    }

    bool isCheckedsumValid() const
    {
        return self_ ? self_->isChecksumValid() : false;
    }

    private:
    struct Concept
    {
        virtual ~Concep() = default;
        virtual std::unique_ptr<Concept> clone() const = 0;
        virtual std::string_view talker() const = 0;
        virtual std::string_view sentenceType() const = 0;
        virtual bool isChecksumValid() const = 0;
    };

    template<typename T>
    struct Model final : Concept
    {
        explicit Model(T sentence)
            : sentence_(std::move(sentence))
        {}

        std::unique_ptr<Concept> clone() const override
        {
            return std::make_unique<Model<T>>(sentence_);
        }

        std::string_view talker() const override
        {
            return TalkerAccessor<T>::get(sentence_);
        }

        std::string_view sentenceType() const override
        {
            return SentenceTypeAccessor<T>::get(sentence_);
        }

        bool isChecksumValid() const override
        {
            return ChecksumValidAccessor<T>::get(sentence_);
        }

        T sentence_;
    };

    static std::string_view toStringView(std::string_view view)
    {
        return view;
    }

    static std::string_view toStringView(const std::string& string)
    {
        return std::string_view(string);
    }

    static std::string_view toStringView(const char* chars)
    {
        return chars ? std::string_view{chars} : std::string_view{};
    }

    template<typename T, class = void>
    struct TalkerAccessor
    {
        static std::string_view get(const T& value)
        {
            return toStringView(value.talker);
        }        
    };

    template<typename T>
    struct TalkerAccessor<T, decltype(void(std::declval<const T&>().talker()))>
    {
        static std::string_view get(const T& value)
        {
            return toStringView(value.talker());
        }
    };

    template<typename T, class = void>
    struct SentenceTypeAccessor
    {
        static std::string_view get(const T& value)
        {
            return toStringView(value.sentenceType());
        }
    };

    template<typename T, class = void>
    struct ChecksumValidAccessor
    {
        static bool get(const T&)
        {
            static_assert(sizeof(T) == 0, "Concrete sentence type must implement: bool isChecksumValid() const");
            return false;
        }
    };

    template<typename T>
    struct ChecksumValidAccessor<T, decltype(void(std::declval<const T&>().isChecksumValid()))>
    {
        static bool get(const T& value)
        {
            return static_cast<bool>(value.isChecksumValid());
        }
    };

    std::unique_ptr<Concept> self_;

};

// Example Usage in main.cpp

struct ExamplePositionSentence
{
    std::string talker;
    std::string sentenceType;
    double latitude = 0.0;
    double longitude = 0.0;
    bool isChecksumValid() const
    {
        return true;
    }
};

struct ExampleStatusSentence
{
    std::string talker;
    std::string sentenceType;
    bool ok = false;
    bool isChecksumValid() const
    {
        return ok;
    }
}

std::vector<AnyNmeaSentence> sentences;
sentences.emplace_back(
    ExamlePositionSentence{"GP", "POS", 43.12, -77.62}
);

sentences.emplace_back(
    exampleStatusSentence{"GP", "STS", true}
);

for (const auto& sentence : sentences)
{
    std::cout
        << "talker=" << sentence.talker()
        << " type=" << sentence.sentenceType()
        << " checksumValid=" << (sentence.isChecksumValid() ? "true" : "false");
        << "\n";
}

```

Here is an improved approach using concepts.  It dramatically reduces the "templatese".

```cpp

```

## Reference
Chapter 4