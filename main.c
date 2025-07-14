#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN() system("clear")

typedef struct{
    int id;
    char * name;
    char * surname;
    char * address;
    char * email;
    char * phone_number;
}PERSON;

typedef struct Node{
    PERSON * person;
    struct Node * next;
}Node;

typedef struct{
    char * directory_name;
    int current_person;
    Node * first;
}DIRECTORY;
DIRECTORY * directory;

void get_list();
void print_functions();
void search_person();
int get_last_id();
int directory_delete_person();
int directory_update_person();
int directory_add_person(PERSON * _person);
int check_other_numbers(char * _phone_number);
DIRECTORY * create_directory();
PERSON * create_person();

int main(int argc, char const *argv[])
{
    directory = create_directory();
    int choose = 0;
    while (choose != -1)
    {
        print_functions();
        printf("[-] Please Enter Key! -> ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            CLEAR_SCREEN();
            printf("\n------- [CREATE PERSON] -------\n");
            PERSON * new_person = create_person();
            if (directory_add_person(new_person))
            {
                printf("\n[INFO] - Directory Added Person!\n\tPerson ID : %d\n", new_person->id);
            }
            else{
                printf("[INFO] - Directory Not Added Person!\n");
            }
            break;
        case 2:
            CLEAR_SCREEN();
            printf("\n------- [DELETE PERSON] -------\n");
            if (directory_delete_person())
            {
                printf("[INFO] - Person Is Deleted!\n");
            }
            else{
                printf("[INFO] - Person Is Not Deleted!\n");
            }
            break;
        case 3:
            CLEAR_SCREEN();
            printf("\n------- [UPDATE PERSON] -------\n");
            directory_update_person();
            break;
        case 4:
            CLEAR_SCREEN();
            printf("\n------- [LIST PERSONS] -------\n");
            get_list();
            break;
        case 5:
            CLEAR_SCREEN();
            printf("\n------- [SEARCH PERSON] -------\n");
            search_person();
            break;
        default:
            printf("\n[INFO] - Please Press Any Key!\n");
            break;
        }
    }
    return 0;
}

int get_last_id(){

    if (directory->first == NULL)
    {
        return 0;
    }
    else{
        Node * temp_node = directory->first;
        while (temp_node->next != NULL)
        {
            temp_node = temp_node->next;
        }
        return temp_node->person->id;
    }
}

void print_functions(){
    printf("\n\n---------- [Functions] ----------\n");
    printf("|\t[1] - Create Person\t|\n|\t[2] - Delete Person\t|\n|\t[3] - Update Person\t|\n|\t[4] - List Persons\t|\n|\t[5] - Search Person\t|\n|\t[-1] - Quit!\t\t|\n---------------------------------\n\n");
}

PERSON * create_person(){
    PERSON * new_person = (PERSON *)malloc(sizeof(PERSON) * 1);
    if (new_person == NULL)
    {
        printf("---------- [WARNING] ----------\n");
        printf("Person Not Created!\nMemory Allocation Error!");
        printf("-------------------------------\n");
        return NULL;
    }
    else{
        new_person->address = (char *)malloc(sizeof(char) * 50);
        new_person->email = (char *)malloc(sizeof(char) * 50);
        new_person->name = (char *)malloc(sizeof(char) * 15);
        new_person->phone_number = (char *)malloc(sizeof(char) * 11);
        new_person->surname = (char *)malloc(sizeof(char) * 15);

        if (new_person->address == NULL || 
            new_person->email == NULL || 
            new_person->name == NULL || 
            new_person->phone_number == NULL || 
            new_person->surname == NULL)
        {
            printf("---------- [WARNING] ----------\n");
            printf("Person Not Created!\nMemory Allocation Error!");
            printf("-------------------------------\n");
            return NULL;
        }
        else{
            printf("[-] Person Name (Max 15 Char):");
            scanf("%s", new_person->name);
            printf("[-] Person Surname (Max 15 Char):");
            scanf("%s", new_person->surname);
            printf("[-] Person Address (Max 50 Char):");
            scanf("%s", new_person->address);
            printf("[-] Person E-mail (Max 50 Char):");
            scanf("%s", new_person->email);
            printf("[-] Person Phone Number (Max 11 Char):");
            scanf("%s", new_person->phone_number);
            int result = check_other_numbers(new_person->phone_number);
            if (result != 0)
            {
                printf("\n\n-------- [ERROR] --------\n");
                printf("[-] This Number Already Have Used!\n\tPerson ID : %d\n", result);
                free(new_person);
                return NULL;
            }
            new_person->id = get_last_id() + 1;
            return new_person;
        }
    }
    return NULL;
}

