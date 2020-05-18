#include<stdio.h>

struct basic_details
{
    char name[20];
    long int phno;
    char residence[20];
    int option; //0 for farmer, 1 for buyer
};

struct farmer_details
{
    char name[20];
    char crop[20];
    char residence[20];
};

struct buyer_details
{
    char name[20];
    char residence[20];
};

struct basic_details main_acc;
struct farmer_details main_farmer;
struct buyer_details main_buyer;
void create_farmer_details();
void create_buyer_details();
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
    int option =3;
    while(option)
    {
    system("cls");
    printf("Select an Option: \n");
    printf("0. Farmer \n");
    printf("1. Buyer \n");
        scanf("%d",&option);
        switch(option)
        {
            case 0: acc.option=0;
            break;
            case 1: acc.option=1;
            option = 0;
            break;
            default: printf("Please enter valid option to continue...");
            getch();
        }
    }

    printf("Enter Name: ");
    scanf("%s",acc.name);
    printf("Enter Phone number: ");
    scanf("%ld",&acc.phno);
    printf("Enter area of residence: ");
    scanf("%s", acc.residence);

    fwrite(&acc,sizeof(acc),1,fp);
    fclose(fp);

    main_acc = acc;

    if(acc.option == 0)
    {
        create_farmer_details();
    }
    else
    {
        create_buyer_details();
    }
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

void create_farmer_details()
{
    system("cls");
    printf("Enter farmer details: \n");
    printf("Crop grown: ");
    strcpy(main_farmer.name,main_acc.name);
    strcpy(main_farmer.residence,main_acc.residence);
    scanf("%s", main_farmer.crop);
    FILE *fp;
    fp = fopen("farmer_details.dat","ab");
    fwrite(&main_farmer,sizeof(main_farmer),1,fp);
    fclose(fp);
}

void create_buyer_details()
{
    strcpy(main_buyer.name, main_acc.name);
    strcpy(main_buyer.residence,main_acc.residence);
    FILE *fp;
    fp = fopen("buyer_details.dat","ab");
    fwrite(&main_buyer,sizeof(main_buyer),1,fp);
    fclose(fp);
}

void temp()
{
    system("cls");
    FILE *fp;
    fp = fopen("acc.dat","rb");
    struct basic_details acc1;

    printf("ALL DETAILS.... \n");
    while(fread(&acc1, sizeof(acc1),1,fp)==1)
    {

        printf("Name: %s \n",acc1.name);
        printf("Phone number: %ld \n",acc1.phno);
        printf("Residence: %s \n", acc1.residence);
        if(acc1.option == 0)
        {
            printf("Type: Farmer \n");
        }
        else
        {
            printf("Type: Buyer \n");
        }
    }

    printf("\nFARMER DETAILS.... \n");
    fp = fopen("farmer_details.dat","rb");
    struct farmer_details fam;
    while(fread(&fam, sizeof(fam),1,fp)==1)
    {
        printf("Name: %s \n",fam.name);
        printf("Crop: %s \n", fam.crop);
        printf("Residence: %s \n",fam.residence);
    }
    fclose(fp);

    printf("BUYER DETAILS.... \n");
    fp = fopen("buyer_details.dat","rb");

    struct buyer_details buyer;
    while(fread(&buyer, sizeof(buyer),1,fp)==1)
    {
        printf("Name: %s \n", buyer.name);
        printf("Residence: %s \n", buyer.residence);
    }

}
