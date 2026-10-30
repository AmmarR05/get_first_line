#include "get_next_line.h"
int ft_strlen(const char *str)
{
    if (str == NULL)
        return 0;
    int size = 0;
    while (str[size])
        size++;
    return size;
}
static void     copy_s2(const char *s2, char *str, size_t i)
{
        size_t  j;

        j = 0;
        while (s2[j])
        {
                str[i] = s2[j];
                i++;
                j++;
        }
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *str;
        size_t  size_s1;
        size_t  size_s2;
        size_t  i;

        size_s1 = ft_strlen(s1);
        size_s2 = ft_strlen(s2);
        i = 0;
        str = malloc(size_s1 + size_s2 + 1);
        if (str == NULL)
                return (NULL);
        if(s1 != NULL)
        {
            while (s1[i])
            {
                str[i] = s1[i];
                i++;
            }
        }
        copy_s2(s2, str, i);
        str[size_s1 + size_s2] = '\0';
        return (str);
}
char    *ft_strchr(const char *s, int c)
{
        int                             count;
        unsigned char   ch;

        count = 0;
        ch = c;
        if (c == '\0')
                return ((char *)&s[ft_strlen(s)]);
        count = 0;
        while (s[count])
        {
                if (s[count] == ch)
                        return ((char *)&s[count]);
                count++;
        }
        return (NULL);
}
static char     *empty_str(void)
{
        char    *str;

        str = malloc(1);
        if (str == NULL)
                return (NULL);
        str[0] = '\0';
        return (str);
}

static char     *copy_part(char const *s, unsigned int start, size_t len)
{
        char    *str;
        size_t  count;

        str = malloc(len + 1);
        if (str == NULL)
                return (NULL);
        count = 0;
        while (len > count)
        {
                str[count] = s[start];
                count++;
                start++;
        }
        str[count] = '\0';
        return (str);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        size_t  len_of_s;

        len_of_s = ft_strlen(s);
        if (start > len_of_s)
                return (empty_str());
        if (len <= len_of_s - start)
                return (copy_part(s, start, len));
        return (copy_part(s, start, len_of_s - start));
}