class RangeEncoding
{
public:
    int minRanges(int arr[])
    {
        int numRanges = 0;
        for (int i = 0; i < arr.size; i++)
        {
            if (arr[i + 1] - 1 != arr[i])
            {
                numRanges += 1;
            }
        }
        return numRanges;
    }
};