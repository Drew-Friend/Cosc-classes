#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;

class hash_table
{
public:
    struct key_line;
    hash_table();
    void insert(const string &);

private:
    int hash(const string &);
    int nextprime(int);
    int qprobe(const string &);
    void resize();
    int num_inuse;
    int max_inuse;
    vector<key_line> table;
};

struct hash_table::key_line
{
    key_line(string);
    ~key_line();
    string *key = new string;
    vector<int> lines;
    bool inuse();
    bool operator==(string);
};

hash_table::key_line::key_line(string in)
{
    *key = in;
}

hash_table::key_line::~key_line()
{
    delete key;
    lines.clear();
}

hash_table::hash_table()
{
    int N = 23;
    table.assign(N, key_line(""));
    num_inuse = 0;
    max_inuse = N / 2; // quadratic probe max value
}

void hash_table::insert(const string &key)
{
    int index = qprobe(key);
    if (table[index].inuse())
    {
        table[index] = key;
        if (++num_inuse >= max_inuse)
            resize();
    }
}

int hash_table::nextprime(int N)
{
    int i = 2;
    while (i * i <= N)
    {
        if (N % i == 0)
        {
            N++;
            i = 1;
        }
        i++;
    }
    return max(3, N);
}

int hash_table::qprobe(const string &key)
{
    int index = hash(key);
    int k = 0;
    while (table[index].inuse() && *table[index].key != key)
    {
        index += 2 * (++k) - 1;
        index = index % table.size();
    }
    return index;
}

void hash_table::resize()
{
    vector<key_line> tmp_table;
    for (int i = 0; i < (int)table.size(); i++)
    {
        if (table[i].inuse())
            tmp_table.push_back(table[i]);
    }
    int N = nextprime(2 * table.size());
    table.assign(N, key_line(""));
    num_inuse = 0;
    max_inuse = N / 2;
    for (int i = 0; i < (int)tmp_table.size(); i++)
    {
        string &key = *tmp_table[i].key;
        table[qprobe(key)] = key;
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

int main(int argc, char *argv[])
{
    hash_table H;
    string key;
    while (cin >> key)
        H.insert(key);
}