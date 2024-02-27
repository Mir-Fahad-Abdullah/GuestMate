#include <stdio.h>
#include <conio.h>
#include <string.h>


typedef struct guest_info{

    char name[30];
    int room_no;
    int rd,rm,ry,cd,cm,cy;
    int total_members;
    char phone[15];

}info;


int password(char str[]);                       //security function=====> password: fahad67
void room_book(int m);                          //function to book a room.
void compare(int n1 , int n2);                  //function to compare two room properties.
void check_data();                              //function to check database.
int count_days(int rd, int rm , int ry , int cd , int cm , int cy);//function to determine the duration of a guest's stay.
float total_bill(int t_day , int choice);       //function to find the total bill for a guest.
void digital_slip(info g_info , float x);       //guest's prove for room reservation.
void Cancel_req();                              //function to Cancel reservation request.


int main(){

    int choice_1 , choice_2;
    char ch;
    int x,y;
    char str[10];


    printf("Enter the password to continue :\n");
    scanf("%[^\n]", str);

    if(password(str)==1){

    printf("\n...........Your password successfully matched.\n");

    printf("\n\n\t======================================================\n");
    printf("            ** WELCOME TO GUEST HOUSE MANAGEMENT SYSTEM **       \n");
    printf("\t======================================================\n\n\n");

    do{
        printf("\nManagement System :\n");
        printf("---------------------\n\n");
        printf("1. Room reservation System .\n");
        printf("2. Check Database .\n");
        printf("Enter Choice :");
        scanf("%d", & choice_1);
        fflush(stdin);

        if(choice_1==1){

            start:

            printf("\n\nAvailable Room Properties :\n");
            printf("-----------------------------\n\n");
            printf("1. Single bed - per night 2000 taka.\n");
            printf("2. Single bed - per night 3000 taka.\n");
            printf("3. Double bed - per night 3500 taka.\n");
            printf("4. Double bed - per night 4000 taka.\n");
            printf("5. Double bedroom (family pack) - per night 5000 taka.\n");
            printf("6. Compare rooms.\n");
            printf("7. Cancel reservation.\n\n");
            printf("Enter your choice: ");
            scanf("%d", & choice_2);
            fflush(stdin);

            switch(choice_2){

            case 1: case 2: case 3: case 4: case 5:{
                room_book(choice_2);
                break;
                }
            case 6:{
                printf("\nEnter two properties number to compare with:\n");
                printf("---------------------------------------------\n");
                printf("Enter first one:");
                scanf("%d", &x);
                printf("Enter second one:");
                scanf("%d", &y);

                compare(x,y);

                goto start;
                break;
                }
            case 7:{
                Cancel_req();
                break;
                }
            default:
                printf("\nWrong Input");
                break;
            }

        }

        else if(choice_1==2){
            check_data();
        }

        else{
            printf("Wrong Input\n");
        }

        printf("\n\nEnter Y or y to continue: ");
        scanf("%c", &ch);

    }while(ch=='Y' || ch=='y');
    }

    else{
        printf("\nInvalid password.......\n");
        return 0;
    }
}


int password(char str[]){

    char dest[10]="fahad67";
    int k;

    k=strcmp(dest , str);

    if(k==0){
        return 1;
    }
    else{
        return 0;
    }
}



void compare(int n1 , int n2){

    printf("\n\nYour compare result:\n");
    printf("--------------------");

    if(n1==1 && n2==2){
        printf("\nRooms for properties %d contains non AC single bed,without balcony and well furnished bathroom\n", n1);
        printf("Rooms for properties %d contains AC single bed,with balcony and well furnished bathroom\n", n2);
    }
    else if(n1==3 && n2==4){
        printf("\nRooms for properties %d contains non AC double bed,without balcony and well furnished bathroom\n", n1);
        printf("Rooms for properties %d contains AC double bed,with balcony and well furnished bathroom\n", n2);
    }
    else{
        printf("\nRooms for properties 5 contains AC two room double bed,with balcony and well furnished bathroom\n");
    }

    getch();

}



void room_book(int m){

    info guest;
    FILE *fp;
    int p;
    float q;

    printf("\nEnter guest information:\n");
    printf("-------------------------\n\n");
    printf("Enter guest name: \n");
    gets(guest.name);
    fflush(stdin);
    printf("Enter room number: \n");
    scanf("%d", & guest.room_no);
    printf("Enter check in date (day,month,year): \n");
    scanf("%d %d %d", &guest.rd, &guest.rm , &guest.ry);
    printf("Enter check out date (day,month,year): \n");
    scanf("%d %d %d", &guest.cd, &guest.cm , &guest.cy);
    printf("Enter total members: \n");
    scanf("%d", &guest.total_members);
    printf("Enter phone number: \n");
    scanf("%s", guest.phone);
    fflush(stdin);

    p=count_days(guest.rd , guest.rm , guest.ry , guest.cd, guest.cm , guest.cy);
    q=total_bill(p , m);

    getch();

    printf("\n\nRoom reservation for :\n");
    printf("------------------------\n\n");
    puts(guest.name);
    printf("Room No : %d\n" , guest.room_no);
    printf("Check IN Date : %d-%d-%d\n" , guest.rd , guest.rm , guest.ry);
    printf("Check Out Date : %d-%d-%d\n" , guest.rd , guest.rm , guest.ry);
    printf("Total Members : %d\n" , guest.total_members);

    printf("\n\t  Total bill ======>> %.2f\n", q);
    printf("----------------------------------------\n");
    printf("Guest must pay this money before check out date.\n\n");

    fp=fopen("database.txt" , "a");

    fprintf(fp , "%s\t" , guest.name);
    fprintf(fp , "%d\t" , guest.room_no);
    fprintf(fp , "%d-%d-%d\t" , guest.rd , guest.rm , guest.ry);
    fprintf(fp , "%d-%d-%d\t" , guest.rd , guest.rm , guest.ry);
    fprintf(fp , "%d\t" , guest.total_members);
    fprintf(fp , "%s\t" , guest.phone);
    fprintf(fp , "%.2f", q);
    fprintf(fp , "\n");

    fclose(fp);

    digital_slip(guest , q);

}



