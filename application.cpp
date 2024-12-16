#include <iostream>
#include <windows.h>
#include <conio.h>
#include <array>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

void gotoxy(int X, int Y);
void print_header();
void sign_up_menu();
bool is_alpha(string s);
bool is_integer(string s);
void Login_menu();
int admin_menu();
int cust_menu();
int anonymous_menu();
void add_customer(int n);
void update_customer_info(string id);
void show_customer_data();
void delete_customer(string id);
void search_customer(string id);
void print_box();
void room_booking();
void check_in();
void check_out();
void exit_menu();
int is_registered(string email);
void register_admin();

void print_front();
void disply_front();

string getField(string record, int field);
void get_data(string filename, string name[], string email[], string password[], int &count);
void update_data(string filename, string name[], string email[], string password[], int &count);

string cust_email[100], cust_password[100], cust_name[100];
string admin_email[100], admin_password[100], admin_name[100];

int total_admins = 3, total_customers = 0;
int user_type = -1;
string customer_name[20], customer_id[20], customer_address[20];
string customer_cell[20], customer_balance[20];
string room_id[20], room_status[20];

main()
{

    get_data("admins.txt", admin_name, admin_email, admin_password, total_admins);
    get_data("customers.txt", cust_name, cust_email, cust_password, total_customers);

    int admin_op, cust_op, op;
    system("cls");
    disply_front();
    system("cls");

val2:
    op = anonymous_menu();
    if (op == 1)
    {
        system("cls");
        Login_menu();
        system("cls");
        // cout<<user_type;
    }
    else if (op == 2)
    {
        system("cls");
        sign_up_menu();
        system("cls");
        Login_menu();
        system("cls");
        // cout<<user_type;
    }
    else
    {
        cout << "    INVALID CHOICE !!!!!";
        Sleep(1000);
        system("cls");
        goto val2;
    }
     
val3:
    if (user_type == 1)
    {
        admin_op = admin_menu();

        if (admin_op == 1)
        {
            system("cls");
            int size;
            gotoxy(2, 4);
            cout << "How many Customers data you want to enter (Maximum 20) : ";
            cin >> size;
            if (size <= 0 && size > 20)
            {
                cout << "Invalid Choice ";
                Sleep(800);
                system("cls");
                goto val3;
            }
            else
            {
                add_customer(size);
                system("cls");
                Sleep(300);
                goto val3;
            }
        }
        else if (admin_op == 2)
        {
            system("cls");
            if (customer_id[0] == "")
            {
                gotoxy(2, 6);
                cout << "You have not entered any customer data yet.";
                Sleep(2000);
                system("cls");
                goto val3;
            }
            else
            {
                show_customer_data();
                system("cls");
                Sleep(300);
                goto val3;
            }
        }
        else if (admin_op == 3)
        {
            system("cls");
            gotoxy(2, 4);
            string id;
            cout << "Which Customer data you want to Update (Enter Customer ID): ";
            cin >> id;
            if (customer_id[0] == "")
            {
                gotoxy(2, 8);
                cout << "You have not entered any customer data yet.";
                Sleep(2000);
                system("cls");
                goto val3;
            }
            else
            {
                update_customer_info(id);
                system("cls");
                Sleep(300);
                goto val3;
            }
        }
        else if (admin_op == 4)
        {
            system("cls");
            gotoxy(2, 4);
            string id;
            cout << "Which Customer data you want to Delete (Enter Customer ID): ";
            cin >> id;
            if (customer_id[0] == "")
            {
                gotoxy(2, 6);
                cout << "You have not entered any customer data yet.";
                Sleep(2000);
                system("cls");
                goto val3;
            }
            else
            {
                delete_customer(id);
                system("cls");
                Sleep(300);
                goto val3;
            }
        }
        else if (admin_op == 5)
        {
            system("cls");
            gotoxy(2, 4);
            string id;
            cout << "Which Customer data you want to see (Enter Customer ID): ";
            cin >> id;
            if (customer_id[0] == "")
            {
                gotoxy(2, 8);
                cout << "You have not entered any customer data yet.";
                Sleep(2000);
                system("cls");
                goto val3;
            }
            else
            {
                search_customer(id);
                system("cls");
                Sleep(300);
                goto val3;
            }
        }
        else if (admin_op == 6)
        {
            system("cls");
            register_admin();
            system("cls");
            goto val3;
        }
        else if (admin_op == 7)
        {
            system("cls");
            goto val2;
        }
        else if (admin_op == 8)
        {
            system("cls");
            exit_menu();
        }
    }
    else if (user_type == 2)
    {
        cust_op = cust_menu();
        if (cust_op == 1)
        {
            system("cls");
            room_booking();
            system("cls");
            Sleep(300);
            goto val3;
        }
        else if (cust_op == 2)
        {
            system("cls");
            check_in();
            system("cls");
            Sleep(300);
            goto val3;
        }
        else if (cust_op == 3)
        {
            system("cls");
            check_out();
            system("cls");
            Sleep(300);
            goto val3;
        }
        else if (cust_op == 4)
        {
            system("cls");
            goto val2;
        }
        else if (cust_op == 5)
        {
            system("cls");
            exit_menu();
        }
    }
    else
    {
        cout << "    INVALID CHOICE !!!!!";
        Sleep(1000);
        system("cls");
        goto val2;
    }
}

