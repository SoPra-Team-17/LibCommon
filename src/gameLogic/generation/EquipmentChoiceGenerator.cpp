//
// Created by Carolin on 07.05.2020.
//

#include "EquipmentChoiceGenerator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    std::map<util::UUID, std::set<gadget::GadgetEnum>>
    EquipmentChoiceGenerator::getRandomEquipmentChoice(const std::vector<util::UUID>& chosenCharacterIds,
                                                       const std::vector<spy::gadget::GadgetEnum>& chosenGadgets) {
        std::map<util::UUID, std::set<gadget::GadgetEnum>> m;
        for (auto id: chosenCharacterIds) {
            m[id];  //add all keys to map
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        auto g = chosenGadgets;

        while (!g.empty()) {
            for (auto id: chosenCharacterIds) {
                if (g.empty()) {
                    return m;
                }
                std::uniform_int_distribution<unsigned int> randNum(0, g.size());
                unsigned int num = randNum(gen);
                for (unsigned int i = 0; i < num; i++) {
                    auto gbuf = util::GameLogicUtils::getRandomItemFromContainer(g);
                    g.erase(gbuf);
                    m.at(id).insert(*gbuf);
                }
            }
        }

        return m;
    }
}