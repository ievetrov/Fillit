# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

#define BUF_SIZE 20

/**
             #
             #
             #
 #### - 0    #    - 1


 ##          ##         #            #
 #            #         #            #
 #    - 2     #   - 3   ##   - 4    ##   - 5

 #             #        ###         ###
 ###  - 6    ###  - 7   #     - 8     #  - 9


                        #            #
 ##           ##        ##          ##
  ##  - 10   ##   - 11   #   - 12   #    - 13


                        #             #
  #          ###        ##           ##
 ###  - 14    #   - 15  #    - 16     #   - 17


 ##
 ##   - 18

 */
void	ft_exit(void)
{
	printf("error\n");
	exit(EXIT_FAILURE);
}

int validate_line(char *line)
{
	// while (*line)
	// {
	// 	if (*line != '.' && *line != '#')
	// 		return (0);
	// 	line++;
	// }
	return (1);
}

int validate_buf(char *str)
{
    printf("%s\n", str);
    int line_count = 0;
    int i = 0;
    char line[4];

    while (*str)
    {
        if (i >= 20)
            return (1);
        if (str[i] == '\n')
        {
            strncmp(line, str, 5);
            if (validate_line(line) == 1)
                ft_exit();

            line_count++;
        }
        i++;
    }
    return (0);
}

// int parse_tetramino(char *str)
// {
//     char *line;

//     *line = (char)malloc(BUF_SIZE + 1);
//     strncpy(line, str, BUF_SIZE);
//     line[BUF_SIZE] = '\0';

//     if (check_char())

//     return 1;
// }

int parse_tetramino_list(const int fd, int **result) {
    int ret = 0;
    char buf[BUF_SIZE];
    int i = 0;

    while ((ret = read(fd, buf, 20)) == 20)
	{
        if (!validate_buf(buf))
            ft_exit();
        i++;
    }
    return i;
}

void fill_result(int *params, char **result) {
    // TODO use tetramino_result array to fill result
    *result = "ABBBB.\nACCCEE\nAFFCEE\nA.FFGG\nHHHDDG\n.HDD.G\n";
}

void print_usage() {
    printf("usage: ./fillit input_file\n");
}

int main(int argc, char const *argv[]) {
    int tetramino_count;
    int fd;
    int *tetramino_result;
    char *result;

    if (argc != 2) {
        print_usage();
        return (-1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("%s\n", "file does not exist");
        return (-1);
    }

    tetramino_count = parse_tetramino_list(fd, &tetramino_result);
    // fill_result(tetramino_count, tetramino_result, &result);
    printf("%s\n", result);
    printf("%d\n", tetramino_count);
    return (0);
}
