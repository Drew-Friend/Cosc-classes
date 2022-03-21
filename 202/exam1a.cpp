// 6
int strcpy(char *s1, const char *s2)
{
    int count = 0;
    do
    {
        *s1 = *s2;
        count++;
        s1++;
    } while (*(s2++));
    return count;
}

char *strupper(char *s)
{
    for (char *i = s; *i; ++i)
        *i = (*i >= 'a' && *i <= 'z') ? *i - 'a' + 'A' : *i;
    return s;
}

// 7 A
bucket::bucket(int data) { this.data = data; }
// 7 B
bool bucket::operator==(int in)
{
    return in == data;
}
// 7 C
void bucket::operator*=(int mult)
{
    data = data * mult;
}

// 7 D&E
template <typename T>
class bucket
{
public:
    bucket(T data = T()) { data = data; }
    int get_data() { return data; }
    bool operator==(T);
    void operator*=(T);

private:
    T data;
};
template <typename T>
bool bucket<T>::operator==(T in)
{
    return in == data;
}
template <typename T>
void bucket<T>::operator*=(T mult)
{
    data = data * mult;
}

// 8 E
for (vector<int>::iterator i = v.begin(); i != v.end(); ++i)
    cout << *i << '\n';

// 9
template <typename T>
void copy(T &A, T &B)
{
    if (A.size() < B.size())
        A.resize(B.size());
    typename T::iterator aPtr = A.begin();
    for (typename T::iterator ptr = B.begin(); ptr != B.end(); ++ptr)
    {
        *aPtr = *ptr;
        ++aPtr;
    }
}

// 10 A
smatrix::smatrix(int num) : N(num)
{
    buf = new char[num * (num + 1) / 2];
}

// 10 B
smatrix::~smatrix()
{
    delete buf;
}

// 10 C
char *smatrix::operator[](int index)
{
    return &buf[index * (index + 1) / 2];
}