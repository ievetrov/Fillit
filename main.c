# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

#define BUF_SIZE 21
#define MAX_TETRA_COUNT 26

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

1. метод, который считывает тетрамино и присваивает им id в массив
2. зная id, формируем минимальный квадрат, комбинируем

 */
void	ft_exit(void)
{
	printf("error\n");
	exit(EXIT_FAILURE);
}

int validate_buf(char *str)
{
    printf("%s\n", str);
    int line_count = 0;
    int i = 0;
    char line[4];

    while (i < BUF_SIZE)
    {
        if (str[i] != '.' && str[i] != '#' && str[i] != '\n')
            ft_exit();
        i++;
    }
    return (0);
}

int parse_tetramino(char *str)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int arr_coords[8];
    int coords_count = 0;

// получение координат (сюда должны прийти валидные тетрамино)
    while (i < BUF_SIZE)
    {
        if (str[i] == '\n')
        {
            y++;
            x = 0;
            i++;
            continue;
        }
        if (str[i] == '#')
        {
            arr_coords[coords_count++] = x;
            arr_coords[coords_count++] = y;
        }
        x++;
        i++;
    }


    // sdvig / Вычисляем минимальное число в массиве

    int min_x;
    int min_y;
    int j = 0;
    int k = 0;

    min_x = arr_coords[j];
    while (j <= 6)
    {
        j += 2;
        if (arr_coords[j] < min_x)
            min_x = arr_coords[j];
    }

    j = 1;
    min_y = arr_coords[j];
    while (j <= 7)
    {
        j += 2;
        if (arr_coords[j] < min_y)
            min_y = arr_coords[j];
    }

    while (k <= 6)
    {
        arr_coords[k] -= min_x;
        k += 2;
    }

    k = 1;
    while (k <= 7)
    {
        arr_coords[k] -= min_y;
        k += 2;
    }




    // int miny = arr_coords[1];

    // minx = min([0][2][4][6])
    // miny = min([1][3][5][7])

    // poluchit code
    return arr_coords;
}


// считаем количество тетрамино
// распознавание и присвоение списка id тетрамино - (&tetramino_result)
int parse_tetramino_list(const int fd, int **result)
{
    int ret = 0;
    char buf[BUF_SIZE];
    int i = 0;

    int arr_coords[8];

    while ((ret = read(fd, buf, BUF_SIZE)) == BUF_SIZE)
	{
        validate_buf(buf);
        // TODO parse_tetramino (отправить buf, вернуть число)
        // *result[i] = parse_tetramino(buf);
        // ** адрес на адрес (меняем извне)

        arr_coords[8] = parse_tetramino(buf);
        // *result[i] = parse_tetramino(buf);
        i++;
        if (i > MAX_TETRA_COUNT)
            ft_exit();
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
    int tetramino_result[26];
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

    //
    tetramino_count = parse_tetramino_list(fd, &tetramino_result);

    //
    // tetramino_result - массив id фигур тетрамино
    // fill_result(tetramino_count, tetramino_result, &result);
    printf("%s\n", result);
    printf("%d\n", tetramino_count);
    return (0);
}
