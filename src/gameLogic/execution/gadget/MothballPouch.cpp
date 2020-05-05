/**
* @file   MohthballPouch.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of mothball pouch gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeMothballPouch(State &s, const GadgetAction &a, const MatchConfig &config) {
        // get persons neighboring the fireplace
        auto charPoints = util::GameLogicUtils::getNearFieldsInDist(s, a.getTarget(), 1, [&s](const util::Point &p) {
            return util::GameLogicUtils::isPersonOnField(s, p);
        });

        if (charPoints.second) {
            for (const auto &p : charPoints.first) {
                auto person = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), p);
                person->subHealthPoints(config.getMothballPouchDamage());
            }
        }

        // subtract a usage
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        auto gadget = character->getGadget(gadget::GadgetEnum::MOTHBALL_POUCH).value();
        gadget->setUsagesLeft(gadget->getUsagesLeft().value() - 1);

        // remove gadget from inventory if no usages left!
        if (gadget->getUsagesLeft() == 0) {
            character->removeGadget(gadget::GadgetEnum::MOTHBALL_POUCH);
        }

        return true;
    }
}