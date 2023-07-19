#include <iostream>     //provides input/output functionalitie
#include <vector>       //used for dynamic arrays
#include <math.h>       //provides mathematical functions
#include <regex>        //used for regular expressions
#include <windows.h>    //Windows-specific header file
#include <exception>    //for handling exceptions


using namespace std;

class Bank {
public:
    //nested Customer struct - details of a bank customer
    struct Customer {
        string name;
        string accountNumber;
        char accountType;
        string address;
        string contact;
        string dob;
        string email;
        string username;
        string password;
        double balance;

        //constructor that takes arguments for each member variable and initializes them using an initialization list
        Customer(const string& name, const string& accountNumber, const string& username, const string& password, double balance, char accountType, const string& address, const string& dob, const string& contact, const string& email)
            : name(name), accountNumber(accountNumber), username(username), password(password), balance(balance), accountType(accountType), address(address), dob(dob), contact(contact), email(email) {}
    };

    // ... member functions ...

    void homeMenu();
    void customerMenu(Customer& customer);
    void createAccount();
    void login();
    void searchCustomers();
    void viewDetails(Customer& customer);
    void transactions(Customer& customer);
    void transferFunds(Customer& sender);
    void deleteAccount(Customer& customer);
    void update(Customer& customer);
    void changePassword(Customer& customer);
    void generateLoan(Customer& customer);
    //void displayLoanDetails(Customer& customer);
    //void system("CLS");
    //void Sleep(int milliseconds);
    bool isUsernameTaken(const string& username);
    bool isValidPassword(const string& password);
    bool isValidDate(const string& date);
    bool isValidEmail(const string& email);
    bool isValidPhoneNumber(const string& phoneNumber);
    string generateAccountNumber();
    Customer* findCustomerByUsername(const string& username);
    Customer* findCustomerByAccountNumber(const string& accountNumber);

private:
    vector<Customer> customers;
};

void Bank::homeMenu() {
    while (true) {
    //Displaying the home menu options and getting user input

        // system("CLS");
        system("CLS");
        cout << "======================================" << endl;
        cout << "          Welcome to Bank           " << endl;
        cout << "======================================" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Search Customers" << endl;
        cout << "4. Exit" << endl;
        cout << "======================================" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        // Handling different choices
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                searchCustomers();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        Sleep(2000);
    }
}

void Bank::customerMenu(Customer& customer) {
    while (true) {
    // Displaying the customer menu options and getting user input
        system("CLS");
        cout << "======================================" << endl;
        cout << "         Welcome, " << customer.name << "!" << endl;
        cout << "======================================" << endl;
        cout << "1. View Account Details" << endl;
        cout << "2. Transactions" << endl;
        cout << "3. Transfer Funds "<< endl;
        cout << "4. Delete Account" << endl;
        cout << "5. Update Account Details"<<endl;
        cout << "6. Change Password" << endl;
        cout << "7. Generate Loan" << endl;
        cout << "8. Logout" << endl;
        cout << "======================================" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        // Handling different choices
        case 1:
            viewDetails(customer);
            break;
        case 2:
            transactions(customer);
            break;
        case 3:
            transferFunds(customer);
            break;
        case 4:
            deleteAccount(customer);
            return;
        case 5:
            update(customer);
            break;
        case 6:
            changePassword(customer);
            break;
        case 7:
            generateLoan(customer);
            break;

        case 8:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        Sleep(2000);
    }
}

