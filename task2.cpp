/*
 * Login & Registration System
 * ---------------------------------------------------------------
 * Features:
 *   - Register a new user (username + password)
 *   - Reject duplicate usernames
 *   - Store passwords as a salted hash (never plain text)
 *   - Log in by re-hashing the entered password and comparing it
 *
 * Note on security:
 *   Each password is combined with a random "salt" before hashing,
 *   so two users with the same password never get the same stored
 *   value. The hash function used here (std::hash) is fast but is
 *   NOT a cryptographic hash - it's fine for a learning project,
 *   but a real-world app should use bcrypt or Argon2 instead.
 */

#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>

using namespace std;

const string DB_FILE = "user.txt";

namespace Color
{
    const string RESET = "\033[0m";
    const string GREEN = "\033[1;32m";
    const string RED = "\033[1;31m";
    const string CYAN = "\033[1;36m";
    const string YELLOW = "\033[1;33m";
    const string BOLD = "\033[1m";
}

void printSuccess(const string &message)
{
    cout << Color::GREEN << "[SUCCESS] " << Color::RESET << message << "\n";
}

void printError(const string &message)
{
    cout << Color::RED << "[ERROR] " << Color::RESET << message << "\n";
}

// A single stored user record: username, salt, and password hash
struct User
{
    string username;
    string salt;
    string passwordHash;
};

// Removes leading/trailing spaces and any stray \r
string trim(const string &text)
{
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos)
        return "";
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

string generateSalt(int length = 8)
{
    static mt19937 rng(random_device{}());
    static uniform_int_distribution<int> dist(0, 15);
    const char *hexChars = "0123456789abcdef";

    string salt;
    for (int i = 0; i < length; i++)
    {
        salt += hexChars[dist(rng)];
    }
    return salt;
}

// Combines the salt and password, then hashes the result.
string hashPassword(const string &password, const string &salt)
{
    hash<string> hasher;
    ostringstream oss;
    oss << hasher(salt + password);
    return oss.str();
}

// Splits one username,salt,hash line into a User
bool parseLine(const string &line, User &outUser)
{
    size_t firstComma = line.find(',');
    size_t secondComma = line.find(',', firstComma + 1);
    if (firstComma == string::npos || secondComma == string::npos)
    {
        return false;
    }

    outUser.username = trim(line.substr(0, firstComma));
    outUser.salt = trim(line.substr(firstComma + 1, secondComma - firstComma - 1));
    outUser.passwordHash = trim(line.substr(secondComma + 1));
    return true;
}

bool findUser(const string &username, User &outUser)
{
    ifstream file(DB_FILE);
    string line;

    while (getline(file, line))
    {
        User current;
        if (parseLine(line, current) && current.username == username)
        {
            outUser = current;
            return true;
        }
    }
    return false;
}

// Core features
void registerUser()
{
    string username, password;

    cout << "\n"
         << Color::CYAN << "=== USER REGISTRATION ===" << Color::RESET << "\n";
    cout << "Username: ";
    getline(cin >> ws, username);
    cout << "Password: ";
    cin >> password;

    username = trim(username);
    password = trim(password);

    // Validation
    if (username.empty() || password.empty())
    {
        printError("Username or password cannot be empty.");
        return;
    }
    if (username.find(',') != string::npos)
    {
        printError("Username cannot contain a comma.");
        return;
    }
    if (password.length() < 6)
    {
        printError("Password must be at least 6 characters.");
        return;
    }

    // Duplicate check
    User existing;
    if (findUser(username, existing))
    {
        printError("Username already exists. Try another one.");
        return;
    }

    // Save salted hash
    string salt = generateSalt();
    string hash = hashPassword(password, salt);

    ofstream file(DB_FILE, ios::app);
    if (!file)
    {
        printError("Could not open the database file.");
        return;
    }

    file << username << "," << salt << "," << hash << "\n";
    file.close();

    printSuccess("Registration completed! Now you can log in.");
}

void loginUser()
{
    string username, password;

    cout << "\n"
         << Color::CYAN << "=== USER LOGIN ===" << Color::RESET << "\n";
    cout << "Username: ";
    getline(cin >> ws, username);
    cout << "Password: ";
    cin >> password;

    username = trim(username);
    password = trim(password);

    User existing;
    if (!findUser(username, existing))
    {
        printError("Invalid username or password.");
        return;
    }

    string attemptedHash = hashPassword(password, existing.salt);
    if (attemptedHash == existing.passwordHash)
    {
        printSuccess("Login successful! Welcome, " + username + "!");
    }
    else
    {
        printError("Invalid username or password.");
    }
}

// Menu
int readMenuChoice()
{
    int choice;
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return choice;
}

int main()
{
    while (true)
    {
        cout << "\n"
             << Color::BOLD << Color::YELLOW;
        cout << "+-----------------------------------+\n";
        cout << "|   LOGIN & REGISTRATION SYSTEM      |\n";
        cout << "+-----------------------------------+\n";
        cout << Color::RESET;
        cout << "  1. Register\n  2. Login\n  3. Exit\n";
        cout << "> ";

        int choice = readMenuChoice();

        if (choice == 1)
        {
            registerUser();
        }
        else if (choice == 2)
        {
            loginUser();
        }
        else if (choice == 3)
        {
            break;
        }
        else if (choice == -1)
        {
            printError("Please enter a number (1, 2 or 3).");
        }
        else
        {
            printError("Invalid choice! Please enter 1, 2, or 3.");
        }
    }

    cout << "\n"
         << Color::CYAN << "Thank you for using the system. Goodbye!" << Color::RESET << "\n";
    return 0;
}