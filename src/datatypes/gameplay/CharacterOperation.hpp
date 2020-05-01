/**
 * @file   Operation.hpp
 * @author Jonas
 * @brief  Generic gameplay operation
 */

#ifndef LIBCOMMON_CHARACTEROPERATION_HPP
#define LIBCOMMON_CHARACTEROPERATION_HPP


#include <datatypes/gameplay/OperationEnum.hpp>
#include <util/Point.hpp>
#include <util/UUID.hpp>
#include <util/OptionalSerialization.hpp>
#include "BaseOperation.hpp"

namespace spy::gameplay {
    class CharacterOperation : public BaseOperation {
        public:


            [[nodiscard]] const util::UUID &getCharacterId() const;

            static void common_to_json(nlohmann::json &j, const CharacterOperation &op);

            static void common_from_json(const nlohmann::json &j, CharacterOperation &op);

            virtual ~CharacterOperation() override = default;

        protected:
            CharacterOperation() = default;

            CharacterOperation(OperationEnum type, bool successful, const util::Point &target);

            CharacterOperation(OperationEnum type, bool successful, const util::Point &target, util::UUID characterId);

            /**
             * Compare the common elements of CharacterOperation, excluding inherited members.
             * This is intentionally not in operator== to prevent overriding.
             * This is intended to be used in operator== of deriving classes.
             */
            [[nodiscard]] bool isCharacterEqual(const CharacterOperation &rhs) const;

        private:

            [[nodiscard]] bool isEqual(const BaseOperation &rhs) const override = 0;

            util::UUID characterId;
    };
}

#endif //LIBCOMMON_CHARACTEROPERATION_HPP