void Bank::createAccount() {
    // Prompting the user to enter account details
    system("CLS");
    cout << "======================================" << endl;
    cout << "           Create Account             " << endl;
    cout << "======================================" << endl;

    cout << "Enter your full name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    cout << "Choose a username: ";
    string username;
    cin >> username;
    // Validating user input and creating a new Customer object
    while (isUsernameTaken(username)) {
        cout << "Username already taken. Please choose a different username: ";
        cin >> username;
    }

    cout << "Choose a password: ";
    string password;
    cin >> password;
    while (!isValidPassword(password)) {
        cout << "Error: Re-enter the password: ";
        cin >> password;
    }

    double balance;
    cout<<"Enter the initial Balance to be deposited: ";
    cin>>balance;

    cout<<"Enter the type of account(Current or Savings) [C/S]: ";
    char accountType;
    cin>>accountType;
    while(toupper(accountType)!='C' && toupper(accountType)!='S'){
        cout<<"Invalid account type. Please enter 'C' for Current or 'S' for Savings Account: ";
        cin>>accountType;
    }

    cout<<"Enter your address: ";
    string address;
    cin.ignore();
    getline(cin, address);
    
    cout<<"Enter your Date of birth (DD/MM/YYYY): ";
    string dob;
    cin>>dob;
    while (!isValidDate(dob)) {
        cout << "Invalid date format. Please enter date in the format DD/MM/YYYY: ";
        cin >> dob;
    }

    cout<<"Enter your contact number: ";
    string contact;
    cin>>contact;
    while (!isValidPhoneNumber(contact)) {
        cout << "Invalid phone number. Please enter a 10-digit phone number: ";
        cin >> contact;
    }

    cout<<"Enter the email address: ";
    string email;
    cin>>email;
    while (!isValidEmail(email)) {
        cout << "Invalid email address. Please enter a valid email address: ";
        cin >> email;
    }

    //Generating a random account number
    string accountNumber = generateAccountNumber();
    //Adding the Customer object to customers vector using emplace_back - append a new element at the end of container as a object not as a copy
    customers.emplace_back(name, accountNumber, username, password, balance,accountType, address, dob, contact, email);

    cout << "Account created successfully!" << endl;
    cout << "Your account number is: " << accountNumber << endl;
    cout << "Please remember it for future reference." << endl;
    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

void Bank::login() {
    system("CLS");
    cout << "======================================" << endl;
    cout << "               Login                  " << endl;
    cout << "======================================" << endl;
    
    // Prompting the user to enter username and password
    cout << "Enter your username: ";
    string username;
    cin >> username;

    // Use the findCustomerByUsername function to find the customer
    Customer* customer = findCustomerByUsername(username);
    if (customer == nullptr) {
        cout << "Account not found. Please try again." << endl;
        cout << "Press enter to continue..." << endl;
        cin.ignore();
        cin.get();
        return;
    }
    // Checking if the entered credentials are valid

    cout << "Enter your password: ";
    string password;
    cin >> password;
    

    if (customer->password == password) {
        // Displaying success message and entering the customer menu

        cout << "Login successful! Welcome, " << customer->name << "!" << endl;
        cout << "Press enter to continue..." << endl;
        cin.ignore();
        cin.get();
        customerMenu(*customer);
    } else {
        cout << "Invalid password. Please try again." << endl;
        cout << "Press enter to continue..." << endl;
        cin.ignore();
        cin.get();
    }
}

Bank::Customer* Bank::findCustomerByUsername(const string& username) {
    for (Customer& customer : customers) {
        if (customer.username == username) {
            return &customer;
        }
    }
    return nullptr;
}

Bank::Customer* Bank::findCustomerByAccountNumber(const string& accountNumber) {
    for (Customer& customer : customers) {
        if (customer.accountNumber == accountNumber) {
            return &customer;
        }
    }
    return nullptr;
}

void Bank::searchCustomers() {
    system("CLS");
    cout << "======================================" << endl;
    cout << "          Search Customers            " << endl;
    cout << "======================================" << endl;
    // Searching for the customer by account number

    cout << "Enter the account number: ";
    string accountNumber;
    cin >> accountNumber;
    // Displaying customer details if found

    Customer* customer = findCustomerByAccountNumber(accountNumber);
    if (customer == nullptr) {
        cout << "Customer not found." << endl;
    } else {
        cout << "Customer Name: " << customer->name << endl;
        cout << "Account Number: " << customer->accountNumber << endl;
        cout << "Username: " << customer->username << endl;
        cout << "Address: " << customer->address<<endl;

        cout << "Balance: Rs." << customer->balance << endl;
    }

    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

void Bank::viewDetails(Customer& customer){
    system("CLS");
    cout << "======================================" << endl;
    cout << "            Account Details           " << endl;
    cout << "======================================" << endl;
    // Displaying the account details of the provided customer

    cout<<"Name: "<<customer.name<<endl;
    cout<<"Account Number: "<<customer.accountNumber<<endl;
    cout<<"Username: "<<customer.username<<endl;
    cout<<"Password: "<<customer.password<<endl;
    cout<<"Account Type: "<<(customer.accountType =='C' ? "Current" : "Savings")<<endl;
    cout<<"Address: "<<customer.address<<endl;
    cout<<"Date of Birth: "<<customer.dob<<endl;
    cout<<"Contact: "<<customer.contact<<endl;
    cout<<"Email: "<<customer.email<<endl;

    cout<<"\nBalance: "<<customer.balance<<endl;
    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();



}

void Bank::transactions(Customer& customer) {
    system("CLS");
    cout << "======================================" << endl;
    cout << "            Transactions              " << endl;
    cout << "======================================" << endl;
    // Displaying transaction options and getting user input

    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Go back to main menu" << endl;
    cout << "======================================" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    // Handling different transaction choices

    switch (choice) {
    case 1: {
        cout << "Enter the amount to deposit: Rs.";
        double amount;
        cin >> amount;
        customer.balance += amount;
        cout << "Deposit successful! Current balance: Rs." << customer.balance << endl;
        break;
    }
    case 2: {
        cout << "Enter the amount to withdraw: Rs.";
        double amount;
        cin >> amount;
        if (amount > customer.balance) {
            cout << "Insufficient balance. Withdrawal canceled." << endl;
        } else {
            customer.balance -= amount;
            cout << "Withdrawal successful! Current balance: Rs." << customer.balance << endl;
        }
        break;
    }
    case 3:
        return;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }

    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

void Bank::transferFunds(Customer& sender){
    cout<<"Enter the account number of the recipient: ";
    // Prompting the user to enter the recipient's account number and amount to transfer

    string recipientAccountNumber;
    cin>>recipientAccountNumber;
    
    // Searching for the recipient customer by account number
    Customer* recipient = findCustomerByAccountNumber(recipientAccountNumber);
    if(recipient== nullptr){
        cout<<"Recipient account not found. Transfer Canceled."<<endl;
        cout<<"Press enter to continue..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }
   
   
    // for(Customer& customer : customers){
    //     if(customer.accountNumber == recipientAccountNumber){
    //         recipient  = &customer;
    //         break;
    //     }
    // }
    cout<<"enter the amount to transfer: Rs. ";
    double amount;
    cin>>amount;

    if(amount>sender.balance){
        cout<<"Insufficient Balance: Transfer Cancelled."<<endl;
        cout<<"Press enter to continue..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }

    // Transferring funds from the sender to the recipient


    sender.balance -=amount;
    recipient->balance += amount;
    
    // displaying success\error messages
    cout<<"Transfer successful Rs."<<amount<<" has been transfered to account number "<< recipient->accountNumber<<endl;
    cout<<"Press enter to continue..."<<endl;
    cin.ignore();
    cin.get();
        
}

void Bank::deleteAccount(Customer& customer) {
    system("CLS");
    cout << "======================================" << endl;
    cout << "           Delete Account             " << endl;
    cout << "======================================" << endl;

    cout << "Are you sure you want to delete your account? (Y/N): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        auto it = customers.begin();
        while (it != customers.end()) {
             // Deleting the customer's account if found
            if (&(*it) == &customer) {
                it = customers.erase(it);
                cout << "Account deleted successfully!" << endl;
                cout << "Press enter to continue..." << endl;
                cin.ignore();
                cin.get();
                return;
            } else {
                ++it;
            }
        }
    }

    cout << "Account not found. Deletion failed." << endl;
    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

void Bank::update(Customer& customer){
    system("CLS");
    cout << "======================================" << endl;
    cout << "        Update Account Details        " << endl;
    cout << "======================================" << endl;

    cout << "Choose the field you want to update: " << endl;
    cout << "1. Address" << endl;
    cout << "2. Contact" << endl;
    cout << "3. Email" << endl;
    cout << "4. Go back to main menu" << endl;
    cout << "======================================" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    
    // Prompting the user to choose a field to update
    switch (choice) {
    
    // Handling different field update choices
    case 1: {
        cout << "Enter the new address: ";
        cin.ignore();
        getline(cin, customer.address);
        cout << "Address updated successfully!" << endl;
        break;
    }
    case 2: {
        cout << "Enter the new contact number: ";
        cin >> customer.contact;
        while (!isValidPhoneNumber(customer.contact)) {
            cout << "Invalid contact number. Contact number should be 10 characters long: ";
            cin >> customer.contact;
        }
        cout << "Contact number updated successfully!" << endl;
        break;
    }
    case 3: {
        cout << "Enter the new email address: ";
        cin >> customer.email;
        while (!isValidEmail(customer.email)) {
            cout << "Invalid email address. Email address should be valid: ";
            cin >> customer.email;
        }
        cout << "Email address updated successfully!" << endl;
        break;
    }
    case 4:
        return;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }

    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

void Bank::changePassword(Customer& customer) {
    system("CLS");
    cout << "======================================" << endl;
    cout << "          Change Password             " << endl;
    cout << "======================================" << endl;

    cout << "Enter your current password: ";
    string currentPassword;
    cin >> currentPassword;
    
    // Checking if the entered password matches the customer's current password
    if (customer.password != currentPassword) {
        cout << "Invalid password. Change password failed." << endl;
        cout << "Press enter to continue..." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    cout << "Enter your new password: ";
    string newPassword;
    cin >> newPassword;
    while (!isValidPassword(newPassword)) {
        cout << "Error: Re-enter the password: ";
        cin >> newPassword;
    }

    customer.password = newPassword;

    cout << "Password changed successfully!" << endl;
    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

void Bank::generateLoan(Customer& customer) {
    system("CLS");
    cout << "======================================" << endl;
    cout << "          Generate Loan               " << endl;
    cout << "======================================" << endl;
    
    // Prompting the user to enter the loan amount
    cout<<"Enter the loan amount: Rs.";
    double loanAmount;
    cin>>loanAmount;

    string collateral;
    double collateralValue = customer.balance;
    bool collateralProvided = false;
    //Check if collateral is required
    if(loanAmount > customer.balance){
        cout<<"Collateral is required for the loan."<<endl;
        // If collateral is required, prompting the user to provide collateral details

        cout<<"Enter Collateral: "<<endl;
        cin.ignore();
        getline(cin, collateral);
        cout<<"Enter the collateral value: Rs.";
        cin>>collateralValue;
        collateralProvided=true;

    }
    
    // Checking if the loan amount is within the customer's eligibility
    double eligibility = collateralValue * 0.75;
    if(loanAmount<=eligibility){
        double interestRate = 0.09; //Assuming 9% interest rate
        int tenure;
        cout<<"Enter the Loan tenure (in months): ";
        cin>>tenure;

        double monthlyInterestRate = interestRate/12.0;

        double monthlyEMI = (loanAmount * monthlyInterestRate * pow(1+monthlyInterestRate, tenure))/(pow(1+monthlyInterestRate, tenure)-1);
        //double yearlyInterest = loanAmount * interestRate;
        //double totalYearlyEMI = monthlyEMI * 12;
        double totalAmountPayable = monthlyEMI * tenure;
    // Displaying loan details and prompting the user to credit the loan amount
        cout<<"Loan approved! Rs."<<loanAmount<<" will credited to your account."<<endl;
        cout<< "Loan Details: "<< endl;
        cout<<"Loan Amount: Rs."<<loanAmount<<endl;
        cout<<"Monthly EMI: Rs."<<monthlyEMI<<endl;
        cout<<"Tenure: "<<tenure<<" months"<<endl;
        cout<<"Total Amount Payable to the bank: Rs."<<totalAmountPayable<<endl;

        if(collateralProvided){
            cout<<"Collateral Value: Rs." << collateralValue<<endl;
        }

        cout<<"Do you want to credit the loan amount to your account? (Y/y): ";
        char choice;
        cin>>choice;
        
        // Crediting the loan amount to the customer's account if requested
        if(choice =='Y' || choice =='y'){
            customer.balance += loanAmount;
            cout<<"Loan amount credited to your account successfully!"<<endl;
        }
        else{
            cout<<"Loan amount not credited to your account." << endl;
        }
    }
    else{
        cout<<" Loan amount exceeds your eligibility based on collateral value." <<endl;
        cout<<" Please provide additional collateral or apply for a lower loan amount."<<endl;
        collateralValue=0;
        collateral="";
        
    }

    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

// \033 is the escape character, which signals the start of an escape sequence.
//2J is the control sequence parameter that specifies the action to clear the entire screen.
//cursor position to the top-left corner of the screen.
// void Bank::system("CLS") {
//     cout << "\033[2J\033[1;1H";  // Clear screen using ANSI escape sequences
// }

// void Bank::Sleep(int milliseconds) {
//     this_thread::sleep_for(chrono::milliseconds(milliseconds));
// }

bool Bank::isUsernameTaken(const string& username) {
    // Checking if the username is already taken by another customer
    for (const Customer& customer : customers) {
        if (customer.username == username) {
            return true;
        }
    }
    return false;
}
    

// Validating the format of a password
bool Bank::isValidPassword(const string& password) {
    try{
    // Password must contain at least 6 characters including at least one uppercase letter, one lowercase letter, and one digit
        // ^ , & - begin and end
        //The .* allows any number of characters before and after the lowercase letter.
        
        regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{6,}$");
        if(!regex_match(password, passwordPattern)){
            throw invalid_argument("Invalid password format. Password must contail at least 6 characters including at least one uppercase, lowercase letter and one digit.");

        }
        return true;
    }catch(const exception& e){
        cout<<"Password Validation error: "<<e.what()<<endl;
        return false;
    }
}


bool Bank::isValidDate(const string& date) {
    try {
        regex datePattern("\\d{2}/\\d{2}/\\d{4}");
        if (!regex_match(date, datePattern)) {
            throw invalid_argument("Invalid date format. Date should be in the format DD/MM/YYYY.");
        }
        return true;
    } catch (const exception& e) {
        cout << "Date Validation Error: " << e.what() << endl;
        return false;
    }
}

bool Bank::isValidEmail(const string& email) {
    try {
        // Regular expression pattern for email validation
        regex emailPattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");

        if (!regex_match(email, emailPattern)) {
            throw invalid_argument("Invalid email format.");
        }

        return true;
    } catch (const exception& e) {
        cout << "Email Validation error: " << e.what() << endl;
        return false;
    }
}

bool Bank::isValidPhoneNumber(const string& phoneNumber) {
    try {
        regex phoneNumberPattern(".{10}");
        if (!regex_match(phoneNumber, phoneNumberPattern)) {
            throw invalid_argument("Invalid phone number format. Phone number should be 10 characters long.");
        }
        return true;
    } catch (const exception& e) {
        cout << "Phone Number Validation Error: " << e.what() << endl;
        return false;
    }
}


string Bank::generateAccountNumber() {
    static int counter = 1;
    string prefix ="20000";
    int randomNumber = 100 + counter++;
    string accountNumber = prefix + to_string(randomNumber);
    return accountNumber;
}


int main() {
    Bank bank;
    bank.homeMenu();
    return 0;
}
