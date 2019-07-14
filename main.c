# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

int parse_tetramino_list(const int fd, int** result)
{
    int ret = 0;
    char buf[20];
    int i = 0;

    while ((ret = read(fd, buf, 20)) == 20)
	{
        i++;
    }
    return i;
}

int main(int argc, char const *argv[])
{
    int tetramino_count;
    int fd;
    int *tetramino_result;

	if (argc > 1)
	{
		printf("%s\n", "too much arguments");
		return (0);
	}


    fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("%s\n", "file does not exist");
		return (0);
	}

    tetramino_count = parse_tetramino_list(fd, &tetramino_result);
    printf("%d\n", tetramino_count);
    return (0);
}
