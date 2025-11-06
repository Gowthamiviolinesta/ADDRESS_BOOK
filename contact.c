#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>
//Validate name: only letters and spaces allowed
int name_validation(char* name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')//isalpha->lowercase,uppercase
            return 0; 
    }
    return 1; 
}
//Validate phone: exactly 10 digits required
int phone_validation(char* phone)
{
    //if phone no is 10 digit and all are digits only return 1
    if(strlen(phone)!=10)
    return 0;
    for(int i = 0 ; i<10 ;i++)
    {
        if (!isdigit(phone[i]))//isdigit->0-9
        return 0;//all are not digits
    }
    return 1;//all are digits
}
//Validate email: lowercase, digit before '@', ends with '.com'
int email_validation(char* gmail)
{
    int len = strlen(gmail);

    //g1@g.com is 8 charecters so minimum it should be 8 charecters 
    if (len < 8)
    return 0;

    //check 1st charecter is low case
    if(!(gmail[0]>='a' && gmail[0]<='z'))
    return 0;

    //get the @ position
    char* at_pos=strchr(gmail, '@');//if strchr is true it will return @ address else it return NULL
    if(at_pos==NULL)
    return 0;

    //find the len from index 0 to @ position
    int before_at_len = at_pos - gmail; //before_at_len is finding the len from base address to @ pos
    if (before_at_len == 0)
    return 0;

    //check all charecters before @ 
    int has_digit=0;
    for (int i = 1; i < before_at_len; i++) 
    {
        if (isupper(gmail[i]) || (!islower(gmail[i]) && !isdigit(gmail[i])))
            return 0;
        if (isdigit(gmail[i]))
            has_digit = 1;
    }
    if (!has_digit)
        return 0;

    //checking the length from @ to .
    int at_to_dot_len = strlen(at_pos) - 4 - 1; // -4 for ".com", -1 for '@'
    if (at_to_dot_len <= 0)
    return 0;

    //checking from last its .com or not
    if (strcmp(gmail+len - 4, ".com") != 0)//checking whether last 4 charecters are .com or not
    return 0;
return 1;    
}
/*int unique_element_phone(struct AddressBook *addressBook,char* str)
{
    int j=addressBook->contactCount;
    for(int i=0;i<j;i++)
    {
        if(strcmp(str,addressBook->contacts[i].phone)==0)
        {
            return -1;
        }
        return 0;
    }
}*/

