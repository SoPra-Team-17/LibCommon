/**
* @file   PropertyValidator.hpp
* @author Carolin
* @date   06.05.2020 (creation)
* @brief  Declaration of property validation
*/

#ifndef LIBCOMMON_PROPERTYVALIDATOR_HPP
#define LIBCOMMON_PROPERTYVALIDATOR_HPP


#include <datatypes/gameplay/PropertyAction.hpp>
#include <datatypes/gameplay/State.hpp>

namespace spy::gameplay {

    /**
     * @brief methods to validate properties
     */
    class PropertyValidator {
        public:
            PropertyValidator() = delete;

            static bool validate(const State &s, const PropertyAction &a);

        private:
            static bool validateObservation(const State &s, const PropertyAction &a);

            static bool validateBangAndBurn(const State &s, const PropertyAction &a);
    };

}


#endif //LIBCOMMON_PROPERTYVALIDATOR_HPP
