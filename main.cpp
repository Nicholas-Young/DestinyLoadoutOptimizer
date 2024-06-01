#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std;

enum statMod {mobilityMod, resilienceMod, recoveryMod, disciplineMod, intellectMod, strengthMod};

struct armorPiece {
    int mobility;
    int resilience;
    int recovery;
    int discipline;
    int intellect;
    int strength;

    string name;
};

struct loadout {
    armorPiece headArmor;
    armorPiece armArmor;
    armorPiece chestArmor;
    armorPiece legArmor;
    armorPiece classArmor;

    bool operator < (const loadout& otherLoadout) const {
        int score = 0;

        int loadoutMobility = headArmor.mobility + armArmor.mobility + chestArmor.mobility + legArmor.mobility + classArmor.mobility;
        int loadoutResilience = headArmor.resilience + armArmor.resilience + chestArmor.resilience + legArmor.resilience + classArmor.resilience;
        int loadoutRecovery = headArmor.recovery + armArmor.recovery + chestArmor.recovery + legArmor.recovery + classArmor.recovery;
        int loadoutDiscipline = headArmor.discipline + armArmor.discipline + chestArmor.discipline + legArmor.discipline + classArmor.discipline;
        int loadoutIntellect = headArmor.intellect + armArmor.intellect + chestArmor.intellect + legArmor.intellect + classArmor.intellect;
        int loadoutStrength = headArmor.strength + armArmor.strength + chestArmor.strength + legArmor.strength + classArmor.strength;

        int otherMobility = otherLoadout.headArmor.mobility + otherLoadout.armArmor.mobility + otherLoadout.chestArmor.mobility + otherLoadout.legArmor.mobility + otherLoadout.classArmor.mobility;
        int otherResilience = otherLoadout.headArmor.resilience + otherLoadout.armArmor.resilience + otherLoadout.chestArmor.resilience + otherLoadout.legArmor.resilience + otherLoadout.classArmor.resilience;
        int otherRecovery = otherLoadout.headArmor.recovery + otherLoadout.armArmor.recovery + otherLoadout.chestArmor.recovery + otherLoadout.legArmor.recovery + otherLoadout.classArmor.recovery;
        int otherDiscipline = otherLoadout.headArmor.discipline + otherLoadout.armArmor.discipline + otherLoadout.chestArmor.discipline + otherLoadout.legArmor.discipline + otherLoadout.classArmor.discipline;
        int otherIntellect = otherLoadout.headArmor.intellect + otherLoadout.armArmor.intellect + otherLoadout.chestArmor.intellect + otherLoadout.legArmor.intellect + otherLoadout.classArmor.intellect;
        int otherStrength = otherLoadout.headArmor.strength + otherLoadout.armArmor.strength + otherLoadout.chestArmor.strength + otherLoadout.legArmor.strength + otherLoadout.classArmor.strength;

        if((loadoutDiscipline / 10) < (otherDiscipline / 10)) {
            return true;
        }

        if (loadoutMobility % 10 >= 5) {
            score++;
        }
        if (otherMobility % 10 >= 5) {
            score--;
        }

        if(loadoutResilience % 10 >= 5) {
            score++;
        }
        if(otherResilience % 10 >= 5) {
            score--;
        }

        if (loadoutRecovery % 10 >= 5) {
            score++;
        }
        if(otherRecovery % 10 >= 5) {
            score--;
        }

        return score < 0;
    }
};

class guardian {
    vector<loadout> goodLoadouts;

    vector<armorPiece> helmets;
    vector<armorPiece> arms;
    vector<armorPiece> chests;
    vector<armorPiece> legs;
    vector<armorPiece> classArmors;

    int mobilityGoal, resilienceGoal, recoveryGoal, disciplineGoal, intellectGoal, strengthGoal;

    bool allowChargedWithLightMods;

    int getRequiredMobilityMods(int helmetIndex, int armIndex, int chestIndex, int legIndex, int classIndex) {
        int mobilityTotal = helmets.at(helmetIndex).mobility + arms.at(armIndex).mobility + chests.at(chestIndex).mobility + legs.at(legIndex).mobility + classArmors.at(classIndex).mobility;
        int mobilityDeficit = max(mobilityGoal - mobilityTotal, 0);
        
        if (allowChargedWithLightMods) {
            mobilityDeficit = max(mobilityDeficit - 20, 0);
        }

        return ceil(mobilityDeficit / 10.0);
    }

