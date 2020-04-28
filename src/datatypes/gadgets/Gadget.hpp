//
// Created by jonas on 02.04.20.
//

#ifndef LIBCOMMON_GADGET_HPP
#define LIBCOMMON_GADGET_HPP

#include <nlohmann/json.hpp>
#include "datatypes/gadgets/GadgetEnum.hpp"
#include "util/OptionalSerialization.hpp"

namespace spy::gadget {

    class Gadget {
        public:
            Gadget() : type{GadgetEnum::INVALID}, usagesLeft{0} {};

            explicit Gadget(GadgetEnum type, int usagesLeft = 0);

            [[nodiscard]] GadgetEnum getType() const;

            [[nodiscard]] std::optional<unsigned int> getUsagesLeft() const;

            void setUsagesLeft(std::optional<unsigned int> newUsages);

            friend void to_json(nlohmann::json &j, const Gadget &g);

            friend void from_json(const nlohmann::json &j, Gadget &g);

            bool operator==(const Gadget &rhs) const;

        private:
            GadgetEnum type;
            std::optional<unsigned int> usagesLeft;
    };
}

#endif //LIBCOMMON_GADGET_HPP
