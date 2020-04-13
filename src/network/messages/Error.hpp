//
// Created by jonas on 10.04.20.
//

#ifndef LIBCOMMON_ERROR_HPP
#define LIBCOMMON_ERROR_HPP

#include <network/MessageContainer.hpp>
#include <network/ErrorTypeEnum.hpp>

namespace spy::network::messages {
    class Error : public MessageContainer {
        public:
            Error();

            Error(util::UUID playerId, ErrorTypeEnum reason);

            [[nodiscard]] ErrorTypeEnum getReason() const;

            friend void to_json(nlohmann::json &j, const Error &e);

            friend void from_json(const nlohmann::json &j, Error &e);

            bool operator==(const Error &rhs) const;

        private:
            ErrorTypeEnum reason = ErrorTypeEnum::GENERAL;
    };
}

#endif //LIBCOMMON_ERROR_HPP