    int getRequiredResilienceMods(int helmetIndex, int armIndex, int chestIndex, int legIndex, int classIndex) {
        int resilienceTotal = helmets.at(helmetIndex).resilience + arms.at(armIndex).resilience + chests.at(chestIndex).resilience + legs.at(legIndex).resilience + classArmors.at(classIndex).resilience;
        int resilienceDeficit = max(resilienceGoal - resilienceTotal, 0);

        return ceil(resilienceDeficit / 10.0);
    }

    int getRequiredRecoveryMods(int helmetIndex, int armIndex, int chestIndex, int legIndex, int classIndex) {
        int recoveryTotal = helmets.at(helmetIndex).recovery + arms.at(armIndex).recovery + chests.at(chestIndex).recovery + legs.at(legIndex).recovery + classArmors.at(classIndex).recovery;
        int recoveryDeficit = max(recoveryGoal - recoveryTotal, 0);

        return ceil(recoveryDeficit / 10.0);
    }

    int getRequiredDisciplineMods(int helmetIndex, int armIndex, int chestIndex, int legIndex, int classIndex) {
        int disciplineTotal = helmets.at(helmetIndex).discipline + arms.at(armIndex).discipline + chests.at(chestIndex).discipline + legs.at(legIndex).discipline + classArmors.at(classIndex).discipline;
        int disciplineDeficit = max(disciplineGoal - disciplineTotal, 0);

        return ceil(disciplineDeficit / 10.0);
    }

    int getRequiredIntellectMods(int helmetIndex, int armIndex, int chestIndex, int legIndex, int classIndex) {
        int intellectTotal = helmets.at(helmetIndex).intellect + arms.at(armIndex).intellect + chests.at(chestIndex).intellect + legs.at(legIndex).intellect + classArmors.at(classIndex).intellect;
        int intellectDeficit = max(intellectGoal - intellectTotal, 0);

        return ceil(intellectDeficit / 10.0);
    }

    int getRequiredStrengthMods(int helmetIndex, int armIndex, int chestIndex, int legIndex, int classIndex) {
        int strengthTotal = helmets.at(helmetIndex).strength + arms.at(armIndex).strength + chests.at(chestIndex).strength + legs.at(legIndex).strength + classArmors.at(classIndex).strength;
        int strengthDeficit = max(strengthGoal - strengthTotal, 0);

        if (allowChargedWithLightMods) {
            strengthDeficit = max(strengthDeficit - 20, 0);
        }

        return ceil(strengthDeficit / 10.0);
    }

    bool isLoadoutGood(int helmetIndex, int armIndex, int chestIndex, int legIndex, int classIndex) {
        int requiredMobilityMods = getRequiredMobilityMods(helmetIndex, armIndex, chestIndex, legIndex, classIndex);
        int requiredResilienceMods = getRequiredResilienceMods(helmetIndex, armIndex, chestIndex, legIndex, classIndex);
        int requiredRecoveryMods = getRequiredRecoveryMods(helmetIndex, armIndex, chestIndex, legIndex, classIndex);
        int requiredDisciplineMods = getRequiredDisciplineMods(helmetIndex, armIndex, chestIndex, legIndex, classIndex);
        int requiredIntellectMods = getRequiredIntellectMods(helmetIndex, armIndex, chestIndex, legIndex, classIndex);
        int requiredStrengthMods = getRequiredStrengthMods(helmetIndex, armIndex, chestIndex, legIndex, classIndex);

        return (requiredMobilityMods + requiredResilienceMods + requiredRecoveryMods + requiredDisciplineMods + requiredIntellectMods + requiredStrengthMods) <= 5;
    }

    public:
    guardian(int mobilityGoal_in, int resilienceGoal_in, int recoveryGoal_in, int disciplineGoal_in, int intellectGoal_in, int strengthGoal_in, bool allowChargedWithLightMods_in) : mobilityGoal(mobilityGoal_in), resilienceGoal(resilienceGoal_in), recoveryGoal(recoveryGoal_in), disciplineGoal(disciplineGoal_in), intellectGoal(intellectGoal_in), strengthGoal(strengthGoal_in), allowChargedWithLightMods(allowChargedWithLightMods_in) {}

