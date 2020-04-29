//
// Created by Carolin on 29.04.2020.
//

#ifndef LIBCOMMON_BASEOPERATION_HPP
#define LIBCOMMON_BASEOPERATION_HPP

#include <util/Point.hpp>
#include <util/UUID.hpp>
#include "OperationEnum.hpp"

namespace spy::gameplay {
    class BaseOperation {
        public:

            BaseOperation() = default;

            virtual ~BaseOperation() = default;

            BaseOperation(OperationEnum type, bool successful, const util::Point &target);

            [[nodiscard]] OperationEnum getType() const;

            [[nodiscard]] bool isSuccessful() const;

            [[nodiscard]] const util::Point &getTarget() const;

        protected:
            OperationEnum type = OperationEnum::INVALID;
            bool successful;
            util::Point target;
    };
}


#endif //LIBCOMMON_BASEOPERATION_HPP
