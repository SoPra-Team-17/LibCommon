//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_STRIKE_HPP
#define LIBCOMMON_STRIKE_HPP

#include <network/MessageContainer.hpp>

namespace spy::network::messages {

    class Strike : public MessageContainer {
        public:
            Strike();

            Strike(const util::UUID &playerId, const int strikeNr, const int strikeMax, std::string reason);

            [[nodiscard]]  int getStrikeNr() const;

            [[nodiscard]] int getStrikeMax() const;

            [[nodiscard]] const std::string &getReason() const;

            friend void to_json(nlohmann::json &j, const Strike &s);

            friend void from_json(const nlohmann::json &j, Strike &s);

            bool operator==(const Strike &rhs) const;

        private:
            int strikeNr;
            int strikeMax;
            std::string reason;
    };

}


#endif //LIBCOMMON_STRIKE_HPP
