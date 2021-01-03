#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;


string Replacing_letters_by_nums(string s);                 // додавання кількості букв до рядка
int Random_Generating(int min, int max);                    // генерація чисел із заданого діапазону
int* Separated_nums(string s, int& amount_of_nums);         // відокремлення чисел з рядка
int** Resulting_Arr(int* nums, int amount, int& size);      // створення результуючого масиву
void Output_Arr(int** arr, int size);                       // вивід результуючого масиву
void Change_min_and_max(int** arr, int size);               // зміна місцями максимума та мінімума
void Sorting_by_last(int** arr, int size);                  // сортування за останнім стовпцем

int main(){

    string s;
    for (int i = 0; i < 5; i++) {           // вводиться 5 рядків
        string temp;
        getline(cin, temp);
        s += temp + " ";
    }
    s = Replacing_letters_by_nums(s);
    cout << s << endl;


    int amount_of_nums,                                         // кількість чисел в рядку
        size_of_res_arr;                                        // розміри масиву


    int* array_of_nums = Separated_nums(s, amount_of_nums);         // масив чисел з перетвореного рядка


    int** res_array = Resulting_Arr(array_of_nums, amount_of_nums, size_of_res_arr);       // результуючий масив

    Output_Arr(res_array, size_of_res_arr);
    cout << endl;

    Change_min_and_max(res_array, size_of_res_arr);

    Output_Arr(res_array, size_of_res_arr);
    cout << endl;

    Sorting_by_last(res_array, size_of_res_arr);

    Output_Arr(res_array, size_of_res_arr);

    // видалення масивів
    for (int i = 0; i < size_of_res_arr; i++) {
        delete[] res_array[i];
    }
    delete[] res_array;
    delete[] array_of_nums;
}

string Replacing_letters_by_nums(string s) {

    size_t l = s.size();            // поточна довжина рядка
    char temp = s[0];               // перший елемент для порівняння
    int amount = 1;                 // кількість повторів букв

    for (int i = 1; i < l; i++) {
        if (temp == ' ') {          // виключення пробілів
            temp = s[i];
            continue;
        }

        if (s[i] == temp) {     // якщо поточний символ рівний попередньому - видаляємо та переходимо на елемент назад
            s.erase(i, 1);
            amount++;           // додаємо до кількості 1
            i--;
            l = s.size();       // оновлюємо довжину після видалення
        }

        else {                                  // якщо символ змінився
            s.insert(i, to_string(amount));     // вставляємо кількість символів
            temp = s[i + 1];                    // вибираємо новий символ для порівняння (і+1 тому що на позиції i у нас вже число)
            amount = 1;                         // оновлення кількості символів до початкового
            l = s.size();                       // оновлення довжини рядка
            i++;                                // перехід через один елемент (через цифру)
        }
        if (i == l - 1 && temp != ' ') {        // якщо останній елемент - то немає з чим порівнювати
            s.insert(l, to_string(amount));     // тому вписуємо останню кількість
        }
    }
    return s;
}

int Random_Generating(int min, int max) {
    return abs(rand() % (max - min + 1)) + min;
}

int* Separated_nums(string s, int& amount_of_nums) {

    amount_of_nums = 0;                            // кількість цифр у рядку
    for (int i = 0; i < s.size(); i++) {           // підрахунок кількості цифр
        if (isdigit(s[i])) {                       // isdigit - перевірка, чи символ є числом
            amount_of_nums++;
        }
    }

    int* array_of_nums = new int[amount_of_nums];            // динамічний масив з числами

    for (int i = 0, k = 0; i < s.size(); i++) {
        if (isdigit(s[i])) {
            array_of_nums[k] = ((int)s[i] - 48);               // за таблицею ASCII цифра 0 має номер 48, тому треба відняти 48
            k++;
        }
    }
    return array_of_nums;
}

int** Resulting_Arr(int* nums, int amount, int& size) {

    // size - розмір результуючого масиву
    // нам треба округлити корінь з кількості чисел вперед, щоб усі числа влізли
    // тобто якщо корінь з 10 = 3.2, то після округлення буде 3, а нам треба 4
    // тому ми порівнюємо чи після округлення число стало більше чи менше
    // якщо менше - то треба ще додати 1 (в приклад корінь з 10 = 3.2; 3.2 - 3 > 0, тому треба до 3 додати 1)
    // якщо більше або рівне, то число округлилось куди треба і не треба нічого змінювати
    size = (pow(amount, 1.0 / 2) - (int)pow(amount, 1.0 / 2) > 0) ? (int)pow(amount, 1.0 / 2) + 1 : (int)pow(amount, 1.0 / 2);


    int** arr = new int*[size];         // результуючий динамічний масив
    for (int i = 0; i < size; i++) {
        arr[i] = new int[size];
    }


    srand(time(NULL));
    int k = 0;                          // індекси для масиву чисел з рядка
    int random_num;                     // якщо чисел з масиву вже немає - випадкове згенероване число

    for (int j = 0; j < size; j++) {    // прохід масиву змійкою вниз

        if (j % 2 == 0) {               // якщо номер стовпця парний(індекс) - треба йти вниз
            for (int i = 0; i < size; i++) {

                if (k < amount) {               // якщо індекс ще менше загальної кількості - беремо елементи з масиву
                    arr[i][j] = nums[k];
                    k++;
                }
                else {                          // в іншому випадку - генеруємо від'ємне число
                    random_num = Random_Generating(-100, 0);
                    arr[i][j] = random_num;
                }

            }
        }

        else {                          // якщо номер стовпця непарний - вверх
            for (int i = size-1; i >= 0; i--) {
                if (k < amount) {
                    arr[i][j] = nums[k];
                    k++;
                }
                else {
                    random_num = Random_Generating(-100, 0);
                    arr[i][j] = random_num;
                }
            }
        }
    }
    return arr;
}

void Output_Arr(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(3) << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void Change_min_and_max(int** arr, int size) {

    for (int i = 0; i < size; i++) {

        int min = arr[i][0],            // мінімальне значення
            max = arr[i][0],            // максимальне значення
            min_i = 0,                  // індекс мінімального
            max_i = 0;                  // індекс мінімального

        for (int j = 1; j < size; j++) {

            if (arr[i][j] >= max) {
                max = arr[i][j];
                max_i = j;
            }

            if (arr[i][j] <= min) {
                min = arr[i][j];
                min_i = j;
            }
        }
        arr[i][min_i] = max;
        arr[i][max_i] = min;
    }
}

void Sorting_by_last(int** arr, int size) {
    int i = 0;
    while (i < size-1)
    {
        if (arr[i][size - 1] > arr[i + 1][size - 1]) {
            for (int k = 0; k < size; k++) {
                    int temp = arr[i][k];
                    arr[i][k] = arr[i + 1][k];
                    arr[i + 1][k] = temp;
            }
        i = 0;
        }
        else {
            i++;
        }
    }
}