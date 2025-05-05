/* The task is as follows: 
Create a class for single-variable polynomials defined by their degree and an array of coefficients. 
The class should include methods to evaluate the polynomial at a given argument, 
perform addition and subtraction operations (resulting in a new polynomial object), 
and display the polynomial's description. 
Write a program demonstrating the use of this class, which may include a menu to test all the class methods.
*/
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
      while(n[i] != '\0' && i < 19)
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

        printf("Input name polynom without spaces (19 symbols maximum): ");
        scanf("%19s", n);
        while (getchar() != '\n');
        
        printf("Input degree polynom: ");
        while (scanf("%d", &s1) != 1) 
        {
            while (getchar() != '\n');
            printf("Error! Input integer number!");
        }
        while (getchar() != '\n');

        c1 = new double[s1+1];
        printf("Input %d coefficients:\n", s1 + 1);
        for(int i = 0; i <=s1; i++)
        {
            printf("coefficients[%d]:", i);
            while(scanf("%lf", &c1[i]) != 1)
            {
                while(getchar() != '\n');
                printf("Error! Input number: ");
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
        for (int i = stepen; i >= 0; --i) { // relies on Horner's scheme
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

        return new Polynom("Sum", result_stepen, new_coeffs);
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

        return new Polynom("Subdivision", result_degree, new_coeffs);
    }

    void print()
    {
        printf("\n-- DEBUGGING! --\n");
        printf("\n**Polynom '%s'**\nDegree: %d\nCoefficients: ", namePolynom, stepen);
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
    printf("\n**Main menu**\n");
    if(debug == true)
    {
    printf("-- DEBUGGING! --\n");
    printf("0. Class demo.\n");
    printf("-----------------------------------\n");
    }
    printf("1. Modifying polynomials.\n");
    printf("2. Viewing polynomials.\n"); 
    printf("3. Sum of two polynomials.\n");
    printf("4. Difference of two polynomials.\n");
    printf("5. Calculation of a polynomial at point x given coefficient.\n");
    printf("6. Quitting the program.\n");
    printf("-->Choose an action: ");
}

void clearConsole() { printf("\033[2J\033[H"); }


void waitForEnter() {
    printf("\nPress Enter to continue...");
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
    printf("Enable menu with debug?: (Y/N)");
    scanf("%1c", &sel);
    while(getchar() != '\n');

    if (sel == 'Y' || sel == 'y')
    {
        debug = true;
    } else if(sel == 'N' || sel == 'n') {
        debug = false;
    }
    clearConsole();
    printf("Enter the parameters to create the first polynomial: \n");
    Polynom* p1 = p1->create();
    clearConsole();
    printf("Enter the parameters to create the second polynomial: \n");
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
                printf("Which polynomial should be recreated? The first (1) or the second (2)?: ");
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
                printf("Which of the polynomials should be shown? (1 - first, 2 - second): ");
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
                printf("Polynom's sum %s ", p1->getName());
                printf("to polynom %s equals:\n", p2->getName());
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
                printf("Difference of a polynomial %s ", p1->getName());
                printf("to polynom %s equals:\n", p2->getName());
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
                printf("ATTENTION! The calculation is carried out according to Horner's scheme, the zero coefficient is taken into account!\n");
                printf("Choose a polynomial (1) or (2): ");
                
                scanf("%1hd", &chh);
                while(getchar() != '\n');

                if(chh == 1)
                {
                    printf("Введите точку х: ");
                    double x;
                    scanf("%lf", &x);



                    double result = p1->evaluate(x);
                    printf("In the polynomial %s the expression at the point x with the value ", p1->getName());
                    printf("%f equals: ", x);
                    printf("%f", result);
                    printf("\nPolynomial %s: ", p1->getName());
                    p1->printCanonical();
                    if(debug == true)
                    {
                        p1->print();
                    }
                waitForEnter();
                } else if (chh == 2)
                {
                    printf("Enter point x: ");
                    double x;

                    scanf("%lf", &x);
                    while(getchar() != '\n');

                    double result = p2->evaluate(x);
                    printf("In the polynomial %s the expression at the point x with the value ", p2->getName());
                    printf("%f equals: ", x);
                    printf("%f", result);
                    printf("\nPolynomial %s: ", p2->getName());
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
                printf("--DEBUGGING--\n");
                printf("**Demonstration of class work.**\n");
                DemoClassPolynoms();
                break;
            }
            default:
            {
                printf("Invalid menu number! Enter correct value!\n");
                waitForEnter();
                break;
            }
        }
    }
    while (ch != 6);
    return 0;
}
