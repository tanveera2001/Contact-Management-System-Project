#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Newcontact{
    char name[20];
    char number[20];
    char email[30];

}contact;

bool isRunning = true;
void welcomeMessage();
void headMessage(const char *message);
void printMessageCenter(const char* message);
void Menu();
void AddNewNumber();
void ShowAllContacts();
void SearchContact();
void EditContact();
void DeleteContact();
void DeleteAllContacts();
void ClearWindow();
void PrintLineWithSpace(char *Name[20],char ContactInfo);
void ShowPhoneWithSpace(char *Phone[20]);
void ShowEmailWithSpace(char *Email[30]);
void ErrorAndRestart(char *error[100]);
bool AlreadyExists(char *GivenLine[30],char ContactInfo);
void GoBackOrExit();
void UserGuideline();
void AboutUs();
void Exit();

int main()
{
    system("cls");

    welcomeMessage();

    while(isRunning == true)
    {
        Menu();
        char str[100];
        char option;
        scanf("%s", str);
        option = str[0];
        switch(option)
        {
            case '0':
                Exit();
                break;
            case '1':
                AddNewContact();
                break;
            case '2':
                ShowAllContacts();
                break;
            case '3':
                SearchContact();
                break;
            case '4':
                EditContact();
                break;
            case '5':
                DeleteContact();
                break;
            case '6':
                DeleteAllContacts();
                break;
            case '7':
                system("cls");
                break;
            case 'I':
            case 'i':
                UserGuideline();
                break;
            case 'A':
            case 'a':
                AboutUs();
                break;
            default:
                ErrorAndRestart("INVALID OPTION!");
                break;
        }
    }

    return 0;
}

