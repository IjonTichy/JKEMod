function int min(int x, int y)
{
    if (x < y) {return x;}
    return y;
}

function int max(int x, int y)
{
    if (x > y) {return x;}
    return y;
}

function int middle(int x, int y, int z)
{
    if ((x < z) && (y < z))
    {
        return min(max(x, y), z);
    }

    return max(min(x, y), z);
}
