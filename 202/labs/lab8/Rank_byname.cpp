#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <numeric>
#include <map>
#include <iomanip>

using namespace std;

class name_t {
  public:
    name_t(const string n) { name = n; w = (n.size() > w) ? n.size():w; }
    bool operator<(const name_t& other) const {return name < other.name;}
    void print() const {cout << setw(w+3) << setfill('.') << left << name << ' ';}

  private:
    static int w;
    string name;
};

int name_t::w = 0;

class scores_t {
  public:
    scores_t() { mean = 0.0;}

    const void insert(const int num) { scores.push_back(num);}
    const void insert_done()  
    { 
      // for(vector<int>::iterator i = scores.begin(); i != scores.end();++i)
      //   mean += *i;
      mean = accumulate(scores.begin(), scores.end(), 0);
      mean /= scores.size();
    }
    const void print() 
    { 
      for(vector<int>::iterator i = scores.begin(); i != scores.end();++i)
        cout << setw(2) << setfill(' ') << *i << ' ';
      cout << ": " << fixed << setprecision(1) << mean << '\n';
    }

  private:
    vector<int> scores;
    float mean;
};

int main(int argc, char** argv) 
{
  ifstream fin;
  string first, last, errCheck;
  bool seen = false;

  if(argc != 2) 
  {
    // I wasn't able to run the solution executables on hydra, so I guessed what the error message would be
    cerr << "usage: ./Rank_byname K filename.txt\n";
    return 1;
  }
  fin.open(argv[1]);

  map<name_t,scores_t> NS;

  while (!fin.eof()) {
    // Name
    getline(fin, first, ' ');
    getline(fin, last, '\t');
      // I had trouble deliniating by spaces, because in file 2 there are 
      // some names with only tabs after, which is why I did this
    while(last[last.size()-1] == ' ' || last[-1] == '\t') last.erase(last.size()-1,1);
    last = last + ", " + first;
    name_t sName(last);
    scores_t sScores;

    // Scores
    getline(fin, first);
    while(first.size() != 0)
    {
        if(!isdigit(first[0]))
          first.erase(0,1);
        else
        {
          sScores.insert(stoi(first.substr(0,2)));
          first.erase(0,2);
        }
    }
    sScores.insert_done();

    //Slap it into the map if it's new
    if(!fin.eof()) 
    {
      for(map<name_t,scores_t>::iterator ptr = NS.begin(); ptr != NS.end();++ptr)
        if(!(ptr->first < sName) && !(sName < ptr->first))
          seen = true;
      if(!seen) NS.insert(make_pair(sName, sScores));
    }
  }
  fin.close();

  map<name_t,scores_t>::iterator ptr = NS.begin();
  while (ptr != NS.end()) {
    ptr->first.print();
    ptr->second.print();
    ++ptr;
  }
}