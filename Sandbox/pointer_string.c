#include <stdio.h>

int main() {
  char str[] = "1234";
  printf("str: \"%s\"\n", str);
  printf("short hex: 0x%04x\n", *(short *)&str);
  printf("int hex: 0x%08x\n", *(int *)&str);
  printf("long hex: 0x%016lx\n", *(long *)&str);

  char buf[] = "ASDF";
  printf("*buf: '%c' 0x%08x\n", *buf, *(int *) buf);
  printf("*(buf+2): '%c' 0x%08x\n", *(buf+2), *(int *) (buf+2));
  printf("buf+2: \"%s\"\n", buf+2);
  *(buf+1) = (char) 0x42;
  printf("buf: \"%s\"\n", buf);

  // buf는 ASDF의 0번째 아이템 A의 주소값을 가리키는 포인터
  // 이 때, A의 크기는 char이기 때문에 1 바이트이고, ASDF는 전체 4바이트를 차지함
  // (int *)buf는 형 변환을 하는 것인데, 본래 1바이트 크기의 'char를 가리키던 포인터'를 4바이트 크기의 'int를 가리키는 포인터'로 변환해주는 것
  // 결과적으로, (int *) buf 는 ASDF 전체(배열)의 시작 주소값을 가리키는 포인터가 됨
  // 그 다음, *(int *) buf 를 하면, 전체의 값을 가져오고, 그 값을 16진수로 표현한 것이 46445341
  // 그럼 각각을 따져보자.. 왜 다르지??
  printf("0x46: 16 * 4 + 1 * 6 = %d, %c\n", 16*4+1*6, 16*4+1*6);
  printf("0x44: 16 * 4 + 1 * 4 = %d, %c\n", 16*4+1*4, 16*4+1*4);
  printf("0x53: 16 * 5 + 1 * 3 = %d, %c\n", 16*5+1*3, 16*5+1*3);
  printf("0x51: 16 * 5 + 1 * 1 = %d, %c\n", 16*5+1*1, 16*5+1*1);

}