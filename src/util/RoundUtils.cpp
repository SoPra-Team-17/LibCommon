/**
* @file   RoundUtils.hpp
* @author Dominik Authaler
* @date   04.05.2020 (creation)
* @brief  Implementation of utility methods for round initialization.
*/

#include <random>

#include "RoundUtils.hpp"
#include "datatypes/gadgets/Cocktail.hpp"
#include "datatypes/gadgets/WiretapWithEarplugs.hpp"
#include "util/GameLogicUtils.hpp"


constexpr unsigned int FOG_ROUND_LIMIT = 3;

namespace spy::util {
    void RoundUtils::refillBarTables(spy::gameplay::State &s) {
        for (unsigned int y = 0; y < s.getMap().getNumberOfRows(); y++) {
            for (unsigned int x = 0; x < s.getMap().getRowLength(y); x++) {
                auto field = s.getMap().getField(x, y);
                if (field.getFieldState() == spy::scenario::FieldStateEnum::BAR_TABLE
                    && !field.getGadget().has_value()) {
                    field.setGadget(std::make_shared<spy::gadget::Cocktail>());
                }
            }
        }
    }

    void RoundUtils::updateFog(gameplay::State &s) {
        for (unsigned int y = 0; y < s.getMap().getNumberOfRows(); y++) {
            for (unsigned int x = 0; x < s.getMap().getRowLength(y); x++) {
                auto field = s.getMap().getField(x, y);
                if (field.isFoggy()) {
                    field.incrementFogCounter();
                    if (field.getFogCounter() >= FOG_ROUND_LIMIT) {
                        field.setFoggy(false);
                        field.resetFogCounter();
                    }
                }
            }
        }
    }

    void RoundUtils::checkGadgetFallouts(gameplay::State &s, const MatchConfig &config) {
        for (auto &c : s.getCharacters()) {
            auto gadget = c.getGadget(gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS);
            if (gadget.has_value()) {
                auto wiretap = std::static_pointer_cast<spy::gadget::WiretapWithEarplugs>(gadget.value());

                if (wiretap->isWorking() && GameLogicUtils::probabilityTest(config.getWiretapWithEarplugsFailChance())) {
                    wiretap->setWorking(false);
                } else if (!wiretap->isWorking() && wiretap->getActiveOn().has_value()) {
                    // Standard specifies that their must be at least one message with the gadget disabled after fallout
                    c.removeGadget(gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS);
                }
            }
        }
    }

    void RoundUtils::resetUpdatedMarker(gameplay::State &s) {
        for (unsigned int y = 0; y < s.getMap().getNumberOfRows(); y++) {
            for (unsigned int x = 0; x < s.getMap().getRowLength(y); x++) {
                s.getMap().getField(x, y).setUpdated(false);
            }
        }
    }
}

