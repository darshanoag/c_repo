#include "stdio.h"
#include "stdlib.h"

// sample file testing CodeQL

//void forward_null(void)
//        {   
//          char* p = 0;
//          *p = 'a';
//        }   

//void reverse_null(char* input)
//    {   
//        *input = 12; 
//                if (input == NULL)
//                        return;
//    }   

void resource_leak(void)
        {   
                char *p = malloc(4);
                p[0] = 12; 
        }   

void resource_leak_2(void)
        {   
                char *p = malloc(4);
                char *q = malloc(12);
                if (!p || !q) 
                        return;
        }   

void use_after_free(void)
        {   
                char *p = malloc(4);
                free(p);
                *p = 'a';
        }   

struct bigger_than_ptr { int a; int b; int c; int d; };

void size_check(void)
        {   
                struct bigger_than_ptr *p; 
                p = malloc(sizeof(struct bigger_than_ptr *));
        }   

int some_func(void)
{
        return 1;
}

void dead_code(void)
        {   
                int x = some_func();
                if (x) {
                        if (!x) {
                                x++;
                                return;
                        }   
                }   
        }   

int read(int, char*, int);

void negative_returns(void)
        {   
                char buf[10];
                int j = read(1, buf, 8); 
                buf[j] = '\0';
        }   

void reverse_negative(void)
        {   
                int j = some_func();
                char buf[10];
                buf[j] = '\0';
                if (j < 0)
                        return;
        }   

void uninit(void)
        {   
                char* p;
                *p = 'a';
        }   

void overrun_static(void)
        {
                char buf[10];
                int i;
                for (i = 0; i <= 10; i++)
                        buf[i] = '\0';
        }   

#define NO_MEM -1
#define OK 0
#define OTHER_ERROR -2

int main() {
  char *p = malloc(12);

  if (!p)
    return NO_MEM;

  if (1) {
    free(p);
    return OTHER_ERROR;
  }

  if (!1) {
    return OTHER_ERROR;
  }

  //do_some_things(p);

  free(p);
  return OK;
}