int directory_add_person(PERSON * _person){
    if (_person == NULL)
    {
        return 0;
    }
    else{
        Node * new_node = (Node *)malloc(sizeof(Node) * 1);
        if (new_node == NULL)
        {
            printf("---------- [WARNING] ----------\n");
            printf("Node Not Created!\nMemory Allocation Error!");
            printf("-------------------------------\n");
        }
        else{
            new_node->next = NULL;
            new_node->person = _person;
        }
        if (directory->first == NULL)
        {
            directory->first = new_node;
            return 1;
        }
        else{
            Node * temp_node = directory->first;
            while (temp_node->next != NULL)
            {
                temp_node = temp_node->next;
            }
            temp_node->next = new_node;
            directory->current_person++;
            return 1;
        }
    }
}

int directory_delete_person(){
    if (directory->first == NULL)
    {
        printf("[INFO] - Directory Is NULL!\n\tAdd Some Persons And Try Again!\n");
        return 0;
    }
    
    int _id;
    printf("[-] Enter Deleting Person ID : ");
    scanf("%d", &_id);

    Node * temp_node = directory->first;
    Node * temp_node_two = NULL;
    if (directory->first->person->id == _id)
    {
        directory->first = temp_node->next;
        free(temp_node);
        directory->current_person--;
        return 1;
    }
    while (temp_node != NULL)
    {
        if (temp_node->person->id == _id){
            temp_node_two->next = temp_node->next;
            free(temp_node);
            directory->current_person--;
            return 1;
        }
        temp_node_two = temp_node;
        temp_node = temp_node->next;
    }
    return 0;
}

int directory_update_person(){
    int _id;
    printf("[-] Updating Person ID :");
    scanf("%d", &_id);

    Node * temp_node = directory->first;
    while (temp_node != NULL)
    {
        if (temp_node->person->id == _id)
        {
            int choose;
            while (choose != -1)
            {
                CLEAR_SCREEN();
                printf("[1] - Name : %s\n[2] - Surname : %s\n[3] - Email : %s\n[4] - Address : %s\n[5] - Phone Number : %s\n[-1] Quit\n",
                temp_node->person->name,
                temp_node->person->surname, 
                temp_node->person->email,
                temp_node->person->address,
                temp_node->person->phone_number);
                printf("[-] Choose Feature : ");
                scanf("%d", &choose);
                switch (choose)
                {
                    case 1:
                        printf("[-] Enter New Name : ");
                        scanf("%s", temp_node->person->name);
                        break;
                    case 2:
                        printf("[-] Enter New Surname : ");
                        scanf("%s", temp_node->person->surname);
                        break;
                    case 3:
                        printf("[-] Enter New Email : ");
                        scanf("%s", temp_node->person->email);
                        break;
                    case 4:
                        printf("[-] Enter New Address : ");
                        scanf("%s", temp_node->person->address);
                        break;
                    case 5:
                        printf("[-] Enter New Phone Number : ");
                        scanf("%s", temp_node->person->phone_number);
                        break;
                }   
            }
            return 1;
        }
        temp_node = temp_node->next;
    }
    printf("[INFO] - No Have ID = %d Person\n", _id);
    return 0;
}

DIRECTORY * create_directory(){
    DIRECTORY * new_directory = (DIRECTORY *)malloc(sizeof(DIRECTORY) * 1);
        if (new_directory == NULL)
        {
            printf("---------- [WARNING] ----------\n");
            printf("Directory Not Created!\nMemory Allocation Error!");
            printf("-------------------------------\n");
            return NULL;
        }
        else{
            new_directory->first = NULL;
            new_directory->current_person = 0;
            new_directory->directory_name = (char *)malloc(sizeof(char) * 15);
            printf("[INFO] - Write Directory Name (Max 15 char): ");
            scanf("%s", new_directory->directory_name);
            printf("- > Directory Name : %s\n", new_directory->directory_name);
            return new_directory;
        }
        
    return NULL;
}

