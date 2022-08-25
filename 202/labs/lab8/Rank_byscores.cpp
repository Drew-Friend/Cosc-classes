#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <numeric>
#include <map>
#include <iomanip>
#include <algorithm>

using namespace std;


class name_t {
  public:
    name_t(){}
    name_t(const string n) { name = n; w = (n.size() > w) ? n.size():w; }
    bool operator<(const name_t& other) const {return name < other.name;}
    void print() const {cout << setw(w+3) << setfill('.') << left << name << ' ';}

  private:
    static int w;
    string name;
};

// class name_t {
//   public:
//     constructor(s);
//     bool operator<(...);
//     void print();
//   private:
// 	static int w;
//     string name;
// };

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
    bool operator<(const scores_t& other) const {return mean < other.mean;}
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

// class scores_t {
//   public:
//     constructor(s);
//     bool operator<(...)
//     void insert(int);
//     void insert_done();
//     void print();
//   private:
//     vector<int> scores;
//     float mean;
// };

class namescores_t {
  public:
    namescores_t(name_t n, scores_t s) 
    {
      name = n;
      scores = s;
    }

    bool operator<(const namescores_t& other) const
    {
      if(!(scores < other.scores) && !(other.scores < scores)) return name < other.name;
      return scores < other.scores;
    }
    
    void print_name() { name.print();}
    void print_scores() {scores.print();}

  private:
    name_t name;
    scores_t scores;
};

// int main(int argc, char** argv) {
//     // commandline parsing
//     // argv[1]: K (number of records to print)
//     // argv[2]: filename.txt
//     //open filename.txt
//   vector<namescores_t> NS;
//   while (more data in file) {
//     add first and lastname to name_t object
//     while (more scores) {
//       insert score into scores_t object
//     have insert_done calculate mean score
//     create and insert namescores_t object into NS list
//   }
//   close filename.txt
//   turn NS list into binary max-heap
//   for (K data elements && heap not empty) {
//     extract top of heap element
//     print name
//     print scores
//   }
// }

int main(int argc, char** argv) 
{
  ifstream fin;
  int K;
  string first, last, errCheck;
  bool seen = false;
  vector<namescores_t> NS;

  if(argc != 3) {
    // I wasn't able to run the solution executables on hydra, so I guessed what the error message would be
    cerr << "usage: ./Rank_byscores K filename.txt\n";
    return 1;
  }
  K = strtol(argv[1], argv+1, 0);
  fin.open(argv[2]);


  while (!fin.eof()) {
    // Name
    getline(fin, first, ' ');
    getline(fin, last, '\t');
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
    namescores_t sNS(sName, sScores);
    //Slap it into the map if it's new
    if(!fin.eof()) 
    {
      for(vector<namescores_t>::iterator ptr = NS.begin(); ptr != NS.end();++ptr)
        if(!(*ptr < sNS) && !(sNS < *ptr)) seen = true;
      if(!seen) NS.push_back(sNS);
    }
  }
  fin.close();

  make_heap(NS.begin(), NS.end());
  sort_heap(NS.begin(), NS.end());
  for(int i = 1; i <= NS.size() && i <= K; ++i) {
    NS[NS.size()-i].print_name();
    NS[NS.size()-i].print_scores();
  }
}