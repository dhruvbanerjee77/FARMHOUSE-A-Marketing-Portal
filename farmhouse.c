#include<stdio.h>

struct basic_details
{
    char name[20];
    long int phno;
    char residence[20];
};

void temp();
void SignIn();
void SignUp();

//Main screen
int main()
{
    int selection=1;
    while(selection)
    {
        system("cls");
        printf("Enter option: \n");
        printf("0. Exit \n");
        printf("1. Sign In \n");
        printf("2. Sign Up \n");
        scanf("%d", &selection);
        switch(selection)
        {
            case 1: SignIn();
            break;

            case 2: SignUp();
            break;

            case 3: temp();
            break;

            case 0: break;

            default: printf("Enter valid input \n Press any key to continue...");
            getch();

        }
        getch();
    }
}

//Sign Up
void SignUp()
{
    FILE *fp;
    fp = fopen("acc.dat","ab");
    struct basic_details acc;
    printf("Enter Name: ");
    scanf("%s",acc.name);
    printf("Enter Phone number: ");
    scanf("%ld",&acc.phno);
    printf("Enter area of residence: ");
    scanf("%s", acc.residence);

    fwrite(&acc,sizeof(acc),1,fp);
    fclose(fp);
}

void SignIn()
{
    FILE *fp;
    fp = fopen("acc.dat","rb");
    struct basic_details acc;
    char check_name[20];
    scanf("%s",check_name);
    while(fread(&acc, sizeof(acc),1,fp)==1)
    {
        if(!strcmp(acc.name,check_name))
        {
            break;
        }
    }
    printf("Name: %s \n",acc.name);
    printf("Phone number: %ld \n",acc.phno);
    printf("Residence: %s \n", acc.residence);
}


void temp()
{
    FILE *fp;
    fp = fopen("acc.dat","rb");
    struct basic_details acc;
    while(fread(&acc, sizeof(acc),1,fp)==1)
    {

        printf("Name: %s \n",acc.name);
        printf("Phone number: %ld \n",acc.phno);
        printf("Residence: %s \n", acc.residence);
    }
    fclose(fp);
}
