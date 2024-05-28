#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>

void printBin(int *ptr) {
  for (int b = 0; b < 8; ++b) {
    std::cout << ((*ptr >> b) & 1);
  }
}

// This is where you add Weapon details
struct Weapon {
  Weapon(std::string, int, int, int, int, bool, std::vector<std::string>);
  std::string output();
  std::string name;
  int A;
  int Skill;
  int damageNormal;
  int damageCrit;
  bool isRanged;
  std::vector<std::string> specialRules;
};

Weapon::Weapon(std::string weaponName, int attacks, int skill, int normal,
               int crit, bool ranged, std::vector<std::string> SR = {}) {
  name = weaponName;
  A = attacks;
  Skill = skill;
  damageNormal = normal;
  damageCrit = crit;
  isRanged = ranged;
  specialRules = SR;
}

std::string Weapon::output() {
  std::cout << A;
  std::cout << (char)A;
  printBin(&A);
  // printBin(&Skill);
  std::cout << '\n';
  std::string ret = std::to_string((A << 4) | Skill);
  // printBin((int *)&ret[0]);

  ret.append(std::to_string((damageNormal << 4) | damageCrit));
  // printBin((int *)&ret[1]);
  // ret.append(" ");
  // ret.append(name);
  std::cout << " " << ret;
  return ret;
}

int main() {
  std::string fileName;
  std::string weapName;
  char buf;
  std::cout << "Filename: ";
  std::cin >> fileName;
  Weapon build = Weapon("Deathspitter_(Leader)", 5, 3, 4, 5, true);

  std::fstream fout;
  fout.open(fileName, std::fstream::binary | std::fstream::out);

  std::cout << "In file(0) or command line(1)? ";
  std::cin >> buf;
  if (buf == 1) {
    std::vector<char> line;
    std::cout << "Weapon Name: ";
    std::cin >> weapName;
    std::cout << "Attacks: ";
    std::cin >> buf;
    line.push_back(buf);
    std::cout << "WS/BS: ";
    line[0] = line[0] << 4 | buf;
    std::cout << "Damage (Normal): ";
    line.push_back(buf);
    std::cout << "Damage (Crit): ";
    line[1] = line[1] << 4 | buf;
  } else {
    fileName = build.output();
    char *out = (char *)&fileName;
    fout.write(out, strlen(out));
  }
  fout.close();
}