// Function Definitions
void update_data(string filename, string name[], string email[], string password[], int &count)
{
    fstream file;
    string line;
    file.open(filename, ios::out);
    file << "";
    file.close();
    file.open(filename, ios::app);
    for (int i = 0; i < count; i++)
    {
        if (i != 0)
            file << endl;
        file << name[i] << ";" << email[i] << ";" << password[i];
    }
    file.close();
}

void get_data(string filename, string name[], string email[], string password[], int &count)
{
    fstream file;
    string line;
    file.open(filename, ios::in);
    count = 0;
    while (getline(file, line))
    {
        name[count] = getField(line, 1);
        email[count] = getField(line, 2);
        password[count] = getField(line, 3);
        count++;
    }
    file.close();
}
string getField(string record, int field)

{
    int commaCount = 1;
    string item;
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ';')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}
void gotoxy(int X, int Y)
{
    COORD coordinates;
    coordinates.X = X;
    coordinates.Y = Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void print_header()
{
    cout << "             |$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|" << endl;
    Sleep(60);
    cout << "             |***********************************************************************************************************************************|" << endl;
    Sleep(60);
    cout << "             |***************************************      HOTEL     MANAGEMENT        SYSTEM     ***********************************************|" << endl;
    Sleep(60);
    cout << "             |***********************************************************************************************************************************|" << endl;
    Sleep(60);
    cout << "             |$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|" << endl;
}

void sign_up_menu()
{
    string username, email, password;
up:
    system("cls");
    print_header();
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     SIGN UP      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    print_box();
    gotoxy(20, 20);
    cout << "Enter User  Name :  ";
    cin >> username;
    if (!is_alpha(username))
    {
        cout << "Invalid Input";
        goto up;
    }
    gotoxy(20, 22);
    cout << "Enter Email :  ";
    cin >> email;
    gotoxy(20, 24);
    cout << "Enter Password :  ";
    cin >> password;
    if (!is_integer(password))
    {
        cout << "Invalid Input";
        goto up;
    }
    cust_name[total_customers] = username;
    cust_email[total_customers] = email;
    cust_password[total_customers] = password;
    total_customers++;
    update_data("customers.txt", cust_name, cust_email, cust_password, total_customers);
    gotoxy(20, 28);
    cout << "Loading Please Wait .....";
    Sleep(3000);
    gotoxy(28, 32);
    cout << "         PRESS   ANY   KEY TO CONTINUE ";
    getch();
}
void register_admin()
{
    if (total_admins < 3)
    {

        string username, email, password;
    up:
        system("cls");
        print_header();
        cout << endl
             << endl
             << endl
             << endl;
        cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     SIGN UP      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        print_box();
        gotoxy(20, 20);
        cout << "Enter User  Name :  ";
        cin >> username;
        if (!is_alpha(username))
        {
            cout << "Invalid Input";
            goto up;
        }
        gotoxy(20, 22);
        cout << "Enter Email :  ";
        cin >> email;
        gotoxy(20, 24);
        cout << "Enter Password :  ";
        cin >> password;
        if (!is_integer(password))
        {
            cout << "Invalid Input";
            goto up;
        }
        admin_name[total_admins] = username;
        admin_email[total_admins] = email;
        admin_password[total_admins] = password;
        total_admins++;
        update_data("admins.txt", admin_name, admin_email, admin_password, total_admins);
        gotoxy(20, 28);
        cout << "Loading Please Wait .....";
        Sleep(3000);
        gotoxy(28, 32);
        cout << "         PRESS   ANY   KEY TO CONTINUE ";
        getch();
    }
    else
    {
        gotoxy(20, 20);
        cout << "Can't add more admins";
        gotoxy(28, 32);
        cout << "         PRESS   ANY   KEY TO CONTINUE ";
        getch();
    }
}
bool is_integer(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}
bool is_alpha(string s)
{
    if (s.size() == 0)
        return false;
    for (int i = 0; i < s.size(); i++)
    {
        if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] == ' ')))
            return false;
    }
    return true;
}
int is_registered(string email)
{
    for (int i = 0; i < total_admins; i++)
    {
        if (admin_email[i] == email)
        {
            user_type = 1;
            return i;
        }
    }
    for (int i = 0; i < total_customers; i++)
    {
        if (cust_email[i] == email)
        {
            user_type = 2;
            return i;
        }
    }
    cout << user_type;
    return -1;
}
void Login_menu()
{
value:
    string email, pass;
    int count = 0;
    print_header();
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     LOGIN  MENU    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    print_box();
    gotoxy(20, 20);
    cout << "email :  ";
    cin >> email;
    gotoxy(20, 24);
    cout << "Password :";
    cin >> pass;
    int index = is_registered(email);
    if (index != -1)
    {
        if (user_type == 1)
        {
            if (admin_password[index] != pass)
            {
                gotoxy(20, 28);
                cout << "INVALID PASSWORD !!!!!!" << endl;
                Sleep(1000);
                count++;
            }
        }
        else if (user_type == 2)
        {
            if (cust_password[index] != pass)
            {
                gotoxy(20, 28);
                cout << "INVALID PASSWORD !!!!!!" << endl;
                Sleep(1000);
                count++;
            }
        }
        else
        {
            gotoxy(20, 28);
            cout << "Loading Please Wait .....";
            Sleep(3000);
            gotoxy(28, 32);
            cout << "         PRESS   ANY   KEY TO CONTINUE ";
            getch();
        }
    }
    else if (index == -1)
    {
        gotoxy(20, 28);
        cout << "INVALID USER NAME !!!!!!!" << endl;
        Sleep(1000);
        count++;
    }
    // if (user_name != email && password != pass)
    // {
    //     gotoxy(20, 28);
    //     cout << "INVALID USER NAME AND PASSWORD !!!!!!" << endl;
    //     Sleep(1000);
    //     count++;
    // }
    // else if (user_name != email)
    // {
    //     gotoxy(20, 28);
    //     cout << "INVALID USER NAME !!!!!!!" << endl;
    //     Sleep(1000);
    //     count++;
    // }
    // else if (password != pass)
    // {
    //     gotoxy(20, 28);
    //     cout << "INVALID  PASSWORD !!!!!!" << endl;
    //     Sleep(1000);
    //     count++;
    // }

    if (count != 0)
    {
        system("cls");
        goto value;
    }
}

