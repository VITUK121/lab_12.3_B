#include <iostream>  
#include <Windows.h>  
#include <string>  
#include <fstream>  
#include <iomanip>  

using namespace std;

enum Majors { KN = 1, IT, ME, PI, TN};

struct Student {
    char prizv[100];
    int course;
    Majors major;
    int physics;
    int math;
    union {
        int prog;
        int it;
        int pedagogika;
    };
};

int counter(string filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Не вдалося відкрити файл!" << endl;
        return 0;
    }

    Student student;
    int count = 0;

    while (file.read((char*)(&student), sizeof(Student))) {
        count++;
    }

    file.close();
    return count;
}

void try_input(const char message[], unsigned short& var) {
    bool fail;
    do {
        fail = false;
        cout << message; cin >> var;
        if (cin.fail()) {
            fail = true;
            cout << "Неправильний ввід!\n";
            cin.clear();
            cin.ignore(65535, '\n');
        }
    } while (fail);

}

void del(string filename, string prizv, int& n) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    ofstream tempFile("temp.dat", ios::binary);
    if (!tempFile) {
        cout << "Не вдалося створити тимчасовий файл!" << endl;
        return;
    }

    Student student;
    bool found = false;

    while (file.read((char*)(&student), sizeof(Student))) {
        if (strcmp(student.prizv, prizv.c_str()) != 0) {
            tempFile.write((char*)(&student), sizeof(Student));
        }
        else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.dat", filename.c_str());  // Correct extension here

    if (found) {
        cout << "Студента з прізвищем " << prizv << " видалено.\n";
    }
    else {
        cout << "Студента з прізвищем " << prizv << " не знайдено.\n";
    }
    n = counter(filename);
}


void writeFile(string filename, int& n) {
    ofstream file(filename, ios::binary | ios::app);

    if (!file) {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    Student student;
    string continueInput;

    do {
        cout << "Введіть прізвище студента: ";
        cin >> student.prizv;

        cout << "Введіть курс: ";
        cin >> student.course;

        while (student.course < 1 || student.course > 5) {
            cout << "Некоректний курс. Введіть курс від 1 до 5: ";
            cin >> student.course;
        }

        cout << "Виберіть спеціальність ( 1 = KN, 2 = IT, 3 = ME, 4 = PI, 5 = TN): ";
        int majorInput;
        cin >> majorInput;

        while (majorInput < 1 || majorInput > 3) {
            cout << "Некоректний вибір. Виберіть 1, 2 або 3: ";
            cin >> majorInput;
        }
        student.major = static_cast<Majors>(majorInput);

        cout << "Введіть оцінку з фізики: ";
        cin >> student.physics;

        cout << "Введіть оцінку з математики: ";
        cin >> student.math;

        string message;

        switch (student.major)
        {
        case KN:
            message = "програмування";
            break;
        case IT:
            message = "чисельних методів";
            break;
        case ME:
            message = "педагогіки";
            break;
        case PI:
            message = "педагогіки";
            break;
        case TN:
            message = "педагогіки";
            break;
        }

        cout << "Введіть оцінку з " << message << ": ";
        cin >> student.prog;

        file.write((char*)(&student), sizeof(Student));

        cout << "Бажаєте додати ще одного студента? (так/ні): ";
        cin >> continueInput;

    } while (continueInput == "так" || continueInput == "Так");

    file.close();
    cout << "Дані успішно записані у файл." << endl;
    n = counter(filename);
}

void correct(string filename, string prizv) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    ofstream tempFile("temp.dat", ios::binary);
    if (!tempFile) {
        cout << "Не вдалося створити тимчасовий файл!" << endl;
        return;
    }

    Student student;
    bool found = false;

    while (file.read((char*)(&student), sizeof(Student))) {
        if (strcmp(student.prizv, prizv.c_str()) == 0) {
            found = true;
            cout << "Редагування інформації про студента " << prizv << endl;

            cout << "Новий курс: "; cin >> student.course;
            while (student.course < 1 || student.course > 5) {
                cout << "Некоректний курс. Введіть курс від 1 до 5: ";
                cin >> student.course;
            }

            cout << "Виберіть нову спеціальність (1 - РІ, 2 - ІК, 3 - ПЗ): ";
            int majorInput;
            cin >> majorInput;
            while (majorInput < 1 || majorInput > 3) {
                cout << "Некоректний вибір. Виберіть 1, 2 або 3: ";
                cin >> majorInput;
            }
            student.major = static_cast<Majors>(majorInput);

            cout << "Нова оцінка з фізики: "; cin >> student.physics;
            cout << "Нова оцінка з математики: "; cin >> student.math;

            string message;

            switch (student.major)
            {
            case KN:
                message = "програмування";
                break;
            case IT:
                message = "чисельних методів";
                break;
            case ME:
                message = "педагогіки";
                break;
            case PI:
                message = "педагогіки";
                break;
            case TN:
                message = "педагогіки";
                break;
            }

            cout << "Нова оцінка з" << message << ": "; cin >> student.prog;
        }

        tempFile.write((char*)(&student), sizeof(Student));
    }

    file.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.dat", filename.c_str());

    if (found) {
        cout << "Інформацію про студента " << prizv << " оновлено.\n";
    }
    else {
        cout << "Студента з прізвищем " << prizv << " не знайдено.\n";
    }
}


