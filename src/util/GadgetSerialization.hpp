/**
 * @file   GadgetSerialization.hpp
 * @author Dominik Authaler
 * @date   10.04.2020
 * @brief  Adds serialization and deserialization for std::shared_ptr<spy::gameplay::Gadget>.
 */

#ifndef LIBCOMMON_GADGET_SERIALIZATION_HPP
#define LIBCOMMON_GADGET_SERIALIZATION_HPP

#include <nlohmann/json.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>
#include <datatypes/gadgets/Gadget.hpp>
#include <datatypes/gadgets/Cocktail.hpp>
#include <datatypes/gadgets/WiretapWithEarplugs.hpp>

namespace nlohmann {
    template<>
    struct adl_serializer<std::shared_ptr<spy::gadget::Gadget>> {
        static void to_json(json &j, const std::shared_ptr<spy::gadget::Gadget> &gadget) {
            using namespace spy::gadget;
            switch (gadget->getType()) {
                case GadgetEnum::COCKTAIL:
                    j = *std::dynamic_pointer_cast<const Cocktail>(gadget);
                    break;

                case GadgetEnum::WIRETAP_WITH_EARPLUGS:
                    j = *std::dynamic_pointer_cast<const WiretapWithEarplugs>(gadget);
                    break;

                default:
                    break;
            }
        }

        static void from_json(const json &j, std::shared_ptr<spy::gadget::Gadget> &gadget) {
            using namespace spy::gadget;

            GadgetEnum gadgetType;
            j.at("GadgetEnum").get_to(gadgetType);

            switch (gadgetType) {
                case GadgetEnum::COCKTAIL:
                    gadget = std::make_shared<Cocktail>();
                    *std::static_pointer_cast<Cocktail>(gadget) = j.get<Cocktail>();
                    break;

                case GadgetEnum::WIRETAP_WITH_EARPLUGS:
                    gadget = std::make_shared<WiretapWithEarplugs>();
                    *std::static_pointer_cast<WiretapWithEarplugs>(gadget) = j.get<WiretapWithEarplugs>();
                    break;

                default:
                    gadget = std::make_shared<Gadget>();
                    *std::static_pointer_cast<Gadget>(gadget) = j.get<Gadget>();
                    break;
            }
        }
    };
}


#endif //LIBCOMMON_GADGET_SERIALIZATION_HPP
