//
// Created by marco on 10.04.20.
//

#include "Statistics.hpp"

#include <utility>


namespace spy::statistics {

    Statistics::Statistics(std::vector<StatisticsEntry> entries) : entries(std::move(entries)) {}

    void to_json(nlohmann::json &j, const Statistics &s) {
        j["entries"] = s.entries;
    }

    void from_json(const nlohmann::json &j, Statistics &s) {
        j.at("entries").get_to(s.entries);
    }

    auto Statistics::getEntries() const -> const std::vector<StatisticsEntry> & {
        return entries;
    }

    bool Statistics::operator==(const Statistics &rhs) const {
        return entries == rhs.entries;
    }

}