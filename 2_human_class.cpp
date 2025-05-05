/*  Создать класс человек, имеющий имя (указатель на строку), возраст, вес. Определить конструктор,
деструктор и функцию печати. Создать public-производный класс – совершеннолетний, имеющий
номер паспорта. Определить конструктор по умолчанию, функцию печати. Определить функции
переназначения возраста и номера паспорта. Программа должна содержать меню, позволяющее
осуществить проверку всех методов классов. */ 
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <limits>
using namespace std;
class Person{ 
    protected:
    char* personName;
    unsigned personAge;
    int personWeight;

    public:

    Person () {
        const char* defaultname = "Нет имени";
        personName = new char[strlen(defaultname) + 1];
        strcpy(personName, defaultname);
        personAge = 15;
        personWeight = 40;
    }


    Person (const char* _personName, unsigned _personAge, int _personWeight) 
    {
        personName = new char[strlen(_personName) + 1];
        strcpy(personName, _personName);
        personAge = _personAge;
        personWeight = _personWeight; 
    }

    virtual ~Person()
    {
        delete [] personName;
    }

    void setAgePerson(int setAge)
    {
        if(setAge < 18 && setAge > 0) personAge = setAge;
        else cout << "Ошибка, возраст должен быть меньше 18 и больше нуля.\n";
    }

    void printPerson() const
    {
        cout << "Имя: " << personName << "\nВозраст: " << personAge << "\nВес: " << personWeight << " кг\n";
    }
};

class Adult : public Person
{
    private:
    unsigned short serial[4]; 
    unsigned short number[6];
    public:
    Adult () : Person ()
    {
        personAge = 18;
        personWeight = 60;
        unsigned short defaultSerial[4] = {0};
        unsigned short defaultNumber[6] = {0};
        setPassport(defaultSerial, defaultNumber);
    }

    Adult(const char* name, int age, int weight, const unsigned short  s[4], const unsigned short n[6]) : Person(name, age, weight)
    {
        memcpy(serial, s, sizeof(serial));
        memcpy(number, n, sizeof(number));
    }

    void printAdult() const 
    {
        cout << "Имя: " << personName << "\nВозраст: " << personAge << "\nВес: " << personWeight << " кг\n";
        cout << "Паспорт: ";

       for(int i = 0; i < 4; i++)
       {
        cout << serial[i];
       }

       cout << "-";
        for(int i = 0; i < 6; i++)
        {
            cout << number[i];
        }
        cout << endl;
    }

    void setPassport(const unsigned short s[4], const unsigned short n[6])
    {
        memcpy(serial, s, sizeof(serial));
        memcpy(number, n, sizeof(number));
    }

    void setAge(int setAge)
    {
        if(setAge >= 18 && setAge > 0) personAge = setAge;
        else cout << "Ошибка, возраст должен быть больше или равен 18 и не быть отрицательным или нулём.\n";
    }
};

void PrintAll(Person** people, int count)
{
    for(int i = 0; i < count; i++)
    {
        cout << "\nЗапись #" << i << "\n";

    if(Adult* a = dynamic_cast<Adult*>(people[i]))
    {
        a->printAdult();
    }
    else 
    {
        people[i]->printPerson();
    }
    }
}

void clearConsole() { printf("\033[2J\033[H"); }

