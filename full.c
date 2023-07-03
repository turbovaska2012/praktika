#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// Реализация алгоритма сортировки Шелла
void shellSort(int arr[], int n) {
	// Определение начального расстояния между элементами, начиная с максимально возможного расстояния
	int gap;
	for (gap = n / 2; gap > 0; gap /= 2) {
		// Выполнение сортировки вставкой с заданным расстоянием
		for (int i = gap; i < n; i++) {
			int temp = arr[i];
			int j;
			// Сравнение элементов с заданным расстоянием и выполнение шага вставки
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}

// Функция для сохранения массива в файл
void saveArrayToFile(int arr[], int n, const char* filename) {
	// Открытие файла в режиме записи
	FILE* file = fopen(filename, "w");
	// Проверка успешного открытия файла
	if (file != NULL) {
		// Запись каждого элемента массива в файл, разделенных пробелами
		for (int i = 0; i < n; i++) {
			fprintf(file, "%d ", arr[i]);
		}
		// Закрытие файла после записи
		fclose(file);
	}
}

// Основная функция
int main() {
	// Установка локализации на "Rus" для поддержки русского языка
	setlocale(LC_ALL, "Rus");

	// Инициализация генератора случайных чисел с использованием текущего времени
	srand(time(0));

	// Переменная для хранения количества элементов в массиве
	int n;

	// Приглашение пользователя ввести количество элементов
	printf("Введите количество элементов: ");
	// Считывание введенных данных и сохранение в 'n'
	scanf("%d", &n);

	// Динамическое выделение памяти для массива с помощью 'malloc'
	int* arr = (int*)malloc(n * sizeof(int));

	// Заполнение массива случайными целыми числами в диапазоне от 0 до 100000
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 100001;
	}

	// Сохранение исходного массива в файл с именем "input.txt"
	saveArrayToFile(arr, n, "input.txt");

	// Засечение времени начала сортировки с помощью 'clock' для измерения времени выполнения сортировки
	clock_t start_time = clock();

	// Сортировка массива с помощью алгоритма сортировки Шелла
	shellSort(arr, n);

	// Засечение времени окончания сортировки с помощью 'clock' для измерения времени выполнения
	clock_t end_time = clock();

	// Сохранение отсортированного массива в файл с именем "sorted.txt"
	saveArrayToFile(arr, n, "sorted.txt");

	// Вычисление времени выполнения сортировки
	double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	// Вывод времени выполнения на консоль
	printf("Время выполнения сортировки: %.4f сек\n", execution_time);

	// Освобождение выделенной памяти для массива с помощью 'free'
	free(arr);

	return 0;
}