void welcomeMessage()
{
    headMessage("Md. Tanveer Ahmed");
    printf("\n\n\n\n\n");
    printf("\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    printf("\n\n");
    printf("\t\t\t\t     =--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=");
    printf("\n");
    printf("\t\t\t\t     =--=              WELCOME                 =--=");
    printf("\n");
    printf("\t\t\t\t     =--=                TO                    =--=");
    printf("\n");
    printf("\t\t\t\t     =--=              CONTACT                 =--=");
    printf("\n");
    printf("\t\t\t\t     =--=            MANAGEMENT                =--=");
    printf("\n");
    printf("\t\t\t\t     =--=              SYSTEM                  =--=");
    printf("\n");
    printf("\t\t\t\t     =--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=");
    printf("\n\n");
    printf("\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    printf("\n\n\n\n");
    printf("\t\t       Enter any key to continue.....");
    getch();
}

void headMessage(const char *message)
{
    system("cls");
    printf("\t\t       ##########################################################################");
    printf("\n");
    printf("\t\t       ############                                                  ############");
    printf("\n");
    printf("\t\t       ############      Contact Management System Project in C      ############");
    printf("\n");
    printf("\t\t       ############                                                  ############");
    printf("\n");
    printf("\t\t       ##########################################################################");
    printf("\n\n");
    printf("\t\t       --------------------------------------------------------------------------");
    printf("\n");
    printMessageCenter(message);
    printf("\n");
    printf("\t\t       --------------------------------------------------------------------------");
}

void printMessageCenter(const char* message)
{
    int pos, len;

    len = (120 - strlen(message)) / 2;

    for(pos = 0; pos < len; pos++)
    {
        printf(" ");
    }

    printf("%s", message);
}

void Menu()
{
    system("cls");

    headMessage("MAIN MENU");

    printf("\n\n");
    printf("\t\t       [1] Add a new contact");
    printf("\n");
    printf("\t\t       [2] Show all contacts");
    printf("\n");
    printf("\t\t       [3] Search for contact");
    printf("\n");
    printf("\t\t       [4] Edit a contact");
    printf("\n");
    printf("\t\t       [5] Delete a contact");
    printf("\n");
    printf("\t\t       [6] Delete all contact");
    printf("\n");
    printf("\t\t       [7] Clear window");
    printf("\n");
    printf("\t\t       [i] User guideline");
    printf("\n");
    printf("\t\t       [a] About us");
    printf("\n");
    printf("\t\t       [0] Exit");
    printf("\n\n");
    printf("\t\t       Enter the choice: ");
}

void AddNewContact()
{
    system("cls");

    headMessage("ADD A NEW CONTACT");

    printf("\n\n");

    char NewContact[100];
    NewContact[0] = '\0';
    contact newContact;

    printf("\t\t       Name: ");
    scanf(" %[^\n]s", newContact.name);
    if(strlen(newContact.name) > 20)
    {
        ErrorAndRestart("Name Length Error!");
        return;
    }
    if(AlreadyExists(newContact.name, 'n') == 1)
    {
        ErrorAndRestart("Name Already Exists!");
        return;
    }

    printf("\t\t       Phone Number: ");
    scanf("%s", newContact.number);
    if(strlen(newContact.number) > 20)
    {
        ErrorAndRestart("Phone Length Error!");
        return;
    }
    if(AlreadyExists(newContact.number, 'p') == 1)
    {
        ErrorAndRestart("Phone Number Already Exists!");
        return;
    }

    printf("\t\t       Email: ");
    scanf("%s",newContact.email);
    if(strlen(newContact.email) > 30)
    {
        ErrorAndRestart("Email Length Error!");
        return;
    }
    if(AlreadyExists(newContact.email, 'e') == 1)
    {
        ErrorAndRestart("Email Already Exists!");
        return;
    }

    strcat(NewContact, newContact.name);
    strcat(NewContact, "\n");
    strcat(NewContact, newContact.number);
    strcat(NewContact, "\n");
    strcat(NewContact, newContact.email);
    strcat(NewContact, "\n");

    FILE *allContactTxtFile = fopen("All-Contact.txt", "a");

    fprintf(allContactTxtFile, NewContact);

    fclose(allContactTxtFile);

    printf("\n\n\n");
    printf("\t\t\t\t\t      Contact Added Successfully!");
    printf("\n\n\n\n");

    GoBackOrExit();
}
void ShowAllContacts()
{
    system("cls");

    headMessage("ALL CONTACTS");

    FILE *AllContactTextFile;

    int LineLength = 300;
    char Line[LineLength];

    printf("\n");
    printf("\t\t       *====================*====================*==============================*");
    printf("\n");
    printf("\t\t       |        Name        |    Phone Number    |            Email             |");
    printf("\n");
    printf("\t\t       *====================*====================*==============================*");
    printf("\n");

    AllContactTextFile = fopen("All-Contact.txt", "r");

    int TotalContact = 0;
    int LineCount = 0;
    while(fgets(Line, LineLength, AllContactTextFile))
    {
        LineCount++;
        if(LineCount == 1)
        {
            PrintLineWithSpace(Line, 'n');
        }
        else if(LineCount == 2)
        {
           PrintLineWithSpace(Line, 'p');
        }
        else if(LineCount == 3)
        {
            PrintLineWithSpace(Line, 'e');

            LineCount = 0;
            TotalContact++;
        }
    }

    printf("\n\n\n");
    printf("\t\t       You Have Total %d Contacts.", TotalContact);

    fclose(AllContactTextFile);

    printf("\n\n\n\n");

    GoBackOrExit();
}


void PrintLineWithSpace(char *Name[20],char ContactInfo)
{
    int i;
    char *FormatedName = NULL;
    FormatedName = strdup(Name);
    int FormatedNameLength = strlen(FormatedName);
    int TotalSpace = 0;

    if(ContactInfo == 'n')
    {
        TotalSpace = 20 - FormatedNameLength;
        printf("\t\t       |   ");
        for(i = 0; i < FormatedNameLength - 1; i++)
        {
            printf("%c", FormatedName[i]);
        }
        for(i = 0; i <= TotalSpace - 3; i++)
        {
            printf(" ");
        }
    }
    else if(ContactInfo == 'p')
    {
        TotalSpace = 20 - FormatedNameLength;
        printf("|    ");
        for(i = 0; i < FormatedNameLength - 1; i++)
        {
            printf("%c", FormatedName[i]);
        }
        for(i = 0; i <= TotalSpace - 4; i++)
        {
            printf(" ");
        }
    }
    else if(ContactInfo == 'e')
    {
        TotalSpace = 30 - FormatedNameLength;
        printf("|   ");
        for(i = 0; i < FormatedNameLength - 1; i++)
        {
            printf("%c", FormatedName[i]);
        }
        for(i = 0; i <= TotalSpace - 3; i++)
        {
            printf(" ");
        }
    }

    if(ContactInfo == 'e')
    {
        printf("|\n");
        printf("\t\t       *--------------------*--------------------*------------------------------*");
        printf("\n");
    }
}

void SearchContact()
{
    system("cls");

    headMessage("SEARCH CONTACT");

    int FoundContact = 0;
    char Name[100];

    printf("\n\n");

    printf("\t\t       Enter the name of the contact you're looking for: ");
    scanf(" %[^\n]s", Name);
    if(strlen(Name) > 20)
    {
        ErrorAndRestart("Name Length Error!");
        return;
    }
    strcat(Name, "\n");

    FILE* AllContactFile;

    int LineLength = 300;
    char Line[LineLength];

    AllContactFile = fopen("All-Contact.txt", "r");

    int LineCount = 0;
    int NeedToPrintLine = 0;
    while(fgets(Line, LineLength, AllContactFile))
    {
        LineCount++;

        if(LineCount == 1 && strcmp(Name, Line) == 0)
        {
            FoundContact = 1;
            NeedToPrintLine = 3;
        }
        if(NeedToPrintLine > 0)
        {
            if(LineCount == 1)
            {
                printf("\n\n");
                printf("\t\t\t\t\tContact Information of %s", Name);
                printf("\n\n");
                printf("\t\t       Name: %s", Line);
                NeedToPrintLine = 2;
            }
            else if(LineCount == 2)
            {
                printf("\t\t       Phone: %s", Line);
                NeedToPrintLine = 1;
            }
            else if(LineCount == 3)
            {
                printf("\t\t       Email: %s\n", Line);
                NeedToPrintLine = 0;
            }
        }
        if(LineCount == 3)
        {
            LineCount = 0;
        }
    }

    fclose(AllContactFile);

    if(FoundContact == 0)
    {
        printf("\n\n");
        printf("\t\t\t\t\tSorry no contact found for %s", Name);
    }

    printf("\n\n\n\n");

    GoBackOrExit();
}

void EditContact()
{
    system("cls");

    headMessage("EDIT CONTACT");

    int LineCount = 0;
    int FoundContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    char NewName[100];
    char NewPhone[20];
    char NewEmail[100];
    char NewFullContact[300];
    NewFullContact[0] = 0;

    printf("\n\n");

    printf("\t\t       Enter the name which one you want to edit: ");
    scanf(" %[^\n]s", GivenName);
    if(strlen(GivenName) > 20)
    {
        ErrorAndRestart("Name Length Error!");
        return;
    }
    strcat(GivenName, "\n");

    FILE *OurExistingFile;
    FILE *NewTempFile;
    int LineLength = 300;
    char Line[LineLength];

    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");

    while(fgets(Line, LineLength, OurExistingFile))
    {
        LineCount++;

        if(LineCount == 1 && strcmp(GivenName, Line) == 0)
        {
            FoundContact = 1;
            SkipLines = 3;
        }
        if(SkipLines > 0)
        {
            if(LineCount == 1)
            {
                printf("\n\n");
                printf("\t\t       Old Name: %s",Line);
                printf("\t\t       New Name (Press 0 for skip): ");
                scanf(" %[^\n]s", NewName);
                if(strcmp(NewName, "0") == 0)
                {
                    strcat(NewFullContact, Line);
                }
                else
                {
                    if(strlen(NewName) > 20)
                    {
                        ErrorAndRestart("Name Length Error!");
                        return;
                    }
                    if(AlreadyExists(NewName, 'n') == 1)
                    {
                        ErrorAndRestart("Name Already Exists!");
                        return;
                    }
                    strcat(NewFullContact, NewName);
                    strcat(NewFullContact, "\n");
                }
                SkipLines = 2;
            }
            else if(LineCount == 2)
            {
                printf("\n");
                printf("\t\t       Old Phone number: %s", Line);
                printf("\t\t       New Phone (Press 0 for skip): ");
                scanf("%s", NewPhone);
                if(strcmp(NewPhone, "0") == 0)
                {
                    strcat(NewFullContact, Line);
                }
                else
                {
                    if(strlen(NewPhone) > 20)
                    {
                        ErrorAndRestart("Phone Length Error!");
                        return;
                    }
                    if(AlreadyExists(NewPhone,'p') == 1)
                    {
                        ErrorAndRestart("Phone Already Exists!");
                        return;
                    }
                    strcat(NewFullContact, NewPhone);
                    strcat(NewFullContact, "\n");
                }
                SkipLines = 1;
            }
            else if(LineCount == 3)
            {
                printf("\n");
                printf("\t\t       Old Email: %s",Line);
                printf("\t\t       New Email (Press 0 for skip): ");
                scanf("%s", NewEmail);

                if(strcmp(NewEmail, "0") == 0)
                {
                    strcat(NewFullContact, Line);
                }
                else
                {
                    if(strlen(NewEmail) > 30)
                    {
                        ErrorAndRestart("Email Length Error!");
                        return;
                    }
                    if(AlreadyExists(NewEmail, 'e') == 1)
                    {
                        ErrorAndRestart("Email Already Exists!");
                        return;
                    }
                    strcat(NewFullContact, NewEmail);
                    strcat(NewFullContact, "\n");
                }
                SkipLines = 0;
                fprintf(NewTempFile, NewFullContact);
            }
        }
        else
        {
            fprintf(NewTempFile, Line);
        }

        if(LineCount == 3)
        {
            LineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundContact == 0)
    {
        printf("\n\n\n");
        printf("\t\t\t\t\t\t   Contact Not Found!\n");
        remove("temp-file.txt");
    }
    else
    {
        printf("\n\n\n");
        printf("\t\t\t\t\t     Contact Updated Successfully!");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }

    printf("\n\n\n\n");

    GoBackOrExit();
}

void DeleteContact()
{
    system("cls");

    headMessage("DELETE A CONTACT");

    printf("\n\n");

    int lineCount = 0;
    int FoundTheContact = 0;
    int SkipLines = 0;
    char GivenName[100];

    printf("\t\t       Enter the name which one you want to delete: ");
    scanf(" %[^\n]s", GivenName);
    if(strlen(GivenName) > 20)
    {
        ErrorAndRestart("Name Length Error!");
    }
    strcat(GivenName, "\n");

    FILE *OurExistingFile;
    FILE *NewTempFile;
    int LineLenght = 300;
    char line[LineLenght];

    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");

    while(fgets(line, LineLenght, OurExistingFile))
    {
        lineCount++;

        if(lineCount == 1 && strcmp(GivenName, line) == 0)
        {
            FoundTheContact = 1;
            SkipLines = 3;
        }
        if(SkipLines > 0)
        {
            SkipLines--;
        }
        else
        {
            fprintf(NewTempFile, line);
        }
        if(lineCount == 3)
        {
            lineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundTheContact == 0)
    {
        printf("\n\n\n");
        printf("\t\t\t\t\t\t   Contact Not Found!\n");
        remove("temp-file.txt");
    }
    else
    {
        printf("\n\n\n");
        printf("\t\t\t\t\t     Contact Deleted Successfully!");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");

    }

    printf("\n\n\n\n");

    GoBackOrExit();
}

void DeleteAllContacts()
{
    system("cls");

    headMessage("DELETE ALL THE CONTACTS");

    printf("\n\n");

    char Option;
    getchar();
    printf("\t\t       Are you sure want to delete all the contacts? (Press 'Y' or 'N'): ");
    scanf("%c", &Option);
    if(Option == 'Y' || Option == 'y')
    {
        int i;
        remove("All-Contact.txt");
        FILE *AllContactTxtFile = fopen("All-Contact.txt","a");
        fclose(AllContactTxtFile);

        printf("\n\n");
        printf("\t\t       ");

        char Deleting[100] = "Deleting....";
        for(i = 0; i < strlen(Deleting); i++)
        {
            printf("%c", Deleting[i]);
            Sleep(40);
        }
        printf("\n\n\n");
        printf("\t\t\t\t\t   Successfully Deleted All Contacts!");

    }

    printf("\n\n\n\n");

    GoBackOrExit();
}

bool AlreadyExists(char *GivenLine[30],char ContactInfo)
{
    char *ThisLine[35];
    ThisLine[0] = 0;
    strcat(ThisLine, GivenLine);
    strcat(ThisLine, "\n");
    int FileLineNumber = 0;
    if(ContactInfo == 'n')
    {
        FileLineNumber = 1;
    }
    else if(ContactInfo == 'p')
    {
        FileLineNumber = 2;
    }
    else if(ContactInfo == 'e')
    {
        FileLineNumber = 3;
    }

    FILE* AllContactFile;

    int LineLength = 300;
    char Line[LineLength];

    AllContactFile = fopen("All-Contact.txt", "r");
    int LineCount = 0;
    int TotalContact = 0;
    int Found = 0;

    while(fgets(Line, LineLength, AllContactFile))
    {
        LineCount++;
        if(LineCount == FileLineNumber && strcmp(ThisLine, Line) == 0)
        {
            Found = 1;
        }
        if(LineCount == 3)
        {
            LineCount = 0;
        }
    }
    fclose(AllContactFile);
    if(Found == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ErrorAndRestart(char *error[100])
{
    printf("\n\n\n");
    int pos, len;

    len = (120 - strlen(error)) / 2;

    for(pos = 0; pos < len; pos++)
    {
        printf(" ");
    }
    printf("%s", error);
    printf("\n\n\n");
    int i = 0;
    printf("\t\t       Restarting the program");
    for(i = 0; i < 10; i++)
    {
        printf(".");
        Sleep(80);
    }
    system("cls");

}

void GoBackOrExit()
{
    char option;
    getchar();
    printf("\t\t       Go Back? (Press 'b') or Exit? (Press '0')  ");
    scanf("%c", &option);
    if(option == '0')
    {
        Exit();
    }
    else
    {
        system("cls");
    }
}

void UserGuideline()
{
    system("cls");

    headMessage("USER GUIDELINE");

    printf("\n\n");

    printf("\t\t       [>] This Program is created using C Language.\n");
    printf("\t\t       [>] Contact information will store in a text file.\n");
    printf("\t\t       [>] You will found the text file in the same folder.\n");
    printf("\t\t       [>] Text file create automatically.\n");
    printf("\t\t       [>] Name, Phone and email should be unique.\n");
    printf("\t\t       [>] Maximum length of name is 20 characters.\n");
    printf("\t\t       [>] Maximum length of phone is 20 characters.\n");
    printf("\t\t       [>] Maximum length of email is 30 characters.\n");


    printf("\n\n\n\n");

    GoBackOrExit();
}

void AboutUs()
{
    system("cls");
    headMessage("ABOUT US");

    printf("\n\n");
    printf("\t\t       Member 1: ");
    printf("\n\n");
    printf("\t\t       Name:        Md. Tanveer Ahmed");
    printf("\n");
    printf("\t\t       Student ID:  2311582042");
    printf("\n");
    printf("\t\t       Department:  Electrical and Computer Engineering");
    printf("\n");
    printf("\t\t       University:  North South University");
    printf("\n\n\n");
    printf("\t\t       Member 2: ");
    printf("\n\n");
    printf("\t\t       Name:        Shidratul Muntaha");
    printf("\n");
    printf("\t\t       Student ID:  2312328042");
    printf("\n");
    printf("\t\t       Department:  Electrical and Computer Engineering");
    printf("\n");
    printf("\t\t       University:  North South University");
    printf("\n\n\n");
    printf("\t\t       Member 3: ");
    printf("\n\n");
    printf("\t\t       Name:        Md. Raheem Ul Islam");
    printf("\n");
    printf("\t\t       Student ID:  2311799642");
    printf("\n");
    printf("\t\t       Department:  Electrical and Computer Engineering");
    printf("\n");
    printf("\t\t       University:  North South University");

    printf("\n\n\n\n");

    GoBackOrExit();
}

void Exit()
{
    getchar();
    printf("\n\n");
    printf("\t\t       Are You Sure Want to Exit? (Press 'Y' or 'N'): ");
    char YesOrNO;
    scanf("%c",&YesOrNO);
    if(YesOrNO == 'Y' || YesOrNO == 'y')
    {
        system("cls");
        headMessage("GOODBYE MESSAGE");
        printf("\n\n\n");
        printf("\t\t\t\t\t\t       Thank You!");
        printf("\n");
        printf("\t\t\t\t\t\t      See You Soon!");
        printf("\n\n\n\n\n");
        isRunning =  false;
    }
}