void digital_slip(info g_info , float x){

    FILE *fp;

    fp=fopen("Digital slip.txt","w");

    fprintf(fp , "\t\tFAHAD'S GUEST HOUSE\n");
    fprintf(fp , "\t=================================\n\n");
    fprintf(fp , "Name : %s\n" , g_info.name);
    fprintf(fp , "Room No : %d\n" , g_info.room_no);
    fprintf(fp , "Check In Date : %d-%d-%d\n" , g_info.rd , g_info.rm , g_info.ry);
    fprintf(fp , "Check Out Date : %d-%d-%d\n" , g_info.rd , g_info.rm , g_info.ry);
    fprintf(fp , "Total Members : %d\n" , g_info.total_members);
    fprintf(fp , "Phone Number : %s\n\n" , g_info.phone);
    fprintf(fp , "Total Bill : %.2f\n", x);
    fprintf(fp , "Guest must pay this money before check out date.\n\n");
    fprintf(fp , "===>>Your room reservation request has been successfully done<<===\n");
    fprintf(fp , "***Please print this document and bring it with you when you come to stay at the guest house.");

    fclose(fp);
}



void check_data(){

    FILE *fx;
    info num[100];
    int i,j;
    float bill[100];
    char str_1[100], str_2[100];

    fx=fopen("Database.txt" , "r");

    fgets(str_1 , 100 , fx);
    fgets(str_2 , 100 , fx);

    for(i=0 ; i<100 ; i++){

        fscanf(fx , "%[^\t]" , num[i].name);
        fscanf(fx , "%d" , &num[i].room_no);
        fscanf(fx , "%d %d %d" , &num[i].rd , &num[i].rm , &num[i].ry);
        fscanf(fx , "%d %d %d" , &num[i].rd , &num[i].rm , &num[i].ry);
        fscanf(fx , "%d" , &num[i].total_members);
        fscanf(fx , "%s" , num[i].phone);
        fscanf(fx , "%f", & bill[i]);

        if(feof(fx))
            break;
    }

    fclose(fx);

    printf("\n\n\n");
    puts(str_1);
    puts(str_2);
    for(j=0 ; j<i ; j++){
        printf("%s\t" , num[j].name);
        printf("%d\t" , num[j].room_no);
        printf("%d%d%d\t" , num[j].rd , num[j].rm , num[j].ry);
        printf("%d%d%d\t" , num[j].rd , num[j].rm , num[j].ry);
        printf("%d\t" , num[j].total_members);
        printf("%s\t" , num[j].phone);
        printf("%.2f taka", bill[j]);
    }

}



int count_days(int rd, int rm , int ry , int cd , int cm , int cy){

    if (rm==cm && ry==cy)
    {
        return cd-rd;
    }
    else if (rm!=cm || ry!=cy)
    {
        int day=0;
        while(rd!=cd || rm!=cm || ry!=cy)
        {
            if (rd==31 && (rm==1 || rm==3 || rm==5 || rm==7 || rm==8 || rm==10 ))
            {
                rm++;
                rd=1;
            }
            else if (rd==30 && (rm==4 || rm==6 || rm==9 || rm==11 ))
            {
                rm++;
                rd=1;
            }
            else if (rd==29 && rm==2 && ((ry%4==0 && ry%100!=0) || (ry%400==0)))    //if leap year.
            {
                rm++;
                rd=1;
            }
            else if (rd==28 && rm==2 && !((ry%4==0 && ry%100!=0) || (ry%400==0)))   //not leap year.
            {
                rd=1;
                rm=3;
            }
            else if (rd==31 && rm==12)
            {
                rd=1;
                rm=1;
                ry++;
            }
            else
            {
                rd++;
            }
            day++;
        }
        return day;
    }
}



float total_bill(int t_day , int choice){

    float temp, total;

    if(choice==1){
        temp=t_day*2000;
        total=(temp+((temp*15)/100)+((temp*20)/100));       //bill + vat(15%) + service charge(20%)
    }

    else if(choice==2){
        temp=t_day*3000;
        total=(temp+((temp*15)/100)+((temp*20)/100));
    }

    else if(choice==3){
        temp=t_day*3500;
        total=(temp+((temp*15)/100)+((temp*20)/100));
    }

    else if(choice==4){
        temp=t_day*4000;
        total=(temp+((temp*15)/100)+((temp*20)/100));
    }

    else if(choice==5){
        temp=t_day*5000;
        total=(temp+((temp*15)/100)+((temp*20)/100));
    }
    return total;
}



void Cancel_req(){

    printf("\n\nYour request for room reservation is canceling...........\n");
    printf("===>>Your request has been successfully canceled<<===\n");
    printf("\n********** Thanks for your precious time **********\n");
}
