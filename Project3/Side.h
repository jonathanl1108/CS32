
#ifndef Side_h
#define Side_h
enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;
const int N_INFINTY = -9999;
const int P_INFINTY = 9999;

inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}

#endif /* Side_h */
