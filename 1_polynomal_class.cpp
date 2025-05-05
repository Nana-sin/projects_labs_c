/* Задание звучит так: Составить описание класса многочленов от одной переменной, задаваемых степенью многочлена
и массивом коэффициентов. Предусмотреть методы для вычисления значения многочлена для
заданного аргумента, операции сложения и вычитания многочленов с получением нового объекта-
многочлена, вывод на экран описания многочлена. Написать программу, демонстрирующую
работу с этим классом. Программа может содержать меню, позволяющее осуществить проверку
всех методов класса. */
#include <cmath>
#include <cstdio>

using namespace std;                                                                                  
class Polynom
{
private:
    char* namePolynom;
    int stepen;
    double* coefficients;

public:
    Polynom(const char* n, int s, const double* c)
    {
      namePolynom = new char[20];
      
      int i {0};
      //копируется только 19 элементов чтобы оставить место для символа конца строки
      while(n[i] != '\0' && i < 19) //символ 0 это конец строки
      {
        namePolynom[i] = n[i];
        i++;
      }
      namePolynom[i] = '\0';

      stepen = s;
      coefficients = new double[s+1];
      for(int i = 0; i <= s; i++)
      {
        coefficients[i] = c[i];
      }
    }

    char* getName()
    {
        return namePolynom;
    }

    ~Polynom()
    {
        delete [] namePolynom;
        delete [] coefficients;
    }

    static Polynom* create()
    {
        char n[20];
        int s1 {0};
        double* c1;

        printf("Введите имя многочлена без пробелов(до 19 символов): ");
        scanf("%19s", n);
        while (getchar() != '\n');
        
        printf("Введите степень многочлена: ");
        while (scanf("%d", &s1) != 1) 
        {
            while (getchar() != '\n');
            printf("Ошибка! Введиет целое число!");
        }
        while (getchar() != '\n');

        c1 = new double[s1+1];
        printf("Введите %d коэффициентов:\n", s1 + 1);
        for(int i = 0; i <=s1; i++)
        {
            printf("coefficients[%d]:", i);
            while(scanf("%lf", &c1[i]) != 1)
            {
                while(getchar() != '\n');
                printf("Ошибка! Введиет число: ");
            }
        }

        return new Polynom(n, s1, c1);
    }

    static void change(Polynom*& poly) {
        delete poly;
        poly = create(); 
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (int i = stepen; i >= 0; --i) { // за основу взята схема Горнера
            result = result * x + coefficients[i];
        }
        return result;
    }

    Polynom* plus(const Polynom* other) 
    {
        int max_stepen = (stepen > other->stepen) ? stepen : other->stepen;
        double* new_coeffs = new double[max_stepen + 1]{0.0};

    
        for (int i = 0; i <= stepen; ++i) {
            new_coeffs[i] = coefficients[i];
        }

        for (int i = 0; i <= other->stepen; ++i) {
            new_coeffs[i] += other->coefficients[i];
        }

        int result_stepen = 0;
        for (int i = max_stepen; i >= 0; --i) {
            if (new_coeffs[i] != 0.0) {
                result_stepen = i;
                break;
            }
        }

        return new Polynom("Сумма", result_stepen, new_coeffs);
    }

    Polynom* minus(const Polynom* other)  
    {
        int max_stepen = (stepen > other->stepen) ? stepen : other->stepen;
        double* new_coeffs = new double[max_stepen + 1]{0.0};

        for (int i = 0; i <= stepen; ++i) {
            new_coeffs[i] = coefficients[i];
        }

        for (int i = 0; i <= other->stepen; ++i) {
            new_coeffs[i] -= other->coefficients[i];
        }

        int result_degree = 0;
        for (int i = max_stepen; i >= 0; --i) {
            if (new_coeffs[i] != 0.0) {
                result_degree = i;
                break;
            }
        }

        return new Polynom("Вычитание", result_degree, new_coeffs);
    }

    void print()
    {
        printf("\n-- Дебаггинг! --\n");
        printf("\n**Многочлен '%s'**\nСтепень: %d\nКоэффициенты: ", namePolynom, stepen);
        for(int i = 0; i <= stepen; i++)
        {
            printf("%.2f ", coefficients[i]);
        }
        printf("\n\n");
    }

    void printCanonical()
    {
        printf("\n%s(x) = ", namePolynom);
        bool first = 1;

        for(int i = 0; i <= stepen; i++)
        {
            const double val = coefficients[i];
            if(val == 0) continue;

            if(!first)
            {
                printf(val > 0 ? " + " : " - ");
            }
            else if(val < 0)
            {
                printf("-");
            }


            const double abs_val = val > 0 ? val : -val;
            if(abs_val != 1 || i == 0)
            {
                printf("%.2f", abs_val);
            }

            if(i > 0)
            {
                printf("x");
                if(i > 1)
                {
                    printf("^%d", i);
                }
            }

            first = 0;
        }

        if (first == 1)
        {
            printf("0.00");
        }
        printf("\n\n");
    }
};



