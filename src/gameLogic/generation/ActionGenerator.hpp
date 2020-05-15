/**
* @file   ActionExecutor.hpp
* @author Carolin
* @date   04.05.2020 (creation)
* @brief  Definition of the static action generation class.
*/

#ifndef LIBCOMMON_ACTIONGENERATOR_HPP
#define LIBCOMMON_ACTIONGENERATOR_HPP

#include <datatypes/gameplay/State.hpp>
#include <datatypes/matchconfig/MatchConfig.hpp>
#include <util/UUID.hpp>
#include <datatypes/matchconfig/MatchConfig.hpp>

namespace spy::gameplay {
    /**
     * @brief Methods to generate Operations
     */
    class ActionGenerator {
        public:
            ActionGenerator() = delete;

            static std::shared_ptr<BaseOperation>
            generateExfiltration(const State &s, const util::UUID &damagedCharacter);

            static std::shared_ptr<BaseOperation> generateCatAction(const State &s);

            static std::shared_ptr<BaseOperation> generateJanitorAction(const State &s);

            static std::shared_ptr<BaseOperation>
            generateNPCAction(const State &s, const util::UUID &activeNPC, const MatchConfig &config);

            static std::shared_ptr<BaseOperation>
            generateRandomAction(const State &s, const util::UUID &activeCharacter, const MatchConfig &config);

            static std::shared_ptr<BaseOperation>
            generateRetire(const util::UUID &activeCharacter);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateMovementActions(const State &s, const util::UUID &activeCharacter, const MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateAllPropertyActions(const State &s, const util::UUID &activeCharacter, const MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateGambleActions(const State &s, const util::UUID &activeCharacter, const MatchConfig &config,
                                  const double chipPercentage=0.5);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateSpyActions(const State &s, const util::UUID &activeCharacter, const MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateAllGadgetActions(const State &s, const util::UUID &activeCharacter, const MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generatePropertyActions(const State &s, const util::UUID &activeCharacter, character::PropertyEnum property,
                                    const MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateGadgetActions(const State &s, const util::UUID &activeCharacter, gadget::GadgetEnum gadget);

        private:
            static std::vector<std::shared_ptr<BaseOperation>>
            generateObservation(const State &s, const util::UUID &activeCharacter, const MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateBangAndBurn(const State &s, const util::UUID &activeCharacter, const MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateMoleDie(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateBowlerBlade(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateChickenFeed(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateCocktail(const State &s, const util::UUID &activeCharacter);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateDiamondCollar(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateFogTin(const State &s, const util::UUID &activeCharacter);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateGasGloss(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateGrapple(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateHairDryer(const State &s, const util::UUID &activeCharacter);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateJetpack(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateLaserCompact(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateMirrorOfWilderness(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateMothballPouch(const State &s, const util::UUID &activeCharacter);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateNugget(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generatePoisonPills(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateRocketPen(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateTechnicolorPrism(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);

            static std::vector<std::shared_ptr<BaseOperation>>
            generateWiretapWithEarplugs(const State &s, const util::UUID &activeCharacter, const spy::MatchConfig &config);
    };
}


#endif //LIBCOMMON_ACTIONGENERATOR_HPP
