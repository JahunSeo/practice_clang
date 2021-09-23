#include <stdio.h>
int main(void) {
    int n;
    scanf("%d", &n);
    int ans = 0;
    char str[100];
    for (int i=0; i<n; i++) {
        scanf("%s", str);
        int alphabet[26] = {0};
        int j = 0;
        int found = 1;
        while(str[j]) {
            // printf("%d %c\n", j, str[j]);
            // 이전의 문자와 동일하면 넘어감
            if (j >= 0 && str[j] == str[j-1]) {
                // printf("case 1\n");
            }
            // 이전의 문자와 다를 경우, 새로운 문자인지 확인
            else if (alphabet[str[j] - 'a'] != 0) {
                // printf("case 2\n");
                found = 0;
                break;
            } else {
                // printf("case 3\n");
                alphabet[str[j] - 'a'] = 1;
            }
            j++;
        }
        if (found) {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}