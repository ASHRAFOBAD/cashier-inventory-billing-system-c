#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>


// File Paths
#define USER_FILE "users.txt"
#define PRODUCT_FILE "products.txt"
#define BILL_FILE  "sale_bills.txt"
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity_in_storage;
} Product;

typedef struct {
    int id;
    char name[50];
    char phone[50];
    int access; // binary access
    char password[50];
    float salary;
} User;

User current_user;

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
    int sold_quantity;
} Products;

typedef struct {
    int bill_no;
    char date_time[50];
    User user;
    Product product;
    float price;
} Bill;

void Header(char Title[50]);
void Tabs(short tab);

int USER_ID ;

// Declaration of the manageInput function
void manageInput(void *variable, bool isInt, bool isFloat, bool isString);
void main_menu(User user);
bool check_Accessibility(int id);
void reports();
void show_access_denied();
void go_back();

//USER
void login();
void manage_users();
void read_users();
void add_user();
void delete_user();
void update_user();
int user_exists(int);

//PRODUCT
void manage_products();
void read_products(bool Bill);
void add_product();
void delete_product();
void update_product();

//bILLING
int check_bill_number_exists(int bill_number);
//int check_product_exists(const char* product_name);
int check_product_exists(const int product_id);
int search_sale_bill(int bill_number);
void billing_system();
void add_sale_bill();
void show_sale_bills();
void update_user_salary(int amount);






int main() {
    system("color 79");
   login();

  //display_menu();

    return 0;
}

void manageInput(void *variable, bool isInt, bool isFloat, bool isString) {

      bool valid = false;

    while (!valid) {
        if (isInt) {
            int temp = 0;
            if (scanf("%d", &temp) == 1) {
                *(int *)variable = temp;
                valid = true;
            } else {
                Tabs(4);
                printf("Invalid input. Please enter a valid integer.\n");
            }
            while (getchar() != '\n'); // Clear input buffer
        }

        if (isFloat && !valid) {
            float temp = 0.0;
            if (scanf("%f", &temp) == 1) {
                *(float *)variable = temp;
                valid = true;
            } else {
                Tabs(4);
                printf("Invalid input. Please enter a valid float.\n");
            }
            while (getchar() != '\n'); // Clear input buffer
        }

        if (isString && !valid) {
            char *temp = (char *)variable;
            if (scanf("%49[^\n]", temp) == 1) { // Limit input to 49 characters
                valid = true;
            } else {
                Tabs(4);
                printf("Invalid input. Please enter a valid string.\n");
            }
            while (getchar() != '\n'); // Clear input buffer
        }
    }

}


void Tabs(short tab){
    for(short i = 0 ; i< tab ; i++)
        printf("\t");

}


 time_t t;
void Header(char title[50]){


  time(&t);
  Tabs(4);
  printf("=================================================================\n");//65
  Tabs(4);
  printf("%s", ctime(&t));
  Tabs(4);
  printf("%s \t\t | Name: %s | ID: %d\n", title, current_user.name, current_user.id);
  Tabs(4);
printf("=================================================================\n");//65
}

bool check_Accessibility (int id){
    FILE* file = fopen(USER_FILE, "r");
    if (!file) {
        Tabs(4);
        system("\a");
        printf("Error opening users file.\n");
        return 0;
    }

    User user;

    while (fscanf(file, "%d#//#%[^#]#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
                  &user.id, user.name, user.phone, &user.access, user.password, &user.salary) != EOF) {
        if (user.id == id) {
                if(user.access == 1)
                {
                    fclose(file);
                    return true;
                }

        }
    }

    fclose(file);
    return false; // User does not exist
}

void display_menu() {
   system("cls");
    int choice;

    while (1) {
        Header("Main Menue");
        Tabs(4);
        printf("1. Manage Users\n");
          Tabs(4);
        printf("2. Manage Products\n");
          Tabs(4);
        printf("3. Billing System\n");
          Tabs(4);
        printf("4. Log-out\n");
          Tabs(4);
        printf("Enter your choice: ");
      //  scanf("%d", &choice);
      manageInput(&choice, true, false,false);

        switch (choice) {
            case 1:
                  Tabs(4);
                 printf("Loading...\n");
                 Sleep(100);
                 system("cls");
                manage_users();
                break;
            case 2:
                  Tabs(4);
                 printf("Loading...\n");
                 Sleep(100);
                 system("cls");
                manage_products();
                break;
            case 3:
                  Tabs(4);
                 printf("Loading...\n");
                 Sleep(100);
                 system("cls");
                billing_system();
                break;
            case 4:
                printf("\n");
                 Tabs(4);
                 printf("Logging out... Goodbye!\n");
                 Sleep(500);
                 system("cls");
                exit(0);//close thewindows
                break;
            default:
                  Tabs(5);
                   system("\a");
                printf("Invalid choice. Please try again.\n");

        }
    }
}

