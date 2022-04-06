#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;
typedef unsigned int uint;
class hash_table
{
public:
    hash_table();
    void insert(const string &, int);
    void show_load();
    void show_stats();
    const vector<int> &find(const string &);

private:
    struct key_line;
    int hash(const string &);
    int nextprime(int);
    int qprobe(const string &, bool);
    void resize();
    int num_inuse;
    int max_inuse;
    int num_col;
    bool show_load_active;
    vector<key_line> table;
};

struct hash_table::key_line
{
    string key;
    vector<int> lines;
    bool inuse()
    {
        return !key.empty();
    }
    bool operator==(string comp)
    {
        return comp == key;
    }
};

hash_table::hash_table()
{
    int N = nextprime(101);
    table.assign(N, key_line());
    num_inuse = 0;
    max_inuse = N / 2; // quadratic probe max value
    show_load_active = false;
    num_col = 0;
}

void hash_table::insert(const string &key, int line)
{
    int index = qprobe(key, true);
    if (!table[index].inuse())
    {
        table[index].key = key;
        table[index].lines.push_back(line);
        if (++num_inuse >= max_inuse)
            resize();
    }
    else if (!binary_search(table[index].lines.begin(), table[index].lines.end(), line))
        table[index].lines.push_back(line);
}

int hash_table::nextprime(int N)
{
    int i = 2;
    N = (2 * N + 1);
    while (i * i < N)
    {
        if (N % i == 0)
        {
            N += 2;
            i = 1;
        }
        i++;
    }
    return max(3, N);
}

int hash_table::qprobe(const string &key, bool colliding)
{
    int index = hash(key);
    int k = 0;
    while (table[index].inuse() && !(table[index] == key))
    {
        index += 2 * (++k) - 1;
        index = index % table.size();
        num_col += (colliding) ? 1 : 0;
    }
    return index;
}

void hash_table::resize()
{
    vector<key_line> tmp_table;
    show_load();
    for (int i = 0; i < (int)table.size(); ++i)
    {
        if (table[i].inuse())
            tmp_table.push_back(table[i]);
    }
    int N = nextprime(table.size());
    table.assign(N, key_line());
    num_inuse = 0;
    max_inuse = N / 2;
    for (int i = 0; i < (int)tmp_table.size(); ++i)
    {
        string &key = tmp_table[i].key;
        N = qprobe(key, false);
        table[N].key = key;
        table[N].lines = tmp_table[i].lines;
        num_inuse++;
    }
}

int hash_table::hash(const string &key)
{
    uint index = 0;
    const char *c = key.c_str();
    while (*c)
        index = ((index << 5) | (index >> 27)) + *c++;

    return index % table.size();
}

const vector<int> &hash_table::find(const string &key)
{
    int index = qprobe(key, false);
    return table[index].lines;
}

void hash_table::show_load()
{
    if (!show_load_active)
    {
        show_load_active = true;
        return;
    }
    float percent_inuse = table.size();
    percent_inuse = num_inuse / percent_inuse;
    cout << fixed << setprecision(2) << "** N = " << right << setw(6) << table.size() << " load = " << percent_inuse << "\n";
}

void hash_table::show_stats()
{
    cout << "Num slots used:   " << setw(6) << num_inuse << '\n'
         << "Num usable slots: " << setw(6) << max_inuse << '\n'
         << "Num collisions:   " << setw(6) << num_col << '\n';
}

template <typename T>
void replace_punctuation(T start, T end)
{
    for (; start != end; ++start)
        (*start) = (ispunct((*start)) && (*start) != '_') ? ' ' : (*start);
}

int main(int argc, char *argv[])
{
    // Initializations
    bool verbose = false;
    ifstream fin;
    istringstream sin;
    vector<string> cache;
    vector<int> line;
    hash_table H;
    string key;

    // Command line parsing / error checking
    if (argc != 3 && argc != 4)
    {
        cout << "usage: ./hash1 [-verbose] -f textfile\n";
        return 1;
    }
    for (int i = 0; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-f"))
        {
            if (argc > i + 1)
            {
                fin.open(argv[i + 1]);
                if (!fin.is_open())
                {
                    cerr << "error opening file: " << argv[i + 1] << '\n';
                    return 1;
                }
            }
        }
        else if (!strcmp(argv[i], "-verbose"))
        {
            verbose = true;
            H.show_load();
        }
    }

    // Read into cache entries with punctuation
    // Read into stringstream without punctuation, parse words from stringstream
    while (getline(fin, key))
    {
        cache.push_back(key);
        replace_punctuation(key.begin(), key.end());
        sin.clear();
        sin.str(key);
        while (sin >> key)
            H.insert(key, cache.size() - 1);
    }
    fin.close();

    // Show extra information if requested
    if (verbose)
    {
        H.show_load();
        H.show_stats();
    }

    // Search loop with user input
    cout << "find> ";
    while (cin >> key)
    {
        line = H.find(key);
        for (int i = 0; i < line.size(); ++i)
            cout << line[i] + 1 << ": " << cache[line[i]] << '\n';
        cout << "find> ";
    }
}