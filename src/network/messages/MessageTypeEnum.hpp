//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_MESSAGETYPEENUM_HPP
#define LIBCOMMON_MESSAGETYPEENUM_HPP

#endif //LIBCOMMON_MESSAGETYPEENUM_HPP

#include <nlohmann/json.hpp>

namespace spy::network::messages {
    enum class MessageTypeEnum {
            INVALID,
            // Spielinitialisierung
            HELLO,
            HELLO_REPLY,
            RECONNECT,
            GAME_STARTED,
            // Wahlphase
            REQUEST_ITEM_CHOICE,
            ITEM_CHOICE,
            REQUEST_EQUIPMENT_CHOICE,
            EQUIPMENT_CHOICE,
            // Spielphase
            GAME_STATUS,
            REQUEST_GAME_OPERATION,
            GAME_OPERATION,
            // Spielende
            STATISTICS,
            // Kontrollnachrichten
            GAME_LEAVE,
            GAME_LEFT,
            REQUEST_GAME_PAUSE,
            GAME_PAUSE,
            REQUEST_META_INFORMATION,
            META_INFORMATION,
            STRIKE,
            ERROR,
            // Optionale Komponenten
            REQUEST_REPLAY,
            REPLAY
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(MessageTypeEnum, {
        { MessageTypeEnum::INVALID, nullptr },
        { MessageTypeEnum::HELLO, "HELLO" },
        { MessageTypeEnum::HELLO_REPLY, "HELLO_REPLY" },
        { MessageTypeEnum::RECONNECT, "RECONNECT" },
        { MessageTypeEnum::GAME_STARTED, "GAME_STARTED" },
        { MessageTypeEnum::REQUEST_ITEM_CHOICE, "REQUEST_ITEM_CHOICE" },
        { MessageTypeEnum::ITEM_CHOICE, "ITEM_CHOICE" },
        { MessageTypeEnum::REQUEST_EQUIPMENT_CHOICE, "REQUEST_EQUIPMENT_CHOICE" },
        { MessageTypeEnum::EQUIPMENT_CHOICE, "EQUIPMENT_CHOICE" },
        { MessageTypeEnum::GAME_STATUS, "GAME_STATUS" },
        { MessageTypeEnum::REQUEST_GAME_OPERATION, "REQUEST_GAME_OPERATION" },
        { MessageTypeEnum::GAME_OPERATION, "GAME_OPERATION" },
        { MessageTypeEnum::STATISTICS, "STATISTICS" },
        { MessageTypeEnum::GAME_LEAVE, "GAME_LEAVE" },
        { MessageTypeEnum::GAME_LEFT, "GAME_LEFT" },
        { MessageTypeEnum::REQUEST_GAME_PAUSE, "REQUEST_GAME_PAUSE" },
        { MessageTypeEnum::GAME_PAUSE, "GAME_PAUSE" },
        { MessageTypeEnum::REQUEST_META_INFORMATION, "REQUEST_META_INFORMATION" },
        { MessageTypeEnum::META_INFORMATION, "META_INFORMATION" },
        { MessageTypeEnum::STRIKE, "STRIKE" },
        { MessageTypeEnum::ERROR, "ERROR" },
        { MessageTypeEnum::REQUEST_REPLAY, "REQUEST_REPLAY" },
        { MessageTypeEnum::REPLAY, "REPLAY" }
    })
}