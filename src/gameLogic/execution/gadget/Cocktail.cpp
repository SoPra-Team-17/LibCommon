/**
* @file   Cocktail.cpp
* @author Marco Deuscher
* @date   05.05.2020 (creation)
* @brief  Implementation of cocktail gadget execution
*/

#include "GadgetExecutor.hpp"
#include "datatypes/gadgets/Cocktail.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeCocktail(State &s, const GadgetAction &a, const MatchConfig &config) {
        // check if cocktail should be drunk
        auto sourceChar = s.getCharacters().getByUUID(a.getCharacterId());
        bool drink = (sourceChar->getCoordinates().value() == a.getTarget());
        if (drink) {
            auto cocktailHP = config.getCocktailHealthPoints();

            // check if cocktail is poisoned
            auto cocktail = std::dynamic_pointer_cast<gadget::Cocktail>(
                    sourceChar->getGadget(gadget::GadgetEnum::COCKTAIL).value());

            if (!cocktail->isPoisoned()) {
                cocktailHP = sourceChar->hasProperty(character::PropertyEnum::ROBUST_STOMACH) ? 2 * cocktailHP
                                                                                              : cocktailHP;
                sourceChar->addHealthPoints(cocktailHP);
            } else {
                // cocktail is poisoned
                cocktailHP = sourceChar->hasProperty(character::PropertyEnum::ROBUST_STOMACH) ? 0.5 * cocktailHP
                                                                                              : cocktailHP;
                sourceChar->subHealthPoints(cocktailHP);
            }
            return true;
        }

        // cocktail is used on target
        bool ret = false;
        auto targetChar = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());
        bool dodged = util::GameLogicUtils::probabilityTestWithCharacter(*targetChar, config.getCocktailDodgeChance());

        if (!dodged) {
            ret = true;
            targetChar->addProperty(character::PropertyEnum::CLAMMY_CLOTHES);
        }

        sourceChar->removeGadget(gadget::GadgetEnum::COCKTAIL);

        return ret;
    }
}

