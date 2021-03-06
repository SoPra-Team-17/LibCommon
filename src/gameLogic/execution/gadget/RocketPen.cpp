/**
* @file   RocketPen.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of rocket pen gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeRocketPen(State &s, const GadgetAction &action, const MatchConfig &config) {
        // Honey Trap property
        bool doHoneyTrap = util::GameLogicUtils::isPersonOnField(s, action.getTarget());
        auto a = doHoneyTrap ? util::GameLogicUtils::getHoneyTrapOperation(s, action, config) : action;

        // babysitter
        bool targetHasPerson = util::GameLogicUtils::isPersonOnField(s, a.getTarget());
        bool babysitter = false;
        if (targetHasPerson) {
            babysitter = util::GameLogicUtils::checkBabySitter(s, a, config);
        }

        if (babysitter) {
            return false;
        }

        // destroy potential wall on target field
        bool targetHasWall = (s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::WALL);
        if (targetHasWall) {
            s.getMap().getField(a.getTarget()).setFieldState(scenario::FieldStateEnum::FREE);
        }

        //Neighboring fields that have walls on them
        auto fieldWithWalls = util::GameLogicUtils::getNearFieldsInDist(s, a.getTarget(), 1,
                                                                        [&s](const util::Point &p) {
                                                                            return s.getMap().getField(
                                                                                    p).getFieldState() ==
                                                                                   scenario::FieldStateEnum::WALL;
                                                                        });
        if (fieldWithWalls.second) {
            for (const auto &p : fieldWithWalls.first) {
                s.getMap().getField(p).setFieldState(scenario::FieldStateEnum::FREE);
            }
        }

        // damage on targetfield, if there is a person
        if (targetHasPerson) {
            auto person = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());
            auto damage = config.getRocketPenDamage();
            util::GameLogicUtils::applyDamageToCharacter(s, *person, damage);
        }

        // get characters on neighboring fields
        auto charPoints = util::GameLogicUtils::getNearFieldsInDist(s, a.getTarget(), 1, [&s](const util::Point &p) {
            return util::GameLogicUtils::isPersonOnField(s, p);
        });
        if (charPoints.second) {
            for (const auto &p : charPoints.first) {
                auto person = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), p);
                auto damage = config.getRocketPenDamage();
                util::GameLogicUtils::applyDamageToCharacter(s, *person, damage);
            }
        }

        // remove rocket pen from inventory
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        character->removeGadget(gadget::GadgetEnum::ROCKET_PEN);

        return true;
    }
}