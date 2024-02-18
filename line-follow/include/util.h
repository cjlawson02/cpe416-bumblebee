// Name:  Lorenzo Pedroza and Chris Lawson
// Lab  2
// Description: Utilities functions used in other code.

#pragma once

class Util
{
public:
    /**
     * @brief Bound a value between a min and max
     */
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

    /**
     * @brief Get a random value between 0 and 1
     */
    static inline float getRandVal()
    {
        return (float)rand() / (float)RAND_MAX;
    }

    static inline float map(float x, float in_min, float in_max, float out_min, float out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
};
