//
// Created by marco on 10.04.20.
//

#include <datatypes/statistics/Statistics.hpp>
#include <utility>
#include "StatisticsMessage.hpp"

namespace spy::network::messages {

    StatisticsMessage::StatisticsMessage() : MessageContainer{MessageTypeEnum::STATISTICS, {}} {}

    StatisticsMessage::StatisticsMessage(const util::UUID &playerId, spy::statistics::Statistics statistics,
                                         const util::UUID &winner,
                                         const spy::statistics::VictoryEnum &reason, bool hasReplay) :
            MessageContainer{MessageTypeEnum::STATISTICS, playerId},
            winner(winner),
            reason(reason),
            statistics(std::move(statistics)),
            hasReplay(hasReplay) {}

    void to_json(nlohmann::json &j, const StatisticsMessage &s) {
        MessageContainer::common_to_json(j, s);
        j["statistics"] = s.statistics;
        j["winner"] = s.winner;
        j["reason"] = s.reason;
        j["hasReplay"] = s.hasReplay;
    }

    void from_json(const nlohmann::json &j, StatisticsMessage &s) {
        MessageContainer::common_from_json(j, s);
        if (j.find("statistics") != j.end()) {
            j.at("statistics").get_to(s.statistics);
        }
        j.at("winner").get_to(s.winner);
        j.at("reason").get_to(s.reason);
        j.at("hasReplay").get_to(s.hasReplay);
    }

    const std::optional<spy::statistics::Statistics> &StatisticsMessage::getStatistics() const {
        return statistics;
    }

    auto StatisticsMessage::getWinner() const -> const util::UUID & {
        return winner;
    }

    auto StatisticsMessage::getReason() const -> const spy::statistics::VictoryEnum & {
        return reason;
    }

    bool StatisticsMessage::getHasReplay() const {
        return hasReplay;
    }

    bool StatisticsMessage::operator==(const StatisticsMessage &rhs) const {
        return isEqual(rhs) &&
               winner == rhs.winner &&
               reason == rhs.reason &&
               statistics == rhs.statistics &&
               hasReplay == rhs.hasReplay;
    }
}