void print_box()
{
    gotoxy(15, 18);
    cout << " ------------------------------------------------------------------------------" << endl;
    gotoxy(15, 19);
    cout << " |                                                                            |" << endl;
    gotoxy(15, 20);
    cout << " |                                                                            |" << endl;
    gotoxy(15, 21);
    cout << " |                                                                            |" << endl;
    gotoxy(15, 22);
    cout << " |                                                                            |" << endl;
    gotoxy(15, 23);
    cout << " |                                                                            |" << endl;
    gotoxy(15, 24);
    cout << " |                                                                            |" << endl;
    gotoxy(15, 25);
    cout << " |                                                                            |" << endl;
    gotoxy(15, 26);
    cout << " ------------------------------------------------------------------------------" << endl;
}

int admin_menu()
{
    print_header();
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     CHOICE  MENU    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    int op;
    gotoxy(20, 16);
    cout << "PRESS 1. Add Customer ";
    gotoxy(20, 18);
    cout << "PRESS 2. View All Customers ";
    gotoxy(20, 20);
    cout << "PRESS 3. Update Customer Info ";
    gotoxy(20, 22);
    cout << "PRESS 4. Delete Customer ";
    gotoxy(20, 24);
    cout << "PRESS 5. Search Customer ";
    gotoxy(20, 26);
    cout<< "PRESS 6. Register admins";
    gotoxy(20, 28);
    cout << "PRESS 7. Logout ";
    gotoxy(20, 30);
    cout << "PRESS 8. Exit ";
    gotoxy(20, 32);
    cout << "Enter Your Choice : ";
    gotoxy(40, 32);
    cin >> op;
    return op;
}
int cust_menu()
{
    print_header();
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     CHOICE  MENU    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    int op;
    gotoxy(20, 16);
    cout << "PRESS 1. Room Booking ";
    gotoxy(20, 18);
    cout << "PRESS 2. Check-in ";
    gotoxy(20, 20);
    cout << "PRESS 3. Check-out ";
    gotoxy(20, 22);
    cout << "PRESS 4. Back ";
    gotoxy(20, 24);
    cout << "PRESS 5. Exit ";
    gotoxy(20, 26);
    cout << "Enter Your Choice : ";
    gotoxy(20, 36);
    cin >> op;
    return op;
}
int anonymous_menu()
{
    print_header();
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     CHOICE  MENU    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    int op;
    gotoxy(20, 16);
    cout << "PRESS 1. Sign In ";
    gotoxy(20, 18);
    cout << "PRESS 2. Sign Up ";
    gotoxy(20, 20);
    cout << "Enter Your Choice : ";
    gotoxy(20, 36);
    cin >> op;
    return op;
}
void add_customer(int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << endl
             << endl
             << endl
             << endl;
        cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     ADD  RECORD      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        gotoxy(20, 16);
        cout << "Enter the Record of Customer " << i + 1 << "  " << endl;
        string name, ID, address, contact, room;
        Sleep(100);
        gotoxy(20, 18);
        cout << "Enter Customer Name: ";
        cin >> customer_name[i];
        Sleep(100);
        gotoxy(20, 19);
        cout << "Enter Customer ID: ";
        cin >> customer_id[i];
        Sleep(100);
        gotoxy(20, 20);
        cout << "Enter Address: ";
        cin >> customer_address[i];
        Sleep(100);
        gotoxy(20, 21);
        cout << "Enter Cell No: ";
        cin >> customer_cell[i];
        Sleep(100);
        gotoxy(20, 22);
        cout << "Enter Room ID: ";
        cin >> room_id[i];
        system("cls");
    }
    gotoxy(20, 26);
    cout << "Press Any Key To Exit : ";
    getch();
}
void show_customer_data()
{
    bool found = false;
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     SHOW  RECORD      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    gotoxy(20, 16);
    cout << "Customer ID";
    gotoxy(40, 16);
    cout << "Customer Name";
    gotoxy(60, 16);
    cout << "Customer Address";
    gotoxy(80, 16);
    cout << "Customer Contact";
    gotoxy(100, 16);
    cout << "Room ID";
    for (int i = 0; customer_id[i] != ""; i++)
    {
        gotoxy(22, 18 + i);
        cout << customer_id[i];
    }
    for (int j = 0; customer_name[j] != ""; j++)
    {
        gotoxy(42, 18 + j);
        cout << customer_name[j];
    }
    for (int k = 0; customer_address[k] != ""; k++)
    {
        gotoxy(62, 18 + k);
        cout << customer_address[k];
    }
    for (int l = 0; customer_cell[l] != ""; l++)
    {
        gotoxy(82, 18 + l);
        cout << customer_cell[l];
    }
    for (int m = 0; room_id[m] != ""; m++)
    {
        gotoxy(102, 18 + m);
        cout << room_id[m];
    }
    Sleep(1000);
    gotoxy(24, 30);
    cout << "Press Any Key To Exit : ";
    getch();
}
void update_customer_info(string id)
{
    bool found = false;
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     UPDATE  RECORD      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    for (int i = 0; customer_id[i] != "\0"; i++)
    {
        if (customer_id[i] == id)
        {
            gotoxy(20, 14);
            cout << "You Want to Update the record of customer id : " << customer_id[i];
            gotoxy(20, 18);
            cout << "Enter Customer Name : ";
            cin >> customer_name[i];
            Sleep(100);
            gotoxy(20, 20);
            cout << "Update Address: ";
            cin >> customer_address[i];
            Sleep(100);
            gotoxy(20, 22);
            cout << "Update Cell No: ";
            cin >> customer_cell[i];
            Sleep(100);
            gotoxy(20, 24);
            cout << "Update Room ID: ";
            cin >> room_id[i];
            Sleep(100);
            gotoxy(20, 26);
            cout << "Record Updated Successfully";
        }
    }
    if (found == false)
    {
        gotoxy(20, 24);
        cout << "Customer With id " << id << " Does not exist : ";
    }
    gotoxy(24, 30);
    cout << "Press Any Key To Exit : ";
    getch();
}
void delete_customer(string id)
{
    bool found = false;
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     DELETE  RECORD      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    for (int i = 0; customer_id[i] != "\0"; i++)
    {
        if (customer_id[i] == id)
        {
            customer_name[i] = "***";
            customer_id[i] = "***";
            customer_address[i] = "***";
            customer_cell[i] = "***";
            room_id[i] = "***";
            gotoxy(24, 20);
            cout << "Deleting Record .....";
            Sleep(1000);
            gotoxy(24, 24);
            cout << "Record Deleted Successfully ";
            Sleep(1000);
            found = true;
        }
    }
    if (found == false)
    {
        gotoxy(20, 24);
        cout << "Customer With id " << id << " Does not exist : ";
    }
    gotoxy(24, 28);
    cout << "Press Any Key To Exit : ";
    getch();
}
void search_customer(string id)
{
    bool found = false;
    cout << endl
         << endl
         << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     SHOW  RECORD      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    for (int i = 0; customer_id[i] != "\0"; i++)
    {
        if (customer_id[i] == id)
        {
            gotoxy(20, 16);
            cout << "You Want to search the record of customer id : " << customer_id[i];
            gotoxy(20, 20);
            cout << "Customer Name : " << customer_name[i];
            gotoxy(20, 22);
            cout << "Customer ID : " << customer_id[i];
            gotoxy(20, 24);
            cout << "Customer Adress : " << customer_address[i];
            gotoxy(20, 26);
            cout << "Customer Contact : " << customer_cell[i];
            gotoxy(20, 28);
            cout << "Room ID: " << room_id[i];
            Sleep(1000);
            found = true;
        }
    }
    if (found == false)
    {
        gotoxy(20, 24);
        cout << "Customer With id " << id << " Does not exist : ";
    }
    gotoxy(24, 31);
    cout << "Press Any Key To Exit : ";
    getch();
}
void room_booking()
{
    string cust_id, roo_id;
    bool room_found = false;
    gotoxy(20, 16);
    cout << "Enter Customer ID for Room Booking: ";
    cin >> cust_id;

    // Find customer
    for (int i = 0; customer_id[i] != ""; i++)
    {
        if (cust_id == customer_id[i])
        {
            room_found = true;
            gotoxy(20, 18);
            cout << "Enter Room ID for Booking: ";
            cin >> roo_id;
            // Assign room
            for (int j = 0; j < 20; j++)
            {
                if (room_id[j] == roo_id)
                {
                    room_id[j] = roo_id;
                    room_status[j] = "Occupied";
                    break;
                }
            }
            gotoxy(20, 20);
            cout << "Room booked successfully!";
            Sleep(1000);
            break;
        }
    }
    if (!room_found)
    {
        gotoxy(20, 20);
        cout << "Customer not found!";
        Sleep(1000);
    }
}