    void addHeadArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, string name) {
        helmets.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void addArmArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, string name) {
        arms.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void addChestArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, string name) {
        chests.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void addLegArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, string name) {
        legs.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void addClassArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, string name) {
        classArmors.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void generateLoadouts() {
        for(int helmetIndex = 0; helmetIndex < helmets.size(); helmetIndex++) {
            for(int armIndex = 0; armIndex < arms.size(); armIndex++) {
                for(int chestIndex = 0; chestIndex < chests.size(); chestIndex++) {
                    for(int legIndex = 0; legIndex < legs.size(); legIndex++) {
                        for(int classIndex = 0; classIndex < classArmors.size(); classIndex++) {
                            if(isLoadoutGood(helmetIndex, armIndex, chestIndex, legIndex, classIndex)) {
                                loadout goodLoadout;
                                goodLoadout.headArmor = helmets.at(helmetIndex);
                                goodLoadout.armArmor = arms.at(armIndex);
                                goodLoadout.chestArmor = chests.at(chestIndex);
                                goodLoadout.legArmor = legs.at(legIndex);
                                goodLoadout.classArmor = classArmors.at(classIndex);

                                goodLoadouts.push_back(goodLoadout);
                            }
                        }
                    }
                }
            }
        }

        sort(goodLoadouts.begin(), goodLoadouts.end());
    }

    void printLoadouts() {
        for (int loadoutIndex = 0; loadoutIndex < goodLoadouts.size(); loadoutIndex++) {
            int loadoutMobility = goodLoadouts.at(loadoutIndex).headArmor.mobility + goodLoadouts.at(loadoutIndex).armArmor.mobility + goodLoadouts.at(loadoutIndex).chestArmor.mobility + goodLoadouts.at(loadoutIndex).legArmor.mobility + goodLoadouts.at(loadoutIndex).classArmor.mobility;
            int loadoutResilience = goodLoadouts.at(loadoutIndex).headArmor.resilience + goodLoadouts.at(loadoutIndex).armArmor.resilience + goodLoadouts.at(loadoutIndex).chestArmor.resilience + goodLoadouts.at(loadoutIndex).legArmor.resilience + goodLoadouts.at(loadoutIndex).classArmor.resilience;
            int loadoutRecovery = goodLoadouts.at(loadoutIndex).headArmor.recovery + goodLoadouts.at(loadoutIndex).armArmor.recovery + goodLoadouts.at(loadoutIndex).chestArmor.recovery + goodLoadouts.at(loadoutIndex).legArmor.recovery + goodLoadouts.at(loadoutIndex).classArmor.recovery;
            int loadoutDiscipline = goodLoadouts.at(loadoutIndex).headArmor.discipline + goodLoadouts.at(loadoutIndex).armArmor.discipline + goodLoadouts.at(loadoutIndex).chestArmor.discipline + goodLoadouts.at(loadoutIndex).legArmor.discipline + goodLoadouts.at(loadoutIndex).classArmor.discipline;
            int loadoutIntellect = goodLoadouts.at(loadoutIndex).headArmor.intellect + goodLoadouts.at(loadoutIndex).armArmor.intellect + goodLoadouts.at(loadoutIndex).chestArmor.intellect + goodLoadouts.at(loadoutIndex).legArmor.intellect + goodLoadouts.at(loadoutIndex).classArmor.intellect;
            int loadoutStrength = goodLoadouts.at(loadoutIndex).headArmor.strength + goodLoadouts.at(loadoutIndex).armArmor.strength + goodLoadouts.at(loadoutIndex).chestArmor.strength + goodLoadouts.at(loadoutIndex).legArmor.strength + goodLoadouts.at(loadoutIndex).classArmor.strength;

            cout << "Loadout " << loadoutIndex << ":\nMobility: " << loadoutMobility << "\nResilience: " << loadoutResilience << "\nRecovery: " << loadoutRecovery << "\nDiscipline: " << loadoutDiscipline << "\nIntellect: " << loadoutIntellect << "\nStrength: " << loadoutStrength << "\n";
            cout << goodLoadouts.at(loadoutIndex).headArmor.name << " / " << goodLoadouts.at(loadoutIndex).armArmor.name << " / " << goodLoadouts.at(loadoutIndex).chestArmor.name << " / " << goodLoadouts.at(loadoutIndex).legArmor.name << " / " << goodLoadouts.at(loadoutIndex).classArmor.name << endl << endl;
        }
    }
};

