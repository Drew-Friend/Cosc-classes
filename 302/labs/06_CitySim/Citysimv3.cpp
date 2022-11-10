/*
  Drew Friend
  11/6/22
  Graphing shorest distances between "Cities" in relation to distance and time
  Version 3
  Score: ???/175
*/

// My output is not formatted correctly, due to time, but you can see the
// begining of the work in the show_route function.
#include <corecrt_math_defines.h>
#include <ios>
#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

enum TYPES { LOCAL, METRO, REGIONAL, NATIONAL };
float conv = M_PI / 180; // *d>r, /r>d

class city {
  string name;
  TYPES type;
  float lat, lon;
  int pop;

public:
  static int w;
  city() {}
  friend istream &operator>>(istream &in, city &c);
  friend ostream &operator<<(ostream &in, city &c);
  // bool operator<(city other) { return pop < other.pop; }
  bool operator<(const city other) const { return pop < other.pop; }
  void read_cityinfo(string fname, vector<city> &cities);
  int getPop() { return pop; }
  float getLat() { return lat; }
  float getLon() { return lon; }
  string getName() { return name; }
  TYPES getType() { return type; }
  void setType(TYPES newType) { this->type = newType; }
};

istream &operator>>(istream &in, city &c) {
  string trash;
  in >> c.name >> trash;
  c.name += '_' + trash;
  in >> trash >> c.lat >> c.lon >> c.pop;
  c.type = (trash == "LOCAL") ? LOCAL : METRO;
  c.lat *= conv;
  c.lon *= conv;
  return in;
  // #city state type lat lng population
}
ostream &operator<<(ostream &out, city &c) {
  string type;
  if (c.type == LOCAL) {
    type = "LOCAL";
  } else if (c.type == REGIONAL) {
    type = "REGIONAL";
  } else {
    type = "NATIONAL";
  }
  out << left << setfill('.') << setw(c.w) << c.name          //
      << "  " << setfill(' ') << setw(8) << type << right     //
      << "  " << setw(8) << c.pop << fixed                    //
      << "  " << setw(7) << setprecision(2) << (c.lat / conv) //
      << "  " << setw(7) << setprecision(2) << (c.lon / conv);
  return out;
}

class costtable {
public:
  vector<vector<float>> table;
  costtable(int size);
  vector<float> &operator[](int i) { return table[i]; }
};
costtable::costtable(int size) {
  table.resize(size);
  // for (auto row : table)
  //   row.resize(size);
  for (int i = 0; i < size; ++i)
    table[i].resize(size, 0.0);
}

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
    fout << setw(4) << right << i << "  " << cities[i] << '\n';
  }
  fout.close();
}