void check_in()
{
    string cust_id, roo_id;
    bool found = false;
    gotoxy(20, 16);
    cout << "Enter Customer ID for Check-in: ";
    cin >> cust_id;
    gotoxy(20, 18);
    cout << "Enter Room ID for Check-in: ";
    cin >> roo_id;

    for (int i = 0; i < 20; i++)
    {
        if (cust_id == customer_id[i] && roo_id == room_id[i] && room_status[i] == "Available")
        {
            room_status[i] = "Occupied";
            found = true;
            gotoxy(20, 20);
            cout << "Check-in successful!";
            break;
        }
    }
    if (!found)
    {
        gotoxy(20, 20);
        cout << "Room or Customer not found!";
    }
    Sleep(1000);
}

void check_out()
{
    string cust_id, roo_id;
    bool found = false;
    gotoxy(20, 16);
    cout << "Enter Customer ID for Check-out: ";
    cin >> cust_id;
    gotoxy(20, 18);
    cout << "Enter Room ID for Check-out: ";
    cin >> roo_id;
    for (int i = 0; i < 20; i++)
    {
        if (cust_id == customer_id[i] && roo_id == room_id[i] && room_status[i] == "Occupied")
        {
            room_status[i] = "Available";
            found = true;
            gotoxy(20, 20);
            cout << "Check-out successful!";
            break;
        }
    }
    if (!found)
    {
        gotoxy(20, 20);
        cout << "Room or Customer not found!";
    }
    Sleep(1000);
}
void exit_menu()

