//
// Created by marco on 10.04.20.
//

#include "Strike.hpp"

#include <utility>

namespace spy::network::messages {

    Strike::Strike() : MessageContainer{MessageTypeEnum::STRIKE, {}} {}

    Strike::Strike(const util::UUID &playerId, const int strikeNr, const int strikeMax, std::string reason)
            : MessageContainer{MessageTypeEnum::STRIKE, playerId}, strikeNr(strikeNr), strikeMax(strikeMax),
              reason(std::move(reason)) {}

    void to_json(nlohmann::json &j, const Strike &s) {
        MessageContainer::common_to_json(j, s);
        j["strikeNr"] = s.strikeNr;
        j["strikeMax"] = s.strikeMax;
        j["reason"] = s.reason;
    }

    void from_json(const nlohmann::json &j, Strike &s) {
        MessageContainer::common_from_json(j, s);
        j.at("strikeNr").get_to(s.strikeNr);
        j.at("strikeMax").get_to(s.strikeMax);
        j.at("reason").get_to(s.reason);
    }

    int Strike::getStrikeNr() const {
        return strikeNr;
    }

    int Strike::getStrikeMax() const {
        return strikeMax;
    }

    const std::string &Strike::getReason() const {
        return reason;
    }

    bool Strike::operator==(const Strike &rhs) const {
        return isEqual(rhs) &&
               strikeNr == rhs.strikeNr &&
               strikeMax == rhs.strikeMax &&
               reason == rhs.reason;
    }
}