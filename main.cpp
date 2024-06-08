#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <algorithm>

struct armorPiece {
    int mobility;
    int resilience;
    int recovery;
    int discipline;
    int intellect;
    int strength;

    std::string name;
};

class loadout {
    armorPiece headArmor;
    armorPiece armArmor;
    armorPiece chestArmor;
    armorPiece legArmor;
    armorPiece classArmor;

    public:
    loadout(armorPiece in_headArmor, armorPiece in_armArmor, armorPiece in_chestArmor, armorPiece in_legArmor, armorPiece in_classArmor) : headArmor(in_headArmor), armArmor(in_armArmor), chestArmor(in_chestArmor), legArmor(in_legArmor), classArmor(in_classArmor) {}

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

        int loadoutStatLevel = loadoutMobility / 10 + loadoutResilience / 10 + loadoutRecovery / 10 + loadoutDiscipline / 10 + loadoutIntellect / 10 + loadoutStrength / 10;
        int otherStatLevel = otherMobility / 10 + otherResilience / 10 + otherRecovery / 10 + otherDiscipline / 10 + otherIntellect / 10 + otherStrength / 10;

        return (loadoutStatLevel < otherStatLevel);
    }

    int getMobility() const {
        return headArmor.mobility + armArmor.mobility + chestArmor.mobility + legArmor.mobility + classArmor.mobility;
    }

    int getResilience() const {
        return headArmor.resilience + armArmor.resilience + chestArmor.resilience + legArmor.resilience + classArmor.resilience;
    }

    int getRecovery() const {
        return headArmor.recovery + armArmor.recovery + chestArmor.recovery + legArmor.recovery + classArmor.recovery;
    }

    int getDiscipline() const {
        return headArmor.discipline + armArmor.discipline + chestArmor.discipline + legArmor.discipline + classArmor.discipline;
    }

    int getIntellect() const {
        return headArmor.intellect + armArmor.intellect + chestArmor.intellect + legArmor.intellect + classArmor.intellect;
    }

    int getStrength() const {
        return headArmor.strength + armArmor.strength + chestArmor.strength + legArmor.strength + classArmor.strength;
    }

    friend std::ostream& operator<<(std::ostream& os, const loadout& currentLoadout);
};

std::ostream& operator<<(std::ostream& os, const loadout& currentLoadout) {
    os << "Mobility: " << currentLoadout.getMobility() << "\nResilience: " << currentLoadout.getResilience() << "\nRecovery: " << currentLoadout.getRecovery() <<
            "\nDiscipline: " << currentLoadout.getDiscipline() << "\nIntellect: " << currentLoadout.getIntellect() << "\nStrength: " << currentLoadout.getStrength() << "\n" <<
            currentLoadout.headArmor.name << " / " << currentLoadout.armArmor.name << " / " << currentLoadout.chestArmor.name << " / " << currentLoadout.legArmor.name << " / " << currentLoadout.classArmor.name;

    return os;
}

class guardian {
    std::vector<loadout> goodLoadouts;

    std::vector<armorPiece> helmets;
    std::vector<armorPiece> arms;
    std::vector<armorPiece> chests;
    std::vector<armorPiece> legs;
    std::vector<armorPiece> classArmors;

    int mobilityGoal, resilienceGoal, recoveryGoal, disciplineGoal, intellectGoal, strengthGoal;
    int mobilityModifier = 0, resilienceModifier = 0, recoveryModifier = 0, disciplineModifier = 0, intellectModifier = 0, strengthModifier = 0;

    int getRequiredMods(int statTotal, int statGoal) {
        int deficit = std::max(statGoal - statTotal, 0);
        return ceil(deficit / 10.0);
    }

    int getRequiredMobilityMods(loadout& testLoadout) {
        int mobilityTotal = testLoadout.getMobility() + mobilityModifier;
        return getRequiredMods(mobilityTotal, mobilityGoal);
    }

    int getRequiredResilienceMods(loadout& testLoadout) {
        int resilienceTotal = testLoadout.getResilience() + resilienceModifier;
        return getRequiredMods(resilienceTotal, resilienceGoal);
    }