#define TEMP_FILE "temp.txt"

void login() {
    //User user;
    int id;
    char input_password[50];
   // current_user.name = NULL;
   // current_user.id = NULL;
    Header("LOG-IN SCREEN");
    Tabs(4);
    printf("Enter User ID: ");
    manageInput(&id, true, false, false);

    Tabs(4);
    printf("- - - - - - - - - - - - - - -\n");

    bool valid = false;
    FILE* file = fopen(USER_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Error opening user file.\n");
        return;
    }


    int attempts = 0;
    while (attempts < 3 && !valid) {
        Tabs(4);
        printf("Enter Password (Attempt %d/3): ", attempts + 1);
        manageInput(input_password, false, false, true);


        rewind(file); // Rewind file to start reading again
        while (fscanf(file, "%d#//#%[^#]#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
                  &current_user.id, current_user.name, current_user.phone, &current_user.access, current_user.password, &current_user.salary) != EOF) {
        if (id == current_user.id && strcmp(input_password, current_user.password) == 0) {
            valid = true;
            USER_ID = current_user.id;

            break;
        }
    }

    if (!valid) {
        Tabs(4);
        printf("Invalid username or password.\n");
        attempts++;
        }
    }

    fclose(file);

    if (valid) {
        display_menu();
    } else {
        Tabs(4);
        printf("Account locked. Too many failed attempts.\n");
        Tabs(4);
        printf("Press any key to close the window...\n");
        getchar();
        getchar(); // Second getchar in case newline was left in buffer
}

}



void manage_users() {

        if(!check_Accessibility(USER_ID)){
            system("cls");
            Header("Manage Users Screen");
            Tabs(4);
            printf("YOU DON'T HAVE ACCESS TO MANAGE THE USERS...\n");
            Tabs(4);
            system("pause");
            system("cls");
            return;

        }

    int choice = 0;

    while (1) {
        system("cls");
        Header("Manage Users Screen");
        Tabs(4);
        printf("1. Show Users List\n");
         Tabs(4);
        printf("2. Add New User\n");
         Tabs(4);
        printf("3. Delete User\n");
         Tabs(4);
        printf("4. Update User\n");
         Tabs(4);
        printf("5. Go Back to Main Screen\n");
         Tabs(4);
        printf("Choose an option: ");
      //  scanf("%d", &choice);
       manageInput(&choice, true, false,false);

        switch (choice) {
        case 1:
             system("cls");
            read_users();
            break;
        case 2:
             system("cls");
            add_user();
            break;
        case 3:
             system("cls");
            delete_user();
            break;
        case 4:
             system("cls");
            update_user();
            break;
        case 5:
             Tabs(4);

            printf("Returning to the main menu...\n");
            Sleep(100);
            system("cls");
            return;
        default:
             system("\a");
             Tabs(4);
             printf("Invalid choice. Please try again.\n");
             Sleep(200);
             system("cls");
        }
    }
}

int user_exists(int  user_id) {
    FILE* file = fopen(USER_FILE, "r");
    if (!file) {
        Tabs(4);
        printf("\a");
        printf("Error opening users file.\n");
        return 0; // File does not exist, so the user can't exist
    }

    User user;

    // Read the file and search for the user ID
    while (fscanf(file, "%d#//#%[^#]#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
                  &user.id, user.name, user.phone, &user.access, user.password, &user.salary) != EOF) {
        if (user.id == user_id) {
            fclose(file);
            return 1; // User exists
        }
    }

    fclose(file);
    return 0; // User does not exist
}

void read_users() {

Header("User List Screen");
    FILE* file = fopen(USER_FILE, "r");
if (!file) {
        Tabs(4);
    printf("Could not open users file.\n");
    return;
}
printf("\n\n");
User user;
Tabs(2);
printf("+------ +--------------------+-----------------+--------+--------------------+------------+\n");
Tabs(2);
printf("| ID   | Name               | Phone           | Access | Password           | Sales (RM)  |\n");
Tabs(2);
printf("+------ +--------------------+-----------------+--------+--------------------+------------+\n");



while (fscanf(file,"%d#//#%[^#]#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
              &user.id, user.name, user.phone, &user.access, user.password, &user.salary) != EOF) {
                  Tabs(2);
    // Print formatted user data with correct column widths
    printf("| %-5d | %-18s | %-15s | %-6d | %-18s | %-10.2f |\n",
           user.id, user.name, user.phone, user.access, user.password, user.salary);
}
Tabs(2);
printf("+------ +--------------------+-----------------+--------+--------------------+------------+\n");

fclose(file);
Tabs(2);
system("pause");


}


