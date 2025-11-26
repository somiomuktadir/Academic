/**
 * @file complex_calculator.c
 * @brief Performs arithmetic operations on complex numbers using structs.
 *
 * This program demonstrates:
 * 1. Structure definition and usage
 * 2. Passing structs to functions
 * 3. Returning structs from functions
 * 4. Complex number arithmetic logic
 */

#include <stdio.h>

// Definition of a complex number
typedef struct {
    double real;
    double imag;
} Complex;

/**
 * @brief Adds two complex numbers.
 *
 * (a + bi) + (c + di) = (a+c) + (b+d)i
 */
Complex add(Complex n1, Complex n2) {
    Complex temp;
    temp.real = n1.real + n2.real;
    temp.imag = n1.imag + n2.imag;
    return temp;
}

/**
 * @brief Subtracts two complex numbers.
 *
 * (a + bi) - (c + di) = (a-c) + (b-d)i
 */
Complex subtract(Complex n1, Complex n2) {
    Complex temp;
    temp.real = n1.real - n2.real;
    temp.imag = n1.imag - n2.imag;
    return temp;
}

/**
 * @brief Multiplies two complex numbers.
 *
 * (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
 */
Complex multiply(Complex n1, Complex n2) {
    Complex temp;
    temp.real = (n1.real * n2.real) - (n1.imag * n2.imag);
    temp.imag = (n1.real * n2.imag) + (n1.imag * n2.real);
    return temp;
}

/**
 * @brief Helper function to print a complex number.
 */
void print_complex(const char *label, Complex n) {
    printf("%s: %.2f + %.2fi\n", label, n.real, n.imag);
}

int main() {
    Complex n1, n2, result;

    printf("For 1st complex number \n");
    printf("Enter real and imaginary parts: ");
    scanf("%lf %lf", &n1.real, &n1.imag);

    printf("\nFor 2nd complex number \n");
    printf("Enter real and imaginary parts: ");
    scanf("%lf %lf", &n2.real, &n2.imag);

    printf("\n----------------------------\n");
    
    result = add(n1, n2);
    print_complex("Sum", result);

    result = subtract(n1, n2);
    print_complex("Difference", result);

    result = multiply(n1, n2);
    print_complex("Product", result);

    return 0;
}
