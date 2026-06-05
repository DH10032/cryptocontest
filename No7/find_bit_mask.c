#include <stdio.h>

long int PandMask[16] = {
    0xffffffffffffffff,	0xfffffffff0ffffff,	0xffffffffffffffff,	0xc00000000000fffe,
    0x0000000000000000,	0x000003ffe0000000,	0x0000000000ffffff,	0xffffffffffffffff,
    0xffffffffffffffff,	0xfffffff000000000,	0x000003ffe0000000,	0x00000000000001ff,
    0xffffffffffffffff,	0xfffffffffc3fffff,	0xffffffffffffffff,	0xffffffffffffffff
};

long int zeroFilter  = 0x0000000000000001;
int ZeroCount = 0;
int NotZeroCount = 0;

int main(){
    for(int i=0;i<16;i++){
        for(int j=0;j<64;j++){
            if(PandMask[i]&(zeroFilter<<j)) ZeroCount++;
        }
    }

    for(int i=0;i<16;i++){
        for(int j=0;j<64;j++){
            if(!(PandMask[i]&(zeroFilter<<j))) NotZeroCount++;
        }
    }

    printf("유출되지 않은 비트수 %d\n", ZeroCount);
    printf("유출된 비트수 %d\n", NotZeroCount);
    printf("총 비트수 %d\n", ZeroCount+NotZeroCount);
}