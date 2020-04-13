//
// Created by marco on 10.04.20.
//

#include "StatisticsEntry.hpp"

#include <utility>


namespace spy::statistics {

    StatisticsEntry::StatisticsEntry(std::string title, std::string description, std::string valuePlayerOne,
                                     std::string valuePlayerTwo) :
            title(std::move(title)), description(std::move(description)), valuePlayerOne(std::move(valuePlayerOne)),
            valuePlayerTwo(std::move(valuePlayerTwo)) {}


    void to_json(nlohmann::json &j, const StatisticsEntry &s) {
        j["title"] = s.title;
        j["description"] = s.description;
        j["valuePlayerOne"] = s.valuePlayerOne;
        j["valuePlayerTwo"] = s.valuePlayerTwo;
    }

    void from_json(const nlohmann::json &j, StatisticsEntry &s) {
        j.at("title").get_to(s.title);
        j.at("description").get_to(s.description);
        j.at("valuePlayerOne").get_to(s.valuePlayerOne);
        j.at("valuePlayerTwo").get_to(s.valuePlayerTwo);
    }

    const std::string &StatisticsEntry::getTitle() const {
        return title;
    }

    const std::string &StatisticsEntry::getDescription() const {
        return description;
    }

    const std::string &StatisticsEntry::getValuePlayerOne() const {
        return valuePlayerOne;
    }

    const std::string &StatisticsEntry::getValuePlayerTwo() const {
        return valuePlayerTwo;
    }

    bool StatisticsEntry::operator==(const StatisticsEntry &rhs) const {
        return std::tie(title, description, valuePlayerOne, valuePlayerTwo) ==
               std::tie(rhs.title, rhs.description, rhs.valuePlayerOne, rhs.valuePlayerTwo);
    }


}