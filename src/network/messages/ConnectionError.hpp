//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_CONNECTIONERROR_HPP
#define LIBCOMMON_CONNECTIONERROR_HPP


#include <network/MessageContainer.hpp>
#include <network/ErrorTypeEnum.hpp>

namespace spy::network::messages {
    class ConnectionError : public MessageContainer {
        public:

            ConnectionError();

            explicit ConnectionError(ErrorTypeEnum errorType);

            [[nodiscard]] ErrorTypeEnum getReason() const;

            friend void to_json(nlohmann::json &j, const ConnectionError &c);

            friend void from_json(const nlohmann::json &j, ConnectionError &c);

        private:
            ErrorTypeEnum reason = ErrorTypeEnum::INVALID;
    };
}

#endif //LIBCOMMON_CONNECTIONERROR_HPP
