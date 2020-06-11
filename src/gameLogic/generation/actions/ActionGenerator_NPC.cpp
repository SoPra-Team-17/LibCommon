//
// Created by Carolin on 07.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::shared_ptr<BaseOperation>
    ActionGenerator::generateNPCAction(const State &s, const util::UUID &activeNPC, const MatchConfig &config) {
        // get rid of mole die if possible
        auto moleDie = generateGadgetActions(s, activeNPC, gadget::GadgetEnum::MOLEDIE, config);
        if (!moleDie.empty()) {
            return *util::GameLogicUtils::getRandomItemFromContainer(moleDie);
        }

        return generateRandomAction(s, activeNPC, config);
    }

    std::shared_ptr<BaseOperation>
    ActionGenerator::generateRandomAction(const State &s, const util::UUID &activeCharacter,
                                          const MatchConfig &config) {
        auto activeCharPosition = s.getCharacters().findByUUID(activeCharacter)->getCoordinates();
        if (!activeCharPosition.has_value()) {
            return {};
        }

        auto allActions = generateMovementActions(s, activeCharacter);
        allActions.insert(allActions.end(), generateRetire(activeCharacter));

        if (!s.getMap().getField(activeCharPosition.value()).isFoggy()) {
            auto properties = generateAllPropertyActions(s, activeCharacter);
            auto gadget = generateAllGadgetActions(s, activeCharacter, config);
            auto spy = generateSpyActions(s, activeCharacter);
            auto gamble = generateGambleActions(s, activeCharacter);

            allActions.insert(allActions.end(), properties.begin(), properties.end());
            allActions.insert(allActions.end(), gadget.begin(), gadget.end());
            allActions.insert(allActions.end(), spy.begin(), spy.end());
            allActions.insert(allActions.end(), gamble.begin(), gamble.end());
        }


        return *util::GameLogicUtils::getRandomItemFromContainer(allActions);
    }
}
