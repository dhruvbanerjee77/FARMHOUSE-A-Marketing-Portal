#include<stdio.h>
#include <stdlib.h>

struct basic_details
{
    char userID[20];
    char password[20];
    char name[20];
    long int phno;
    char residence[20];
    int option; //0 for farmer, 1 for buyer
};

struct farmer_details
{
    char userID[20];
    char name[20];
    char crop[20];
    char residence[20];
};

struct buyer_details
{
    char userID[20];
    char name[20];
    char residence[20];
    int no_of_quotes;
};

struct buyer_quotes
{
    int valid;
    char userID[20];
    int quote_no;
    char crop[20];
    float price;
    char residence[20];
};

struct basic_details main_acc;
struct farmer_details main_farmer;
struct buyer_details main_buyer;
void create_farmer_details();
void create_buyer_details();
void display_current();
void farmer_portal();
void buyer_portal();
void add_quote();
void remove_quote();
void all_quotes();
int check_valid_userID(char check[20]);
void temp();
void SignIn();
void SignUp();

//Main screen
int main()
{
    int selection=1;
    main_acc.option = -1;
    while(selection)
    {
        if(main_acc.option==0)
        {
            farmer_portal();
        }
        if(main_acc.option==1)
        {
            buyer_portal();
        }
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

            case 4: display_current();
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

    while(1)
    {
        system("cls");
        printf("Enter USER-ID: ");
        char input[20];
        scanf("%s",input);
        if(check_valid_userID(input))
        {
           strcpy(acc.userID,input);
           char input2[20],ch;
           int i =0;
           printf("\n");
           printf("Enter Password: ");
           while(1)
           {
               ch = getch();
               if(ch == '\r')
               {
                   break;
               }
               else
               {
                   input2[i] = ch;
                   i++;
                   printf("*");
               }
           }
           input2[i] = '\0';
           strcpy(acc.password,input2);
           break;
        }
        else
        {
           printf("User ID already Exists. Try another ID. \nPress any key to continue...");
           getch();
        }
    }

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
    int tries = 1;
    while(tries!=3)
    {
        FILE *fp;
        fp = fopen("acc.dat","rb");
        struct basic_details acc;
        char input1[20];
        system("cls");
        printf("Enter USER ID: ");
        scanf("%s",input1);
        printf("Enter Password: ");
        char input2[20], ch;
        int i = 0;
        while(1)
        {
            ch = getch();
            if(ch == '\r')
            {
                input2[i] = '\0';
                break;
            }
            else
            {
                input2[i] = ch;
                i++;
                printf("*");
            }
        }
        int validated = 0;
        while(fread(&acc, sizeof(acc),1,fp)==1)
        {
            if(!strcmp(acc.userID,input1) && !strcmp(acc.password,input2))
            {
                validated = 1;
                break;
            }
        }
        fclose(fp);
        if(validated)
        {
            main_acc = acc;
            if(main_acc.option == 0)
            {
                fp = fopen("farmer_details.dat","rb");
                while(fread(&main_farmer, sizeof(main_farmer),1,fp)==1)
                    {
                        if(!strcmp(main_farmer.userID,input1))
                        {
                            break;
                        }
                    }
            }
            else
            {
                fp = fopen("buyer_details.dat","rb");
                while(fread(&main_buyer, sizeof(main_buyer),1,fp)==1)
                    {
                        if(!strcmp(main_buyer.userID,input1))
                        {
                            break;
                        }
                    }
            }
            break;
        }
        else
        {
            printf("INVALID ID or PASSWORD. Try Again. \nPress any key to continue...");
            getch();
            tries++;
        }
    }
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
    main_buyer.no_of_quotes=0;
    FILE *fp;
    fp = fopen("buyer_details.dat","ab");
    fwrite(&main_buyer,sizeof(main_buyer),1,fp);
    fclose(fp);
}

void display_current()
{
    printf("Name: %s \n",main_acc.name);
    printf("Phone number: %ld \n",main_acc.phno);
    printf("Residence: %s \n", main_acc.residence);
    printf("USER ID: %s \n",main_acc.userID);
    printf("Password: %s \n",main_acc.password);
    if(main_acc.option == 0)
    {
        printf("FARMER DETAILS \n");
        printf("Crop: %s \n", main_farmer.crop);
        printf("Residence: %s \n", main_farmer.residence);
    }
    if(main_acc.option==1)
    {
        printf("BUYER DETAILS \n");
        printf("Name: %s \n",main_buyer.name);
    }
}

int check_valid_userID(char check[20])
{
    struct basic_details acc;
    FILE *fp;
    fp = fopen("acc.dat","rb");
    int valid = 1;
    while(fread(&acc,sizeof(acc),1,fp))
    {
        if(!strcmp(check,acc.userID))
        {
            valid = 0;
            break;
        }
    }
    return valid;
}

void farmer_portal()
{
    int selection;
    while(selection!=7)
    {
        system("cls");
        printf("FARMER PORTAL \n");
        printf("Select Option: \n");
        printf("1. Find best buyer based on price \n");
        printf("2. Find nearest local buyer \n");
        printf("3. Search buyer by userID \n");
        printf("4. Show all buyers \n");
        printf("5. Statistics \n");
        printf("6. Change my details \n");
        printf("7. Back");
        scanf("%d", &selection);
        switch(selection)
        {
            default: printf("Enter Valid Option. \nPress any key to continue...");
            getch();
        }
    }
}

void buyer_portal()
{
    int selection;
    while(selection!=5)
    {
        system("cls");
        printf("BUYER PORTAL \n");
        printf("Select Option: \n");
        printf("1. Add quote \n");
        printf("2. Remove Quote \n");
        printf("3. Quote history \n");
        printf("4. Statistics \n");
        printf("5. Back");
        scanf("%d",&selection);
        switch(selection)
        {
            case 1: add_quote();
            break;

            case 2: remove_quote();
            break;

            case 3: all_quotes();
            break;

            default: printf("Enter Valid Option. \nPress any key to continue...");
            getch();
        }
    }

}

void add_quote()
{
    main_buyer.no_of_quotes++;
    struct buyer_quotes quote;
    quote.quote_no=main_buyer.no_of_quotes;
    system("cls");
    printf("Enter Crop: ");
    scanf("%s", quote.crop);
    printf("Quote: ");
    scanf("%f",&quote.price);
    quote.valid=1;
    strcpy(quote.userID,main_acc.userID);
    strcpy(quote.residence,main_acc.residence);
    FILE *fp;
    fp = fopen("quotes.dat","ab");
    fwrite(&quote,sizeof(quote),1,fp);
    fclose(fp);

    printf("Quote Added \nPress any key to continue...");

    struct buyer_details acc;
    fp = fopen("buyer_details.dat","rb");
    FILE *fp2;
    fp2 = fopen("temp.dat","wb");
    while(fread(&acc,sizeof(acc),1,fp))
    {
        if(!strcmp(acc.userID,main_buyer.userID))
        {
            fwrite(&main_buyer,sizeof(main_buyer),1,fp2);
        }
        else
        {
            fwrite(&acc,sizeof(acc),1,fp2);
        }
    }
    fclose(fp);
    fclose(fp2);

    remove("buyer_details.dat");
    rename("temp.dat","buyer_details.dat");
    getch();
}

void remove_quote()
{
    system("cls");
    printf("List of all quotes: \n");
    FILE *fp;
    fp = fopen("quotes.dat","rb");

    struct buyer_quotes quote;
    while(fread(&quote,sizeof(quote),1,fp))
    {
        printf("Quote number: %d \n",quote.quote_no);
        if(quote.valid)
        {
            printf("\t Crop: %s \n",quote.crop);
            printf("\t Quote: %f \n",quote.price);
            printf("\n");
        }
    }
    fclose(fp);
    printf("Enter Quote number of quote to be deleted: ");
    int input;
    scanf("%d",&input);
    FILE *fp2;
    fp2=fopen("temp.dat","wb");
    fp = fopen("quotes.dat","rb");
    while(fread(&quote,sizeof(quote),1,fp))
    {
        if(!strcmp(main_acc.userID,quote.userID) && quote.quote_no==input)
        {
            quote.valid = 0;
            fwrite(&quote,sizeof(quote),1,fp2);
        }
        else
        {
            fwrite(&quote,sizeof(quote),1,fp2);
        }

    }
    fclose(fp2);
    fclose(fp);


    remove("quotes.dat");
    rename("temp.dat","quotes.dat");
}

void all_quotes()
{
    system("cls");
    printf("ALL QUOTES: \n");
    FILE *fp;
    fp = fopen("quotes.dat","rb");
    struct buyer_quotes quote;
    while(fread(&quote,sizeof(quote),1,fp))
    {
        if(!strcmp(quote.userID, main_acc.userID))
        {
            printf("Quote ID: %d\n", quote.quote_no);
            printf("Crop: %s\n",quote.crop);
            printf("Quote: %f\n",quote.price);
            printf("Is valid: %d\n\n",quote.valid);
        }
    }
    getch();
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
        printf("USER ID: %s\n",acc1.userID);
        printf("Password: %s \n",acc1.password);
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
