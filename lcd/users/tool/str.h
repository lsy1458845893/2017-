//
// Created by lsy on 17-5-17.
//

#ifndef TEMPLATE_STR_H
#define TEMPLATE_STR_H

int str_length(char *str);
char* str_concat(char *head, char *tail);
char* str_copy(char *obj, char *src, int len);
char* str_fill(char *str, int len, char c);
char* str_uint(char *buff, unsigned int num);
char* str_decimal(char *buff, float num);
char* str_append(char *buff, char c);

#endif //TEMPLATE_STR_H
