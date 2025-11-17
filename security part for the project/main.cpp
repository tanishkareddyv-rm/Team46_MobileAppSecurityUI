#include <iostream>
#include "SecurityAPI.h"

int main() {
    std::cout << "Security module running...\n";

    SecurityAPI api("users.txt");

    while (true) {
        std::cout << "\n=== Security Menu ===\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Reset Password\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string u, p;
            std::cout << "Enter new username: ";
            std::cin >> u;
            std::cout << "Enter new password: ";
            std::cin >> p;

            if (api.registerUser(u, p))
                std::cout << "User registered successfully.\n";
            else
                std::cout << "User already exists.\n";
        }

        else if (choice == 2) {
            std::string u, p;
            std::cout << "Enter username: ";
            std::cin >> u;
            std::cout << "Enter password: ";
            std::cin >> p;

            std::string token;
            if (api.loginUser(u, p, token)) {
                std::cout << "Login successful.\n";
                std::cout << "Session Token: " << token << "\n";
            }
            else {
                std::cout << "Invalid username or password.\n";
            }
        }

        else if (choice == 3) {
            std::string u, p;
            std::cout << "Enter username: ";
            std::cin >> u;
            std::cout << "Enter new password: ";
            std::cin >> p;

            if (api.resetPassword(u, p))
                std::cout << "Password reset successful.\n";
            else
                std::cout << "User not found.\n";
        }

        else if (choice == 4) {
            std::cout << "Exiting...\n";
            break;
        }

        else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
