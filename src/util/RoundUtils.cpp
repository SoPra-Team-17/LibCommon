/**
* @file   RoundUtils.hpp
* @author Dominik Authaler
* @date   04.05.2020 (creation)
* @brief  Implementation of utility methods for round initialization.
*/

#include <random>

#include "RoundUtils.hpp"
#include "datatypes/gadgets/Cocktail.hpp"

namespace spy::util {
    void RoundUtils::refillBarTables(spy::gameplay::State &s) {
        for (unsigned int y = 0; y < s.getMap().getNumberOfRows(); y++) {
            for (unsigned int x = 0; x < s.getMap().getRowLength(y); x++) {
                auto field = s.getMap().getField(x, y);
                if (field.getFieldState() == spy::scenario::FieldStateEnum::BAR_TABLE
                    && !field.getGadget().has_value()) {
                    field.setGadget(spy::gadget::Cocktail());
                }
            }
        }
    }

    std::vector<unsigned int> RoundUtils::getRandomCharacterOrder(const gameplay::State &s) {
        std::vector<unsigned int> order(s.getCharacters().size());
        std::generate(order.begin(), order.end(), [n = 0] () mutable { return n++; });

        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(order.begin(), order.end(), g);

        return order;
    }
}

