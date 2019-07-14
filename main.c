# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

#define BUF_SIZE 20

int parse_tetramino(char *str) {
    return 10;
}

int parse_tetramino_list(const int fd, int **result) {
    int ret = 0;
    char buf[BUF_SIZE];
    int i = 0;

//    result = malloc(1)
    while ((ret = read(fd, buf, BUF_SIZE)) == BUF_SIZE) {
        parse_tetramino(buf);
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
    fill_result(tetramino_count, tetramino_result, &result);
    printf("%s\n", result);
    return (0);
}
