#include "get_next_line.h"

size_t  ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (s[i])
        i++;
    return(i);
}

char    *ft_strdup(const char *src)
{
    int i;
    int len;
    char    *dest;

    i = 0;
    len = ft_strlen(src);
    dest = malloc(len + 1);
    if (!dest) 
        return (NULL);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    return (dest);
}

char    *ft_strchr(const char *s, int c)
{
    int i;

    i = 0;
    if (!s)
        return (NULL);
    while(s[i])
    {
        if (s[i] == c)
            return ((char *)s + i);
    }
    if (c == 0)
        return ((char*)s + i);
    return (0);
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    int i;
    int j;
    char *str;

    if (!s1 || !s2)
        return (NULL);
    str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    str[i + j] = '\0';
    return (str);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *sub;
    char    *str;
    size_t  size;
    size_t  i;

    i = 0;
    str = (const *)s;
    if (!str)
        return (NULL);
    if (start >= ft_strlen(s))
        return (ft_strdup(""));
    size = ft_strlen(s) - start;
    if (len > size)
        len = size;
    while (i < len)
    {
        sub[i] = str[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}