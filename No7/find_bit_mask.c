#include <stdio.h>

/*
0
c -> 1100
e -> 1110
3 -> 0011




*/

long int PandMask[16] = {
    0xffffffffffffffff,	0xfffffffff0ffffff,	0xffffffffffffffff,	0xc00000000000fffe,
    0x0000000000000000,	0x000003ffe0000000,	0x0000000000ffffff,	0xffffffffffffffff,
    0xffffffffffffffff,	0xfffffff000000000,	0x000003ffe0000000,	0x00000000000001ff,
    0xffffffffffffffff,	0xfffffffffc3fffff,	0xffffffffffffffff,	0xffffffffffffffff
};

unsigned long int zeroFilter  = 0x8000000000000000;
int ZeroCount = 0;
int NotZeroCount = 0;
int bitCount = 0;

int main(){

    for(int i=0;i<16;i++){
        for(int j=0;j<64;j++){
            if(!(PandMask[i]&(zeroFilter>>j))) ZeroCount++;
        }
    }

    for(int i=0;i<16;i++){
        for(int j=0;j<64;j++){
            if(PandMask[i]&(zeroFilter>>j)) NotZeroCount++;
        }
    }

    printf("유출되지 않은 비트수 %d\n", ZeroCount);
    printf("유출된 비트수 %d\n", NotZeroCount);
    printf("총 비트수 %d\n", ZeroCount+NotZeroCount);
    printf("비트 블럭 분석\n");
    printf("2^k : 2^%d\n", bitCount);
    ZeroCount = 0;
    for(int i=0;i<16;i++){\
        for(int j=0;j<64;j++){
            if(!(PandMask[i]&(zeroFilter>>j))){
                printf("0");
                ZeroCount++;
            }

            else{
                if(ZeroCount) printf("->블럭 길이:%d, 2^k : 2^%d\n", ZeroCount, bitCount);
                ZeroCount = 0;
            }
            bitCount++;
        }
    }

    printf("\n");
    if(bitCount==1024) printf("검증: bit길이 체크 완료. 참\n");
    else printf("검증 오류 총길이 : %d\n", bitCount);
}