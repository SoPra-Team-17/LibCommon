//
// Created by Carolin on 07.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::shared_ptr<BaseOperation>
    ActionGenerator::generateNPCAction(const State &s, const util::UUID &activeNPC, const MatchConfig &config) {
        // get rid of mole die if possible
        auto moleDie = generateGadgetActions(s, activeNPC, gadget::GadgetEnum::MOLEDIE);
        if (!moleDie.empty()) {
            return *util::GameLogicUtils::getRandomItemFromContainer(moleDie);
        }

        return generateRandomAction(s, activeNPC, config);
    }

    std::shared_ptr<BaseOperation>
    ActionGenerator::generateRandomAction(const State &s, const util::UUID &activeCharacter,
                                          const MatchConfig &config) {
        auto move = generateMovementActions(s, activeCharacter, config);
        auto properties = generateAllPropertyActions(s, activeCharacter, config);
        auto gadget = generateAllGadgetActions(s, activeCharacter, config);
        auto spy = generateSpyActions(s, activeCharacter, config);
        auto gamble = generateGambleActions(s, activeCharacter, config);

        auto ret = move;
        ret.insert(ret.end(), properties.begin(), properties.end());
        ret.insert(ret.end(), gadget.begin(), gadget.end());
        ret.insert(ret.end(), spy.begin(), spy.end());
        ret.insert(ret.end(), gamble.begin(), gamble.end());
        ret.insert(ret.end(), generateRetire(activeCharacter));

        return *util::GameLogicUtils::getRandomItemFromContainer(ret);
    }
}
