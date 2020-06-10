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

    /**
     * Executes the drinking action of a cocktail.
     * @param s          Current state (will get modified).
     * @param config     Matchconfig for cocktail damage.
     * @param sourceChar Character that executes the action.
     * @return Always true, as the action will never fail.
     */
    static bool executeDrink(State &s,
                             const MatchConfig &config,
                             character::CharacterSet::iterator sourceChar) {
        auto cocktailHP = config.getCocktailHealthPoints();

        // check if cocktail is poisoned
        auto cocktail = std::dynamic_pointer_cast<gadget::Cocktail>(
                sourceChar->getGadget(gadget::GadgetEnum::COCKTAIL).value());

        if (!cocktail->isPoisoned()) {
            cocktailHP = sourceChar->hasProperty(character::PropertyEnum::ROBUST_STOMACH) ? 2 * cocktailHP
                                                                                          : cocktailHP;
            sourceChar->addHealthPoints(cocktailHP);

            //update stats
            if (sourceChar->getFaction() == character::FactionEnum::PLAYER1) {
                s.getFactionStats().cocktails.first++;
            } else if (sourceChar->getFaction() == character::FactionEnum::PLAYER2) {
                s.getFactionStats().cocktails.second++;
            }

        } else {
            // cocktail is poisoned
            cocktailHP = sourceChar->hasProperty(character::PropertyEnum::ROBUST_STOMACH) ? 0.5 * cocktailHP
                                                                                          : cocktailHP;
            sourceChar->subHealthPoints(cocktailHP);

            // update stats --> damage suffered, also counts as cocktail!
            if (sourceChar->getFaction() == character::FactionEnum::PLAYER1) {
                s.getFactionStats().cocktails.first++;
                s.getFactionStats().damageSuffered.first += cocktailHP;
            } else if (sourceChar->getFaction() == character::FactionEnum::PLAYER2) {
                s.getFactionStats().cocktails.second++;
                s.getFactionStats().damageSuffered.second += cocktailHP;
            }
        }

        // remove the cocktail as it was used
        sourceChar->removeGadget(gadget::GadgetEnum::COCKTAIL);
        return true;
    }

    /**
     * Executes the cocktail pouring action.
     * @param s          Current state (will get modified).
     * @param a          Action to execute.
     * @param config     Matchconfig for honey trap and dodge probabilities.
     * @param sourceChar Character that executes the action.
     * @return True if the action was successfull, otherwise false.
     */
    static bool executeCocktailAttack(State &s,
                             const GadgetAction &a,
                             const MatchConfig &config,
                             character::CharacterSet::iterator sourceChar) {

        bool ret = false;

        //Honey Trap property
        bool doHoneyTrap = util::GameLogicUtils::isPersonOnField(s, a.getTarget());
        auto action = doHoneyTrap ? util::GameLogicUtils::getHoneyTrapOperation(s, a, config) : a;

        auto targetChar = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), action.getTarget());
        bool dodged = util::GameLogicUtils::probabilityTestWithCharacter(*targetChar, config.getCocktailDodgeChance());

        if (!dodged) {
            ret = true;
            if (!targetChar->hasProperty(character::PropertyEnum::CONSTANT_CLAMMY_CLOTHES) &&
                !targetChar->hasProperty(character::PropertyEnum::CLAMMY_CLOTHES)) {
                targetChar->addProperty(character::PropertyEnum::CLAMMY_CLOTHES);
            }

            // update cocktail poured stats
            if (sourceChar->getFaction() == character::FactionEnum::PLAYER1) {
                s.getFactionStats().cocktailsPoured.first++;
            } else if (sourceChar->getFaction() == character::FactionEnum::PLAYER2) {
                s.getFactionStats().cocktailsPoured.second++;
            }
        }

        sourceChar->removeGadget(gadget::GadgetEnum::COCKTAIL);

        return ret;
    }

    bool GadgetExecutor::executeCocktail(State &s, const GadgetAction &a, const MatchConfig &config) {
        auto sourceChar = s.getCharacters().getByUUID(a.getCharacterId());
        auto &targetField = s.getMap().getField(a.getTarget());
        bool drink = (sourceChar->getCoordinates().value() == a.getTarget());

        if (drink) {
            // drink the cocktail
            return executeDrink(s, config, sourceChar);
        } else if (targetField.getFieldState() == scenario::FieldStateEnum::BAR_TABLE {
            // take the cocktail from the bar table
            sourceChar->addGadget(targetField.getGadget().value());
            targetField.removeGadget();

            return true;
        } else {
            // pour the cocktail over another character
            return executeCocktailAttack(s, a, config, sourceChar);
        }
    }
}
