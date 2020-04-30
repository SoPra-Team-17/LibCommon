//
// Created by jonas on 10.04.20.
//

#include "GambleAction.hpp"

namespace spy::gameplay {

    GambleAction::GambleAction(bool successful, const util::Point &target, const util::UUID &characterId,
                               unsigned int stake)
            : CharacterOperation(OperationEnum::GAMBLE_ACTION, successful, target, characterId),
              stake(stake) {}

    unsigned int GambleAction::getStake() const {
        return stake;
    }

    void to_json(nlohmann::json &j, const GambleAction &g) {
        CharacterOperation::common_to_json(j, g);
        j["stake"] = g.stake;
    }
    
    void from_json(const nlohmann::json &j, GambleAction &g) {
        CharacterOperation::common_from_json(j, g);
        j.at("stake").get_to(g.stake);
    }
    
    bool GambleAction::operator==(const GambleAction &rhs) const {
        return std::tie(static_cast<const spy::gameplay::CharacterOperation &>(*this), stake) ==
               std::tie(static_cast<const spy::gameplay::CharacterOperation &>(rhs), rhs.stake);
    }

    bool GambleAction::operator!=(const GambleAction &rhs) const {
        return !(rhs == *this);
    }
}