int main() {
    guardian m_guardian(90, 90, 50, 0, 0, 0, true);

    //Helmets
    m_guardian.addHeadArmor(24, 8, 4, 8, 25, 4, "Insight Rover Mask");
    m_guardian.addHeadArmor(22, 4, 12, 17, 17, 4, "Tusked Allegiance Mask");
    m_guardian.addHeadArmor(4, 29, 4, 14, 13, 8, "Holdfast Mask");
    m_guardian.addHeadArmor(23, 4, 12, 15, 20, 4, "Resonant Fury Mask");
    m_guardian.addHeadArmor(8, 9, 22, 4, 15, 18, "Shadow's Mask");
    m_guardian.addHeadArmor(4, 17, 18, 24, 4, 10, "Equitis Shade Cowl");
    m_guardian.addHeadArmor(20, 9, 8, 14, 11, 14, "Iron Fellowship Casque");
    m_guardian.addHeadArmor(18, 12, 8, 21, 12, 4, "Legacy's Oath Mask");
    m_guardian.addHeadArmor(22, 4, 12, 21, 8, 8, "Mask of the Emperor's Agent");
    m_guardian.addHeadArmor(17, 8, 12, 4, 24, 9, "Mask of the Great Hunt");
    m_guardian.addHeadArmor(20, 4, 14, 13, 22, 4, "Pyrrhic Ascent Mask");
    m_guardian.addHeadArmor(14, 4, 19, 10, 12, 13, "Deep Explorer Mask");
    m_guardian.addHeadArmor(29, 4, 4, 12, 16, 8, "Twisting Echo Mask");
    m_guardian.addHeadArmor(9, 4, 24, 8, 16, 11, "Cowl of Righteousness");
    m_guardian.addHeadArmor(16, 11, 8, 9, 19, 9, "Helm of the Ace-Defiant");
    m_guardian.addHeadArmor(24, 8, 4, 4, 14, 19, "Iron Forerunner Mask");
    m_guardian.addHeadArmor(23, 4, 9, 24, 10, 4, "Mask of Feltroc");
    m_guardian.addHeadArmor(16, 8, 10, 4, 32, 4, "Pathfinder's Helmet");
    m_guardian.addHeadArmor(11, 14, 12, 13, 11, 12, "Prime Zealot Mask");

    //Arms
    m_guardian.addArmArmor(26, 4, 8, 10, 23, 4, "Prime Zealot Gloves");
    m_guardian.addArmArmor(24, 8, 8, 11, 14, 14, "Holdfast Grips");
    m_guardian.addArmArmor(14, 16, 8, 8, 24, 8, "Flowing Grips (CODA)");
    m_guardian.addArmArmor(11, 12, 13, 18, 16, 4, "Gloves of the Emperor's Agent");
    m_guardian.addArmArmor(14, 13, 12, 8, 14, 17, "Grips of the Ace-Defiant");
    m_guardian.addArmArmor(4, 15, 17, 11, 24, 4, "Grips of the Great Hunt");
    m_guardian.addArmArmor(13, 4, 21, 24, 4, 8, "Iron Truage Grips");
    m_guardian.addArmArmor(14, 18, 8, 14, 4, 20, "Legacy's Oath Grips");
    m_guardian.addArmArmor(24, 8, 4, 17, 14, 4, "Moonfang-X7 Grips");
    m_guardian.addArmArmor(15, 4, 20, 8, 4, 28, "Pyrrhic Ascent Grasps");
    m_guardian.addArmArmor(18, 9, 10, 8, 4, 25, "Resonant Fury Grips");
    m_guardian.addArmArmor(23, 4, 9, 11, 22, 4, "Prime Zealot Gloves");
    m_guardian.addArmArmor(12, 11, 15, 12, 8, 15, "Bladesmith's Memory Grips");
    m_guardian.addArmArmor(22, 4, 9, 22, 4, 13, "Grips of Exaltation");
    m_guardian.addArmArmor(12, 4, 20, 9, 4, 24, "Grips of Feltroc");
    m_guardian.addArmArmor(24, 4, 9, 10, 15, 10, "Iron Fellowship Grips");
    m_guardian.addArmArmor(24, 11, 4, 9, 21, 4, "Iron Forerunner Grips");
    m_guardian.addArmArmor(10, 8, 16, 15, 10, 14, "Prime Zealot Gloves");

    //Chest
    m_guardian.addChestArmor(5, 5, 31, 17, 15, 4, "Sixth Coyote A");
    m_guardian.addChestArmor(25, 5, 13, 15, 9, 11, "Sixth Coyote B");
    m_guardian.addChestArmor(15, 13, 11, 17, 4, 15, "Sixth Coyote C");
    m_guardian.addChestArmor(19, 16, 5, 4, 24, 9, "Sixth Coyote D");

    //Legs
    m_guardian.addLegArmor(22, 12, 4, 12, 24, 4, "Legacy's Oath Strides A");
    m_guardian.addLegArmor(19, 16, 4, 4, 16, 18, "Deep Explorer Strides");
    m_guardian.addLegArmor(25, 10, 4, 8, 18, 10, "Iron Truage Boots");
    m_guardian.addLegArmor(23, 9, 4, 10, 11, 18, "Moonfang-X7 Strides");
    m_guardian.addLegArmor(4, 10, 24, 10, 16, 11, "Strides of the Great Hunt");
    m_guardian.addLegArmor(8, 20, 11, 25, 8, 4, "Boots of Feltroc");
    m_guardian.addLegArmor(18, 16, 4, 10, 14, 14, "Boots of the Emeperor's Agent");
    m_guardian.addLegArmor(11, 4, 23, 4, 22, 11, "Flowing Boots (CODA)");
    m_guardian.addLegArmor(17, 10, 11, 4, 21, 14, "Iron Forerunner Strides A");
    m_guardian.addLegArmor(18, 8, 12, 4, 16, 16, "Iron Forerunner Strides B");
    m_guardian.addLegArmor(13, 4, 20, 28, 8, 4, "Iron Forerunner Strides C");
    m_guardian.addLegArmor(4, 13, 21, 18, 9, 8, "Iron Remembrance Strides");
    m_guardian.addLegArmor(25, 10, 4, 17, 4, 16, "Legacy's Oath Strides B");
    m_guardian.addLegArmor(14, 11, 12, 4, 16, 17, "Deep Explorer Strides");
    m_guardian.addLegArmor(14, 11, 12, 10, 16, 11, "Resonant Fury Strides");
    m_guardian.addLegArmor(9, 11, 14, 17, 17, 4, "Bladesmith's Memory Strides");
    m_guardian.addLegArmor(17, 10, 9, 12, 17, 8, "Twisting Echo Strides");
    m_guardian.addLegArmor(4, 9, 23, 9, 4, 24, "Boots of the Ace-Defiant");
    m_guardian.addLegArmor(17, 16, 4, 23, 9, 4, "Equitis Shade Boots");
    m_guardian.addLegArmor(8, 18, 14, 4, 20, 10, "Iron Fellowship Strides");
    m_guardian.addLegArmor(11, 8, 17, 11, 18, 9, "Iron Truage Boots");
    m_guardian.addLegArmor(8, 4, 22, 13, 12, 14, "Prime Zealot Strides");
    m_guardian.addLegArmor(26, 8, 4, 4, 27, 4, "Red Moon Phantom Steps");
    m_guardian.addLegArmor(11, 16, 10, 9, 11, 16, "Shadow's Strides");
    m_guardian.addLegArmor(16, 8, 12, 14, 14, 8, "Solstice Strides (Magnificent)");

    //Cloak
    m_guardian.addClassArmor(2, 2, 2, 2, 2, 2, "Cloak of Remembrance");

    m_guardian.generateLoadouts();
    m_guardian.printLoadouts();

    cout << "Done" << endl;

    return 0;
}