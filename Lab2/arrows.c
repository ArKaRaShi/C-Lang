#include <stdio.h>

void loop_symbol(char symbol, int size) {
    for (int i = 0; i < size; i++) 
        printf("%c", symbol);
}

void one_line_detail(int space_size, int sharp_size) {
    loop_symbol(' ', space_size);
    loop_symbol('#', sharp_size);
    printf("\n");
}

void vertical_tail(int n) {
    int sharp = n * 2 - 1, line = n + 1;
    for (int i = 0; i < line; i++) 
        one_line_detail(1, sharp);
}

void vertical_top_head(int n) {
    int space = n, sharp = 1, line = n + 1;
    for (int i = 0; i < line; i++) {
        one_line_detail(space, sharp);
        space--;
        sharp += 2;
    }
}

void vertical_down_head(int n) {
    int space = 0, sharp = n * 2 + 1, line = n + 1;
    for (int i = 0; i < line; i++) {
        one_line_detail(space, sharp);
        space++;
        sharp -= 2;
    }

}

void horizontal_first_last_line(int space_size) {
    one_line_detail(space_size, 1);
}

void horizontal_main(int space_size, int sharp_size, int line_size) {
    int space = space_size, sharp = sharp_size;
    int top_part_line = line_size, bottom_part_line = line_size - 1;

    for (int i = 0; i < top_part_line; i++) 
        (space == 0) ? one_line_detail(0, sharp++) : one_line_detail(space--, sharp++);
    
    sharp = sharp - 2;
    if (space_size != 0) space = 1;
    for (int i = 0; i < bottom_part_line; i++)
        (space == 0) ? one_line_detail(0, sharp--) : one_line_detail(space++, sharp--);
}

int main() {
    char direction;
    int size;
    scanf("%c %d", &direction, &size);
    switch(direction) {
        case 'N': vertical_top_head(size);
                  vertical_tail(size);
                  break;

        case 'S': vertical_tail(size);
                  vertical_down_head(size);
                  break;

        case 'E': horizontal_first_last_line(size + 1);
                  horizontal_main(0, size + 3, size);
                  horizontal_first_last_line(size + 1);
                  break;

        case 'W': horizontal_first_last_line(size);
                  horizontal_main(size - 1, size + 3, size);
                  horizontal_first_last_line(size);
                  break;

        default:  break;
    }
    return 0;
}