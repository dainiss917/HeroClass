#include <iostream>
#include <string>

class Guild {
public:
    std::string title;
    
    Guild(std::string t) : title(t) { 
        std::cout << "[Spawn] Guild '" << title << "' created." << std::endl; 
    }
    ~Guild() { 
        std::cout << "[Despawn] Guild '" << title << "' destroyed." << std::endl; 
    }
    void display() const { 
        std::cout << "Guild Server: '" << title << "' is still active and running." << std::endl; 
    }
};

class Weapon {
public:
    std::string weaponTitle;
    int damageValue;
    
    Weapon(std::string t, int dmg) : weaponTitle(t), damageValue(dmg) {
        std::cout << "[Spawn] Weapon '" << weaponTitle << "' forged." << std::endl;
    }
    virtual ~Weapon() { 
        std::cout << "[Despawn] Weapon '" << weaponTitle << "' destroyed." << std::endl; 
    }
    virtual void attack() const {
        std::cout << "Attacked with " << weaponTitle << " dealing " << damageValue << " damage!" << std::endl;
    }
};

class Sword : public Weapon {
public:
    int edgePower;
    
    Sword(std::string t, int dmg, int edge) : Weapon(t, dmg), edgePower(edge) {
        std::cout << "[Spawn] Sword traits applied to '" << weaponTitle << "'." << std::endl;
    }
    void attack() const override {
        int totalHit = damageValue + edgePower;
        std::cout << "Slashed with " << weaponTitle << " dealing " << totalHit << " damage!" << std::endl;
    }
};

class Potion {
public:
    int healValue;
    
    Potion(int heal) : healValue(heal) {}
    void consume() const {
        std::cout << "Potion consumed! Healed for " << healValue << " HP." << std::endl;
    }
};

class GameObject {
public:
    virtual ~GameObject() {
        std::cout << "[Despawn] GameObject generic data cleared." << std::endl;
    }
};

class Stats {
public:
    int hp;
    int mp;
    
    Stats(int h, int m) : hp(h), mp(m) {
        std::cout << "  -> Stats initialized (HP: " << hp << ", MP: " << mp << ")." << std::endl;
    }
    ~Stats() { 
        std::cout << "  -> Stats wiped from memory." << std::endl; 
    }
};

class SoulMark {
public:
    std::string seal;
    
    SoulMark(std::string s) : seal(s) {
        std::cout << "  -> SoulMark '" << seal << "' bound to entity." << std::endl;
    }
    ~SoulMark() { 
        std::cout << "  -> SoulMark faded away." << std::endl; 
    }
};

class Hero : public GameObject {
private:
    Stats playerStats;          
    SoulMark playerSeal;    
    Guild* guildRef;         
    Weapon* currentWeapon;       

public:
    std::string heroTitle;
    Hero(std::string t, int hp, int mp, std::string s)
        : heroTitle(t), playerStats(hp, mp), playerSeal(s), guildRef(nullptr), currentWeapon(nullptr) {
        std::cout << "[Spawn] Hero '" << heroTitle << "' has entered the world." << std::endl;
    }

    ~Hero() override {
        std::cout << "[Despawn] Hero '" << heroTitle << "' has died." << std::endl;
    }

    void joinGuild(Guild* g) {
        guildRef = g;
        std::cout << heroTitle << " joined the guild: " << guildRef->title << std::endl;
    }

    void equipWeapon(Weapon* w) {
        currentWeapon = w;
        std::cout << heroTitle << " equipped " << currentWeapon->weaponTitle << std::endl;
    }

    void usePotion(Potion* p) {
        if (p) {
            std::cout << heroTitle << " uses an item..." << std::endl;
            p->consume();
            playerStats.hp += p->healValue;
        }
    }

    void performAttack() const {
        if (currentWeapon) {
            std::cout << heroTitle << " attacks! ";
            currentWeapon->attack();
        } else {
            std::cout << heroTitle << " flails their fists harmlessly!" << std::endl;
        }
    }
};

int main() {
    std::cout << "--- 1. CREATING INDEPENDENT ENTITIES ---" << std::endl;
    Guild* mainGuild = new Guild("Warriors of the Heap");
    Weapon* epicSword = new Sword("Blade of Polymorphism", 50, 25);

    std::cout << "\n--- 2. SPAWNING HERO ---" << std::endl;
    Hero* playerHero = new Hero("Alaric", 100, 50, "Crest of Pointers");

    std::cout << "\n--- 3. FORMING RELATIONSHIPS ---" << std::endl;
    playerHero->joinGuild(mainGuild);
    playerHero->equipWeapon(epicSword);

    std::cout << "\n--- 4. COMBAT & ITEM USAGE ---" << std::endl;
    playerHero->performAttack();
    
    Potion hpPotion(20);
    playerHero->usePotion(&hpPotion);

    std::cout << "\n--- 5. FATAL EVENT: HERO DIES ---" << std::endl;
    delete playerHero; 

    std::cout << "\n--- 6. VERIFYING AGGREGATION SURVIVAL ---" << std::endl;
    mainGuild->display();
    std::cout << "The dropped weapon remains on the ground: ";
    epicSword->attack();

    std::cout << "\n--- 7. SERVER SHUTDOWN (MANUAL CLEANUP) ---" << std::endl;
    delete mainGuild;
    delete epicSword;

    return 0;
}
