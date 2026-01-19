#include <cassert>
#include <iostream>
#include <vector>
#include "anynmeasentence1.h"
#include "anynmeasentence2.h"

int main() {
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

    struct ExampleStatusSentence {
        std::string talker;
        std::string sentenceType;
        bool ok = false;
        [[nodiscard]] bool isChecksumValid() const
        {
            return ok;
        }
    };

    struct ExampleStatusSentenceMethods {
        [[nodiscard]] std::string talker() const
        {
            return "GP1";
        };
        [[nodiscard]] std::string sentenceType() const {
            return "POS1";
        }
        bool ok = false;
        [[nodiscard]] bool isChecksumValid() const
        {
            return ok;
        }
    };

    struct ExampleStringViewMethods {
        [[nodiscard]] std::string_view talker() const { return "GPX"; }
        [[nodiscard]] std::string_view sentenceType() const { return "POSX"; }
        [[nodiscard]] bool isChecksumValid() const { return true; }
    };

    struct ExampleStringViewFromMember {
        std::string talker_storage = "GPV";
        std::string sentenceType_storage = "POSV";
        [[nodiscard]] std::string_view talker() const { return std::string_view(talker_storage); }
        [[nodiscard]] std::string_view sentenceType() const { return std::string_view(sentenceType_storage); }
        [[nodiscard]] bool isChecksumValid() const { return true; }
    };


    std::vector<AnyNmeaSentence_2::AnyNmeaSentence> sentences{
        AnyNmeaSentence_2::AnyNmeaSentence(ExamplePositionSentence{"GP", "POS", 43.12, -77.62}),
        AnyNmeaSentence_2::AnyNmeaSentence(ExampleStatusSentence{"GP", "STS", true}),
        AnyNmeaSentence_2::AnyNmeaSentence(ExampleStatusSentenceMethods {false}),
        AnyNmeaSentence_2::AnyNmeaSentence(ExampleStringViewMethods {})
    };

    struct ExampleStatusSentenceBoolField {
        [[nodiscard]] std::string talker() const
        {
            return "GP1";
        };
        [[nodiscard]] std::string sentenceType() const {
            return "POS1";
        }
        bool isChecksumValid = false;
    };    

    // Compiler error because isChecksumValid is a field instead of a method
    // sentences.emplace_back(
    //     ExampleStatusSentenceBoolField{}
    // );


    for (const auto& s : sentences)
    {
        std::cout
        << "talker=" << s.talker()
        << " type=" << s.sentenceType()
        << " checksumValid=" << (s.isChecksumValid() ? "true" :
        "false")
        << "\n";
    }

    // Tests the string_view path where the string_view references a member of the source
    // object. Construct AnyNmeaSentence from a temporary of this type and then destroy the
    // temporary; the resulting AnyNmeaSentence must own the strings so no dangling view escapes.
    struct ExampleStringViewFromMember2 {
        std::string talker_storage = "GPV";
        std::string sentenceType_storage = "POSV";
        [[nodiscard]] std::string_view talker() const { return std::string_view(talker_storage); }
        [[nodiscard]] std::string_view sentenceType() const { return std::string_view(sentenceType_storage); }
        [[nodiscard]] bool isChecksumValid() const { return true; }
    };

    // Build a sentence from a scoped temporary and ensure AnyNmeaSentence copied the data.
    AnyNmeaSentence_2::AnyNmeaSentence sv_from_member;
    {
        ExampleStringViewFromMember2 tmp;
        sv_from_member = AnyNmeaSentence_2::AnyNmeaSentence(tmp);
    } // tmp destroyed here
    // If the implementation didn't copy the string_view into an owning std::string,
    // this would read from destroyed memory and the assert would likely fail / UB occur.
    assert(sv_from_member.talker() == "GPV");
    assert(sv_from_member.sentenceType() == "POSV");
    std::cout << "sv_from_member: talker=" << sv_from_member.talker()
              << " type=" << sv_from_member.sentenceType() << "\n";    

    return 0;
}