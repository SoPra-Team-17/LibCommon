//
// Created by Carolin on 04.05.2020.
//

#include <datatypes/gameplay/CatAction.hpp>
#include <util/GameLogicUtils.hpp>
#include <datatypes/gameplay/JanitorAction.hpp>
#include <datatypes/gameplay/Exfiltration.hpp>
#include "ActionGenerator.hpp"

namespace spy::gameplay {
    std::shared_ptr<BaseOperation>
    ActionGenerator::generateExfiltration(const State &s, const util::UUID &damagedCharacter) {
        auto target = util::GameLogicUtils::getRandomFreeSeatField(s);
        auto character = s.getCharacters().findByUUID(damagedCharacter);
        auto action = std::make_shared<Exfiltration>(
                spy::gameplay::Exfiltration(true, target, damagedCharacter, character->getCoordinates().value()));
        return action;
    }

    std::shared_ptr<BaseOperation> ActionGenerator::generateCatAction(const State &s) {
        auto target = util::GameLogicUtils::getRandomCharacterFreeNeighbourField(s, s.getCatCoordinates().value());
        target = target.has_value() ? target : s.getCatCoordinates().value();
        auto action = std::make_shared<CatAction>(spy::gameplay::CatAction(target.value()));
        return action;
    }

    std::shared_ptr<BaseOperation> ActionGenerator::generateJanitorAction(const State &s) {
        auto target = util::GameLogicUtils::getRandomCharacterNearField(s, s.getJanitorCoordinates().value());
        auto action = std::make_shared<JanitorAction>(spy::gameplay::JanitorAction(target));
        return action;
    }

    std::shared_ptr<BaseOperation>
    ActionGenerator::generateNPCAction(const State &/*s*/, const util::UUID &/*activeNPC*/) {
        // TODO implement
        return nullptr;
    }
}
