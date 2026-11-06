#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static char *buff;
    char    *arr;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!buff)
    {
        ft_strdup("");
        if (!buff)
            return (NULL);
    }
    buff = read_buffer(fd, buff);
    if (!buff)
        return (NULL);
    if (buff[0] == '\0')
    {
        free(buff);
        buff = NULL;
        return (NULL);
    }
    arr = get_buffer(buff);
    buff = get_leftover(buff);
    return (arr);
}

char    *read_buffer(int fd, char *buff)
{
    char    *stash;
    char    *temp;
    int     reading;

    if (!buff)
        return (NULL);
    stash = malloc(buff + 1);
    if (!stash)
        return (NULL);
    reading = read(fd, buff, BUFFER_SIZE);
    while (reading > 0)
    {
        stash[reading] = '\0';
        temp = ft_strjoin(buff, stash);
        free(buff);
        buff = temp;
        if (ft_strchr(buff, DELIMITER))
            break;
        reading = read(fd, stash, BUFFER_SIZE);
    }
    free (stash);
    if (reading < 0)
    {
        free(buff);
        return (NULL);
    }
    return (buff);
}

char    *get_buffer(char *buff)
{
    char    *arr;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (buff[i] && buff[i] != DELIMITER)
        i++;
    while (buff[i] == DELIMITER)
        i++;
    arr = malloc(i + 1);
    if (!arr)
        return (NULL);
    while (j < i)
    {
        arr[j] = buff[j];
        j++;
    }
    arr[j] = '\0';
    return (arr);
}

char    *get_leftover(char *buff)
{
    char    *leftover;
    int     i;

    i = 0;
    while (buff[i] && buff[i] != DELIMITER)
        i++;
    if (!buff[i])
    {
        free(buff);
        return (NULL);
    }
    i++;
    leftover = ft_substr(buff, i, ft_strlen(buff - i));
    free(buff);
    return (leftover);
}