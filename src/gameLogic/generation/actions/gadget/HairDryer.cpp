/**
 * @file   HairDryer.cpp
 * @author Marco Deuscher (code), Carolin (creation)
 * @date   08.05.2020 (creation)
 * @brief  Implementation of hair dryer gadget action generation
 */


#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateHairDryer(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config) {
        std::vector<std::shared_ptr<BaseOperation>> valid_ops;
        // action on

        return {nullptr};
    }
}