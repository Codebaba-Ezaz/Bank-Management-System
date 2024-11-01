
/* Author: Ezaz Ahmed Sayem (github: github.com/Codebaba-Ezaz*/

#include <bits/stdc++.h>
#include <windows.h>
#include <openssl/sha.h>

using namespace std;
void menu();
void close();
void saveAccountNumber(int acc_no);
bool isAccountNumberExist(int acc_no);
string hashFunction(int acc_no);
int main_exit;
struct date
{
    int month, day, year;
};
const int TABLE_SIZE = 100;
const int TRUNCATED_HASH_SIZE = 8;
struct customer
{
    string name1, name2;
    int acc_no, age;
    string address;
    string NID;
    string phone;
    string acc_type;
    float amt;
    date dob;
    date deposit;
} add, upd, check, rem, transaction;

float interest(float t, float amount, int rate)
{
    float SI;
    SI = (float)(rate * t * amount) / 100;
    return (SI);
}

void errorMessage()
{
    cout << "+++!!!You selected an invalid number!!!+++\n";
}

void dep_dobInfo()
{
    char c='/';
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    add.deposit.day = localTime->tm_mday;
    add.deposit.month = localTime->tm_mon + 1;
    add.deposit.year = localTime->tm_year + 1900;
    cout << "\n\n\n Today's date(mm/dd/yyyy):";
    cout << add.deposit.month <<c<< add.deposit.day<<c << add.deposit.year<<endl;
dob_date:
    cout << "\nEnter the date of birth(mm/dd/yyyy):";
    cin >> add.dob.month >>c>> add.dob.day>>c >> add.dob.year;
    if (add.dob.month <= 0 || add.dob.month > 12 || add.dob.day <= 0 || add.dob.day > 31 || add.dob.year <= 0 || add.dob.year >= add.deposit.year)
    {
        cout << "Sorry, this month/day/year is invalid. Please try again!";
        Sleep(1000);
        system("cls");
        goto dob_date;
    }
}

int age()
{
    dep_dobInfo();
    int d, m, y, x;
    d = add.deposit.day - add.dob.day;
    m = add.deposit.month - add.dob.month;
    y = add.deposit.year - add.dob.year;
    x = d;
    if (d < 0)
    {
        d = 31 + d;
    }
    else
        d = add.deposit.day - add.dob.day;
    if (m <= 0)
    {
        if (x < 0)
        {
            m = 11 + m;
            y = y - 1;
        }
        if (x > 0)
        {
            y = y - 1;
            m = m + 12;
        }
    }
    else
    {
        m = add.deposit.month - add.dob.month;
    }
    return y;
}

