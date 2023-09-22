Задание 1:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	clock_t start, end;
	clock_t start1;
	start = clock();

	int size = 1000; // Размерность массивов

	int** a = (int**)malloc(size * sizeof(int*));
	int** b = (int**)malloc(size * sizeof(int*));
	int** c = (int**)malloc(size * sizeof(int*));

	if (a == NULL || b == NULL || c == NULL)
	{
		printf("Не удалось выделить память.\n");
		return 1;
	}

	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		a[i] = (int*)malloc(size * sizeof(int));
		b[i] = (int*)malloc(size * sizeof(int));
		c[i] = (int*)malloc(size * sizeof(int));

	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			a[i][j] = rand() % 100 + 1;
			b[i][j] = rand() % 100 + 1;
		}
	}

	start1 = clock();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int elem_c = 0;
			for (int r = 0; r < size; r++)
			{
				elem_c += a[i][r] * b[r][j];
			}
			c[i][j] = elem_c;
		}
	}

	end = clock();

	printf("program time: %f sec\n", (difftime(end, start)) / CLOCKS_PER_SEC);
	printf("algoritm time: %f sec\n", (difftime(end, start1)) / CLOCKS_PER_SEC);

	
	// Освобождаем выделенную память
	for (int i = 0; i < size; i++)
	{
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}
	free(a);
	free(b);
	free(c);

	return 0;
}

Задание 2:
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Сравнительная функция для qsort
int compare(const void *a, const void *b) {
	return (*(int *)a - *(int *)b);
}

void shell(int *items, int count)
{
	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	// Проходим по всем возможным гапам (инкрементам)
	for (k = 0; k < 5; k++) {
		gap = a[k]; // Текущий гап

		// Начинаем сортировку вставками с текущим гапом
		for (i = gap; i < count; ++i) {
			x = items[i]; // Запоминаем текущий элемент

			// Перемещаем элементы, пока не найдем правильное место для x
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap) {
				items[j + gap] = items[j]; // Сдвигаем элементы
			}

			items[j + gap] = x; // Вставляем x на правильное место в отсортированной части массива
		}
	}
}

void qs(int *items, int left, int right)
{
	int i, j;
	int x, y;

	// Инициализация индексов i и j для разделения массива
	i = left;
	j = right;

	// Выбор опорного элемента (компаранда)
	x = items[(left + right) / 2];

	// Разделение массива на две части
	do {
		// Поиск элемента в левой части, который больше или равен опорному
		while ((items[i] < x) && (i < right))
			i++;

		// Поиск элемента в правой части, который меньше или равен опорному
		while ((x < items[j]) && (j > left))
			j--;

		// Если найдены элементы, которые нужно поменять местами
		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++;
			j--;
		}
	} while (i <= j);

	// Рекурсивная сортировка для левой и правой частей
	if (left < j)
		qs(items, left, j);
	if (i < right)
		qs(items, i, right);
}

// Функция для генерации случайного массива
void generateRandomArray(int *arr, int size)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 1000; // Генерируем случайные числа от 0 до 999
	}
}

// Функция для генерации возрастающей последовательности
void generateIncreasingArray(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = i;
	}
}

// Функция для генерации убывающей последовательности
void generateDecreasingArray(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = size - i - 1;
	}
}

// Функция для генерации массива, где первая половина возрастающая, а вторая убывающая
void generateIncreasingDecreasingArray(int *arr, int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		arr[i] = i;
	}
	for (int i = size / 2; i < size; i++)
	{
		arr[i] = size - i - 1;
	}
}


int main()
{


	setlocale(LC_ALL, "Rus");
	int n; // Размер массива
	clock_t start_time;
	clock_t end_time;
	printf("Введите размер массива: ");
	scanf("%d", &n);

	int *arr = (int *)malloc(n * sizeof(int));
	printf("Случайный массив\n\n");
	// Генерируем массив случайных чисел
	generateRandomArray(arr, n);

	// Измеряем время для сортировки с помощью Shell Sort
	start_time = clock();
	shell(arr, n);
	end_time = clock();
	printf(" Shell Sort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	// Генерируем массив случайных чисел
	generateRandomArray(arr, n);

	// Измеряем время для сортировки с помощью Quick Sort
	start_time = clock();
	qs(arr, 0, n - 1);
	end_time = clock();
	printf(" Quick Sort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	// Добавляем замеры времени для стандартной функции qsort
	generateRandomArray(arr, n); // Перезаполняем массив случайными числами
	start_time = clock();
	qsort(arr, n, sizeof(int), compare);
	end_time = clock();
	printf(" qsort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	printf("\nВозрастающий массив\n");
	// Генерируем массив возрастающей последовательности
	generateIncreasingArray(arr, n);

	// Измеряем время для сортировки с помощью  Shell Sort
	start_time = clock();
	shell(arr, n);
	end_time = clock();
	printf(" Shell Sort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	// Генерируем массив возрастающей последовательности
	generateIncreasingArray(arr, n);

	// Измеряем время для сортировки с помощью Quick Sort
	start_time = clock();
	qs(arr, 0, n - 1);
	end_time = clock();
	printf(" Quick Sort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	// Добавляем замеры времени для стандартной функции qsort
	generateIncreasingArray(arr, n); // Перезаполняем массив случайными числами
	start_time = clock();
	qsort(arr, n, sizeof(int), compare);
	end_time = clock();
	printf(" qsort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	printf("\nУбывающий массив\n");
	// Генерируем массив убывающей последовательности
	generateDecreasingArray(arr, n);

	// Измеряем время для сортировки с помощью Shell Sort
	start_time = clock();
	shell(arr, n);
	end_time = clock();
	printf(" Shell Sort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	// Генерируем массив убывающей последовательности
	generateDecreasingArray(arr, n);

	// Измеряем время для сортировки с помощью Quick Sort
	start_time = clock();
	qs(arr, 0, n - 1);
	end_time = clock();
	printf(" Quick Sort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	// Добавляем замеры времени для стандартной функции qsort
	generateDecreasingArray(arr, n); // Перезаполняем массив случайными числами
	start_time = clock();
	qsort(arr, n, sizeof(int), compare);
	end_time = clock();
	printf(" qsort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	printf("\nМассив с первой половиной возрастающей и второй половиной убывающей\n");
	// Генерируем массив с первой половиной возрастающей и второй половиной убывающей
	generateIncreasingDecreasingArray(arr, n);

	// Измеряем время для сортировки с помощью Shell Sort
	start_time = clock();
	shell(arr, n);
	end_time = clock();
	printf(" Shell Sort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	// Добавляем замеры времени для стандартной функции qsort
	generateIncreasingDecreasingArray(arr, n); // Перезаполняем массив случайными числами
	start_time = clock();
	qsort(arr, n, sizeof(int), compare);
	end_time = clock();
	printf(" qsort: %f секунд\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
	
	// Генерируем массив с первой половиной возрастающей и второй половиной убывающей
	generateIncreasingDecreasingArray(arr, n);

	// Измеряем время для сортировки с помощью Quick Sort
	start_time = clock();
	qs(arr, 0, n - 1);
	end_time = clock();
	double elapsed_time = difftime(end_time, start_time) / CLOCKS_PER_SEC;
	printf(" Quick Sort: %f секунд\n", elapsed_time);
	   	
	return 0;
}
