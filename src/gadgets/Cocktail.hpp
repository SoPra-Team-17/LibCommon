//
// Created by jonas on 02.04.20.
//

#ifndef LIBCOMMON_COCKTAIL_HPP
#define LIBCOMMON_COCKTAIL_HPP

#include <Gadget.hpp>

namespace spy::gadget {
    class Cocktail : public Gadget {
    public:
        Cocktail() : Gadget{GadgetEnum::COCKTAIL}, isPoisoned{false} {};

    private:
        bool isPoisoned;

    };
}

#endif //LIBCOMMON_COCKTAIL_HPP
