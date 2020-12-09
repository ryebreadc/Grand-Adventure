#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

class Inventory {
  public:
    static Inventory *addItem(string choice);
    virtual void io() = 0;
    virtual ~Inventory() = default;
    virtual vector<int> getStats() = 0;
    virtual int getType() = 0;
};

class Sword: public Inventory {
  private:
    vector<int> stats = {5, 6, 5};
    int weaponType = 0;
  public:
    vector<int> getStats() { return stats; }
    int getType() { return weaponType; }
    void io() { cout << "Sword\n"; }
};
class Mace: public Inventory {
  private:
    int weaponType = 0;
    vector<int> stats = {4, 8, 5};
  public:
    vector<int> getStats() { return stats; }
    int getType() { return weaponType; }
    void io() { cout << "Mace\n"; }
};
class Spear: public Inventory {
  private:
    int weaponType = 1;
    vector<int> stats = {5, 6, 7};
  public:
    vector<int> getStats() { return stats; }
    int getType() { return weaponType; }
    void io() { cout << "Spear\n"; }
};
class Crossbow: public Inventory {
  private:
    int weaponType = 2;
    vector<int> stats = {7, 3, 4};
  public:
    vector<int> getStats() { return stats; }
    int getType() { return weaponType; }
    void io() { cout << "Crossbow\n"; }
};
class Bowstaff: public Inventory {
  private:
    int weaponType = 1;
    vector<int> stats = {4, 5, 8};
  public:
    vector<int> getStats() { return stats; }
    int getType() { return weaponType; }
    void io() { cout << "Bowstaff\n"; }
};
class Fiendish_Codex: public Inventory {
  private:
    int weaponType = 2;
    vector<int> stats = {8, 2, 5};
  public:
    vector<int> getStats() { return stats; }
    int getType() { return weaponType; }
    void io() { cout << "Fiendish Codex\n"; }
};
class Mittens: public Inventory {
  private:
    int weaponType = 0;
    vector<int> stats = {1, 1, 1};
  public:
    vector<int> getStats() { return stats; }
    int getType() { return weaponType; }
    void io() { cout << "Mittens\n"; }
};

Inventory *Inventory::addItem(string choice) {
  if (choice ==  "1") return new Sword;
  else if (choice == "2") return new Mace;
  else if (choice == "3") return new Spear;
  else if (choice == "4") return new Crossbow;
  else if (choice == "5") return new Bowstaff;
  else if (choice == "6") return new Fiendish_Codex;
  else return new Mittens;
};

class advDialog {
  public:
    //TO DISPLAY MAIN MENU OPTIONS FOR THE PLAYER
    string displayOptions() {
      cout << "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << endl;
      cout << "This is your adventure, choose an option!" << endl;
      cout << "#-#" << endl;
      cout << "Choose Weapons..[1]  Display Inventory..[2]" << endl;
      cout << "Weapon Stats....[3]  Find Combat........[4]" << endl;
      cout << "Quit[0]" << endl;
      cout << "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << endl;

      string choice;
      cin >> choice;
      return choice;
    }
    //TO CHOOSE ANY NUMBER OF WEAPONS TO ADD TO INVENTORY
    vector<Inventory*> chooseWeapons() {
      vector<Inventory*> inv;
      string choice;
      cout << "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << endl;
      cout << "Pick a weapon(s) for your quest!" << endl;
      cout << "Choices include:" << endl;
      cout << "#-#" << endl;
      cout << "Sword[1]  Mace[2]  Spear[3]  Crossbow[4]" << endl;
      cout << "Bowstaff[5]  Fiendish Codex[6]  Fists[7]" << endl;
      cout << "Done[0]" << endl;
      cout << "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << endl;

      while (true) {
        cin >> choice;
        if (choice == "0") break;
        inv.push_back(Inventory::addItem(choice));
      }
      return inv;
    }
    //TO DISPLAY ALL THE OF THE PLAYERS INVENTORY
    void displayInventory(vector<Inventory*> inv) {
      for (int i = 0; i < inv.size(); i++) {
        inv[i]->io();
      }

      finished();
    }
    //TO DISPLAY ALL OF THE PLAYERS INVENTORY WITH STATS FOR COMBAT
    void displayInventoryStats(vector<Inventory*> inv) {
      vector<vector<int>> invStats;

      for(int i = 0; i < inv.size(); i++) {
        vector<int> temp = inv[i]->getStats();
        invStats.push_back(temp);
      }
      for(int i = 0; i < invStats.size(); i++) {
        cout << "[" << i + 1 << "]" << endl;
        inv[i]->io();
        for(int j = 0; j < invStats[i].size(); j++) {
          cout << invStats[i][j] << ' ';
        }
        cout << endl;
      }
    }