void new_acc()
{
    int choice;
    ofstream ptr;
    ptr.open("BankRecord.txt", ios::app);
    system("cls");
    cout << "\t\t\t==== ADD RECORD  ====\n";
Again:
    add.age = age();
    cout << "\nEnter the age: " << add.age;
    if (add.age < 18)
    {
        cout << "\nSorry, you are not 18. So you can't create an account. Thank you.";
        Sleep(2000);
        system("cls");
        goto Again;
    }
    else
    {
        cout << "\nYou are eligible to create an account.";
    }
    Sleep(3000);
    system("cls");
account_no:
    cout << "\nEnter the account number:";
    cin >> check.acc_no;
    if (isAccountNumberExist(check.acc_no))
    {
        cout << "Account number already in use!";
        goto account_no;
    }
    add.acc_no = check.acc_no;
    cout << "\nEnter the First name: ";
    cin >> add.name1;
    cout << "\nEnter the Last name: ";
    cin >> add.name2;
    cout << "\nEnter the address:";
    cin.ignore();
    cin.clear();
    getline(cin,add.address);
    cout << "\nEnter the NID number:";
    cin >> add.NID;
    cout << "\nEnter the phone number: ";
    cin >> add.phone;
    cout << "\nEnter the amount to deposit:TK. ";
    cin >> add.amt;
acctype:
    cout << "\nType of account:\n\t[1]Saving\n\t[2]Current\n\t[3]Fixed2(for 2 year)\n\t[4]Fixed4(for 4 years)\n\t[5]Fixed5(for 5 years)\n\n\tEnter your choice:";
    cin >> add.acc_type;
    if (add.acc_type=="Saving" || add.acc_type== "Current" || add.acc_type== "Fixed2" || add.acc_type== "Fixed4" || add.acc_type== "Fixed5")
    {
        cout << "Please wait we are checking the account type you have given";
        for (int i = 0; i <= 5; i++)
        {
            cout << ". ";
            Sleep(1000);
        }
        cout << "\n\t\tOk, it is Valid";
    }
    else
    {
        cout << "Sorry, this is not a valid account type. Please try again.";
        Sleep(1000);
        system("cls");
        goto acctype;
    }

    ptr << add.acc_no << " " << add.name1 << " " << add.name2 << " " << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << " " << add.age << " " << add.address << " " << add.NID << " " << add.phone << " " << add.acc_type << " " << add.amt << " " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << endl;
    saveAccountNumber(check.acc_no);
    ptr.close();
    cout << "\nAccount created successfully!";

add_invalid:
    cout << "\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:";
    cin >> main_exit;
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        cout << "\nInvalid!";
        goto add_invalid;
    }
}
void view_list()
{
    char c='/';
    ifstream view;
    view.open("BankRecord.txt", ios::in);
    int test = 0;
    system("cls");
    cout << "\nACC. NO.\tNAME\t\t\tADDRESS\t\t\tPHONE\n";

    while (view >> add.acc_no >> add.name1 >> add.name2 >> add.dob.month >>c>> add.dob.day>>c>> add.dob.year>> add.age >> add.address >> add.NID >> add.phone >> add.acc_type >> add.amt >> add.deposit.month>>c>> add.deposit.day>>c>> add.deposit.year)
    {
        cout << "\n" << add.acc_no << "\t " << add.name1 << " " << add.name2 << "\t\t\t" << add.address << "\t" << add.phone;
        test++;
    }

    view.close();
    if (test == 0)
    {
        system("cls");
        cout << "\nNO RECORDS!!\n";
    }

view_list_invalid:
    cout << "\n\nEnter 1 to go to the main menu and 0 to exit:";
    cin >> main_exit;
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        errorMessage();
        goto view_list_invalid;
    }
}
void edit()
{
    char c='/';
    int choice, test = 0;
    ifstream old;
    ofstream newrec;
    old.open("BankRecord.txt", ios::in);
    newrec.open("NewBankrecord.txt", ios::app);

    cout << "\nEnter the account no. of the customer whose info you want to change:";
    cin >> upd.acc_no;
    while (old >> add.acc_no >> add.name1 >> add.name2 >> add.dob.month >>c>> add.dob.day>>c>> add.dob.year>> add.age >> add.address >> add.NID >> add.phone >> add.acc_type >> add.amt >> add.deposit.month>>c>> add.deposit.day>>c>> add.deposit.year)
    {
        if (add.acc_no == upd.acc_no)
        {
            test = 1;
            cout << "\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):";
            cin >> choice;
            system("cls");
            if (choice == 1)
            {
                cout << "Enter the new address:";
                cin >> upd.address;
                newrec << add.acc_no << " " << add.name1 << " " << add.name2 << " " << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << " " << add.age << " " << upd.address << " " << add.NID << " " << add.phone << " " << add.acc_type << " " << add.amt << " " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << "\n";
                system("cls");
                cout << "Changes saved!";
            }
            else if (choice == 2)
            {
                cout << "Enter the new phone number:";
                cin >> upd.phone;
                newrec << add.acc_no << " " << add.name1 << " " << add.name2 << " " << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << " " << add.age << " " << add.address << " " << add.NID << " " << upd.phone << " " << add.acc_type << " " << add.amt << " " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << "\n";
                system("cls");
                cout << "Changes saved!";
            }
        }
        else
            newrec << add.acc_no << " " << add.name1 << " " << add.name2 << " " << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << " " << add.age << " " << add.address << " " << add.NID << " " << add.phone << " " << add.acc_type << " " << add.amt << " " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << "\n";
    }
    old.close();
    newrec.close();
    remove("BankRecord.txt");
    rename("NewBankrecord.txt", "BankRecord.txt");

    if (test != 1)
    {
        system("cls");
        cout << "\nRecord not found!!";
edit_invalid:
        cout << "\nEnter 0 to try again,1 to return to the main menu and 2 to exit:";
        cin >> main_exit;
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            edit();
        else
        {
            errorMessage();
            Sleep(1000);
            system("cls");
            goto edit_invalid;
        }
    }
    else
    {
t:
        cout << "\n\n\nEnter 1 to go to the main menu and 0 to exit:";
        cin >> main_exit;
        system("cls");
        if (main_exit == 1)
            menu();
        else if(main_exit==0)
            close();
        else
            errorMessage();
        Sleep(1000);
        system("cls");
        goto t;
    }
}
void transact()
{
    char c='/';
    int choice, test = 0;
    ifstream old;
    ofstream newrec;
    old.open("BankRecord.txt", ios::in);
    newrec.open("NewBankrecord.txt", ios::app);

    cout << "Enter the account no. of the customer:";
    cin >> transaction.acc_no;
    while (old >> add.acc_no >> add.name1 >> add.name2 >> add.dob.month >>c>> add.dob.day>>c>> add.dob.year>> add.age >> add.address >> add.NID >> add.phone >> add.acc_type >> add.amt >> add.deposit.month>>c>> add.deposit.day>>c>> add.deposit.year)
    {
        if (add.acc_no == transaction.acc_no)
        {
            test = 1;
            if (add.acc_type== "Fixed2" || add.acc_type== "Fixed4" || add.acc_type== "Fixed5")
            {
                cout << "\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!";
                Sleep(3000);
                system("cls");
                menu();
            }
Again:
            cout << "\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):";
            cin >> choice;
            if (choice == 1)
            {
deposit:
                cout << "Enter the amount you want to deposit:TK.  ";
                cin >> transaction.amt;
                if (transaction.amt < 0)
                {
                    cout << "Sorry you cannot deposit this amount";
                    Sleep(2000);
                    system("cls");
                    goto deposit;
                }
                add.amt += transaction.amt;
                newrec << add.acc_no << " " << add.name1 << " " << add.name2 << " " << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << " " << add.age << " " << add.address << " " << add.NID << " " << add.phone << " " << add.acc_type << " " << add.amt << " " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << "\n";
                cout << "\n\nDeposited successfully!";
            }
            else if(choice==2)
            {
withdraw:
                cout << "Enter the amount you want to withdraw:TK.  ";
                cin >> transaction.amt;
                if (add.amt < transaction.amt)
                {
                    cout << "Sorry you cannot withdraw this amount";
                    Sleep(2000);
                    system("cls");
                    goto withdraw;
                }
                add.amt -= transaction.amt;
                newrec << add.acc_no << " " << add.name1 << " " << add.name2 << " " << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << " " << add.age << " " << add.address << " " << add.NID << " " << add.phone << " " << add.acc_type << " " << add.amt << " " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << "\n";
                cout << "\n\nWithdrawn successfully!";
            }
            else
            {
                cout<<"Invalid Choice!!"<<endl;
                Sleep(2000);
                system("cls");
                goto Again;
            }
        }
        else
        {
            newrec << add.acc_no << " " << add.name1 << " " << add.name2 << " " << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << " " << add.age << " " << add.address << " " << add.NID << " " << add.phone << " " << add.acc_type << " " << add.amt << " " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << "\n";
        }
    }
    old.close();
    newrec.close();
    remove("BankRecord.txt");
    rename("NewBankrecord.txt", "BankRecord.txt");
    if (test != 1)
    {
        cout << "\n\nRecord not found!!";
transact_invalid:
        cout << "\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:";
        cin >> main_exit;
        system("cls");
        if (main_exit == 0)
            transact();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else
        {
            cout << "\nInvalid!";
            goto transact_invalid;
        }
    }
    else
    {
        cout << "\nEnter 1 to go to the main menu and 0 to exit:";
        cin >> main_exit;
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}
void erase()
{
    char c='/';
    ifstream old, hashFile;
    ofstream newrec, newHashFile;
    int test = 0;
    old.open("BankRecord.txt", ios::in);
    newrec.open("NewBankrecord.txt", ios::app);
    hashFile.open("HashTable.txt", ios::in);
    newHashFile.open("NewHashTable.txt", ios::app);

    cout << "Enter the account no. of the customer you want to delete:";
    cin >> rem.acc_no;
    while (old >> add.acc_no >> add.name1 >> add.name2 >> add.dob.month >>c>> add.dob.day>>c>> add.dob.year>> add.age >> add.address >> add.NID >> add.phone >> add.acc_type >> add.amt >> add.deposit.month>>c>> add.deposit.day>>c>> add.deposit.year)
    {
        if (add.acc_no != rem.acc_no)
        {
            newrec << add.acc_no << " " << add.name1 << " " << add.name2 << " " << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << " " << add.age << " " << add.address << " " << add.NID << " " << add.phone << " " << add.acc_type << " " << add.amt << " " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << "\n";
        }
    }
    int stored_acc_no;
    string hashKey;
    while (hashFile >> stored_acc_no >> hashKey)
    {
        if (stored_acc_no != rem.acc_no)
        {
            newHashFile << stored_acc_no << " " << hashKey << endl;
        }
        else
        {
            test++;
        }
    }

    old.close();
    newrec.close();
    hashFile.close();
    newHashFile.close();
    remove("BankRecord.txt");
    remove("HashTable.txt");

    rename("NewBankrecord.txt", "BankRecord.txt");
    rename("NewHashTable.txt", "HashTable.txt");

    cout << "\nRecord Deleted!!";
    Sleep(2000);

    if (test == 0)
    {
        cout << "\nRecord not found!!";
erase_invalid:
        cout << "\nEnter 0 to try again,1 to return to main menu and 2 to exit:";
        cin >> main_exit;

        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            erase();
        else
        {
            cout << "\nInvalid!";
            goto erase_invalid;
        }
    }
    else
    {
        cout << "\nEnter 1 to go to the main menu and 0 to exit:";
        cin >> main_exit;
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

void see()
{
    char c='/';
    ifstream ptr;
    int test = 0, rate;
    int choice;
    float time;
    float intrst;
    ptr.open("BankRecord.txt", ios::in);
    cout << "Enter the account no. of the customer whose info you want to search:";
    cin >> check.acc_no;

    while (ptr >> add.acc_no >> add.name1 >> add.name2 >> add.dob.month >>c>> add.dob.day>>c>> add.dob.year>> add.age >> add.address >> add.NID >> add.phone >> add.acc_type >> add.amt >> add.deposit.month>>c>> add.deposit.day>>c>> add.deposit.year)
    {
        if (add.acc_no == check.acc_no)
        {
            system("cls");
            test = 1;

            cout << "\nAccount NO.:" << add.acc_no << "\nName:" << add.name1 << " " << add.name2 << "\nDOB:" << add.dob.month << "/" << add.dob.day << "/" << add.dob.year << "\nAge:" << add.age << "\nAddress:" << add.address << "\nNID No:" << add.NID << "\nPhone number:" << add.phone << "\nType Of Account:" << add.acc_type << "\nAmount deposited:TK. " << add.amt << "\nDate Of Deposit:" << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year << "\n\n";
            if (add.acc_type== "Fixed2")
            {
                time = 2.0;
                rate = 9;
                intrst = interest(time, add.amt, rate);
                cout << "\nYou will get TK. " << intrst << " as interest on " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year + 2;
            }
            else if (add.acc_type== "Fixed4")
            {
                time = 4.0;
                rate = 11;
                intrst = interest(time, add.amt, rate);
                cout << "\nYou will get TK. " << intrst << " as interest on " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year + 4;
            }
            else if (add.acc_type== "Fixed5")
            {
                time = 5.0;
                rate = 13;
                intrst = interest(time, add.amt, rate);
                cout << "\nYou will get TK. " << intrst << " as interest on " << add.deposit.month << "/" << add.deposit.day << "/" << add.deposit.year + 5;
            }
            else if (add.acc_type== "Saving")
            {
                time = (1.0 / 12.0);
                rate = 8;
                intrst = interest(time, add.amt, rate);
                cout << "\nYou will get TK. " << intrst << " as interest on day " << add.deposit.day << " of every month";
            }
            else if (add.acc_type== "Current")
            {
                cout << "\nYou will get no interest";
            }
        }
    }
    ptr.close();
    if (test != 1)
    {
        system("cls");
        cout << "\nRecord not found!!";
see_invalid:
        cout << "\nEnter 0 to try again, 1 to return to the main menu and 2 to exit:";
        cin >> main_exit;
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            see();
        else
        {
            system("cls");
            cout << "\nInvalid!";
            goto see_invalid;
        }
    }
    else
    {
        cout << "\nEnter 1 to go to the main menu and 0 to exit:";
        cin >> main_exit;
    }
    if (main_exit == 1)
    {
        system("cls");
        menu();
    }
    else
    {
        system("cls");
        close();
    }
}
void close()
{
    cout<<"\n\n\n\nThanks Everyone.\nThis programme is brought to you by\n\nGroup Name: Quattuor \n\nGroup Leader: Ezaz Ahmed (C223009)\n\n Members:\n1.Robayat Kalam Farsit (C223007)\n2.Mohammad Sajedul Tasrik (C223017)\n3.MD Zeaul Kader Opel(C223033)";
    return;
}
void menu()
{
    int choice;
    system("cls");
    cout<<"\n\n\t\t\tWelcome to the bank of IIUC";
    cout<<"\n\n\n\t\t\t\ MAIN MENU";
    cout<<"\n\n\t\t[1] Create a new account\n\t\t[2] Update information of existing account\n\t\t[3] Transactions\n\t\t[4] Check the details of existing account\n\t\t[5] Remove existing account\n\t\t[6] View customer's list\n\t\t[7] Exit\n\n\n\t\t Enter your choice:";
    cin>>choice;

    system("cls");
    switch(choice)
    {
    case 1:
        new_acc();
        break;
    case 2:
        edit();
        break;
    case 3:
        transact();
        break;
    case 4:
        see();
        break;
    case 5:
        erase();
        break;
    case 6:
        view_list();
        break;
    case 7:
        close();
        break;
    default:
        errorMessage();
        menu();
        break;
    }
}


string hashFunction(int acc_no)
{
    string acc_no_str = to_string(acc_no);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)acc_no_str.c_str(), acc_no_str.length(), hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

void saveAccountNumber(int acc_no)
{
    ofstream hashFile("HashTable.txt", ios::app);
    string hashKey = hashFunction(acc_no).substr(0, TRUNCATED_HASH_SIZE);
    hashFile << acc_no << " " << hashKey << endl;
    hashFile.close();
}

bool isAccountNumberExist(int acc_no)
{
    ifstream hashFile("HashTable.txt");
    int stored_acc_no;
    string stored_hashKey;
    string hashKey = hashFunction(acc_no).substr(0, TRUNCATED_HASH_SIZE);
    while (hashFile >> stored_acc_no >> stored_hashKey)
    {
        if (stored_hashKey == hashKey)
        {
            hashFile.close();
            return true;
        }
    }
    hashFile.close();
    return false;
}


int main()
{
    string pass,password="pass";
    int i=0;
    cout<<"\n\n\n\t\t\tBank Management System\n\t\t\t\tLogin \n";
    cout<<"\n\n\t\t\t---------------------------";
    cout<<"\n\t\t\t|Please enter the password|";
    cout<<"\n\t\t\t---------------------------\n\t\t\t\t";
    cin>>pass;
    if (pass==password)
    {
        cout<<"\n\n\t\t\tPlease wait";
        for(i=0; i<=5; i++)
        {
            Sleep(300);
            printf(". ");
        }
        cout<<"\n\n\t\t\tPassword Match.";
        Sleep(300);
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n\n\t\tYou will now be redirecting to the main menu";
        for(i=0; i<=5; i++)
        {
            cout<<". ";
            Sleep(300);
        }
        menu();
    }
    else
    {
        cout<<"\n\n\t\t\tPlease wait";
        for(int i=0; i<=7; i++)
        {
            Sleep(300);
            cout<<". ";
        }

        cout<<"\n\n\t\t\tWrong password!! You can't proceed";
login_try:
        cout<<"\nEnter 1 to try again and 0 to exit:";
        scanf("%d",&main_exit);
        if (main_exit==1)
        {

            system("cls");
            main();
        }

        else if (main_exit==0)
        {
            system("cls");
            close();
        }
        else
        {
            errorMessage();
            Sleep(1000);
            system("cls");
            goto login_try;
        }
    }
    return 0;

}
