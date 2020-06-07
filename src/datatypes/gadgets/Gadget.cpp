//
// Created by jonas on 02.04.20.
//

#include "Gadget.hpp"

namespace spy::gadget {

    Gadget::Gadget(GadgetEnum type) : type(type) {
        switch (type) {
            case GadgetEnum::HAIRDRYER:
                [[fallthrough]];
            case GadgetEnum::BOWLER_BLADE:
                [[fallthrough]];
            case GadgetEnum::MAGNETIC_WATCH:
                [[fallthrough]];
            case GadgetEnum::LASER_COMPACT:
                [[fallthrough]];
            case GadgetEnum::GRAPPLE:
                [[fallthrough]];
            case GadgetEnum::DIAMOND_COLLAR:
                [[fallthrough]];
            case GadgetEnum::POCKET_LITTER:
                [[fallthrough]];
            case GadgetEnum::ANTI_PLAGUE_MASK:
                [[fallthrough]];
            case GadgetEnum::MOLEDIE:
                usagesLeft = std::nullopt;
                break;


            case GadgetEnum::NUGGET:
                [[fallthrough]];
            case GadgetEnum::TECHNICOLOUR_PRISM:
                [[fallthrough]];
            case GadgetEnum::ROCKET_PEN:
                [[fallthrough]];
            case GadgetEnum::GAS_GLOSS:
                [[fallthrough]];
            case GadgetEnum::WIRETAP_WITH_EARPLUGS:
                [[fallthrough]];
            case GadgetEnum::JETPACK:
                [[fallthrough]];
            case GadgetEnum::CHICKEN_FEED:
                [[fallthrough]];
            case GadgetEnum::COCKTAIL:
                [[fallthrough]];
            case GadgetEnum::FOG_TIN:
                usagesLeft = 1;
                break;

            case GadgetEnum::MOTHBALL_POUCH:
                [[fallthrough]];
            case GadgetEnum::POISON_PILLS:
                usagesLeft = 5;
                break;

            default:
                usagesLeft = 0;
                break;
        }
    }

    Gadget::Gadget(GadgetEnum type, unsigned int usagesLeft) : type(type), usagesLeft(usagesLeft) {}

    GadgetEnum Gadget::getType() const {
        return type;
    }

    std::optional<unsigned int> Gadget::getUsagesLeft() const {
        return usagesLeft;
    }

    void Gadget::setUsagesLeft(std::optional<unsigned int> newUsages) {
        Gadget::usagesLeft = newUsages;
    }

    void Gadget::common_to_json(nlohmann::json &j, const Gadget &g) {
        j["GadgetEnum"] = g.type;
        j["usages"] = g.usagesLeft;
    }

    void Gadget::common_from_json(const nlohmann::json &j, spy::gadget::Gadget &g) {
        j.at("GadgetEnum").get_to(g.type);
        j.at("usages").get_to(g.usagesLeft);
    }

    bool Gadget::operator==(const Gadget &rhs) const {
        return this->type == rhs.type;
    }
}  // namespace spy::gadget