    void displayInventoryStatsWithFinished(vector<Inventory*> inv) {
      displayInventoryStats(inv);
      finished();
    }
    //TO INITIALIZE THE COMBAT
    void startCombat(vector<Inventory*> inv) {

      cout << "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << endl;
      cout << "You are about to enter combat!" << endl;
      cout << "What weapon will you choose?" << endl;
      cout << "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << endl;

      displayInventoryStats(inv);
    }
    //LINE TO MAKE USER HIT 0 TO PROCEED
    void finished() {
      cout << "#-#-#-#-#-#-#-#-#-#" << endl;
      cout << "Done[0]" << endl;
      cout << "#-#-#-#-#-#-#-#-#-#" << endl;
      string choice;   
      while(true) {
        cin >> choice;
        if(choice == "0") break;
      }
    }
};

class Combat {
  private:
    advDialog dialog;

  public:
    void duel(vector<Inventory*> inv) {   

      string choice;
      cin >> choice;
      int c = std::stoi(choice);

      vector<Inventory*> enemyInv;
      int ran = rand() % 6 + 1;
    
      if (ran ==  1) enemyInv.push_back(new Sword);
      else if (ran == 2) enemyInv.push_back(new Mace);
      else if (ran == 3) enemyInv.push_back(new Spear);
      else if (ran == 4) enemyInv.push_back(new Crossbow);
      else if (ran == 5) enemyInv.push_back(new Bowstaff);
      else if (ran == 6) enemyInv.push_back(new Fiendish_Codex);
      else enemyInv.push_back(new Mittens);
      cout << ran << endl;

      int playerStr;
      int playerType;
      vector<int> playerWeaponStats = inv[c - 1]->getStats();

      int enemyStr;
      int enemyType;
      vector<int> enemyWeaponStats = enemyInv[0]->getStats();

      playerType = inv[c - 1]->getType();
      enemyType = enemyInv[0]->getType();

      if(playerType == 0) {
        enemyStr = enemyWeaponStats[0];
        playerStr = playerWeaponStats[0];
      } else if (playerType == 1) {
        enemyStr = enemyWeaponStats[1];
        playerStr = playerWeaponStats[1];
      } else {
        enemyStr = enemyWeaponStats[2];
        playerStr = playerWeaponStats[2];
      }

      if(playerStr >= enemyStr) {
        cout << "You won the duel" << endl;
      } else {
        cout << "You got smashed" << endl;
      }

      dialog.finished();
      
    }
    void ambush(vector<Inventory*> inv) {

    }
};

int main() {

  advDialog dialog;
  Combat combat;
  vector<Inventory*> inv;
  
  while (true) {
    cout << "\033[2J\033[0;0H";
    string choice;
    choice = dialog.displayOptions();
    if(choice == "0") break;
    if(choice == "1") inv = dialog.chooseWeapons();
    if(choice == "2") dialog.displayInventory(inv);
    if(choice == "3") dialog.displayInventoryStatsWithFinished(inv);
    if(choice == "4") {
      dialog.startCombat(inv);
      combat.duel(inv);
    }
  }  
}