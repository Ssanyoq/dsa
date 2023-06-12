#include <stdio.h>

int main() {
    FILE *fd = fopen("savedata.bin", "rb");
    int out = 1;
    fseek(fd, 0, SEEK_SET);
    while (1)
    {
        int a;
        out = fread(&a, sizeof(int), 1, fd);
        if (out == 0) {
            break;
        } 
        printf("%d\n", a);
    }
    
}