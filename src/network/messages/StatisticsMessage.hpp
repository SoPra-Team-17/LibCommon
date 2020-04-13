//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_STATISTICSMESSAGE_HPP
#define LIBCOMMON_STATISTICSMESSAGE_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/statistics/Statistics.hpp>
#include <datatypes/statistics/VictoryEnum.hpp>

namespace spy::network::messages {

    class StatisticsMessage : public MessageContainer {
        public:
            StatisticsMessage();

            StatisticsMessage(const util::UUID &playerId, spy::statistics::Statistics statistics,
                              const util::UUID &winner,
                              const spy::statistics::VictoryEnum &reason, bool hasReplay);

            [[nodiscard]] const std::optional<spy::statistics::Statistics> &getStatistics() const;

            [[nodiscard]] auto getWinner() const -> const util::UUID &;

            [[nodiscard]] auto getReason() const -> const spy::statistics::VictoryEnum &;

            [[nodiscard]] bool getHasReplay() const;

            friend void to_json(nlohmann::json &j, const StatisticsMessage &s);

            friend void from_json(const nlohmann::json &j, StatisticsMessage &s);

            bool operator==(const StatisticsMessage &rhs) const;

        private:
            util::UUID winner;
            spy::statistics::VictoryEnum reason = spy::statistics::VictoryEnum::INVALID;
            std::optional<spy::statistics::Statistics> statistics;
            bool hasReplay = false;
    };


}

#endif //LIBCOMMON_STATISTICSMESSAGE_HPP
