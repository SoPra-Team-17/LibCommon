/**
 * @file equipmentChoiceTest.cpp
 * @author ottojo
 * @date 09.05.20
 * Test encoding of EquipmentChoice message
 */

#include <gtest/gtest.h>
#include <network/messages/EquipmentChoice.hpp>

/**
 * Test encoding of EquipmentChoice message
 */
TEST(messages, equipmentChoice) {
    using spy::network::messages::EquipmentChoice;
    using spy::gadget::GadgetEnum;

    spy::util::UUID clientId{"845e8cc5-76d0-4ffa-bf35-2fd29ce2d842"};
    spy::util::UUID character1Id{"845e8cc5-76d0-4ffa-bf35-2fd29ce2d843"};
    spy::util::UUID character2Id{"845e8cc5-76d0-4ffa-bf35-2fd29ce2d844"};

    EquipmentChoice equipmentChoice{clientId, {
            {character1Id, {GadgetEnum::JETPACK, GadgetEnum::LASER_COMPACT}},
            {character2Id, {GadgetEnum::HAIRDRYER}}
    }};

    std::string expected =
            "{\n"
            "    \"clientId\": \"845e8cc5-76d0-4ffa-bf35-2fd29ce2d842\",\n"
            "    \"creationDate\": \"" +
            equipmentChoice.getCreationDate() +
            "\",\n"
            "    \"equipment\": {\n"
            "        \"845e8cc5-76d0-4ffa-bf35-2fd29ce2d843\": [\n"
            "            \"LASER_COMPACT\",\n"
            "            \"JETPACK\"\n"
            "        ],\n"
            "        \"845e8cc5-76d0-4ffa-bf35-2fd29ce2d844\": [\n"
            "            \"HAIRDRYER\"\n"
            "        ]\n"
            "    },\n"
            "    \"type\": \"EQUIPMENT_CHOICE\"\n"
            "}";

    nlohmann::json equipmentChoiceJson = equipmentChoice;
    EXPECT_EQ(expected, equipmentChoiceJson.dump(4));
}