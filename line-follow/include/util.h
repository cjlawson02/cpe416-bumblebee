#pragma once

class Util
{
public:
    static inline float bound(float val, float min, float max)
    {
        if (val < min)
        {
            return min;
        }
        else if (val > max)
        {
            return max;
        }
        else
        {
            return val;
        }
    }
};