void create_citydist(costtable &dists, vector<city> cities) {
  string trash;
  for (int i = 0; i < cities.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      dists[i][j] =
          7964 *
          asin(sqrt(
              pow(sin((cities[i].getLat() - cities[j].getLat()) / 2), 2) +
              cos(cities[i].getLat()) * cos(cities[j].getLat()) *
                  pow(sin((cities[i].getLon() - cities[j].getLon()) / 2), 2)));
      dists[i][j] = 5 * round(dists[i][j] / 5);
    }
  }
}
void create_citytime(costtable dists, costtable &times, vector<vector<int>> adj,
                     vector<city> cities) {
  for (int i = 0; i < cities.size(); ++i) {
    for (int j = 0; j < adj.size(); ++j) {
      int k = adj[j][1];
      if (adj[j][0] == i) {
        if (cities[i].getType() == NATIONAL && cities[k].getType() == NATIONAL)
          times[i][k] = dists[i][k] / 500;
        else
          times[i][k] = dists[i][k] / 55;
      }
    }
  }
}
void create_citygraph(vector<city> &cities, vector<vector<int>> &adj,
                      costtable dists) {
  // For each city:
  // If it's big enough, and there are no nearby national cities, bump it up
  // because it is previously sorted, you only need to check previously set
  // cities
  for (int i = 0; i < cities.size(); ++i)
    if (cities[i].getType() == METRO) {
      if (cities[i].getPop() >= 2000000) {
        cities[i].setType(NATIONAL);
        for (int j = 0; j < i; ++j) {
          if (dists[i][j] < 200 && cities[j].getType() == NATIONAL) {
            cities[i].setType(REGIONAL);
          }
        }
      } else if (cities[i].getPop() >= 500000) {
        cities[i].setType(REGIONAL);
      } else {
        cities[i].setType(LOCAL);
      }
    }

  // For each city: check connections based on rules in html
  for (int i = 0; i < cities.size(); ++i) {

    if (cities[i].getType() == NATIONAL) {
      for (int j = 0; j < i; ++j)
        if (cities[j].getType() == NATIONAL)
          adj.push_back({i, j});
    } else if (cities[i].getType() == REGIONAL) {
      int min1 = -1, min2 = -1, min3 = -1;
      for (int j = 0; j < i; ++j) {
        if ((dists[i][j] < dists[i][min1] || min1 == -1) &&
            cities[j].getType() != LOCAL) {
          min2 = min1;
          min1 = j;
        } else if ((dists[i][j] < dists[i][min2] || min2 == -1) &&
                   cities[j].getType() != LOCAL) {
          min3 = min2;
          min2 = j;
        } else if ((dists[i][j] < dists[i][min3] || min3 == -1) &&
                   cities[j].getType() != LOCAL) {
          min3 = j;
        }
      }
      adj.push_back({i, min1});
      adj.push_back({i, min2});
      adj.push_back({i, min3});
    } else {
      for (int j = 0; j < i; ++j) {
        if (cities[j].getType() == LOCAL && dists[i][j] <= 75)
          adj.push_back({i, j});
      }
      int min1 = -1, min2 = -1;
      for (int j = 0; j < i; ++j) {
        if ((dists[i][j] < dists[i][min1] || min1 == -1) &&
            cities[j].getType() != LOCAL) {
          min2 = min1;
          min1 = j;
        } else if ((dists[i][j] < dists[i][min2] || min2 == -1) &&
                   cities[j].getType() != LOCAL) {
          min2 = j;
        }
      }
      adj.push_back({i, min1});
      adj.push_back({i, min2});
    }
  }
}

void write_distancetable(vector<city> &cities, costtable &dists,
                         vector<vector<int>> adj) {
  bool used = false;
  vector<int> seen;
  ofstream fout("city_dist.txt");
  for (int i = 1; i < cities.size(); ++i) {
    used = false;
    seen.clear();
    for (int j = 0; j < adj.size(); ++j) {
      if (adj[j][0] == i && !count(seen.begin(), seen.end(), j)) {
        used = true;
        seen.push_back(j);
        fout << setw(4) << right << i << "  " << setfill('.') << left
             << setw(cities[i].w) << cities[i].getName() << " to " << fixed
             << setprecision(1) << setw(cities[i].w)
             << cities[adj[j][1]].getName() << "  " << setprecision(1)
             << setfill(' ') << setw(6) << right << dists[i][adj[j][1]]
             << " miles\n";
      }
    }
    if (used)
      fout << '\n';
  }
  fout.close();
}
void write_timetable(vector<city> &cities, costtable &times,
                     vector<vector<int>> adj) {
  bool used = false;
  vector<int> seen;
  ofstream fout("city_time.txt");
  for (int i = 1; i < cities.size(); ++i) {
    used = false;
    seen.clear();
    for (int j = 0; j < adj.size(); ++j) {
      used = true;
      if (adj[j][0] == i && !count(seen.begin(), seen.end(), j)) {
        seen.push_back(j);
        fout << setw(4) << right << i << "  " << setfill('.') << left
             << setw(cities[i].w) << cities[i].getName() << " to " << fixed
             << setprecision(1) << setw(cities[i].w)
             << cities[adj[j][1]].getName() << "  " << setprecision(1)
             << setfill(' ') << setw(6) << right << times[i][adj[j][1]]
             << " hours\n";
      }
    }
    if (used)
      fout << '\n';
  }
  fout.close();
}
void write_citygraph(vector<city> &cities, costtable &dists, costtable &time,
                     vector<vector<int>> adj) {
  int k = -1;
  vector<int> seen;
  ofstream fout("city_graph.txt");
  for (int i = 0; i < cities.size(); ++i) {
    seen.clear();
    k = -1;
    fout << setw(4) << right << i << " " << cities[i].getName() << '\n';
    for (int j = 0; j < adj.size(); ++j) {
      if (adj[j][0] == i)
        k = adj[j][1];
      else if (adj[j][1] == i)
        k = adj[j][0];
      if (k != -1 && !count(seen.begin(), seen.end(), k)) {
        seen.push_back(k);
        fout << setw(6) << right << k << " " << left << setw(cities[i].w)
             << setfill('.') << cities[k].getName() << "  " << right;
        if (i > k)
          fout << fixed << setprecision(1) << setfill(' ') << setw(6)
               << dists[i][k] << " miles  " << time[i][k] << " hours\n";
        else
          fout << fixed << setprecision(1) << setfill(' ') << setw(6)
               << dists[k][i] << " miles  " << time[k][i] << " hours\n";
      }
    }
    fout << '\n';
  }
  fout.close();
}

