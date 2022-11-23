#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
# include <stdio.h>

void  sum_of_positive(int a){

    int s = 0;
    for(int i=1;i<=a;i++){
        s=s+i;
    }
    printf("Sum of positive numbers is %d",s);
    printf("\n Identifier ID is [%d] \n ",getpid()); 
}

void sum_of_factorial(int a){
    int s1 = 1;
    for(int i=1;i<=a;i++){
        s1=s1*i;
    }
    printf("Sum of factorial is %d",s1);
    printf("\n Identifier ID is [%d] \n ",getpid()); 
}

int main(){
    int n, ret,ret1;
    printf("%s","Enter The Number: ");
    scanf("%d",&n);
    ret = fork();
    if(ret ==0){
        ret1 = fork();
        if(ret1 == 0){
            sum_of_factorial(n);
        }
        else{
            sum_of_positive(n);
        }
    }
    
    else{
    wait(NULL);
    printf("\n DONE \n");
    printf("\n Identifier ID is [%d] \n ",getpid());
    
    }

}