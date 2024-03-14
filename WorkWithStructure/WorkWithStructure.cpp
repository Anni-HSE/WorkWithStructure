#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <Windows.h>

using namespace std;

struct Book
{
    string title;
    string author;
    int year;

    Book() 
    {
        title = "";
        author = "";
        year = NULL;
    }

    Book(string _title, string _author, int _year) 
    {
        title = _title;
        author = _author;
        year = _year;
    }

    void setTitle(string value)  
    {
        title = value;
    }

    string getTitle() 
    {
        return title;
    }

    void setAuthor(string value) 
    {
        author = value;
    }

    string getAuthor() 
    {
        return author;
    }

    void setYear(int value) 
    {
        if (value > 0 && value <= 2024) 
        {
            year = value;
        }
        else 
        {
            year = 2024;
        }
    }

    int getYear() 
    {
        return year;
    }

    void print() 
    {
        cout << "Книга: " << title << endl;
        cout << "Автор: " << author << endl;
        cout << "Год публикации: " << year << endl;
    }
};

Book* createBooks() 
{
    Book* books = new Book[10]{
        Book("Маг в законе", "Олди", 2000),
        Book("Почти как бьютик", "Кинг", 2002),
        Book("Герои племен", "Хантер", 2008),
        Book("Путь демона", "Глушановский", 2009),
        Book("Перси Джексон и лабиринт смерти", "Риордан", 2008),
        Book("Сибирочка", "Чарская", 1910),
        Book("В арбузнос сахаре", "Бротиган", 1968),
        Book("Чемодан", "Довлатов", 1986),
        Book("Ожог", "Бэнкс", 2013),
        Book("Ночь черного хрусталя", "Михайлов", 1990)
    };

    return books;
}

auto authorComparator = [](const Book& p, string search)
{
    return p.author.compare(search);
};

auto yearComparator = [](const Book& p, string search)
    {
        int s = stoi(search);
        if (p.year == s)
            return 0;
        else if (p.year < s)
            return -1;
        else
            return 1;
    };

int BinnarySearch(Book* books, int* indexes, int size, string search, function<int(const Book&, string search)> comparator)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (comparator(books[indexes[mid]], search) == 0)
        {
            return mid;
        } 
        else if (comparator(books[indexes[mid]], search) < 0)
        {
            left = mid + 1;
        }
        else 
        {
            right = mid - 1;
        }
    }

    return -1;
}

int inputNumber(int minValue, int maxValue, string infoText, string errorText)
{
    int number;
    while (true)
    {
        cout << infoText;
        cin >> number;

        if (cin && number >= minValue && number <= maxValue)
            break;

        cout << errorText << endl;
        cin.clear();
        while (cin.get() != '\n');
    }

    return number;
}

string inputString(string infoText)
{
    string value;
    cout << infoText ;
    cin >> value;
    return value;
}

void printBooks(Book* books, int* indexes, int size)
{
    cout << "-----------------------------" << endl;
    cout << "Список книг:" << endl;
    cout << "-----------------------------" << endl;
    for (int i = 0; i < size; i++)
    {
        books[indexes[i]].print();
        cout << "-----------------------------" << endl;
    }
}

bool compareObjectsByParam(const Book& obj1, const Book& obj2, int type) {
    switch (type)
    {
        case 0:
            return obj1.author < obj2.author;
        case 1:
            return obj1.year < obj2.year;
    };
}

void mainMenu() 
{
    cout << "-----------------------------" << endl;
    cout << "Меню:" << endl;
    cout << "-----------------------------" << endl;
    cout << "1. Печать спика книг" << endl;
    cout << "2. Отсортировать список книг по выбранному полю" << endl;
    cout << "3. Найти книгу по выбранному полю" << endl;
    cout << "4. Изменть книгу по выбранному полю" << endl;
    cout << "5. Удалить книгу по выбранному полю" << endl;
    cout << "6. Выход из приложения" << endl;
    cout << "-----------------------------" << endl;
}

void secondMenu(string title)
{
    cout << "-----------------------------" << endl;
    cout << title << endl;
    cout << "-----------------------------" << endl;
    cout << "1. По автору" << endl;
    cout << "2. По году публикации" << endl;
    cout << "3. Отмена" << endl;
    cout << "-----------------------------" << endl;
}

