//
// Created by will on 2/11/22.
//

#pragma once

template <typename T>
T clip(T x, T min, T max){
    if (x < min){
        return min;
    }else if (x > max){
        return max;
    }

    return x;
}

template <typename T>
int sign(T x){
    if (x < 0){
        return -1;
    }else if (x > 0){
        return 1;
    }

    return 0;
}