int lenOfLongestPrizv(string filename, int n) {
    int res = 0;

    ifstream file(filename, ios::binary);
    Student student;

    for (int i = 0; i < n; i++) {
        file.read((char*)(&student), sizeof(Student));
        if (strlen(student.prizv) > res) {
            res = strlen(student.prizv);
        }
    }

    file.close();
    return res;
}

int calc_n(int n) {
    int res = 0;
    while (n != 0) {
        n /= 10;
        res++;
    }
    return res;
}

void printStudents(string filename, int n) {
    int width = lenOfLongestPrizv(filename, n);
    (width <= 8) ? (width = 8) : (NULL);
    int maxDigits = calc_n(n);

    for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
        cout << "=";
    }
    cout << endl;

    cout << "|" << setw(maxDigits) << right << "№";
    cout << "|" << setw(width) << left << "Прізвище" << "| Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;

    for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
        cout << "-";
    }
    cout << endl;

    ifstream file(filename, ios::binary);
    Student student;

    for (int i = 0; i < n; i++) {
        file.read((char*)(&student), sizeof(Student));

        cout << "|" << setw(maxDigits) << right << i + 1;
        cout << "|" << setw(width) << left << student.prizv;
        cout << "|" << setw(6) << left << student.course;
        cout << "|" << setw(15) << left;

        switch (student.major) {
            case KN: cout << "KN"; break;
            case IT: cout << "IT"; break;
            case ME: cout << "ME"; break;
            case PI: cout << "PI"; break;
            case TN: cout << "TN"; break;
        }


        cout << "|" << setw(8) << left << student.physics;
        cout << "|" << setw(12) << left << student.math;
        cout << "|" << setw(15) << left;
        (student.major == KN ? cout << student.prog : cout << "-");
        cout << "|" << setw(17) << left;
        (student.major == IT ? cout << student.prog : cout << "-");
        cout << "|" << setw(12) << left;
        (student.major != KN && student.major != IT ? cout << student.prog : cout << "-");
        cout << setw(13) << "|" << endl;
    }

    for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
        cout << "-";
    }
    cout << endl;
    file.close();
}

double average(string filename, int n, int subject) {
    ifstream file(filename, ios::binary);
    Student student;
    double res = 0;

    for (int i = 0; i < n; i++) {
        file.read((char*)(&student), sizeof(Student));

        switch (subject) {
        case 1:
            res += student.physics;
            break;
        case 2:
            res += student.math;
            break;
        case 3:
            res += student.it;
            break;
        }
    }
    file.close();
    return res / n;
}

void sort(string filename, int n) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    // Читання всіх студентів в масив
    Student* students = new Student[n];
    for (int i = 0; i < n; i++) {
        file.read((char*)&students[i], sizeof(Student));
    }
    file.close();

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].course > students[j].course ||
                (students[i].course == students[j].course && students[i].it > students[j].it) ||
                (students[i].course == students[j].course && students[i].it == students[j].it && students[i].prizv < students[j].prizv)) {

                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    ofstream tempFile("temp.dat", ios::binary);
    if (!tempFile) {
        cout << "Не вдалося створити тимчасовий файл!" << endl;
        delete[] students;
        return;
    }

    for (int i = 0; i < n; i++) {
        tempFile.write((char*)&students[i], sizeof(Student));
    }
    tempFile.close();

    remove(filename.c_str());
    rename("temp.dat", filename.c_str());

    delete[] students;
    cout << "Сортування завершено!" << endl;
}


void make_index_file(string filename, int n) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Не вдалося відкрити основний файл!" << endl;
        return;
    }


    ofstream indexFile("index.dat", ios::binary);
    if (!indexFile) {
        cout << "Не вдалося створити індексний файл!" << endl;
        return;
    }


    int* mas = new int[n];
    for (int i = 0; i < n; i++) {
        mas[i] = i;
    }


    for (int i = 1; i < n; i++) {
        int value = mas[i];
        int j;
        for (j = i - 1; j >= 0; j--) {
            bool should_swap = false;


            file.seekg(mas[j] * sizeof(Student), ios::beg);
            Student student1;
            file.read((char*)&student1, sizeof(Student));

            file.seekg(mas[j + 1] * sizeof(Student), ios::beg);
            Student student2;
            file.read((char*)&student2, sizeof(Student));


            if (student1.course > student2.course) {
                should_swap = true;
            }
            else if (student1.course == student2.course &&
                student1.it > student2.it) {
                should_swap = true;
            }
            else if (student1.course == student2.course &&
                student1.it == student2.it &&
                strcmp(student1.prizv, student2.prizv) > 0) {
                should_swap = true;
            }

            if (should_swap) {
                mas[j + 1] = mas[j];
            }
            else {
                break;
            }
        }
        mas[j + 1] = value;
    }

    for (int i = 0; i < n; i++) {
        indexFile.write((char*)&mas[i], sizeof(int));
    }

    delete[] mas;
    file.close();
    indexFile.close();

    cout << "Індексний файл успішно створений!" << endl;
}


