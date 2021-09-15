#include <stdio.h>
int main(void) {
    char arr[100000] = {0};
    scanf("%s", arr);
    int i=0;
    int count[26] = {0};
    while (arr[i] != 0) {
        // printf("%c\n", arr[i]);
        // 대문자인 경우
        if (arr[i] < 'a') {
            count[arr[i]-'A'] += 1;            
        } else {
            count[arr[i]-'a'] += 1;                        
        }
        i++;
    }
    
    int max_idx = 0;
    int is_only = 1;
    for (int i=1; i < 26; i++) {
        if (count[i] > count[max_idx]) {
            max_idx = i;
            is_only = 1;
        } else if (count[i] == count[max_idx]) {
            is_only = 0;
        }
        // printf("%c %d\n", i+'A', count[i]);
    }
    
    if (is_only == 1) {
        printf("%c\n", max_idx + 'A');
    } else {
        printf("?\n");
    }
    
    return 0;
}