void clearInputBuffer()
{
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void MainMenu()
{
    cout << "\nГЛАВНОЕ МЕНЮ ПРОГРАММЫ\n";
    cout << "0. Создание учетных записей по умолчанию.\n";
    cout << "1. Создать учетную запись совершеннолетнего человека, имеющий паспорт.\n";
    cout << "2. Создание учетной записи несовершеннолетнего человека (нет паспорта).\n";
    cout << "3. Изменить возраст совершеннолетнего.\n";
    cout << "4. Изменить возраст несовершеннолетнего.\n";
    cout << "5. Изменение паспорта совершеннолетнего.\n";
    cout << "6. Просмотр всех учётных записей в программе.\n";
    cout << "7. Выход из программы.\n";
    cout << "Введите команду ->>> ";
}

void waitForEnter() {
    printf("\nНажмите Enter чтобы продолжить...");
    fflush(stdout);
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void inputPasswordData(unsigned short* dest, int size, const char* prompt)
{
    cout << prompt;
    for(int i = 0; i < size; i++)
    {
        cin >> dest[i];
        dest[i] %= 10;
    }
}


int main()
{
    Person* people[10];
    int count = 0;
    int choice {0};

    do {
        clearConsole();
        MainMenu();
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 0:
            {
                clearConsole();
                cout << "Создание учетных записей по умолчанию.\n";
                int ch;
                cout << "Введите кого хотите создать по умолчанию (1 - совершеннолетнего, 2 - несовершеннолетнего): ";
                cin >> ch; 
                clearInputBuffer(); 
            
                if (ch == 1) {
                    people[count++] = new Adult();
                    cout << "Совершеннолетний создан по умолчанию.\n";
                } else if (ch == 2) {
                    people[count++] = new Person();
                    cout << "Несовершеннолетний создан по умолчанию.\n";
                } else {
                    cout << "Неверный выбор.\n";
                }
                waitForEnter();
                break;
            }
            case 1: {
                clearConsole();
                cout << "Создание совершеннолетнего.\n";
                char name[50];
                int age;
                int weight;
                unsigned short s[4], n[6];
                cout << "Введите имя: ";
                cin.getline(name, 50);

                cout << "Введите возраст (>=18): ";
                cin >> age;
                while(age < 18)
                {
                    cout << "Введите нормальный возраст!: ";
                    clearInputBuffer();
                    cin >> age;
                }

                cout << "Введите вес (не дробный): ";
                cin >> weight;
                clearInputBuffer();

                inputPasswordData(s, 4, "Введите серию паспорта (4 цифры через пробел): ");
                inputPasswordData(n, 6, "Введите номер паспорта (6 цифр через пробел): ");

                people[count++] = new Adult(name, age, weight, s, n);
                cout << "совершеннолетний создан\n";
            
                waitForEnter();
                break;
            }

            case 2: {
                char name[50];
                int age;
                int weight;

                clearConsole();
                cout << "Создание несовершеннолетнего.\n";
                cout << "Введите имя: ";
                cin.getline(name, 50);

                cout << "Введите возраст: ";
                cin >> age;
                while(age >= 18)
                {
                    cout << "Введите нормальный возраст!: ";
                    clearInputBuffer();
                    cin >> age;
                }
                cout << "Введите вес: ";
                cin >> weight;
                clearInputBuffer();

                people[count++] = new Person(name, age, weight);
                cout << "Несовершеннолетний создан";
                waitForEnter();
                break;
            }

            case 3: {
                clearConsole();
                cout << "Изменение возраста совершеннолетнего.\n";
                if(count == 0)
                {
                    cout << "Сначала создайте хотябы одного человека!\n";
                    waitForEnter();
                    break;
                }

                int index, newAge;
                cout << "Номер объекта (0-" << count-1 << "): ";
                cin >> index;

                if(index >= 0 && index < count)
                {
                    if(Adult* a = dynamic_cast<Adult*>(people[index]))
                    {
                        cout << "Новый возраст: ";
                        cin >> newAge;
                        a->setAge(newAge);
                    } else {
                        cout << "Это не совершеннолетний!\n";
                    }
                }
                clearInputBuffer();
                waitForEnter();
                break;
            }
            case 4: {
                clearConsole();
                cout << "Изменение возраста несовершеннолетнего.\n";
                if(count == 0)
                {
                    cout << "Сначала создайте хотябы одного человека!\n";
                    waitForEnter();
                    break;
                }

                int index, newAge;
                cout << "Номер объекта (0-" << count-1 << "): ";
                cin >> index;

                if(index >= 0 && index < count)
                {
                    if(Person* a = dynamic_cast<Person*>(people[index]))
                    {
                        cout << "Новый возраст: ";
                        cin >> newAge;
                        a->setAgePerson(newAge);
                        cout << "Установлен возраст!\n";
                    } else {
                        cout << "Это совершеннолетний!\n";
                    }
                }
                clearInputBuffer();
                waitForEnter();
                break;

            }

            case 5: {
                clearConsole();
                cout << "Изменение паспорта совершеннолетнего.\n";
                if(count == 0)
                {
                    cout << "Сначала создайте хотя-бы одного человека!.\n";
                    waitForEnter();
                    break;
                }

                int index;
                unsigned short s[4], n[6];
                cout << "Номер записи человека(0-" << count-1 << " ): ";
                cin >> index;
                clearInputBuffer();

                if(index >= 0 && index < count)
                {
                    if(Adult* a = dynamic_cast<Adult*>(people[index]))
                    {
                        inputPasswordData(s, 4, "Новая серия паспорта: ");

                        inputPasswordData(n, 6, "Новый номер паспорта: ");

                        a->setPassport(s, n);
                        cout << "Паспорт изменён!";
                    } else {
                        cout << "Это не совершеннолетний!\n";
                    }
                }
                
                waitForEnter();
                break;
            }

            case 6:
            {
                clearConsole();
                cout << "Все записи в программе:\n";
                PrintAll(people, count);
                waitForEnter();
                break;
            }

            case 7: {
                for(int i = 0; i < count; ++i)
                {
                    delete people[i];
                }
                exit(0);
            }

            default:
            {
                cout << "Неверный номер меню.\n";
                waitForEnter();
                break;
            }
        }
    } while(choice != 7);

    for(int i = 0; i < count; ++i)
    {
        delete people[i];
    }

    return 0;
}
