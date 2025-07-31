#include<stdio.h>
#include<string.h>
#define MAX_USERS 10
struct User
{
    char name[100];
    int acc_number;
    char pin[10];
    int balance;
};
struct User s[MAX_USERS];
int user_count = 0;

void create_account()
{
    if (user_count >= MAX_USERS)
    {
        printf("Registration limit reached! Maximum %d users allowed.\n", MAX_USERS);
        return;
    }

    printf("Enter your name: ");
    scanf(" %[^\n]", s[user_count].name);
    printf("Enter account number: ");
    scanf("%d", &s[user_count].acc_number);
    for (int i = 0; i < user_count; i++)
    {
        if (s[i].acc_number == s[user_count].acc_number)
        {
            printf("Account number already exists! Please use a different account number.\n");
            return;
        }
    }
    while(1) {
        printf("Create a pin: ");
        scanf(" %s", s[user_count].pin);


        int valid = 1;
        for(int i = 0; s[user_count].pin[i] != '\0'; i++) {
            if(s[user_count].pin[i] == ' ') {
                printf("Invalid PIN. It cannot contain spaces.\n");
                valid = 0;
                break;
            }
        }

        if(valid) {
            break;
        }
    }

    s[user_count].balance = 0;

    user_count++;
    printf("Account created successfully! You are user %d of %d.\n", user_count, MAX_USERS);
}
int find_user(int acc, char pin[])
{
    for (int i = 0; i < user_count; i++)
    {
        if (s[i].acc_number == acc && strcmp(s[i].pin, pin) == 0)
        {
            return i;
        }
    }
    return -1;
}
void deposit_money(int user_index)
{
    int amount;
    printf("Enter amount to deposit: ");
    scanf("%d", &amount);
    if (amount < 500)
    {
        printf("Invalid amount. Deposit must be minimum 500.\n");
        return;
    }
    s[user_index].balance += amount;
    printf("Deposit successful! Current balance: %d\n", s[user_index].balance);
}
void withdraw_money(int user_index)
{
    int amount;
    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);
    if (amount < 500 || amount >25000)
    {
        printf("Invalid amount. Withdrawal must be more than 500 and less than 25000.\n");
        return;
    }
    if (amount > s[user_index].balance)
    {
        printf("Insufficient balance! Current balance: %d\n", s[user_index].balance);
        return;
    }
    s[user_index].balance -= amount;
    printf("Withdrawal successful! Current balance: %d\n", s[user_index].balance);
}
void check_balance(int user_index)
{
    printf("Your current balance is: %d\n", s[user_index].balance);
}

int main()
{

    while(1)
    {
        printf("\n================================\n");
        printf("   BANKING SYSTEM MANAGEMENT\n");
        printf("================================\n");
        printf("\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Select an option : ");
        int n;
        scanf("%d",&n);
        getchar();
        switch(n)
        {
        case 1:
            create_account();
            break;

        case 2:
        case 3:
        case 4:
        {
            if (user_count == 0)
            {
                printf("No accounts exist. Please create an account first.\n");
                break;
            }

            int inputAcc;
            char inputPin[10];

            printf("Enter your account number: ");
            scanf("%d", &inputAcc);

            printf("Enter your PIN: ");
            scanf("%s", inputPin);

            int user_index = find_user(inputAcc, inputPin);
            if (user_index == -1)
            {
                printf("Authentication failed! Account number not found or Incorrect PIN.\n");
                break;
            }

            printf("Welcome, %s!\n", s[user_index].name);


            if (n == 2)
                deposit_money(user_index);
            else if (n == 3)
                withdraw_money(user_index);
            else
                check_balance(user_index);
            break;
        }

        case 5:
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Invalid option. Try again.\n");
            break;

        }
    }
    return 0;
}