void add_user() {
    Header("Add A New User Screen");
    FILE* file = fopen(USER_FILE, "a");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Error opening user file.\n");
        return;
    }

    User user;
    int temproray = 0;
    Tabs(4);
    printf("Enter User ID: ");
  //  scanf("%d", &user.id);
    manageInput( &temproray, true, false,false);
    user.id = (int)temproray;

    // Check if user ID already exists
    if (user_exists(user.id)) {
        printf("\a");
        Tabs(4);
        printf("User with ID %d already exists.\n", user.id);
        fclose(file);
        return;
}

Tabs(4);
    printf("Enter User Name: ");
    //scanf(" %[^\n]", user.name); //  read an entire line of input until a newline (\n) is encountered
    manageInput(&user.name, false, false,true);

    Tabs(4);
    printf("Enter User Password: ");
   // scanf(" %[^\n]", user.password );
    manageInput(&user.password, false, false,true);
    Tabs(4);
    printf("Enter User Phone: ");
    //scanf(" %[^\n]", user.phone );
    manageInput(&user.phone, false, false,true);

    user.salary = 0;
    char chioce = 'n';
    user.access = 0;
    Tabs(4);
    printf ("Full Access ? [Y/N] ");
   // scanf(" %c", &chioce);
   manageInput(&chioce, false, false,true);

    if( chioce == 'Y' || chioce == 'y' ){
        user.access = 1;
    }


    printf("\n\n");
    Tabs(4);
    printf ("******New User Details******\n\n");
    Tabs(4);
    printf("User ID       : %d\n", user.id);
    Tabs(4);
    printf("User Name     : %s\n", user.name);
    Tabs(4);
    printf("User Phone    : %s\n", user.phone);
    Tabs(4);
    printf("User Access   : %d\n", user.access);
    Tabs(4);
    printf("User Password : %s\n", user.password);
    Tabs(4);
    printf("User Salary   : %f\n", user.salary);
    Tabs(4);
    printf("***************************\n");


    fprintf(file, "%d#//#%s#//#%s#//#%d#//#%s#//#%.2f\n",
        user.id, user.name, user.phone, user.access, user.password, user.salary);

    fclose(file);
    Tabs(4);
    printf("User added successfully.\n");
    Tabs(4);
    system("pause");

}