void printIndex(string indexFilename, string dataFilename, int n) {
    ifstream indexFile(indexFilename, ios::binary);
    if (!indexFile) {
        cout << "Не вдалося відкрити індексний файл!" << endl;
        return;
    }

    ifstream file(dataFilename, ios::binary);
    if (!file) {
        cout << "Не вдалося відкрити основний файл!" << endl;
        return;
    }

    indexFile.seekg(0, ios::end);
    int indexSize = indexFile.tellg() / sizeof(int);
    indexFile.seekg(0, ios::beg);

    int* mas = new int[indexSize];
    indexFile.read((char*)mas, indexSize * sizeof(int));


    int width = lenOfLongestPrizv(dataFilename, n);
    (width <= 8) ? (width = 8) : (NULL);
    int maxDigits = calc_n(n);

    for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
        cout << "=";
    }
    cout << endl;

    cout << "|" << setw(maxDigits) << right << "№";
    cout << "|" << setw(width) << left << "Прізвище" << "| Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;

    for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
        cout << "-";
    }
    cout << endl;


    for (int i = 0; i < indexSize; i++) {
        int index = mas[i];
        file.seekg(index * sizeof(Student), ios::beg);

        Student student;
        file.read((char*)&student, sizeof(Student));

        cout << "|" << setw(maxDigits) << right << i + 1;
        cout << "|" << setw(width) << left << student.prizv;
        cout << "|" << setw(6) << left << student.course;
        cout << "|" << setw(15) << left;

        switch (student.major) {
            case KN: cout << "KN"; break;
            case IT: cout << "IT"; break;
            case ME: cout << "ME"; break;
            case PI: cout << "PI"; break;
            case TN: cout << "TN"; break;
        }


        cout << "|" << setw(8) << left << student.physics;
        cout << "|" << setw(12) << left << student.math;
        cout << "|" << setw(15) << left;
        (student.major == KN ? cout << student.prog : cout << "-");
        cout << "|" << setw(17) << left;
        (student.major == IT ? cout << student.prog : cout << "-");
        cout << "|" << setw(12) << left;
        (student.major != KN && student.major != IT ? cout << student.prog : cout << "-");
        cout << setw(13) << "|" << endl;

    }

    for (int i = 0; i < (maxDigits - 1) + (width - 8) + 104; i++) {
        cout << "-";
    }
    cout << endl;

    delete[] mas;
    indexFile.close();
    file.close();
}

int binSearch(string filename, int n, const string prizv, int course, int it) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Не вдалося відкрити файл!" << endl;
        return -1;
    }

    Student* students = new Student[n];
    for (int i = 0; i < n; i++) {
        file.read((char*)&students[i], sizeof(Student));
    }
    file.close();

    int L = 0, R = n - 1, m;

    while (L <= R) {
        m = (L + R) / 2;

        int comparison = strcmp(students[m].prizv, prizv.c_str());

        if (students[m].course == course && students[m].it == it && comparison == 0) {
            delete[] students;
            return m;
        }

        if ((students[m].course < course) ||
            (students[m].course == course && students[m].it < it) ||
            (students[m].course == course && students[m].it == it && comparison > 0)) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    }

    delete[] students;
    return -1;
}

void menu(string filename, int& n) {
    int option_1, course, it, res;
    string prizv;

    while (true) {
        cout << "Меню:\n[1] Додати студента\n[2] Видалити студента\n[3] Редагувати інформацію про студента\n[4] Вивід списку студентів\n[5] Сортування списку студентів\n[6] Створення індексного файлу\n[7] Пошук студента\n[8] Вихід з програми\n : ";
        cin >> option_1;

        switch (option_1) {
        case 1:
            writeFile(filename, n);
            break;

        case 2:
            cout << "Введіть прізвище студента: "; cin >> prizv;
            del(filename, prizv, n);
            break;

        case 3:
            cout << "Введіть прізвище студента: "; cin >> prizv;
            correct(filename, prizv);
            break;

        case 4:
            printStudents(filename, n);
            break;

        case 5:
            sort(filename, n);
            break;

        case 6:
            make_index_file(filename, n);
            printIndex("index.dat", filename, n);
            break;

        case 7:
            cout << "Введіть прізвище студента: "; cin >> prizv;
            cout << "Введіть курс: "; cin >> course;
            cout << "Введіть оцінку з інформатики: "; cin >> it;
            sort(filename, n);
            res = binSearch(filename, n, prizv, course, it);
            cout << "Index: " << res << endl;
            break;

        case 8:
            return;

        default:
            cout << "Неправильний ввід!\n";
            break;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string filename;

    cout << "Ім'я файлу: ";
    cin >> filename;

    int n = counter(filename);

    menu(filename, n);
}