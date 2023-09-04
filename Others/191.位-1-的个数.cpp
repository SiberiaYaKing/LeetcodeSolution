/*
 * @lc app=leetcode.cn id=191 lang=cpp
 *
 * [191] 位1的个数
 */

// @lc code=start
#include <iostream>
class Solution {
    uint8_t Recursive(uint32_t bitData , uint16_t bitMask = UINT16_MAX, uint8_t slot= 16 ){
        uint8_t count = 0;
        uint16_t rightBitData = bitData&bitMask;
        uint16_t leftBitData = bitData>>slot;
        uint8_t halfSlot = slot>>1;
        if(rightBitData == bitMask) {
            count +=slot;
        } else if(rightBitData && halfSlot){
            count +=Recursive(rightBitData, bitMask>>halfSlot, halfSlot);
        }
        if(leftBitData == bitMask) {
            count +=slot;
        } else if(leftBitData && halfSlot){
            count +=Recursive(leftBitData, bitMask>>halfSlot, halfSlot);
        }
        return count;
    }
public:
    int hammingWeight(uint32_t n) {
        // int count = 0;
        // while(n){
        //     count++;
        //     n = (n-1)&n;
        // }
        // return count;
        return Recursive(n);
    }
};
// @lc code=end

