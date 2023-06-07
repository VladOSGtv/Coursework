#include <iostream>
#include <string>
#include <vector>
#include <Random>
#include <windows.h> 
#include <chrono>

using namespace std;

void printParentheses(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
        printParentheses(s, i, s[i][j]);
        printParentheses(s, s[i][j] + 1, j);
        cout << ")";
    }
}

// Функція для перемноження двох матриць
vector<vector<long long int>> multiplyMatrices(const vector<vector<long long int>>& matrix1, const vector<vector<long long int>>& matrix2) {
    int row1 = matrix1.size();
    int col1 = matrix1[0].size();
    int row2 = matrix2.size();
    int col2 = matrix2[0].size();

    // Перевірка на коректність розмірів матриць
    if (col1 != row2) {
        cout << "Неможливо перемножити матриці. Неправильні розміри." << endl;
        return {};
    }

    // Створення результуючої матриці
    vector<vector<long long int>> result(row1, vector<long long int>(col2, 0));

    // Перемноження матриць
    for (int row = 0; row < row1; row++) {
        for (int col = 0; col < col2; col++) {
            // Multiply the row of A by the column of B to get the row, column of product.
            for (int inner = 0; inner < 2; inner++) {
                result[row][col] += matrix1[row][inner] * matrix2[inner][col];
            }
        }
    }
    return result;
}

// Функція для отримання оптимального порядку множення матриць
vector<vector<int>> Matrix_Chain_Order(const vector<vector<vector<long long int>>>& matrices) {
    int n = matrices.size() - 1;

    // Створення матриць m та s
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + matrices[i - 1].size() * matrices[k].size() * matrices[j].size();
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    return s;
}

// Функція для перемноження колекції матриць за оптимальним порядком
vector<vector<long long int>> multiplyMatrixCollection(const vector<vector<vector<long long int>>>& matrixCollection, const vector<vector<int>>& s, int i, int j) 
{
    if (i == j)     return matrixCollection[i];
    

    vector<vector<long long int>> matrix1 = multiplyMatrixCollection(matrixCollection, s, i, s[i][j]);
    vector<vector<long long int>> matrix2 = multiplyMatrixCollection(matrixCollection, s, s[i][j] + 1, j);

    return multiplyMatrices(matrix1, matrix2);
}



vector<vector<vector<long long int>>> rand_matrices(int numMatrices, int maxSizes)
{ 
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> sizeDist(maxSizes, maxSizes);  //  Випадковий розмір матриці 
    uniform_int_distribution<int> el(0, 5);       //   елементи матриці

    vector<vector<vector<long long int>>> matricesCollection(numMatrices); // 3-вимірний вектор для зберігання матриць

    int rows = sizeDist(gen);    // Випадкова кількість рядків для першої матриці
    int cols = sizeDist(gen);    // Випадкова кількість стовпців для першої матриці
    
    for (int i = 0; i < numMatrices; i++)
    {
        vector<vector<long long int>> matrix(rows, vector<long long int>(cols)); // Створення матриці з випадковими розмірами

        // Ініціалізація матриці випадковими значеннями
        for (int j = 0; j < rows; j++)
            for (int k = 0; k < cols; k++)
                matrix[j][k] = el(gen); // Випадкове значення для елемента матриці
        
        matricesCollection[i] = matrix; // Додавання матриці до колекції

        // Оновлення розмірів для наступної матриці (рядки матриці i будуть стовпцями матриці i+1)
        rows = cols;
        cols = sizeDist(gen); // Випадкова кількість стовпців для наступної матриці
    }

    return matricesCollection;
}



vector<vector<vector<long long int>>> own_matrices()
{
    cout << " Матриці користувача. " << endl;

    cout << "    Введіть кіль-ть матриць : ";
    int numMatrices; // кількість матриць
    cin >> numMatrices;
    vector<vector<vector<long long int>>> matricesCollection(numMatrices); // 3-вимірний вектор для зберігання матриць

    int rows, cols;
    for (int i = 0; i < numMatrices; i++)
    {
        cout << "    Введіть кіль-ть рядків для матриці " << i + 1 << ": ";
        cin >> rows;
        cout << "    Введіть кіль-ть стовпців для матриці " << i + 1<< ": ";
        cin >> cols;
        cout << " Заповнення матриці " << endl;
        vector<vector<long long int>> matrix(rows, vector<long long int>(cols)); // Створення матриці з заданими розмірами

        // Ініціалізація матриці заданими значеннями
        for (int j = 0; j < rows; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                cout << " Рядок " << j + 1 << " Стовпчик " << k + 1 << ", елемент:";
                cin >> matrix[j][k]; // задане значення для елемента матриці
            }
            cout << endl;
        }
        matricesCollection[i] = matrix; // Додавання матриці до колекції
    }

    return matricesCollection;
}


int main() {

    setlocale(LC_ALL, "ru");
    SetConsoleOutputCP(1251);

    int choice = 1;
    int choices[6]{ 50, 70, 90, 110, 150, 200};

    int sizes_of_matrices;
    for (int amount_of_matrices: choices)
    {
        sizes_of_matrices = amount_of_matrices;
    /*system("cls");
    cout << " Виконавець: Владислав Крамар" << endl;
    cout << " Курсова Робота. Застосування динамічного програмування для перемноження кількох матриць " << endl;

    cout << "1. Рандомні вхідні дані " << endl;
    cout << "2. Вхідні дані користувача " << endl;
    cout << "0. Вихід." << endl;
    cout << "Ваш вибір: ";    
    cin >> choice;*/

    vector<vector<vector<long long int>>> matrices;


        //switch (choice)
        //{
        //case 1:
        //    system("cls");
        //    cout << " Введіть кіль-ть матриць: ";
        //    cin >> amount_of_matrices;
        //    cout << " Введіть максимальні розміри матриць: ";
        //    cin >> sizes_of_matrices;
        //    matrices = rand_matrices(amount_of_matrices, sizes_of_matrices);
        //    break;
        //case 2:
        //    system("cls");
        //    matrices = own_matrices();
        //    break;
        //case 0:
        //    cout << " Вихід" << endl;
        //    return 0;
        //default:
        //    cout << " Такого выбора нет!" << endl;
        //    continue;
        //}
        
    cout << " amount: " << amount_of_matrices << " sizes: " << sizes_of_matrices << endl;
        matrices = rand_matrices(amount_of_matrices, sizes_of_matrices);

        // Засікання часу на початку роботи функції

        auto start = chrono::high_resolution_clock::now();

        int n = matrices.size();

        vector<vector<int>> s = Matrix_Chain_Order(matrices);
        
        vector<vector<long long int>> result = multiplyMatrixCollection(matrices, s, 0, n - 1);

        // Засікання часу після закінчення роботи функції
        auto end = chrono::high_resolution_clock::now();
        // Обчислення тривалості роботи функції в мілісекундах
        chrono::duration<double, milli> duration = end - start;
        cout << " Час виконання множення: " << duration.count() << " мс" << endl;
        cout << endl;

        /*cout << " Порядок множення матриць: \n ";
        printParentheses(s, 0, n - 1);
        cout << endl;*/

        //cout << "\n Елементи результуючої матриці: " << endl;
        //for (int i = 0; i < result.size(); i++)
        //{
        //    for (int j = 0; j < result[0].size(); j++)
        //        cout << " " << result[i][j] << " ";
        //    cout << endl;
        //}
    }
    system("pause");
    return 0;
 }