void PrintMenu(bool debug)
{
    printf("\n**Главное меню**\n");
    if(debug == true)
    {
    printf("-- ДЕБАГГИНГ! --\n");
    printf("0. Демо класса.\n");
    printf("-----------------------------------\n");
    }
    printf("1. Изменение многочленов.\n");
    printf("2. Просмотр многочленов.\n"); 
    printf("3. Сумма двух многочленов.\n");
    printf("4. Разность двух многочленов.\n");
    printf("5. Вычисление многочлена в точке x с заданным коэффициентом.\n");
    printf("6. Выход из программы.\n");
    printf("-->Выберите действие: ");
}

void clearConsole() { printf("\033[2J\033[H"); }


void waitForEnter() {
    printf("\nНажмите Enter чтобы продолжить...");
    fflush(stdout);
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    while (getchar() != '\n');
}



void DemoClassPolynoms()
{
    double c1[] = {1.0, 3.0, 2.0};
    Polynom p1("Poly1", 2, c1);
    p1.printCanonical();

    double c2[] = {4.0, -1.0, 0.0, 1.0};
    Polynom p2("Poly2", 3, c2);
    p2.printCanonical();
 
    Polynom* sum = p1.plus(&p2);
    sum->printCanonical(); 
 
    Polynom* diff = p1.minus(&p2);
    diff->printCanonical(); 
    waitForEnter();
    delete sum;
    delete diff;
}

int main()
{ 
    bool debug = false;
    int ch;
    char sel;
    printf("Включить меню с дебагом?: (Y/N) ");
    scanf("%1c", &sel);
    while(getchar() != '\n');

    if (sel == 'Y' || sel == 'y')
    {
        debug = true;
    } else if(sel == 'N' || sel == 'n') {
        debug = false;
    }
    clearConsole();
    printf("Введите параметры для создания первого многочлена: \n");
    Polynom* p1 = p1->create();
    clearConsole();
    printf("Введите параметры для создания второго многочлена: \n");
    Polynom* p2 = p2->create();
    do 
    {
        clearConsole();
        PrintMenu(debug);
        scanf("%1d", &ch);
        switch (ch) 
        {
           
            case 1: { 
                clearConsole();
                printf("Какой из многочленов пересоздать? Первый (1) или второй (2)?: ");
                int c;
                scanf("%1d", &c);
                while(getchar() != '\n');
                
                if (c == 1) {                       
                    Polynom::change(p1);
                    p1->printCanonical();
                } else if (c == 2) {
                    Polynom::change(p2);
                    p2->printCanonical();
                } 

                waitForEnter();
                break;
            }
            case 2: {
                clearConsole();
                printf("Какой из многочленов показать? (1 - первый, 2 - второй): ");
                int c;
                scanf("%d", &c);
                while(getchar() != '\n');

                if(c == 1)
                {
                    if(debug == true)
                    {
                    p1->print();
                    }
                    p1->printCanonical();
                    waitForEnter();
                } else if (c == 2) {
                    if (debug == true)
                    {
                    p2->print();
                    }
                    p2->printCanonical();
                    waitForEnter();
                }
                break;
            }
            case 3: {
                clearConsole();
                printf("Сумма многочлена %s ", p1->getName());
                printf("к многочлену %s равна:\n", p2->getName());
                Polynom* sum = p1->plus(p2);
                sum->printCanonical();
                if(debug == true)
                {
                    p1->print();
                    p2->print();
                    sum->print();
                }
                waitForEnter();
             break;
            }
            case 4: {
                clearConsole();
                printf("Разность многочлена %s ", p1->getName());
                printf("к многочлену %s равна:\n", p2->getName());
                Polynom* rasn = p1->minus(p2);
                rasn->printCanonical();
                if(debug == true)
                {
                    p1->print();
                    p2->print();
                    rasn->print();
                }
                waitForEnter();
                break;
            }
            case 5: {
                clearConsole();
                short chh;
                printf("ВНИМАНИЕ! Вычисление проводится по схеме Горнера, учитывается нулевой коэффициент!\n");
                printf("Выберите многочлен (1) или (2): ");
                
                scanf("%1hd", &chh);
                while(getchar() != '\n');

                if(chh == 1)
                {
                    printf("Введите точку х: ");
                    double x;
                    scanf("%lf", &x);



                    double result = p1->evaluate(x);
                    printf("В многочлене %s выражение в точке х со значением ", p1->getName());
                    printf("%f равна: ", x);
                    printf("%f", result);
                    printf("\nМногочлен %s: ", p1->getName());
                    p1->printCanonical();
                    if(debug == true)
                    {
                        p1->print();
                    }
                waitForEnter();
                } else if (chh == 2)
                {
                    printf("Введите точку х: ");
                    double x;

                    scanf("%lf", &x);
                    while(getchar() != '\n');

                    double result = p2->evaluate(x);
                    printf("В многочлене %s выражение в точке х со значением ", p2->getName());
                    printf("%f равна: ", x);
                    printf("%f", result);
                    printf("\nМногочлен %s: ", p2->getName());
                    p2->printCanonical();
                    if(debug == true)
                    {
                        p2->print();
                    }
                    waitForEnter();
                }
                
            }
            case 6: 
              break;
              case 0: {
                clearConsole();
                printf("--Дебаггинг--\n");
                printf("**Демонстрация работы класса.**\n");
                DemoClassPolynoms();
                break;
            }
            default:
            {
                printf("Неправильная цифра меню! Введите корректное значение!\n");
                waitForEnter();
                break;
            }
        }
    }
    while (ch != 6);
    return 0;
}
