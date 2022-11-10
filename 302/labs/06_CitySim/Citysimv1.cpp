/*
  Drew Friend
  11/4/22
  Graphing shorest distances between "Cities" in relation to distance and time
  Version 1
*/
#include <ios>
#include <iostream>
#define _USE_MATH_DEFINES
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

enum TYPES { LOCAL, METRO };

class city {
  string name;
  TYPES type;
  float lat, lon;
  int pop;
  float conv = M_PI / 180; // *d>r, /r>d

public:
  static int w;
  city() {}
  friend istream &operator>>(istream &in, city &c);
  friend ostream &operator<<(ostream &in, city &c);
  bool operator<(city other) { return pop < other.pop; }
  void read_cityinfo(string fname, vector<city> &cities);
};

istream &operator>>(istream &in, city &c) {
  string trash;
  in >> c.name >> trash;
  c.name += '_' + trash;
  in >> trash >> c.lat >> c.lon >> c.pop;
  c.type = (trash == "LOCAL") ? LOCAL : METRO;
  c.lat *= c.conv;
  c.lon *= c.conv;
  return in;
  // #city state type lat lng population
}
ostream &operator<<(ostream &out, city &c) {
  string type = (c.type == LOCAL) ? "LOCAL" : "METRO";
  out << left << setfill('.') << setw(c.w) << c.name            //
      << "  " << setfill(' ') << setw(8) << type << right       //
      << "  " << setw(8) << c.pop << fixed                      //
      << "  " << setw(7) << setprecision(2) << (c.lat / c.conv) //
      << "  " << setw(7) << setprecision(2) << (c.lon / c.conv);
  return out;
}

class costtable;

void city::read_cityinfo(string fname, vector<city> &cities) {
  int max_size = 0;
  ifstream fin(fname);
  string trash;
  getline(fin, trash);
  while (true) {
    if (fin.eof())
      break;
    cities.push_back(city());
    fin >> cities.back();
    if (cities.back().name.size() > max_size)
      max_size = cities.back().name.size();
  }
  fin.close();
  cities.pop_back();
  w = max_size + 3;
  sort(cities.begin(), cities.end());
  reverse(cities.begin(), cities.end());
}
void write_cityinfo(vector<city> &cities) {
  ofstream fout("city_info.txt");
  for (int i = 0; i < cities.size(); ++i) {
    fout << setw(3) << right << i << "  " << cities[i] << '\n';
  }
  fout.close();
}

// write_distancetable() {}
// write_timetable() {}

// create_citygraph() {}
// write_citygraph() {}

// dijkstra_route() {}

int city::w = 0;
int main(int argc, char *argv[]) {
  // commandline option decoding
  vector<city> cities;
  city().read_cityinfo("uscities.txt", cities);
  write_cityinfo(cities);
  // // set up costtables

  // create_citygraph()
  // if (mode == graphinfo) {
  //   write_cityinfo()
  //   write_distancetable() write_timetable()
  //   write_citygraph()
  //   return from program
  // }

  // while (not done) {
  //   enter > from, to cities dijkstra_route(costmode, from, to)
  // }
}
