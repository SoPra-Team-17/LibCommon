/**
* @file   PropertyExecutor.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
*/
#include "PropertyExecutor.hpp"

namespace spy::gameplay {

    std::shared_ptr<const BaseOperation>
    PropertyExecutor::execute(State &s, const PropertyAction &a, const MatchConfig &config) {
        switch (a.getUsedProperty()) {
            case character::PropertyEnum::BANG_AND_BURN:
                return PropertyExecutor::executeBangAndBurn(s, a);
            case character::PropertyEnum::OBSERVATION:
                return PropertyExecutor::executeObservation(s, a, config);
            default:
                throw std::invalid_argument("Execution of property type not implemented");
        }
    }
}