// Search contact by name and return index if found
int searchconctact_name(struct AddressBook *addressBook)
{
    int j=addressBook->contactCount;
    char str[100];
            printf("enter the name:");
            scanf(" %[^\n]",str);
            while(!name_validation(str))
            {
                printf("Invalid name,name should contain only uppercase,lowercase,if needed space,please try again\n");
                printf("Re-enter the name:");
                scanf(" %[^\n]",str);
            }
            for(int i=0;i<j;i++)
            {
                if(strcmp(str,addressBook->contacts[i].name)==0)
                    return i;
            }
            return -1;
}
//Search contact by phone number and return index if found
int searchconctact_phone(struct AddressBook *addressBook)
{
    int j=addressBook->contactCount;
    char str[100];
            printf("enter the phone:");
            scanf(" %[^\n]",str);
            while (!phone_validation(str))
            {
                printf("Invalid phone number! Enter exactly 10 digits:\n");
                printf("please re-enter the phone number:");
                scanf("%s", str);
            }
            for(int i=0;i<j;i++)
            {
                if(strcmp(str,addressBook->contacts[i].phone)==0)
                    return i;
            }
            return -1;
}
// Search contact by email and return index if found
int searchconctact_email(struct AddressBook *addressBook)
{
    int j=addressBook->contactCount;
    char str[100];
            printf("enter the email:");
            scanf(" %[^\n]",str);
            while(!email_validation(str))
            {
                printf("Invalid email: use lowercase, include a digit, and a valid domain before .com\n");
                printf("please re-enter the email:");
                scanf("%s",str);
            }
            for(int i=0;i<j;i++)
            {
                if(strcmp(str,addressBook->contacts[i].email)==0)
                    return i;
            }
            return -1;
}
// Display all contacts if available
void listContacts(struct AddressBook *addressBook)
{
    int i=addressBook->contactCount;
    if(i==0)
    {
        printf("No contacts to dispaly\n");
        return ;
    }

    printf("-------Contact List-------\n");

    for(int j=0;j<i;j++)
    {
        printf("contact %d:\n",j+1);
        printf(" Name:-%s \n Phone no:-%s \n email:-%s\n",addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
    }
    /* Define the logic for print the contacts */
    // printf("%s\n", addressBook->contacts[addressBook->contactCount].name);
}

//initializes addressbook and load dummy contact
//Initialize contact list and load data from file
void initialize(struct AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// Save all contacts to file and exit the program
void saveAndExit(struct AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

// Collect contact info from user with validations
// Check for duplicate phone and email
void createContact(struct AddressBook *addressBook)
{
    int i=addressBook->contactCount;
    while(1)
    {
        printf("Enter the name:");
        scanf(" %[^\n]",addressBook->contacts[i].name);//(*addressBook).contacts[i].name
        while(!name_validation(addressBook->contacts[i].name))
        {
            printf("Invalid name,name should contain only uppercase,lowercase,if needed space,please try again\n");
            printf("Re-enter the name:");
            scanf(" %[^\n]",addressBook->contacts[i].name);
        }
        printf("Enter the phone number:");
        scanf("%s",addressBook->contacts[i].phone);
        while (!phone_validation(addressBook->contacts[i].phone))
        {
            printf("Invalid phone number! Enter exactly 10 digits:\n");
            printf("please re-enter the phone number:");
            scanf("%s",addressBook->contacts[i].phone);
        }
        //unique phone number
        for(int j=0;j<i;j++)
        {
            while(strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone)==0)
            {
                printf("Phone number already exist:\n");
                printf("please re-enter phone number:");
                scanf(" %[^\n]",addressBook->contacts[i].phone);
                j = 0;  // Restart checking from beginning after re-entry
            }
        }
        //it was checking only for one iteration
        /*while(1)
        {
            for(int j=0;j<i;j++)
            {
                if(strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].email)==0)
                {
                    printf("Phone number already exist:\n");
                    printf("please re-enter phone number:");
                    scanf(" %[^\n]",addressBook->contacts[j].phone);
                }
            }
            break;
        }*/
        /*int res;
        while(res=unique_element_name(addressBook,addressBook->contacts[i].phone))
        {
            if(res==-1)
            {
                printf("Phone number already exist:\n");
                printf("please re-enter phone number:")
                scanf(" %[^\n]",addressBook->contacts[i].phone);
            }
        }*/
        printf("enter the email:");
        scanf("%s",addressBook->contacts[i].email);
        while(!email_validation(addressBook->contacts[i].email))
        {
            printf("Invalid email: use lowercase, include a digit, and a valid domain before .com\n");
            printf("please re-enter the email:");
            scanf("%s",addressBook->contacts[i].email);
        }
        //unique emailid
        for(int j=0;j<i;j++)
        {
            while(strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email)==0)
            {
                printf("email already exist:\n");
                printf("please re-enter email:");
                scanf(" %[^\n]",addressBook->contacts[i].email);
                j=0;//restart
            }
        }
        //addressBook->contactCount++;
        i++;
        int opt;
        printf("enter 0 to exit and 1 to create contact\n");
        scanf("%d",&opt);
        if(opt == 0)
        break;
    }
    addressBook->contactCount=i;
    /* Define the logic to create a Contacts */

    // Read the name from the user

    // Increment the contact count.
}

// Menu-driven contact search using name, phone, or email
void searchContact(struct AddressBook *addressBook)
{
    int j=addressBook->contactCount;
    char str[100];
    while(1)
    {
        printf("\t:::Search Contact Menu:::\n");
        printf("1.Search by Name\n2.Search by phone no\n3.Search by email\n4.Exit\n");
        int opt;
        printf("please enter the contact option\n");
        scanf("%d",&opt);
        switch(opt)
        {
            // Case 1: Search by name
            // Case 2: Search by phone
            // Case 3: Search by email
            // Case 4: Exit search
            case 1:
            printf("enter the name:");
            scanf(" %[^\n]",str);
            while(!name_validation(str))
            {
                printf("Invalid name,name should contain only uppercase,lowercase,if needed space,please try again\n");
                printf("Re-enter the name:");
                scanf(" %[^\n]",str);
            }
            int name_flag=0,name_k=0;
            for(int i=0;i<j;i++)
            {
                if(strcmp(str,addressBook->contacts[i].name)==0)
                {
                    name_k=i;
                    name_flag=1;
                    break;
                }
            }
            if(name_flag==1)
            {
                printf("Name:-%s \nPhone no:-%s \nemail:-%s\n",addressBook->contacts[name_k].name,addressBook->contacts[name_k].phone,addressBook->contacts[name_k].email);
                break;
            }
            else
            {
                printf("contact not found\n");
                break;
            }
            case 2:
            printf("enter the phone:");
            scanf("%s",str);
            while (!phone_validation(str))
            {
                printf("Invalid phone number! Enter exactly 10 digits:\n");
                printf("please re-enter the phone number:");
                scanf("%s", str);
            }
            int phone_flag=0,phone_k=0;
            for(int i=0;i<j;i++)
            {
                if(strcmp(str,addressBook->contacts[i].phone)==0)
                {
                    phone_k=i;
                    phone_flag=1;
                    break;
                }
            }
            if(phone_flag==1)
            {
                printf("Name:-%s \nPhone no:-%s \nemail:-%s\n",addressBook->contacts[phone_k].name,addressBook->contacts[phone_k].phone,addressBook->contacts[phone_k].email);
                break;
            }
            else
            {
                printf("contact not found\n");
                break;
            }
            case 3:
            printf("enter the email:");
            scanf("%s",str);
            while(!email_validation(str))
            {
                printf("Invalid email\n");
                printf("please re-enter the email:");
                scanf("%s",str);
            }
            int gmail_flag=0,gmail_k=0;
            for(int i=0;i<j;i++)
            {
                if(strcmp(str,addressBook->contacts[i].email)==0)
                {
                    gmail_k=i;
                    gmail_flag=1;
                    break;
                }
            }
            if(gmail_flag==1)
            {
                printf("Name:-%s \nPhone no:-%s \nemail:-%s\n",addressBook->contacts[gmail_k].name,addressBook->contacts[gmail_k].phone,addressBook->contacts[gmail_k].email);
                break;
            }
            else
            {
                printf("contact not found\n");
                break;
            }
            case 4:
            return ;
            default:
            printf("invalid input\n");
        }
    }
    /* Define the logic for search */
}

// Menu-driven contact edit by field or all details
void editContact(struct AddressBook *addressBook)
{
    int j=addressBook->contactCount;
    while(1)
    {
        printf("\t:::Edit Contact Menu:::\n");
        printf("1.edit by Name\n2.edit by phone no\n3.edit by email\n4.edit by all\n5.Exit\n");
        int opt;
        printf("please enter the contact option\n");
        scanf("%d",&opt);
        switch(opt)
        {
            // Case 1: Edit name
            // Case 2: Edit phone
            // Case 3: Edit email
            // Case 4: Edit all fields
            // Case 5: Exit edit menu
            case 1:
                int index1=searchconctact_name(addressBook);
                if(index1!=-1)//0 is an valid index
                {
                    printf("contact found\n");
                    char str[100];
                    printf("enter new name:");
                    scanf(" %[^\n]",str);
                    while(!name_validation(str))
                    {
                        printf("Invalid name,name should contain only uppercase,lowercase,if needed space,please try again\n");
                        printf("Re-enter the name:");
                        scanf(" %[^\n]",str);
                    }
                    strcpy(addressBook->contacts[index1].name,str);
                    printf("contact edited successfully\n");
                }
                else
                    printf("contact not found\n");
                break;
            case 2:
                int index2=searchconctact_phone(addressBook);
                if(index2!=-1)//0 is an valid index
                {
                    printf("contact found\n");
                    char str[100];
                    printf("enter new phone:");
                    scanf(" %[^\n]",str);
                    while (!phone_validation(str))
                    {
                        printf("Invalid phone number! Enter exactly 10 digits:\n");
                        printf("please re-enter the phone number:");
                        scanf("%s", str);
                    }
                        int i=addressBook->contactCount;
                        for(int j=0;j<i;j++)
                        {
                            while(strcmp(str,addressBook->contacts[j].phone)==0)
                            {
                                printf("Phone number already exist:\n");
                                printf("please re-enter phone number:");
                                scanf(" %[^\n]",str);
                                j=0;
                            }
                        }
                    strcpy(addressBook->contacts[index2].phone,str);
                    printf("contact edited successfully\n");
                }
            else
            printf("contact not found\n");
            break;
            case 3:
                int index3=searchconctact_email(addressBook);
                if(index3!=-1)//0 is an valid index
                {
                    printf("contact found\n");
                    char str[100];
                    printf("enter new email:");
                    scanf(" %[^\n]",str);
                    while(!email_validation(str))
                    {
                        printf("Invalid email: use lowercase, include a digit, and a valid domain before .com\n");
                        printf("please re-enter the email:");
                        scanf("%s",str);
                    }
                        int i=addressBook->contactCount;
                        for(int j=0;j<i;j++)
                        {
                            while(strcmp(str,addressBook->contacts[j].email)==0)
                            {
                                printf("email already exist:\n");
                                printf("please re-enter email:");
                                scanf(" %[^\n]",str);
                                j=0;
                            }
                        }
                    strcpy(addressBook->contacts[index3].email,str);
                    printf("contact edited successfully\n");
                }
                else
                printf("contact not found\n");
                break;
            case 4:
                {
                    int index = searchconctact_name(addressBook);
                    if (index != -1)
                    {
                        char str[100];
                        //edit name
                        printf("contact found\n");
                        printf("Enter new name: ");
                        scanf(" %[^\n]", str);
                        while (!name_validation(str)) {
                            printf("Invalid name,name should contain only uppercase,lowercase,if needed space, please re-enter: ");
                            scanf(" %[^\n]", str);
                        }
                        strcpy(addressBook->contacts[index].name, str);


                        //edit phone no
                        //printf("contact found\n");
                        printf("Enter new phone: ");
                        scanf(" %[^\n]", str);
                        while (!phone_validation(str)) {
                            printf("Invalid phone, Phone must be 10 digits only.\n");
                            printf("please re-enter the phone number:");
                            scanf(" %[^\n]", str);
                        }
                        strcpy(addressBook->contacts[index].phone, str);

                        // Edit email
                        //printf("contact found\n");
                        printf("Enter new email: ");
                        scanf(" %[^\n]", str);
                        while (!email_validation(str)) {
                            printf("Invalid email: use lowercase, include a digit, and a valid domain before .com\n");
                            printf("please re-enter your email:");
                            scanf(" %[^\n]", str);
                        }
                        
                        /*for (int j = 0; j < addressBook->contactCount; j++) {
                            if (j != index && strcmp(str, addressBook->contacts[j].email) == 0) {
                                printf("Email already exists. Please enter a different one: ");
                                j = 0;
                                scanf(" %[^\n]", str);
                                continue;
                            }
                        }*/
                        strcpy(addressBook->contacts[index].email, str);

                        printf("All contact fields edited successfully!\n");
                    }
                    else
                        printf("Contact not found.\n");

                    break;
                }
            case 5:
            return ;
            default:
            printf("invalid input\n");
        }
    }
    /* Define the logic for Editcontact */
}

void deleteContact(struct AddressBook *addressBook)
{
    int j=addressBook->contactCount;
    char str[100];
    while(1)
    {
        printf("\t:::Delete Contact Menu:::\n");
        printf("1.Delete by Name\n2.Delete by phone no\n3.Delete by email\n4.Exit\n");
        int opt;
        printf("please enter the contact option\n");
        scanf("%d",&opt);
        switch(opt)
        {
            // Case 1: Delete by name
            // Case 2: Delete by phone
            // Case 3: Delete by email
            // Case 4: Exit delete menu
            case 1:
                int index=searchconctact_name(addressBook);
                if(index!=-1)//0 is an valid index
                {
                    for(int i=index;i<j-1;i++)
                    {
                            addressBook->contacts[i]=addressBook->contacts[i+1];
                    }
                    addressBook->contactCount--;//deleted one contact
                    printf("contact deleted successfully\n");
                }
                else
                    printf("contact not found");
                break;
            case 2:
                int phone_index=searchconctact_phone(addressBook);
                if(phone_index!=-1)//0 is an valid index
                {
                    for(int i=phone_index;i<j-1;i++)
                    {
                            addressBook->contacts[i]=addressBook->contacts[i+1];
                    }
                    addressBook->contactCount--;//deleted one contact
                    printf("contact deleted successfully\n");
                }
                else
                    printf("contact not found");
                break;
            
            case 3:
                int email_index=searchconctact_email(addressBook);
                if(email_index!=-1)//0 is an valid index
                {
                    for(int i=email_index;i<j-1;i++)
                    {
                            addressBook->contacts[i]=addressBook->contacts[i+1];
                    }
                    addressBook->contactCount--;//deleted one contact
                    printf("contact deleted successfully\n");
                }
                else
                    printf("contact not found\n");
                break;
            case 4:
                printf("Exit\n");
                return;
            default:
            printf("invalid input\n");
        }
    }
    /* Define the logic for deletecontact */
}