    int getRequiredRecoveryMods(loadout& testLoadout) {
        int recoveryTotal = testLoadout.getRecovery() + recoveryModifier;
        return getRequiredMods(recoveryTotal, recoveryGoal);
    }

    int getRequiredDisciplineMods(loadout& testLoadout) {
        int disciplineTotal = testLoadout.getDiscipline() + disciplineModifier;
        return getRequiredMods(disciplineTotal, disciplineGoal);
    }

    int getRequiredIntellectMods(loadout& testLoadout) {
        int intellectTotal = testLoadout.getIntellect() + intellectModifier;
        return getRequiredMods(intellectTotal, intellectGoal);
    }

    int getRequiredStrengthMods(loadout& testLoadout) {
        int strengthTotal = testLoadout.getStrength() + strengthModifier;
        return getRequiredMods(strengthTotal, strengthGoal);
    }

    bool isLoadoutGood(loadout& testLoadout) {
        int requiredMobilityMods = getRequiredMobilityMods(testLoadout);
        int requiredResilienceMods = getRequiredResilienceMods(testLoadout);
        int requiredRecoveryMods = getRequiredRecoveryMods(testLoadout);
        int requiredDisciplineMods = getRequiredDisciplineMods(testLoadout);
        int requiredIntellectMods = getRequiredIntellectMods(testLoadout);
        int requiredStrengthMods = getRequiredStrengthMods(testLoadout);

        return (requiredMobilityMods + requiredResilienceMods + requiredRecoveryMods + requiredDisciplineMods + requiredIntellectMods + requiredStrengthMods) <= 5;
    }

    void addHeadArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, std::string name) {
        helmets.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void addArmArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, std::string name) {
        arms.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void addChestArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, std::string name) {
        chests.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void addLegArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, std::string name) {
        legs.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    void addClassArmor(int mobility, int resilience, int recovery, int discipline, int intellect, int strength, std::string name) {
        classArmors.push_back({mobility, resilience, recovery, discipline, intellect, strength, name});
    }

    public:
    guardian() : mobilityGoal(0), resilienceGoal(0), recoveryGoal(0), disciplineGoal(0), intellectGoal(0), strengthGoal(0) {}

    guardian(int mobilityGoal_in, int resilienceGoal_in, int recoveryGoal_in, int disciplineGoal_in, int intellectGoal_in, int strengthGoal_in) :
                mobilityGoal(mobilityGoal_in), resilienceGoal(resilienceGoal_in), recoveryGoal(recoveryGoal_in), disciplineGoal(disciplineGoal_in), intellectGoal(intellectGoal_in), strengthGoal(strengthGoal_in) {}

    void addArmorPiecesFromFile(std::string inputFile) {
        std::ifstream armorPieces(inputFile);
        std::string line;
        int mobility, resilience, recovery, discipline, intellect, strength;
        std::string name, type;

        while(std::getline(armorPieces, line)) {
            name = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);

            type = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);

            mobility = std::stoi(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);

            resilience = std::stoi(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);

            recovery = std::stoi(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);

            discipline = std::stoi(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);

            intellect = std::stoi(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);

            strength = std::stoi(line);

            addArmorPiece(name, type, mobility, resilience, recovery, discipline, intellect, strength);
        }
    }

    void addArmorPiece(std::string name, std::string type, int mobility, int resilience, int recovery, int discipline, int intellect, int strength) {
        if (type == "head") {
            addHeadArmor(mobility, resilience, recovery, discipline, intellect, strength, name);
        }
        else if (type == "arm") {
            addArmArmor(mobility, resilience, recovery, discipline, intellect, strength, name);
        }
        else if (type == "chest") {
            addChestArmor(mobility, resilience, recovery, discipline, intellect, strength, name);
        }
        else if (type == "leg") {
            addLegArmor(mobility, resilience, recovery, discipline, intellect, strength, name);
        }
        else if (type == "class") {
            addClassArmor(mobility, resilience, recovery, discipline, intellect, strength, name);
        }
        else {
            std::cerr << "Unknown class type " << type << std::endl;
        }
    }

    void setMobilityGoal(int goal) {
        mobilityGoal = goal;
    }

    void setResilienceGoal(int goal) {
        resilienceGoal = goal;
    }

    void setRecoveryGoal(int goal) {
        recoveryGoal = goal;
    }

    void setDisciplineGoal(int goal) {
        disciplineGoal = goal;
    }

    void setIntellectGoal(int goal) {
        intellectGoal = goal;
    }

    void setStrengthGoal(int goal) {
        strengthGoal = goal;
    }

    void setMobilityModifier(int modifier) {
        mobilityModifier = modifier;
    }

    void setResilienceModifier(int modifier) {
        resilienceModifier = modifier;
    }

    void setRecoveryModifier(int modifier) {
        recoveryModifier = modifier;
    }

    void setDisciplineModifier(int modifier) {
        disciplineModifier = modifier;
    }

    void setIntellectModifier(int modifier) {
        intellectModifier = modifier;
    }

    void setStrengthModifier(int modifier) {
        strengthModifier = modifier;
    }

    void generateLoadouts() {
        for(int helmetIndex = 0; helmetIndex < helmets.size(); helmetIndex++) {
            for(int armIndex = 0; armIndex < arms.size(); armIndex++) {
                for(int chestIndex = 0; chestIndex < chests.size(); chestIndex++) {
                    for(int legIndex = 0; legIndex < legs.size(); legIndex++) {
                        for(int classIndex = 0; classIndex < classArmors.size(); classIndex++) {
                            loadout tempLoadout(helmets.at(helmetIndex), arms.at(armIndex), chests.at(chestIndex), legs.at(legIndex), classArmors.at(classIndex));

                            if(isLoadoutGood(tempLoadout)) {
                                goodLoadouts.push_back(tempLoadout);
                            }
                        }
                    }
                }
            }
        }

        sort(goodLoadouts.begin(), goodLoadouts.end());
    }

    void printLoadouts(size_t maxLoadouts = 20) {
        if (goodLoadouts.size() == 0) {
            std::cout << "\nNo loadouts found with desired stats." << std::endl << std::endl;
        }
        else {
            for (int loadoutIndex = 0; loadoutIndex < std::min(maxLoadouts, goodLoadouts.size()); loadoutIndex++) {
                std::cout << "\nLoadout " << loadoutIndex << ":\n" << goodLoadouts.at(loadoutIndex) << std::endl << std::endl;
            }
        }
    }
};