void delete_user() {
    Header("Delete User Screen");
    FILE* file = fopen(USER_FILE, "r");
    if (!file) {
            printf("\a");
            Tabs(4);
        printf("Could not open users file.\n");
        return;
    }

    FILE* temp_file = fopen(TEMP_FILE, "w");
    if (!temp_file) {
            printf("\a");
            Tabs(4);
        printf("Could not open temporary file.\n");
        fclose(file);
        return;
    }

    User user;
    int id_to_delete, found = 0;
    char confirm = 'n';
    Tabs(4);
    printf("Enter User ID to delete: ");
   // scanf("%d", &id_to_delete);
    manageInput( &id_to_delete, true, false,false);

    while (fscanf(file, "%d#//#%[^#]#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
        &user.id, user.name, user.phone, &user.access, user.password, &user.salary) != EOF) { //EOF End of file
        if (user.id == id_to_delete) {

            printf("\n");
            Tabs(4);
            printf("User Details:\n");
            Tabs(4);
            printf("ID       : %d\n", user.id);
             Tabs(4);
            printf("Name     : %s\n", user.name);
             Tabs(4);
            printf("Phone    : %s\n", user.phone);
             Tabs(4);
            printf("Access   : %d\n", user.access);
             Tabs(4);
            printf("Password : %s\n", user.password);
             Tabs(4);
            printf("Salary   : %.2f\n\n", user.salary);
            Tabs(4);
            printf("Are you sure to delete this user ?[y/n] \n");
            manageInput(&confirm, false,false,true);
            if(confirm == 'Y' || confirm == 'y')
            {
                 found = 1;
            };


            Tabs(4);

        }
        else {
               // rewind(file);
            fprintf(temp_file, "%d#//#%s#//#%s#//#%d#//#%s#//#%.2f\n",
                user.id, user.name, user.phone, user.access, user.password, user.salary);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove(USER_FILE);
        rename(TEMP_FILE, USER_FILE);
        printf("\n\n");
        Tabs(4);
        printf("User deleted successfully.\n");

    }
    else {
        printf("\n\n");
            Tabs(4);

        printf("User not found or cancelled\n");
        remove(TEMP_FILE);
    }
    Tabs(4);
    system("pause");
}

void update_user() {
    Header("Update User Screen");
    FILE* file = fopen(USER_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Could not open users file.\n");
        return;
    }

    FILE* temp_file = fopen(TEMP_FILE, "w");
    if (!temp_file) {
       printf("\a");
        Tabs(4);
        printf("Could not open temporary file.\n");
        fclose(file);
        return;
    }

    User user;
    int id_to_update, found = 0, update_choice;
    char choice ;
    Tabs(4);

    printf("Enter User ID to update: ");
    //scanf("%d", &id_to_update);
     manageInput(&id_to_update, true, false,false);


    while (fscanf(file, "%d#//#%[^#]#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
        &user.id, user.name, user.phone, &user.access, user.password, &user.salary)  != EOF) {
        if (user.id == id_to_update) {
            found = 1;
            Tabs(4);
            printf("User Details:\n");
            Tabs(4);
            printf("ID       : %d\n", user.id);
             Tabs(4);
            printf("Name     : %s\n", user.name);
             Tabs(4);
            printf("Phone    : %s\n", user.phone);
             Tabs(4);
            printf("Access   : %d\n", user.access);
             Tabs(4);
            printf("Password : %s\n", user.password);
             Tabs(4);
            printf("Salary   : %.2f\n\n", user.salary);
            Tabs(4);


            printf ("Do you want to update User Name [Y/N]? ");
           // scanf(" %c", &choice);
            manageInput( &choice, false, false,true);

            if(choice == 'Y' || choice == 'y')
            {
                Tabs(4);
                printf ("Enter A new User Name : ");
               // scanf (" %c", &user.name);
                  manageInput( &user.name, false, false,true);
            }
            Tabs(4);
            printf ("Do you want to update User Password [Y/N]? ");
         //   scanf(" %c", &choice);
            manageInput( &choice, false, false,true);

            if(choice == 'Y' || choice == 'y')
            {
                Tabs(4);
                printf ("Enter A new User Password : ");
               // scanf (" %c", &user.password);
                manageInput(&user.password, false, false,true);
            }
            Tabs(4);
            printf ("Do you want to update User Phone [Y/N]? ");
         //   scanf(" %c", &choice);
              manageInput(& choice, false, false,true);
            if(choice == 'Y' || choice == 'y')
            {
                Tabs(4);
                printf ("Enter A new User Phone : ");
               // scanf ("%c", &user.phone)
                manageInput( &user.phone, false, false,true);
            }
            printf("\n");
            Tabs(4);
            printf("=================================================\n");//50
            Tabs(4);
           printf("After Updating User's Details :\n");
            Tabs(4);
            printf("ID       : %d\n", user.id);
             Tabs(4);
            printf("Name     : %s\n", user.name);
             Tabs(4);
            printf("Phone    : %s\n", user.phone);
             Tabs(4);
            printf("Access   : %d\n", user.access);
             Tabs(4);
            printf("Password : %s\n", user.password);
             Tabs(4);
            printf("Salary   : %.2f\n", user.salary);
            Tabs(4);
            printf("=================================================\n");//50

        }

      fprintf(temp_file, "%d#//#%s#//#%s#//#%d#//#%s#//#%.2f\n",
            user.id, user.name, user.phone, user.access, user.password, user.salary);
    }

    fclose(file);
    fclose(temp_file);
 printf("\n");
    if (found) {
        remove(USER_FILE);
        rename(TEMP_FILE, USER_FILE);

        Tabs(4);
        printf("User updated successfully.\n");
    }
    else {
        printf("\a");
        Tabs(4);
        printf("User not found.\n");
        remove(TEMP_FILE);
    }
    Tabs(4);
    system("pause");
}




void manage_products() {

    system("cls");
    int choice;

    while (1) {
        Header("Manage Products Screen");
        Tabs(4);
        printf("1. Show Products List\n");
        Tabs(4);
        printf("2. Add New Product\n");
        Tabs(4);
        printf("3. Delete Product\n");
        Tabs(4);
        printf("4. Update Product\n");
        Tabs(4);
        printf("5. Go Back to Main Screen\n");
        Tabs(4);
        printf("Choose an option: ");
        //scanf("%d", &choice);
        manageInput( &choice, true, false,false);

        switch (choice) {
            case 1:
                system("cls");
                read_products(false);
                break;
            case 2:
                system("cls");
                add_product();
                break;
            case 3:
                system("cls");
                delete_product();
                break;
            case 4:
                system("cls");
                update_product();
                break;
            case 5:

                printf("\n");
                Tabs(4);
                printf("Returning to the main menu...\n");
                Sleep(100);
                 system("cls");
                return;
            default:

                Tabs(4);
                printf("Invalid choice. Please try again.\n");
                Sleep(200);
                system("cls");
        }
    }
}

void read_products(bool Bill) {
    Header("Show Porduct List Screen");
    FILE *file = fopen(PRODUCT_FILE, "r");
    if (!file) {
      printf("\a");
        Tabs(4);
        printf("Could not open products file.\n");
        return;
    }

    Products product;
    printf("\n");
     Tabs(4);
    printf("+------+------------------------+-------------+----------------+\n");
     Tabs(4);
    printf("| ID   | Name                   | Price       |    Quantity    |\n");
     Tabs(4);
    printf("+------+------------------------+-------------+----------------+\n");


    while (fscanf(file, "%d#//#%[^#]#//#%f#//#%d\n",
              &product.id, product.name, &product.price, &product.sold_quantity) != EOF) {


    product.name[strcspn(product.name, "\n")] = '\0';
       Tabs(4);

    printf("| %-4d | %-23s | %-10.2f | %-14d |\n",
           product.id, product.name, product.price, product.sold_quantity);
}
 Tabs(4);
 printf("+----+--------------------------+------------+----------------+\n");
    fclose(file);
    if(Bill == false)
    {
            printf("\a");
            printf("\n");
            Tabs(4);
            system("pause");
            system("cls");
    }

}

void add_product() {
    Header("Add A New Product Screen");
    FILE *file = fopen(PRODUCT_FILE, "a");
    if (!file) {
       printf("\a");
        Tabs(4);
        printf("Could not open products file.\n");
        return;
    }

    Products product, temp;
    int product_exists = 0;
    Tabs(4);

    printf("Enter Product ID: ");
   // scanf("%d", &product.id);
    manageInput( &product.id, true, false,false);

    // Check if the product already exists
    while (fscanf(file, "%d#//#%[^#]#//#%f#//#%d\n",
                  &temp.id, temp.name, &temp.price, &temp.sold_quantity) != EOF) {
        if (temp.id == product.id) {
            product_exists = 1;
            Tabs(4);
            printf("Product already exists:\n");
            Tabs(4);
            printf("ID      : %d\n", temp.id);
            Tabs(4);
            printf("Name    : %s\n", temp.name);
            Tabs(4);
            printf("Price   : %f\n", temp.price);
            Tabs(4);
            printf("Sold Qt : %d\n", temp.sold_quantity);
            break;
        }
    }

    if (product_exists) {
        Tabs(4);
        printf("This product is already added.\n");
        fclose(file);
        return;
    }
 Tabs(4);
    // Add new product
     printf("Enter Product Name: ");
     manageInput( &product.name, false, false,true);

    Tabs(4);
    printf("Enter Product Price: ");

    manageInput( &product.price, false, true,false);
    product.sold_quantity = 50; // Default quantity

    fprintf(file,  "%d#//#%-22s#//#%.2f#//#%d\n", product.id, product.name, product.price, product.sold_quantity);

    fclose(file);
    printf("\n");
     Tabs(4);
    printf("Product added successfully.\n");
            Tabs(4);
            printf("ID      : %d\n", product.id);
            Tabs(4);
            printf("Name    : %s\n", product.name);
            Tabs(4);
            printf("Price   : %f\n", product.price);
            Tabs(4);
            printf("Sold Qt : %d\n", product.sold_quantity);

    printf("\n");
    Tabs(4);
    system("pause");
    system("cls");
}

void delete_product() {
    read_products(true);
    Header("Delete Product Screen");
    FILE *file = fopen(PRODUCT_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Could not open products file.\n");
        return;
    }

    FILE *temp_file = fopen(TEMP_FILE, "w");
    if (!temp_file) {
        Tabs(4);
        printf("Could not open temporary file.\n");
        fclose(file);
        return;
    }

    Products product;
    int id_to_delete, found = 0;
 Tabs(4);
    printf("Enter Product ID to delete: ");
 //   scanf("%d", &id_to_delete);
     manageInput(&id_to_delete, true, false,false);

    while (fscanf(file, "%d#//#%[^#]#//#%f#//#%d\n",
                  &product.id, product.name, &product.price, &product.sold_quantity) != EOF) {
        if (product.id == id_to_delete) {
            found = 1;
            printf("\n");
             Tabs(4);
            printf("Deleting Product:\n");

            Tabs(4);
             printf("ID      : %d\n", product.id);
              Tabs(4);
             printf("Name    : %s\n", product.name);
              Tabs(4);
             printf("Price   : %f\n", product.price);
              Tabs(4);
             printf("Sold Qt : %d\n", product.sold_quantity);
        } else {
            fprintf(temp_file, "%d#//#%s#//#%.2f#//#%d\n",
                    product.id, product.name, product.price, product.sold_quantity);
        }
    }

    fclose(file);
    fclose(temp_file);
     printf("\n");
    if (found) {
        remove(PRODUCT_FILE);
        rename(TEMP_FILE, PRODUCT_FILE);
        Tabs(4);
        printf("Product deleted successfully.\n");
    } else {
        system("\a");
        Tabs(4);
        printf("Product not found.\n");
        remove(TEMP_FILE);
    }


    printf("\n");
    Tabs(4);
    system("pause");
    system("cls");
}

void update_product() {
    read_products(true);
    Header("Update Product Screen");
    FILE *file = fopen(PRODUCT_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Could not open products file.\n");
        return;
    }

    FILE *temp_file = fopen(TEMP_FILE, "w");
    if (!temp_file) {
        Tabs(4);
        printf("Could not open temporary file.\n");
        fclose(file);
        return;
    }

    Products product;
    int id_to_update, found = 0, update_choice;
    Tabs(4);
    printf("Enter Product ID to update: ");
    //scanf("%d", &id_to_update);
     manageInput(&id_to_update, true, false,false);
    while (fscanf(file, "%d#//#%[^#]#//#%f#//#%d\n",
                  &product.id, product.name, &product.price, &product.sold_quantity) != EOF) {
        if (product.id == id_to_update) {
            found = 1;
            printf("\n");
            Tabs(4);
            printf("Updating Product:\n");
            Tabs(4);
            printf("ID      : %d\n", product.id);
            Tabs(4);
            printf("Name    : %s\n", product.name);
            Tabs(4);
            printf("Price   : %f\n", product.price);
            Tabs(4);
            printf("Sold Qt : %d\n", product.sold_quantity);
            Tabs(4);
            printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
            Tabs(4);
            printf("What do you want to update?\n");
            Tabs(4);
            printf("1. Price\n");
            Tabs(4);
            printf("2. Add Quantity to Storage\n");
            Tabs(4);
            printf("Choose an option: ");
           // scanf("%d", &update_choice);
            manageInput(&update_choice, true, false,false);

            if (update_choice == 1) {
                Tabs(4);
                printf("Enter New Price: ");
               // scanf("%f", &product.price);
                manageInput(&product.price, false, true,false);
            } else if (update_choice == 2) {
                int additional_quantity;
                Tabs(4);
                printf("Enter Quantity to Add: ");
                //scanf("%d", &additional_quantity);
                manageInput(&additional_quantity, true, false,false);
                product.sold_quantity += additional_quantity;
            } else {
                Tabs(4);
                printf("Invalid choice.\n");
            }
        }
        fprintf(temp_file, "%d#//#%s#//#%.2f#//#%d\n",
                product.id, product.name, product.price, product.sold_quantity);
    }

    fclose(file);
    fclose(temp_file);
    printf("\n");
    if (found) {
        remove(PRODUCT_FILE);
        rename(TEMP_FILE, PRODUCT_FILE);
        Tabs(4);
        printf("Product updated successfully.\n");
    } else {
        printf("\a");
        Tabs(4);
        printf("Product not found.\n");
        remove(TEMP_FILE);
    }

    printf("\n");
    Tabs(4);
    system("pause");
    system("cls");
}



int check_bill_number_exists(int bill_number) {

    FILE* file = fopen(BILL_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Error opening sale bills file.\n");
        return 0;
    }

    Bill bill;
    int found = 0;

    while (fscanf(file, "%d#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
        &bill.bill_no, bill.date_time, &bill.user.id, bill.product.name, &bill.price) != EOF) {
        if (bill.bill_no == bill_number) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
}

int check_product_exists(const int product_id) {
    FILE* file = fopen(PRODUCT_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Error opening product file.\n");
        return 0;
    }

    Product product;
    int found = 0;

    while (fscanf(file, "%d#//#%[^#]#//#%f#//#%d\n",
                  &product.id, product.name, &product.price, &product.quantity_in_storage) != EOF) {
        if (product_id == product.id) {
            found = 1;

            break;
        }
    }

    fclose(file);
    return found;
}


int search_sale_bill(int bill_number) {
    FILE* file = fopen(BILL_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Error opening sale bills file.\n");
        return 0;
    }

    Bill bill;
    int found = 0;

    while (fscanf(file, "%d#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
                  &bill.bill_no, bill.date_time, &bill.user.id, bill.product.name, &bill.price) != EOF) {
        // Check if the current bill matches the desired bill number
        if (bill.bill_no == bill_number) {
                found = 1;
                Tabs(4);
                printf("Return Bill Details:\n");
                Tabs(4);
                printf("  Bill Number: %d\n", bill.bill_no);
                Tabs(4);
                printf("  Date & Time: %s\n", bill.date_time);
                Tabs(4);
                printf("  User ID: %d\n", bill.user.id);
                break;
                }
            }


    fclose(file);
    if(found == 1){
      FILE* file = fopen(BILL_FILE, "r");
        if (!file) {
            printf("\a");
            Tabs(4);
            printf("Error opening sale bills file.\n");
            return 0;
        }
        while (fscanf(file,"%d#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
                  &bill.bill_no, bill.date_time, &bill.user.id, bill.product.name, &bill.price) != EOF) {
        // Check if the current bill matches the desired bill number
        if (bill.bill_no == bill_number)
            {
                Tabs(4);
                printf("  ProductName: %s\n", bill.product.name );
                Tabs(4);
                printf("  Product ID : %d\n", bill.product.id);
                Tabs(4);
                printf("  Price      : %.2f\n", bill.product.price);

            }


        }
         fclose(file);
    }


    if (!found) {
        printf("\a");
        Tabs(4);
        printf("No bill found with the given number.\n");
        return 0;
    }
    return found;
}


void billing_system() {
    int choice;

    while (1) {
            Header("Billing System Screen");
            Tabs(4);
            printf("1. Add Sale Bill\n");
            Tabs(4);
            printf("2. Show Sale Bills\n");
            Tabs(4);
            printf("3. Go Back to Main Screen\n");
            Tabs(4);
            printf("Choose an option: ");

       manageInput(&choice, true, false,false);

        switch (choice) {
        case 1:
             system("cls");
             add_sale_bill();
            break;
        case 2:
             system("cls");
             show_sale_bills();
            break;
        case 3:
             Tabs(4);
             printf("Returning to the main menu...\n");
             Sleep(200);
             system("cls");
             display_menu();

            return;
        default:

            printf("\a");
            Tabs(4);
            printf("Invalid choice. Please try again.\n");
            system("cls");
        }
    }
}

void update_user_salary(int amount)
{
    FILE* file = fopen(USER_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Could not open users file.\n");
        return;
    }

    FILE* temp_file = fopen(TEMP_FILE, "w");
    if (!temp_file) {
       printf("\a");
        Tabs(4);
        printf("Could not open temporary file.\n");
        fclose(file);
        return;
    }

    User user;


    while (fscanf(file, "%d#//#%[^#]#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
        &user.id, user.name, user.phone, &user.access, user.password, &user.salary) != EOF) {
        if (user.id == current_user.id) {
            user.salary += amount;
        }
        fprintf(temp_file, "%d#//#%s#//#%s#//#%d#//#%s#//#%.2f\n",
            user.id, user.name, user.phone, user.access, user.password, user.salary);
    }

    fclose(file);
    fclose(temp_file);
 printf("\n");
        remove(USER_FILE);
        rename(TEMP_FILE, USER_FILE);
    system("pause");

}


void add_sale_bill() {
    Bill bill;
    int found = 0;
    Header("Add A New Sale Bill Screen");


    do {
        bill.bill_no = rand() % (9999 - 1000 + 1) + 1000;
        found = check_bill_number_exists(bill.bill_no);
    } while (found);


    time_t now = time(NULL);
    strftime(bill.date_time, sizeof(bill.date_time), "%Y-%m-%d %H:%M:%S", localtime(&now));
    Tabs(4);
   // printf("Enter User ID: ");
   // manageInput(&bill.user.id, true, false, false);
    bill.user.id = current_user.id;
   read_products(true);


    float total_amount = 0.0f;
    Product product, product_for_sale;

    do {
            //read_products(true);
        printf("\n");
        Tabs(4);

        printf("Enter Product ID (or '0' to finish): ");
        manageInput(&product_for_sale.id,true,false,false);

        if (product_for_sale.id != 0) {

            found = check_product_exists(product_for_sale.id);

            if (found) {
                FILE* file = fopen(PRODUCT_FILE, "r");
                if (!file) {
                    system("\a");
                    Tabs(4);
                    printf("Error: Could not open products file.\n");
                    return;
                }
                short quantity_to_sale = 0;

                while (fscanf(file, "%d#//#%[^#]#//#%f#//#%d\n",
                              &product.id, product.name, &product.price, &product.quantity_in_storage) != EOF) {
                    if (product.id == product_for_sale.id) {
                             Tabs(4);
                        printf("Product Details:\n");
                        Tabs(4);
                        printf("  Name: %s\n", product.name);
                        Tabs(4);
                        printf("  Price: %.2f\n", product.price);
                        Tabs(4);
                        printf("Enter Quantity: ");
                        manageInput(&product.quantity_in_storage, true, false, false);
                       // manageInput(&quantity_to_sale , true,false,false);
                        if (product.quantity_in_storage <= 0 || (product.quantity_in_storage > product.quantity_in_storage)) {
                            printf("\a");
                            Tabs(4);
                            printf("Invalid quantity. Please enter a valid count.\n");
                            break;
                        }


                        float product_total = product.price * product.quantity_in_storage;

                        total_amount += product_total;
                        //fclose(file);

                        Tabs(4);
                        printf("  Product Total: %.2f\n", product_total);

                        FILE* file2 = fopen("sale_bills.txt", "a");
                        if (!file2) {
                            system("\a");
                            Tabs(4);
                            printf("Error: Could not open sale bills file.\n");
                            fclose(file);
                            return;
                        }


                        /*fprintf(file2, "%d#//#%s#//#%d#//#%s#//#%.2f\n",
                                bill.bill_no, bill.date_time, bill.user.id, product.name, product_total);*/
                        fprintf(file2, "%d#//#%s#//#%d#//#%s#//#%.2f\n",
                        bill.bill_no, bill.date_time, current_user.id, product.name, product_total);

                        fclose(file2);
                        Tabs(4);
                        printf("Product added to the bill.\n");

                       // break;
                    }
                }
                fclose(file);
            } else {
                printf("\a");
                Tabs(4);
                printf("Error: Product not found.\n");
                Sleep(100);
                return;
            }
        }
    } while (product_for_sale.id != 0);

    // Print bill summary
    Tabs(4);
    printf("\nBill Summary:\n");
    Tabs(4);
    printf("  Bill Number: %d\n", bill.bill_no);
    Tabs(4);
    printf("  Date & Time: %s\n", bill.date_time);
    Tabs(4);
    printf("  User ID: %d\n", bill.user.id);
    Tabs(4);
    printf("  Total Amount: %.2f\n", total_amount);
   // current_user.salary += total_amount;
    update_user_salary(total_amount);
    Tabs(4);

    printf("Sale bill saved successfully.\n");

    printf("\n");
    Tabs(4);
    system("pause");
    system("cls");
}

void show_sale_bills() {
    Header("Show Sale Bills List Screen");
    FILE* file = fopen(BILL_FILE, "r");
    if (!file) {
        printf("\a");
        Tabs(4);
        printf("Error: Could not open sale bills file.\n");
        return;
    }

    Bill bill;

    Tabs(3);
   printf("+---------+---------------------+----------+----------------------+-----------+\n");
Tabs(3);
printf("| Bill No | Date & Time         | User ID  | Product              | Price     |\n");
Tabs(3);
printf("+---------+---------------------+----------+----------------------+-----------+\n");

while (fscanf(file, "%d#//#%[^#]#//#%d#//#%[^#]#//#%f\n",
              &bill.bill_no, bill.date_time, &bill.user.id, bill.product.name, &bill.product.price) == 5) {
    Tabs(3);
    printf("| %7d | %-19s | %8d | %-20s | %9.2f |\n",
           bill.bill_no, bill.date_time, bill.user.id, bill.product.name, bill.product.price);
}
Tabs(3);
printf("+---------+---------------------+----------+----------------------+-----------+\n");

    fclose(file);
    printf("\n");
    Tabs(4);
    system("pause");
    system("cls");
}
