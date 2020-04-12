//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_STATISTICS_HPP
#define LIBCOMMON_STATISTICS_HPP

#include <vector>
#include <statistics/StatisticsEntry.hpp>


namespace spy::statistics {

    class Statistics {
        public:
            Statistics() = default;

            explicit Statistics(std::vector<StatisticsEntry> entries);

            [[nodiscard]] auto getEntries() const -> const std::vector<StatisticsEntry> &;

            friend void to_json(nlohmann::json &j, const Statistics &s);

            friend void from_json(const nlohmann::json &j, Statistics &s);

        private:
            std::vector<StatisticsEntry> entries;
    };

}

#endif //LIBCOMMON_STATISTICS_HPP