int getNextSelection() {
    int selection;

    std::cout << "Enter selection\n" << "1. Enter desired stats\n" << "2. Add subclass stat modifiers\n" << "3. Print best loadouts\n" << "9. Quit\n" << "Selection: ";
    std::cin >> selection;

    return selection;
}

int promptInt(std::string prompt) {
    int value;

    std::cout << prompt;
    std::cin >> value;

    return value;
}

int main() {
    guardian m_guardian;
    int selection;

    do {
        selection = getNextSelection();

        if(selection == 1) {
            m_guardian.setMobilityGoal(promptInt("Desired Mobility: "));
            m_guardian.setResilienceGoal(promptInt("Desired Resilience: "));
            m_guardian.setRecoveryGoal(promptInt("Desired Recovery: "));
            m_guardian.setDisciplineGoal(promptInt("Desired Discipline: "));
            m_guardian.setIntellectGoal(promptInt("Desired Intellect: "));
            m_guardian.setStrengthGoal(promptInt("Desired Strength: "));
        }
        else if (selection == 2) {
            m_guardian.setMobilityModifier(promptInt("Mobility Modifier: "));
            m_guardian.setResilienceModifier(promptInt("Resilience Modifier: "));
            m_guardian.setRecoveryModifier(promptInt("Recovery Modifier: "));
            m_guardian.setDisciplineModifier(promptInt("Discipline Modifier: "));
            m_guardian.setIntellectModifier(promptInt("Intellect Modifier: "));
            m_guardian.setStrengthModifier(promptInt("Strength Modifier: "));
        }
        else if (selection == 3) {
            m_guardian.addArmorPiecesFromFile("armorPieces.txt");
            m_guardian.generateLoadouts();
            m_guardian.printLoadouts();
        }
    } while (selection != 9);

    return 0;
}