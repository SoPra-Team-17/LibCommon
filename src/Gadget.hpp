//
// Created by jonas on 02.04.20.
//

#ifndef LIBCOMMON_GADGET_HPP
#define LIBCOMMON_GADGET_HPP
namespace spy::gadget {
    enum class GadgetEnum {
        HAIRDRYER,
        MOLEDIE,
        TECHNICOLOUR_PRISM,
        BOWLER_BLADE,
        MAGNETIC_WATCH,
        POISON_PILLS,
        LASER_COMPACT,
        ROCKET_PEN,
        GAS_GLOSS,
        MOTHBALL_POUCH,
        FOG_TIN,
        GRAPPLE,
        WIRETAP_WITH_EARPLUGS,
        DIAMOND_COLLAR,
        JETPACK,
        CHICKEN_FEED,
        NUGGET,
        MIRROR_OF_WILDERNESS,
        POCKET_LITTER,
        COCKTAIL
    };

    class Gadget {
    public:
        explicit Gadget(GadgetEnum type) : type{type}, usagesLeft{0} {};

        [[nodiscard]] GadgetEnum getType() const {
            return type;
        }

        [[nodiscard]] int getUsagesLeft() const {
            return usagesLeft;
        }

        void setUsagesLeft(int newUsages) {
            Gadget::usagesLeft = newUsages;
        }

    private:
        const GadgetEnum type;
        int usagesLeft;
    };
}

#endif //LIBCOMMON_GADGET_HPP
