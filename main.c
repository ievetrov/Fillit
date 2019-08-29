# include "fillit.h"

/*

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
    // printf("%s\n", str);
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


    // sdvig / Вычисляем минимальное число в массиве, сдвигаем в ноль

    int min_x;
    int min_y;
    int j = 0;
    int k = 0;

    min_x = arr_coords[j];
    while (j < 6)
    {
        j += 2;
        if (arr_coords[j] < min_x)
            min_x = arr_coords[j];
    }

    j = 1;
    min_y = arr_coords[j];
    while (j < 7)
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
    i = 0;
    j = 0;
    int result = -1;
    while (i < TETROMINO_TYPE_COUNT)
    {
        while(j < 8)
        {
            if(TETROMINOS[i][j] != arr_coords[j])
                break;
            j++;
            if(j == 7)
            {
                result = i;
            }
        }
        if(result != -1)
        {
            break;
        }
        i++;
        j = 0;
    }

    // poluchit code
    printf("%d\n", result);
    return result;
}


// считаем количество тетрамино
// распознавание и присвоение списка id тетрамино - (&tetramino_result)
int parse_tetramino_list(const int fd, int *result)
{
    int ret = 0;
    char buf[BUF_SIZE];
    int i = 0;
    int z = 0;

    while ((ret = read(fd, buf, BUF_SIZE)) == BUF_SIZE)
	{
        validate_buf(buf);
        // TODO parse_tetramino (отправить buf, вернуть число)
        // *result[i] = parse_tetramino(buf);
        // ** адрес на адрес (меняем извне)
        result[i] = parse_tetramino(buf);
        i++;
        if (i > MAX_TETRA_COUNT)
            ft_exit();
        z++;
        printf("z = %d\n", z);
    }
    result[i] = parse_tetramino(buf);
    i++;
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
    int i;

    if (argc != 2) {
        print_usage();
        return (-1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("%s\n", "file does not exist");
        return (-1);
    }

    tetramino_result = malloc(sizeof(int) * MAX_TETRA_COUNT);
    tetramino_count = parse_tetramino_list(fd, tetramino_result);

    // tetramino_result - массив id фигур тетрамино
    // fill_result(tetramino_count, tetramino_result, &result);
    // printf("%s\n", result);

    printf("Количество фигур (tetramino_count) = %d\n", tetramino_count);
    i = 0;
    while(tetramino_count > i)
        printf("Фигура %d: id %d\n", i + 1, tetramino_result[i++]);
    return (0);
}
