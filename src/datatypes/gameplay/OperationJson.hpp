//
// Created by jonas on 29.04.20.
//

#ifndef LIBCOMMON_OPERATIONJSON_HPP
#define LIBCOMMON_OPERATIONJSON_HPP


#include <memory>
#include <nlohmann/json.hpp>
#include "BaseOperation.hpp"

namespace spy::gameplay {

    class OperationJson {
        public:
            static std::shared_ptr<BaseOperation> fromJson(const nlohmann::json &j);

            static nlohmann::json toJson(std::shared_ptr<const BaseOperation> op);
    };

}
#endif //LIBCOMMON_OPERATIONJSON_HPP
