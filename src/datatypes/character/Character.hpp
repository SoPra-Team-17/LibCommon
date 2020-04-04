//
// Created by Carolin on 02.04.2020.
//

#ifndef LIBCOMMON_CHARACTER_HPP
#define LIBCOMMON_CHARACTER_HPP

#include <string>
#include <list>
#include <util/Point.hpp>
#include <datatypes/gadgets/Gadget.hpp>
#include <datatypes/character/PropertyEnum.hpp>
#include <util/UUID.hpp>

namespace spy::character {
    class Character {
    public:
        Character(util::UUID &character_id,
                  std::string &name)
                : characterId(character_id),
                  name(name),
                  coordinates{spy::util::Point{}},
                  mp(0),
                  ap(0),
                  hp(100),
                  ip(0),
                  chips(10),
                  properties({}),
                  gadgets({}) {}

        // setter and getter
        [[nodiscard]] const util::UUID &getCharacterId() const;

        [[nodiscard]] const std::string &getName() const;

        [[nodiscard]] const util::Point &getCoordinates() const;

        void setCoordinates(const util::Point &coordinates);

        [[nodiscard]] unsigned int getMp() const;

        void setMp(unsigned int mp);

        [[nodiscard]] unsigned int getAp() const;

        void setAp(unsigned int ap);

        [[nodiscard]] unsigned int getHp() const;

        void setHp(unsigned int hp);

        [[nodiscard]] unsigned int getIp() const;

        void setIp(unsigned int ip);

        [[nodiscard]] unsigned int getChips() const;

        void setChips(unsigned int chips);

        [[nodiscard]] const std::list<PropertyEnum> &getProperties() const;

        void setProperties(const std::list<PropertyEnum> &properties);

        [[nodiscard]] const std::list<gadget::Gadget> &getGadgets() const;

        void setGadgets(const std::list<gadget::Gadget> &gadgets);

    private:
        const spy::util::UUID characterId;
        const std::string name;
        spy::util::Point coordinates;
        unsigned int mp;  // MovePoints
        unsigned int ap;  // ActionsPoints
        unsigned int hp;  // HealthPoints
        unsigned int ip;  // IntelligencePoints
        unsigned int chips;
        std::list<PropertyEnum> properties;
        std::list<spy::gadget::Gadget> gadgets;
    };
}

#endif //LIBCOMMON_CHARACTER_HPP
