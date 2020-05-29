//
// Created by Carolin on 07.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateAllPropertyActions(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        auto observation = generateObservation(s, activeCharacter);
        auto bangAndBurn = generateBangAndBurn(s, activeCharacter);

        observation.insert(observation.end(), bangAndBurn.begin(), bangAndBurn.end());
        return observation;
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generatePropertyActions(const State &s, const util::UUID &activeCharacter,
                                             character::PropertyEnum property) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        switch (property) {
            case character::PropertyEnum::OBSERVATION:
                return generateObservation(s, activeCharacter);
            case character::PropertyEnum::BANG_AND_BURN:
                return generateBangAndBurn(s, activeCharacter);
            default:
                return {};
        }
    }
}
