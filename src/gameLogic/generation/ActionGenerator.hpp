/**
* @file   ActionExecutor.hpp
* @author Carolin
* @date   04.05.2020 (creation)
* @brief  Definition of the static action generation class.
*/

#ifndef LIBCOMMON_ACTIONGENERATOR_HPP
#define LIBCOMMON_ACTIONGENERATOR_HPP

#include <datatypes/gameplay/State.hpp>
#include <util/UUID.hpp>

namespace spy::gameplay {
    /**
     * @brief Methods to generate Operations
     */
    class ActionGenerator {
        public:
            static std::shared_ptr<BaseOperation>
            generateExfiltration(const State &s, const util::UUID &damagedCharacter);

            static std::shared_ptr<BaseOperation> generateCatAction(const State &s);

            static std::shared_ptr<BaseOperation> generateJanitorAction(const State &s);

            static std::shared_ptr<BaseOperation> generateNPCAction(const State &s, const util::UUID &activeNPC);
    };
}


#endif //LIBCOMMON_ACTIONGENERATOR_HPP