void trim_table(vector<vector<int>> &adj) {
  for (auto pair : adj)
    sort(pair.begin(), pair.end());
  sort(adj.begin(), adj.end());
  adj.erase(unique(adj.begin(), adj.end()), adj.end());
}
// vvvvv Handout code vvvvv
template <typename Tkey, typename Twgt> class graph {
public:
  // void dijkstra_route(Tkey &, Tkey &);
  void dijkstra_route(int, int);
  graph() {}
  void read(vector<Tkey>, vector<vector<int>>, costtable);
  void print();
  void show_route(int, int);

private:
  enum { WGT_UNDIRECTED, WGT_DIRECTED } graph_type;
  vector<Tkey> V;         // vertex list
  vector<vector<int>> E;  // edge matrix
  vector<vector<Twgt>> W; // weight matrix
  map<Tkey, int> key_map; // key-to-index map
  enum vcolor_t { WHITE, BLACK };
  vector<vcolor_t> vcolor;
  vector<Twgt> vdist;
  vector<int> vlink;
};
template <typename Tkey, typename Twgt>
void graph<Tkey, Twgt>::read(vector<Tkey> cities, vector<vector<int>> adj,
                             costtable weights) {
  // Determine graph type: WGT_UNDIRECTED or WGT_DIRECTED
  // Create mapping from key to index
  vector<pair<int, int>> Eij;
  vector<Twgt> Wij;
  // while (in >> key1 >> key2 >> wgt) {
  //   key_map.insert(make_pair(key1, key_map.size()));
  //   key_map.insert(make_pair(key2, key_map.size()));
  //   Eij.push_back(make_pair(key_map[key1], key_map[key2]));
  //   Wij.push_back(wgt);
  // }
  for (int i = 0; i < adj.size(); ++i) {
    key_map.insert(make_pair(cities[adj[i][0]], adj[i][0]));
    key_map.insert(make_pair(cities[adj[i][1]], adj[i][1]));
    Eij.push_back(
        make_pair(key_map[cities[adj[i][0]]], key_map[cities[adj[i][1]]]));
    Wij.push_back((weights[adj[i][0]][adj[i][1]] == 0)
                      ? weights[adj[i][1]][adj[i][0]]
                      : weights[adj[i][0]][adj[i][1]]);
  }
  // Create vertex list and edge matrix
  V.resize(key_map.size());
  E.resize(key_map.size());
  W.resize(key_map.size());
  typename map<Tkey, int>::iterator kmp;
  for (kmp = key_map.begin(); kmp != key_map.end(); ++kmp)
    V[kmp->second] = kmp->first;
  vector<map<int, Twgt>> EW;
  EW.resize(key_map.size());
  for (int k = 0; k < (int)Eij.size(); k++) {
    int i = Eij[k].first;
    int j = Eij[k].second;
    Twgt w = Wij[k];
    EW[i].insert(make_pair(j, w));
    if (graph_type == WGT_UNDIRECTED)
      EW[j].insert(make_pair(i, w));
  }
  typename map<int, Twgt>::iterator p;
  for (int i = 0; i < (int)EW.size(); i++) {
    for (p = EW[i].begin(); p != EW[i].end(); ++p) {
      E[i].push_back(p->first);
      W[i].push_back(p->second);
    }
  }
}

