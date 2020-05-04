//
// Created by jonas on 02.04.20.
//

#include "Cocktail.hpp"

namespace spy::gadget {
    bool Cocktail::isPoisoned() const {
        return poisoned;
    }

    void Cocktail::setIsPoisoned(bool isPoisoned) {
        poisoned = isPoisoned;
    }

    void to_json(nlohmann::json &j, const Cocktail &c) {
        Gadget::common_to_json(j, c);
        j["poisoned"] = c.poisoned;
    }

    void from_json(const nlohmann::json &j, Cocktail &c) {
        Gadget::common_from_json(j, c);
        j.at("poisoned").get_to(c.poisoned);
    }
}
