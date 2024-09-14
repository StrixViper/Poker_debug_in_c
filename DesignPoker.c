#include <stdio.h>
#include <wchar.h>
#include <locale.h>


int main() {


     setlocale(LC_ALL, "");

    int poker_symbols[] = {0x2660, 0x2665, 0x2666, 0x2663};
    int num_symbols = sizeof(poker_symbols) / sizeof(poker_symbols[0]);


    for (int i = 0; i < num_symbols; ++i) {
        printf("%lc\n", poker_symbols[i]);
    }

    return 0;
}
