#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <iostream>

namespace AnyNmeaSentence_2
{
    class AnyNmeaSentence;

    // Concepts
    template <typename T>
    concept NotAnyNmeaSentence = not std::same_as<std::remove_cvref_t<T>, AnyNmeaSentence>;

    template <typename T>
    concept StringLike =
        std::convertible_to<T, std::string_view> ||
        std::convertible_to<T, std::string> ||
        std::convertible_to<T, const char*>;

    // Utility Templates/Free Functions
    template<typename>
    inline constexpr bool always_false = false;

    [[nodiscard]] std::string toString(const StringLike auto& value)
    {
        // using Type = std::remove_cvref_t<decltype(value)>;

        // if constexpr (std::same_as<Type, std::string_view>) {
        //     return std::string{value};
        // } else if constexpr (std::same_as<Type, std::string>) {
        //     return value;
        // } else if constexpr(std::same_as<Type, const char*>) {
        //     return value ? std::string{value} : std::string{};
        // } else {
        //     static_assert(always_false<Type>,
        //                   "Unsupported type passed to toStringView");
        //     return std::string{};
        // }
        return std::string{std::string_view{value}};
    }

    template<typename Tag>
    decltype(auto) Accessor(const auto& value) {
        return Tag::get(value);
    }

    // Class Definition
    class AnyNmeaSentence
    {
    public:
        AnyNmeaSentence() = default;
        /// Primary constructor (1)
        explicit AnyNmeaSentence(NotAnyNmeaSentence auto&& sentence)
            : self_(
                 std::make_unique<
                    Model<std::remove_cvref_t<decltype(sentence)>>
                    >(std::forward<decltype(sentence)>(sentence)))
        {}

        AnyNmeaSentence(const AnyNmeaSentence &other)
            : self_(other.self_ ? other.self_->clone() : nullptr)
        {
        }

        AnyNmeaSentence &operator=(const AnyNmeaSentence &other)
        {
            if (this != &other)
            {
                self_ = other.self_ ? other.self_->clone() : nullptr;
            }
            return *this;
        }

        AnyNmeaSentence(AnyNmeaSentence &&) noexcept = default;
        AnyNmeaSentence &operator=(AnyNmeaSentence &&) noexcept = default;

        [[nodiscard]] bool hasValue() const noexcept
        {
            return static_cast<bool>(self_);
        }

        explicit operator bool() const noexcept
        {
            return hasValue();
        }

        [[nodiscard]] std::string talker() const
        {
            return self_ ? self_->talker() : std::string{};
        }
        [[nodiscard]] std::string sentenceType() const
        {
            return self_ ? self_->sentenceType() : std::string{};
        }
        [[nodiscard]] bool isChecksumValid() const
        {
            return self_ ? self_->isChecksumValid() : false;
        }

    private:
        struct Concept
        {
            virtual ~Concept() = default;
            [[nodiscard]] virtual std::unique_ptr<Concept> clone() const = 0;
            [[nodiscard]] virtual std::string talker() const = 0;
            [[nodiscard]] virtual std::string sentenceType() const = 0;
            [[nodiscard]] virtual bool isChecksumValid() const = 0;
        };

        template <class T>
        struct Model final : Concept
        {
            explicit Model(T sentence)
                : sentence_(std::move(sentence))
            {
            }

            [[nodiscard]] std::unique_ptr<Concept> clone() const override
            {
                return std::make_unique<Model<T>>(sentence_);
            }

            [[nodiscard]] std::string talker() const override
            {
                static_assert(std::convertible_to<
                                std::decay_t<decltype(Accessor<TalkerTag>(sentence_))>, 
                                std::string>,
                              "TalkerTag::get must be convertible to std::string");
                return Accessor<TalkerTag>(sentence_);
            }

            [[nodiscard]] std::string sentenceType() const override
            {
                static_assert(std::convertible_to<
                                std::decay_t<decltype(Accessor<SentenceTypeTag>(sentence_))>,
                                std::string>,
                              "SentenceTypeTag::get must be convertible to std::string");
                return Accessor<SentenceTypeTag>(sentence_);
            }

            [[nodiscard]] bool isChecksumValid() const override
            {
                static_assert(std::convertible_to<
                                std::decay_t<decltype(Accessor<ChecksumValidTag>(sentence_))>,
                                bool>,
                              "ChecksumValidTag::get must be convertible to bool");
                return Accessor<ChecksumValidTag>(sentence_);
            }

            T sentence_;
        };

    private:
        // talker: supports s.talker (field) or s.talker() (method)
        struct TalkerTag {
            static std::string get(const auto& value)
                requires (requires { value.talker(); } || requires { value.talker; })
            {
                if constexpr (requires { value.talker(); })
                {
                    return toString(value.talker());
                } else {
                    return toString(value.talker);
                }
            }
        };

        // sentenceType: supports s.sentenceType (field) or s.sentenceType()(method)
        struct SentenceTypeTag {
            static std::string get(const auto& value) 
                requires (requires { value.sentenceType(); } || requires { value.sentenceType; })
            {
                if constexpr (requires { value.sentenceType(); }) {
                    return toString(value.sentenceType());
                } else {
                    return toString(value.sentenceType);
                }
            }
        };

        // isChecksumValid: supports s.isChecksumValid() only (method)
        struct ChecksumValidTag {
            static bool get(const auto& value) 
                requires requires { value.isChecksumValid(); }
            {
                if constexpr (requires { value.isChecksumValid(); }) {
                    return value.isChecksumValid();
                } else {
                    using T = decltype(value);
                    static_assert(always_false<T>, "Concrete sentence type must implement: bool isChecksumValid() const");
                }
            }
        };

        std::unique_ptr<Concept> self_;
    };
} // AnyNmeaSentence_2