{
    cout << endl
         << endl;
    cout << "                                   @@@@@@@@@@@@@@@@@@@@@@@@@     EXIT  MENU     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << endl
         << endl;
    cout << endl
         << endl;
    cout << endl
         << endl;
    cout << "                @@@@@@@ @   @  @@  @@    @ @   @         @   @  @@  @  @    @" << endl;
    Sleep(70);
    cout << "                   @    @   @ @  @ @ @   @ @  @          @   @ @  @ @  @    @" << endl;
    Sleep(70);
    cout << "                   @    @@@@@ @@@@ @  @  @ @@@            @@@  @  @ @  @    @" << endl;
    Sleep(70);
    cout << "                   @    @   @ @  @ @   @ @ @  @            @   @  @ @  @     " << endl;
    Sleep(70);
    cout << "                   @    @   @ @  @ @    @@ @   @           @    @@   @@     @" << endl;
    Sleep(70);
    cout << endl
         << endl;
    cout << "              @@@@@@@@  @@@   @@@@@           @   @   @@@   @@@@@@@@  @@     @   @@@           @  @     @@   @@   @@@ " << endl;
    Sleep(70);
    cout << "              @	       @   @  @    @          @   @  @   @      @     @ @    @  @   @          @  @     @ @ @ @  @   @" << endl;
    Sleep(70);
    cout << "              @@@@@@   @   @  @    @          @   @   @         @     @  @   @  @              @@@@     @  @  @   @    " << endl;
    Sleep(70);
    cout << "              @        @   @  @@@@@           @   @    @        @     @   @  @  @  @@          @  @     @     @    @     " << endl;
    Sleep(70);
    cout << "              @        @   @  @    @          @   @ @   @       @     @    @ @  @   @          @  @     @     @  @   @  " << endl;
    Sleep(70);
    cout << "              @         @@@   @     @@         @@@   @@@    @@@@@@@@  @     @@   @@@           @  @     @     @   @@@  " << endl;
    gotoxy(2, 35);
}

