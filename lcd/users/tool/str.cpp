#include <stdio.h>

int str_length(char *str) {
    int len = 0;
    while (*(str++)) len++;
    return len;
}

char *str_concat(char *head, char *tail) {
    int offset = str_length(head);
    int len = 0;
    while (tail[len]) {
        head[offset + len] = tail[len];
        len++;
    }
    head[offset + len] = 0;
    return head;
}

char *str_copy(char *obj, char *src, int len) {
    int offset = str_length(obj);
    int t = 0;
    while (t < len) {
        obj[offset + t] = src[t];
        t++;
    }
    obj[offset + len] = 0;
    return obj;
}

char *str_fill(char *str, int len, char c) {
    int offset = str_length(str), t = 0;
    while (offset + t < len) {
        str[offset + t++] = c;
    }
    str[t + len] = 0;
    return str;
}

static int str_exchange(char *buff, int a, int b) {
    char t = buff[a];
    buff[a] = buff[b];
    buff[b] = t;
}

static int str_reverse(char *buff) {
    int len = str_length(buff);
    int t = 0;
    while (t < len / 2) {
        str_exchange(buff, t, len - t - 1);
        t++;
    }
    return len;
}

char *str_uint(char *buff, unsigned int num) {
    int len = 0;
    while (num) {
        buff[len++] = (char) (num % 10 + '0');
        num /= 10;
    }
    buff[len] = 0;
    str_reverse(buff);
    return buff;
}

char *str_decimal(char *buff, float num) {
    int len = 0, t;
    if (num >= 1) return 0;
    if (num < 0) return 0;
    while (num) {
        num *= 10;
        t = (int) num;
        buff[len++] = (char) (t + '0');
        num -= t;
    }
    buff[len] = 0;
    return buff;
}

char *str_append(char *buff, char c) {
    int len = str_length(buff);
    buff[len] = c;
    buff[len + 1] = 0;
    return buff;
}

//int main(void) {
//  char *s = (char *) "1234567890";
//  char buff[30] = {};
//  // printf("len = %d:%s\n", str_length(s), s);
//  // str_concat(buff, s);
//  // str_concat(buff, s);
//  // printf("len = %d:%s\n", str_length(buff), buff);
//  // str_copy(buff, s);
//  // printf("len = %d:%s\n", str_length(s), s);
//  // str_fill(buff, 20, '+');
//  // printf("len = %d:%s\n", str_length(buff), buff);
//  str_copy(buff, s, 3);
//  printf("len = %d:%s\n", str_length(buff), buff);
//  str_reverse(buff);
//  printf("len = %d:%s\n", str_length(buff), buff);
//  str_uint(buff, 1234567890);
//  printf("len = %d:%s\n", str_length(buff), buff);
//  str_decimal(buff, 0.123456789f);
//  printf("len = %d:%s\n", str_length(buff), buff);
//  return 0;
//}