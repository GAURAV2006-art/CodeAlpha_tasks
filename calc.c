// c program to perform basic arithmetic operations
#include<stdio.h>
int main(){
    int choice;
    float num1, num2, result;
    printf("enter two no.s:-\n");
    scanf("%f %f",&num1,&num2);
    printf("select operation to perform:\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            result = num1 + num2;
            printf("Addition: %.2f\n", result);
            break;
        case 2:
            result = num1 - num2;
            printf("Subtraction: %.2f\n", result);
            break;
        case 3:
            result = num1 * num2;
            printf("Multiplication: %.2f\n", result);
            break;
        case 4:
            if(num2 != 0){
                result = num1 / num2;
                printf("Division: %.2f\n", result);
            } else {
                printf("Error: Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Invalid choice!\n");
    }
    return 0;  
}

