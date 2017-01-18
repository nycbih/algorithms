#pragma once
#include <vector>


namespace my
{
    void reverse1(char *str)
    {
        if( !str || !*str )
        {
            return;
        }

        int sz = strlen(str);

        for(int i=0, j=sz-1; i < sz/2; i++, j--)
        {
            char c = str[j];
            str[j] = str[i];
            str[i] = c;
        }
    }

    void reverse2(char *str)
    {
        if( !str || !*str )
        {
            return;
        }

        int sz = strlen(str);

        char *b = str;
        char *e = str + sz-1;

        while ( b < e )
        {
            std::swap(*b++,*e--);
        }
    }

    void remove(char *str, char c)
    {
        char *pos = str;

        while( *str )
        {
            if( *str == c )
            {
                str++;
                continue;
            }

            *pos++ = *str++;
        }

        *pos = 0x0;
    }

    int atoi(char *str)
    {
        int num=0;

        while(*str)
        {
            num *= 10;
            num += *str - '0';
            str++;
        }

        return num;
    }

    int pow(int base, int exp)
    {
        int result=1;
        while( exp != 0 )
        {
            result *= base;
            exp--;
        }

        return result;
    }

    int fib(int val)
    {
        if( val == 0 ) return 0;

        if( val == 1 ) return 1;

        return fib(val - 1) + fib(val - 2);
    }
}