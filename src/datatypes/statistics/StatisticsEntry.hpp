//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_STATISTICSENTRY_HPP
#define LIBCOMMON_STATISTICSENTRY_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace spy::statistics {

    class StatisticsEntry {
        public:

            StatisticsEntry() = default;

            StatisticsEntry(std::string title, std::string description, std::string valuePlayerOne,
                            std::string ValuePlayerTwo);

            friend void to_json(nlohmann::json &j, const StatisticsEntry &s);

            friend void from_json(const nlohmann::json &j, StatisticsEntry &s);

            [[nodiscard]] const std::string &getTitle() const;

            [[nodiscard]] const std::string &getDescription() const;

            [[nodiscard]] const std::string &getValuePlayerOne() const;

            [[nodiscard]] const std::string &getValuePlayerTwo() const;


        private:
            std::string title;
            std::string description;
            std::string valuePlayerOne;
            std::string valuePlayerTwo;

    };

}
#endif //LIBCOMMON_STATISTICSENTRY_HPP