template <typename Tkey, typename Twgt>
void graph<Tkey, Twgt>::dijkstra_route(int source, int sink) {
  vcolor.assign(V.size(), WHITE);
  vdist.assign(V.size(), numeric_limits<Twgt>::max());
  vdist[source] = 0;
  vlink.assign(V.size(), -1);
  vlink[source] = source;
  while (1) {
    int next_i = -1;
    Twgt mindist = numeric_limits<Twgt>::max();
    for (int i = 0; i < (int)vcolor.size(); i++) {
      if (vcolor[i] == WHITE && mindist > vdist[i]) {
        next_i = i;
        mindist = vdist[i];
      }
    }
    int i = next_i;
    if (i == -1)
      return;
    vcolor[i] = BLACK;
    if (i == sink)
      break;

    for (int k = 0; k < (int)E[i].size(); k++) {
      int j = E[i][k];
      Twgt wij = W[i][k];
      if (vcolor[j] == BLACK)
        continue;
      if (vdist[j] > vdist[i] + wij) {
        vdist[j] = vdist[i] + wij;
        vlink[j] = i;
      }
    }
  }
}

template <typename Tkey, typename Twgt> void graph<Tkey, Twgt>::print() {
  for (int i = 0; i < (int)V.size(); i++) {
    cout << setw(3) << right << i << " " << V[i] << ": ";
    for (int k = 0; k < (int)E[i].size(); k++) {
      int j = E[i][k];
      cout << V[j] << "  \n";
    }
    cout << "\n";
  }
}

template <typename Tkey, typename Twgt>
void graph<Tkey, Twgt>::show_route(int source, int sink) {
  if (vdist[sink] == INT_MAX) {
    cout << "No path from\n";
    return;
  }
  stack<int> S;
  for (int i = sink; i != source; i = vlink[i])
    S.push(i);
  S.push(source);
  float totalD = 0, totalT = 0;
  while (!S.empty()) {
    int i = S.top();
    S.pop();
    cout << setw(3) << i << " " << V[i] << " " << setw(3) << vdist[i] << "\n";

    // cout << fixed << setw(8) << setprecision(2) << right << totalD << " miles
    // "
    //      << setw(5) << setprecision(2) << totalT << " hours " << setw(3) << i
    //      << " " << right << V[i] << vdist[i] <<
  }
}
// ^^^^^ Handout code ^^^^^

int city::w = 0;
int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage:   ./Citysim -[mode] [filename].txt";
    return 1;
  }
  string mode = argv[1];
  string fname = argv[2];
  // commandline option decoding
  graph<city, float> dij;
  vector<city> cities;
  vector<vector<int>> adj_table;

  city().read_cityinfo(fname, cities);

  costtable dist_table(cities.size());
  costtable time_table(cities.size());
  create_citydist(dist_table, cities);

  create_citygraph(cities, adj_table, dist_table);
  trim_table(adj_table);
  create_citytime(dist_table, time_table, adj_table, cities);

  // Make Files
  if (mode == "-info") {
    write_cityinfo(cities);
    write_distancetable(cities, dist_table, adj_table);
    write_timetable(cities, time_table, adj_table);
    write_citygraph(cities, dist_table, time_table, adj_table);
    return 0;
  }

  else if (mode == "-time")
    dij.read(cities, adj_table, time_table);
  else if (mode == "-dist")
    dij.read(cities, adj_table, dist_table);

  string enter, exit;
  cout << "Enter> ";
  while (cin >> enter >> exit) {
    for (int city1 = 0; city1 < cities.size(); ++city1) {
      if (cities[city1].getName() == enter) {
        for (int city2 = 0; city2 < cities.size(); ++city2) {
          if (cities[city2].getName() == exit) {
            dij.dijkstra_route(city1, city2);
            dij.show_route(city1, city2);
          }
        }
      }
    }
    cout << "Enter> ";
  }
}
