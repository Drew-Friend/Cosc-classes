int getNum(int start, int end, int value)
{
    value = value >> start;
    int mask, mult = 1;
    for (int i = 0; i < end - start; i++)
    {
        for (int j = 0; j < i; j++)
            mult *= 2;
        mask += mult;
    }
}