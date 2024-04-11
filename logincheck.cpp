#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

string encrypt(string pass)
{
    string alphabet{" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()"};
    string key{"@3cDe5HbAr9QIu#vL!6J2zN0@h4F1Gp$oW7aE8SfV2YrT5mXkOwZiUMt?IgRd8jKynqPb&l(*AsV"};

    string encrypted_message{};

    for (char c : pass)
    {
        size_t position = alphabet.find(c);
        if (position != string::npos)
        {
            char new_char{key.at(position)};
            encrypted_message += new_char;
        }
        else
        {
            encrypted_message += c;
        }
    }

    return encrypted_message;
}

class user
{
private:
    string user_name; // Current_user_name of the user
    string token;     // Password as token of the user

public:
    user(string val1, string val2) : user_name(val1), token(encrypt(val2)){};

    ~user() = default;

    string get_user_name() { return user_name; }
    string get_token() { return token; }
};

void line(int n) // A simple line used for formatting
{
    for (int i(0); i < n; i++)
    {
        cout << '-';
    }
    cout << "+" << endl;
}

void display_users(vector<user> &vec) // Display list of the users in a formmated way(SQL)
{

    line(140);

    cout << setw(85) << left << "token"
         << "  |  "
         << setw(50) << "user_name"
         << "|" << endl;

    line(140);

    for (int i(0); i < vec.size(); i++)
    {
        cout << setw(5) << i + 1 << setw(80) << left << vec[i].get_token() << "  |  " << setw(50) << vec[i].get_user_name() << "|" << endl;
    }

    line(140);
}

void add_user(vector<user> &vec, string val1, string val2)
{
    bool found = false;

    for (int i(0); i < vec.size(); i++)
    {
        if (vec[i].get_user_name() == val1)
        {
            cout << "Cannot Add User!! Try Another Username!!" << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        vec.push_back(user(val1, val2));
        cout << "User Added Successfully" << endl;
    }
}

void delete_user(vector<user> &vec, string val1, string val2)
{
    int pos = -1;

    for (int i(0); i < vec.size(); i++)
    {
        if (val1 == vec[i].get_user_name())
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        cout << "No such user Found!!" << endl;
    }

    else if (pos != -1)
    {

        if (vec[pos].get_token() == encrypt(val2))
        {
            cout << "User Found!! Details Matched!! Now Deleting User!!" << endl;
            vec.erase(vec.begin() + pos);
        }

        else if (vec[pos].get_token() != encrypt(val2))
        {
            cout << "Wrong Credentials Cannot Delete User" << endl;
        }
    }
}

string getPassword()
{
    string password;
    char ch;
    while ((ch = _getch()) != '\r')  // '\r' is the Enter key
    {
        password += ch;
        cout << '*';  // Print '*' instead of the actual character
    }
    cout << endl;  // Move to a new line after masking the password
    return password;
}

void start()
{
    vector<user> user_details;
    int choice;

    do {
        cout << "1. Add User\n2. Delete User\n3. Display Users\n4. Quit\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                {
                    string username;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    string password = getPassword();  // Using the getPassword() function to mask the password
                    add_user(user_details, username, password);
                    break;
                }
            case 2:
                {
                    string username;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    string password = getPassword();  // Using the getPassword() function to mask the password
                    delete_user(user_details, username, password);
                    break;
                }
            case 3:
                display_users(user_details);
                break;
            case 4:
                cout << "Quitting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 4);
}

int main()
{
    start();
    return 0;
}
