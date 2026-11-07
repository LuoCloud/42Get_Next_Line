#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd1;
	//int	fd2;
	//int	fd3;
	char	*s;

	fd1 = open("test.txt", O_RDWR);
	//fd2 = open("test1.txt", O_RDWR);
	//fd3 = open("test2.txt", O_RDWR);

	s = get_next_line(fd1);
	printf("%s", s);
	free (s);
	s = get_next_line(fd1);
	printf("%s", s);
	free (s);
	s = get_next_line(fd1);
	printf("%s", s);
	free (s);
/*	s = get_next_line(fd2);
	printf("%s", s);
	free (s);
	s = get_next_line(fd3);
	printf("%s", s);
	free (s);
	s = get_next_line(fd1);
	printf("%s", s);
	free (s);
	s = get_next_line(fd2);
	printf("%s", s);
	free (s);
	s = get_next_line(fd3);
	printf("%s", s);
	free (s);
	s = get_next_line(fd1);
	printf("%s", s);
	free (s);
	s = get_next_line(fd2);
	printf("%s", s);
	free (s);
	s = get_next_line(fd3);
	printf("%s", s);
	free (s);
*/
}
