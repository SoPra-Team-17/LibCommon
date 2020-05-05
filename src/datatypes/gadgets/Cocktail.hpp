//
// Created by jonas on 02.04.20.
//

#ifndef LIBCOMMON_COCKTAIL_HPP
#define LIBCOMMON_COCKTAIL_HPP

#include <datatypes/gadgets/Gadget.hpp>

namespace spy::gadget {
    class Cocktail : public Gadget {
    public:
        Cocktail() : Gadget{GadgetEnum::COCKTAIL}, poisoned{false} {};

        [[nodiscard]] bool isPoisoned() const;

        void setIsPoisoned(bool isPoisoned);

        friend void to_json(nlohmann::json &j, const Cocktail &c);

        friend void from_json(const nlohmann::json &j, Cocktail &c);

    private:
        bool poisoned;
    };
}

#endif //LIBCOMMON_COCKTAIL_HPP
