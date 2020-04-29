/**
* @file   Hairdryer.cpp
* @author Dominik Authaler
* @date   29.04.2020 (creation)
* @brief  Implementation of hairdryer gadget validation.
*/

namespace spy::gameplay {
    bool GadgetValidator::validateHairdryer(const State &s, GadgetAction a) {
        // check range
        if (Movement::getMoveDistance(character->getCoordinates().value(), op.getTarget()) > 1) {
            return false;
        }

        // search for character at target position
        auto charTarget = std::find_if(characters.begin(), characters.end(),
                                       [&op](const character::Character &c) {
                                           return c.getCoordinates() == op.getTarget();
                                       });

        return (charTarget != characters.end());
    }
}