void print_front()
{
    cout << endl
         << endl
         << endl
         << endl;
    cout << "			         ********************************************************************************************************************************" << endl;
    Sleep(80);
    cout << "			    ******************************************************************************************************************************************" << endl;
    Sleep(80);
    cout << "			  *********************************************************************************************************************************************** " << endl;
    Sleep(80);
    cout << "			*************|----------------------------------------------------------------------------------------------------------------|********************" << endl;
    Sleep(80);
    cout << "			*************|                                                                                                                |********************" << endl;
    Sleep(80);
    cout << "			*************| @@   @@      @@     @@@@@@  @@ @@@@   @@            @@   @@  @@  @@    @  @@   @@  @@   @@ @@@@ @@    @ @@@@@  |********************" << endl;
    Sleep(80);
    cout << "			*************| @@   @@    @    @     @     @@        @@            @ @ @ @ @  @ @ @   @ @  @ @    @ @ @ @ @    @ @   @   @    |********************" << endl;
    Sleep(80);
    cout << "			*************| @ @@ @@    @    @     @     @@ @@@@   @@            @  @  @ @@@@ @  @  @ @@@@ @ @@ @  @  @ @@@  @  @  @   @    |********************" << endl;
    Sleep(80);
    cout << "			*************| @@   @@    @    @     @     @@        @@            @     @ @  @ @   @ @ @  @ @  @ @     @ @    @   @ @   @    |********************" << endl;
    Sleep(80);
    cout << "			*************| @@   @@     @  @      @     @@ @@@@   @@@@@@@       @     @ @  @ @    @@ @  @  @@  @     @ @@@@ @    @@   @    |********************" << endl;
    Sleep(80);
    cout << "			*************|                                                                                                                |********************" << endl;
    Sleep(80);
    cout << "			*************|                                          @@@  @   @  @@@ @@@@@ @@@@@ @@   @@                                   |********************" << endl;
    Sleep(80);
    cout << "			*************|                                         @     @   @ @      @   @     @ @ @ @                                   |********************" << endl;
    Sleep(80);
    cout << "			*************|                                          @@     @    @@    @   @@@@  @  @  @                                   |********************" << endl;
    Sleep(80);
    cout << "			*************|                                            @    @      @   @   @     @     @                                   |********************" << endl;
    Sleep(80);
    cout << "			*************|                                         @@@     @   @@@    @   @@@@@ @     @                                   |********************" << endl;
    Sleep(80);
    cout << "			**************----------------------------------------------------------------------------------------------------------------|********************" << endl;
    Sleep(80);
    cout << "			***************************************************************************************************************************************************" << endl;
    Sleep(80);
    cout << "			**************************************************************************************************************************************************" << endl;
    Sleep(80);
    cout << "			 *********************************************************************************************************************************************** " << endl;
    Sleep(80);
    cout << "			    ****************************************************************************************************************************************" << endl;
    Sleep(80);
    cout << "			         ******************************************************************************************************************************  " << endl;
}

void disply_front()
{

    system("cls");
    system("color 02");
    print_front();
    Sleep(700);
    system("cls");
    system("color 03");
    print_front();
    Sleep(700);
    system("cls");
    system("color 05");
    print_front();
    Sleep(700);
    system("color 07");
    cout << endl
         << endl
         << endl
         << endl
         << endl;
    system("color 07");
    cout << "                                                     PRESS   ANY   KEY TO CONTINUE ";
    getch();
    system("cls");
}