void get_list(){
    if (directory->first == NULL)
    {
        printf("[INFO] - Directory Is Empty!\n");
        return;
    }
    else{
        Node * temp_node = directory->first;
        while (temp_node != NULL)
        {
            printf("\n---------- [ID -> %d] ----------\n|\t[] - Name : %s\n|\t[] - Surname : %s\n|\t[] - Address : %s\n|\t[] - E-mail : %s\n|\t[] - Phone Number : %s\n-------------------------------\n", 
                temp_node->person->id,
                temp_node->person->name, 
                temp_node->person->surname, 
                temp_node->person->address, 
                temp_node->person->email, 
                temp_node->person->phone_number);
            temp_node = temp_node->next;
        }
        return;
    }
}

void search_person(){
    int choose;
    Node * temp_node = directory->first;
    char * word = (char *)malloc(sizeof(char) * 50);
    printf("[1] - Name\n[2] - Surname\n[3] - Email\n[4] - Address\n[5] - Phone Number\n[-1] - Quit\n");
    printf("[-] Choose Search Feature : ");
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        printf("[-] Enter Searching Name : ");
        scanf("%s", word);

        while (temp_node != NULL)
        {  
            if (!strcmp(temp_node->person->name, word))
            {
                printf("\n----------[ID -> %d]----------\n[1] - Name : %s\n[2] - Surname : %s\n[3] - Email : %s\n[4] - Address : %s\n[5] - Phone Number : %s\n[-1] Quit\n",
                temp_node->person->id,
                temp_node->person->name,
                temp_node->person->surname, 
                temp_node->person->email,
                temp_node->person->address,
                temp_node->person->phone_number);
            }
            temp_node = temp_node->next;
        }
        
        break;
    case 2:
        printf("[-] Enter Searching Name : ");
        scanf("%s", word);

        while (temp_node != NULL)
        {  
            if (!strcmp(temp_node->person->surname, word))
            {
                printf("\n----------[ID -> %d]----------\n[1] - Name : %s\n[2] - Surname : %s\n[3] - Email : %s\n[4] - Address : %s\n[5] - Phone Number : %s\n[-1] Quit\n",
                temp_node->person->id,
                temp_node->person->name,
                temp_node->person->surname, 
                temp_node->person->email,
                temp_node->person->address,
                temp_node->person->phone_number);
            }
            temp_node = temp_node->next;
        }
        break;
    case 3:
        printf("[-] Enter Searching Name : ");
        scanf("%s", word);

        while (temp_node != NULL)
        {  
            if (!strcmp(temp_node->person->email, word))
            {
                printf("\n----------[ID -> %d]----------\n[1] - Name : %s\n[2] - Surname : %s\n[3] - Email : %s\n[4] - Address : %s\n[5] - Phone Number : %s\n[-1] Quit\n",
                temp_node->person->id,
                temp_node->person->name,
                temp_node->person->surname, 
                temp_node->person->email,
                temp_node->person->address,
                temp_node->person->phone_number);
            }
            temp_node = temp_node->next;
        }
        break;
    case 4:
        printf("[-] Enter Searching Name : ");
        scanf("%s", word);

        while (temp_node != NULL)
        {  
            if (!strcmp(temp_node->person->address, word))
            {
                printf("\n----------[ID -> %d]----------\n[1] - Name : %s\n[2] - Surname : %s\n[3] - Email : %s\n[4] - Address : %s\n[5] - Phone Number : %s\n[-1] Quit\n",
                temp_node->person->id,
                temp_node->person->name,
                temp_node->person->surname, 
                temp_node->person->email,
                temp_node->person->address,
                temp_node->person->phone_number);
            }
            temp_node = temp_node->next;
        }
        break;
    case 5:
        printf("[-] Enter Searching Name : ");
        scanf("%s", word);

        while (temp_node != NULL)
        {  
            if (!strcmp(temp_node->person->phone_number, word))
            {
                printf("\n----------[ID -> %d]----------\n[1] - Name : %s\n[2] - Surname : %s\n[3] - Email : %s\n[4] - Address : %s\n[5] - Phone Number : %s\n[-1] Quit\n",
                temp_node->person->id,
                temp_node->person->name,
                temp_node->person->surname, 
                temp_node->person->email,
                temp_node->person->address,
                temp_node->person->phone_number);
            }
            temp_node = temp_node->next;
        }
        break;
    default:
        break;
    }
}

int check_other_numbers(char * _phone_number){
    Node * temp_node = directory->first;
    if (temp_node == NULL)
    {
        return 0;
    }
    else{
        while (temp_node != NULL)
        {
            if (!strcmp(temp_node->person->phone_number, _phone_number))
            {
                return temp_node->person->id;
            }
            temp_node = temp_node->next;   
        }
    }
    return 0;
}