void deleteBook(Book* &books, int* &indexes, int* size, int deletePos)
{
    int newSize = *size - 1;

    if (newSize <= 0)
    {
        books = new Book[0];
        indexes = new int[0];
        *size = 0;

        return;
    }

    Book* newBooks = new Book[newSize];
    int* newIndexes = new int[newSize];

    int i;
    for (i = 0; indexes[i] != deletePos; i++)
    {
        if (indexes[i] < deletePos)
            newIndexes[i] = indexes[i];
        else
            newIndexes[i] = indexes[i] - 1;
    }
    for (i; i < newSize; i++)
    {
        if (indexes[i] < deletePos)
            newIndexes[i] = indexes[i + 1];
        else
            newIndexes[i] = indexes[i + 1] - 1;
    }
    for (i = 0; i < newSize; i++)
    {
        if (i < deletePos)
            newBooks[i] = books[i];
        else
            newBooks[i] = books[i + 1];
    }

    books = newBooks;
    indexes = newIndexes;
    *size = newSize;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);

    int size = 10;
    bool isSortedByAuthor = false;
    bool isSortedByYear = false;
    Book* books = createBooks();
    int* indexes = new int[size]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    bool isWork = true;
    while (isWork)
    {
        mainMenu();

        int choiseMenu = inputNumber(1, 6, "Выберите пункт меню: ", "Ошибка! Неверно введен пункт меню. Повторите ввод");
        switch (choiseMenu)
        {
        case 1:
            printBooks(books, indexes, size);
            break;
        case 2:
            {
                secondMenu("Выберите характеристику книги, по которой будет найдена книга из списка:");
                int choiseSort = inputNumber(1, 3, "Выберите пункт меню: ", "Ошибка! Неверно введен пункт меню. Повторите ввод");
                switch (choiseSort)
                {
                case 1:
                    sort(indexes, indexes + size, [&](int i, int j)
                        {
                            return compareObjectsByParam(books[i], books[j], 0);
                        });
                    isSortedByAuthor = true;
                    isSortedByYear = false;
                    cout << "Сортировка списка книг по автору была выполнена" << endl;
                    break;
                case 2:
                    sort(indexes, indexes + size, [&](int i, int j)
                        {
                            return compareObjectsByParam(books[i], books[j], 1);
                        });
                    isSortedByAuthor = false;
                    isSortedByYear = true;
                    cout << "Сортировка списка книг по году публикации была выполнена" << endl;
                    break;
                case 3:
                    cout << "Отмена." << endl;
                    break;
                }
            }
            break;
        case 3:
            {
                secondMenu("Выберите характеристику книги, по которой будет найдена книга из списка");
                int choiseSort = inputNumber(1, 3, "Выберите пункт меню: ", "Ошибка! Неверно введен пункт меню. Повторите ввод");
                switch (choiseSort)
                {
                    case 1:
                        if (isSortedByAuthor)
                        {
                            string search = inputString("Введите автора: ");
                            int pos = BinnarySearch(books, indexes, size, search, authorComparator);
                            if (pos != -1)
                            {
                                cout << "Книга по полю \"Автор\" и значению \"" << search << "\" была найдена." << endl;
                                books[indexes[pos]].print();
                            }
                            else
                            {
                                cout << "Книга по полю \"Автор\" и значению \"" << search << "\" не была найдена." << endl;
                            }
                        }
                        else
                        {
                            cout << "Невозможно выполнить действие, так как массив не отсортирован по нужной характеристике.\n"
                                << "Выполните необходимую сортировку и возвращайтесь к данному действию." << endl;
                        }
                        break;
                    case 2:
                        if (isSortedByYear)
                        {
                            int search = inputNumber(1, 2024, "Введите год публикации: ", "Ошибка. Вы неверно ввели год публикации. Повторите ввод");
                            int pos = BinnarySearch(books, indexes, size, to_string(search), authorComparator);
                            if (pos != -1)
                            {
                                cout << "Книга по полю \"Год публикации\" и значению \"" << search << "\" была найдена." << endl;
                                books[indexes[pos]].print();
                            }
                            else
                            {
                                cout << "Книга по полю \"Год публикации\" и значению \"" << search << "\" не была найдена." << endl;
                            }
                        }
                        else
                        {
                            cout << "Невозможно выполнить действие, так как массив не отсортирован по нужной характеристике.\n"
                                << "Выполните необходимую сортировку и возвращайтесь к данному действию." << endl;
                        }
                        break;
                    case 3:
                        cout << "Отмена." << endl;
                        break;
                }
            }
            break;
        case 4:
            {
                string newAuthor = "";
                int newYear;
                secondMenu("Выберите характеристику книги, которую будете редактировать.");
                int choiseSort = inputNumber(1, 3, "Выберите пункт меню: ", "Ошибка! Неверно введен пункт меню. Повторите ввод");
                switch (choiseSort)
                {
                    case 1:
                        {
                            int pos = inputNumber(1, size, "Введите номер книги: ", "Ошибка. Неверно ввели номер книги. Повторите ввод");
                            newAuthor = inputString("Ввдите новые данные автора: ");
                            books[indexes[pos - 1]].setAuthor(newAuthor);
                            cout << "Данные изменены" << endl;
                            isSortedByAuthor = false;
                        }
                        break;
                    case 2:
                        {
                            int pos = inputNumber(1, size, "Введите номер книги: ", "Ошибка. Неверно ввели номер книги. Повторите ввод");
                            newYear = inputNumber(1, 2024, "Введите новую дату публикации книги", "Ошибка. Неверно указана дата публикации. Повторите ввод");
                            books[indexes[pos - 1]].setYear(newYear);
                            cout << "Данные изменены" << endl;
                            isSortedByYear = false;
                        }
                        break;
                    case 3:
                        cout << "Отмена." << endl;
                        break;
                }
            }
        break;
        case 5:
            {
                secondMenu("Выберите характеристику книги, по которой будете искать книгу из списка для удаления.");
                int choiseSort = inputNumber(1, 3, "Выберите пункт меню: ", "Ошибка! Неверно введен пункт меню. Повторите ввод");
                switch (choiseSort)
                {
                case 1:
                    if (isSortedByAuthor)
                    {
                        string search = inputString("Введите автора: ");
                        int pos = BinnarySearch(books, indexes, size, search, authorComparator);
                        if (pos != -1)
                        {
                            cout << "Книга по полю \"Автор\" и значению \"" << search << "\" была найдена." << endl;
                            books[indexes[pos]].print();
                            deleteBook(books, indexes, &size, indexes[pos]);
                            cout << "Данная книга была удалена из списка" << endl;
                        }
                        else
                        {
                            cout << "Книга по полю \"Автор\" и значению \"" << search << "\" не была найдена." << endl;
                        }
                    }
                    else
                    {
                        cout << "Невозможно выполнить действие, так как массив не отсортирован по нужной характеристике.\n"
                            << "Выполните необходимую сортировку и возвращайтесь к данному действию." << endl;
                    }
                    break;
                case 2:
                    if (isSortedByYear)
                    {
                        int search = inputNumber(1, 2024, "Введите год публикации: ", "Ошибка. Вы неверно ввели год публикации. Повторите ввод");
                        int pos = BinnarySearch(books, indexes, size, to_string(search), authorComparator);
                        if (pos != -1)
                        {
                            cout << "Книга по полю \"Год публикации\" и значению \"" << search << "\" была найдена." << endl;
                            books[indexes[pos]].print();
                            deleteBook(books, indexes, &size, indexes[pos]);
                            cout << "Данная книга была удалена из списка" << endl;
                        }
                        else
                        {
                            cout << "Книга по полю \"Год публикации\" и значению \"" << search << "\" не была найдена." << endl;
                        }
                    }
                    else
                    {
                        cout << "Невозможно выполнить действие, так как массив не отсортирован по нужной характеристике.\n"
                            << "Выполните необходимую сортировку и возвращайтесь к данному действию." << endl;
                    }
                    break;
                case 3:
                    cout << "Отмена." << endl;
                    break;
                }
            }
            break;
        case 6:
            cout << "Конец работы" << endl;
            isWork = false;
            break;
        }
    }
}