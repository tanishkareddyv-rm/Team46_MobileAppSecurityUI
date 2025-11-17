#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

/* ==========================================================
   SIMPLE BUILT-IN SECURITY SYSTEM (REPLACEMENT FOR SecurityAPI)
========================================================== */

map<string, string> userDB;

bool registerUser(string u, string p) {
    if (userDB.count(u)) return false;
    userDB[u] = p;
    return true;
}

bool loginUser(string u, string p) {
    return userDB.count(u) && userDB[u] == p;
}

bool resetPassword(string u, string p) {
    if (!userDB.count(u)) return false;
    userDB[u] = p;
    return true;
}

/* ===============================================
   FEEDFORGE APP DECLARATIONS
=============================================== */

void startQuiz();
void quizQuestions();
void quizResults();
void home();
void bookTab();
void bookDetails(string title);
void volunteerTab();
void volunteerDetails(string eventName);

vector<string> questions = {
    "How much do you enjoy reading the news?",
    "How political are your personal interests?",
    "How often do you read science or tech updates?"
};

vector<int> answers;
vector<string> books = {"Book One", "Book Two", "Book Three"};
vector<string> events = {
    "Clean the Park",
    "Food Bank Sorting",
    "Animal Shelter Help"
};

void waitEnter() {
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}

/* ===============================================
   LOGIN / REGISTER MENU
=============================================== */

void securityMenu() {
    while (true) {
        cout << "\n========== SECURITY MENU ==========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Reset Password\n";
        cout << "4. Exit App\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string u, p;
            cout << "New username: ";
            cin >> u;
            cout << "New password: ";
            cin >> p;

            if (registerUser(u, p))
                cout << "Account created successfully.\n";
            else
                cout << "User already exists.\n";
        }

        else if (choice == 2) {
            string u, p;
            cout << "Username: ";
            cin >> u;
            cout << "Password: ";
            cin >> p;

            if (loginUser(u, p)) {
                cout << "Login successful!\n";
                waitEnter();
                startQuiz();     // CONTINUE TO FEEDFORGE APP
                return;
            } else {
                cout << "Invalid login.\n";
            }
        }

        else if (choice == 3) {
            string u, p;
            cout << "Username: ";
            cin >> u;
            cout << "New password: ";
            cin >> p;

            if (resetPassword(u, p))
                cout << "Password reset successful.\n";
            else
                cout << "User not found.\n";
        }

        else if (choice == 4) {
            cout << "Exiting...\n";
            exit(0);
        }

        else {
            cout << "Invalid.\n";
        }
    }
}

/* ===============================================
   START QUIZ SCREEN
=============================================== */

void startQuiz() {
    system("clear || cls");
    cout << "=============================\n";
    cout << "         FEEDFORGE\n";
    cout << "=============================\n\n";
    cout << "1. Start Quiz\n";
    cout << "2. Exit\n\nChoose: ";

    int choice;
    cin >> choice;

    if (choice == 1) quizQuestions();
    else exit(0);
}

/* ===============================================
   QUIZ QUESTIONS
=============================================== */

void quizQuestions() {
    answers.clear();
    system("clear || cls");

    for (int i = 0; i < questions.size(); i++) {
        cout << "Question " << i+1 << ": " << questions[i] << "\n\n";
        cout << "Rate 1-5 → ";
        int ans;
        cin >> ans;
        answers.push_back(ans);

        system("clear || cls");
    }

    quizResults();
}

/* ===============================================
   RESULTS
=============================================== */

void quizResults() {
    system("clear || cls");

    cout << "============== QUIZ RESULTS ==============\n";
    cout << "Suggested publications:\n\n";
    cout << "• New York Times\n";
    cout << "• Wall Street Journal\n";
    cout << "• Reuters\n\n";

    cout << "1. Continue → Home\n";
    cout << "2. Retake Quiz\n\n";

    int choice;
    cin >> choice;

    if (choice == 1) home();
    else quizQuestions();
}

/* ===============================================
   HOME SCREEN
=============================================== */

void home() {
    system("clear || cls");

    cout << "================ HOME ================\n";
    cout << "Welcome to your personalized FeedForge feed.\n\n";

    cout << "1. Book Recommendations\n";
    cout << "2. Volunteer Events\n";
    cout << "3. Logout\n\n";

    int choice;
    cin >> choice;

    if (choice == 1) bookTab();
    else if (choice == 2) volunteerTab();
    else securityMenu();
}

/* ===============================================
   BOOKS
=============================================== */

void bookTab() {
    system("clear || cls");

    cout << "========= BOOK RECOMMENDATIONS =========\n\n";

    for (int i = 0; i < books.size(); i++)
        cout << i+1 << ". " << books[i] << "\n";

    cout << "\n0. Back\n\n";

    int choice;
    cin >> choice;

    if (choice == 0) home();
    else if (choice >= 1 && choice <= books.size())
        bookDetails(books[choice-1]);
    else
        bookTab();
}

void bookDetails(string title) {
    system("clear || cls");

    cout << "============== BOOK DETAILS ==============\n";
    cout << "Title: " << title << "\n";
    cout << "Summary: A book matched to your interests.\n";
    cout << "Price: $9.99\n\n";

    cout << "1. Buy\n";
    cout << "2. Back\n\n";

    int choice;
    cin >> choice;

    if (choice == 2) bookTab();
    else {
        cout << "Purchase successful!\n";
        waitEnter();
        bookTab();
    }
}

/* ===============================================
   VOLUNTEERING
=============================================== */

void volunteerTab() {
    system("clear || cls");

    cout << "========= VOLUNTEER EVENTS =========\n\n";

    for (int i = 0; i < events.size(); i++)
        cout << i+1 << ". " << events[i] << "\n";

    cout << "\n0. Back\n\n";

    int choice;
    cin >> choice;

    if (choice == 0) home();
    else if (choice >= 1 && choice <= events.size())
        volunteerDetails(events[choice-1]);
    else
        volunteerTab();
}

void volunteerDetails(string name) {
    system("clear || cls");

    cout << "=========== VOLUNTEER DETAILS ===========\n";
    cout << "Event: " << name << "\n";
    cout << "Description: A chance to help your community.\n\n";

    cout << "1. Register\n";
    cout << "2. Back\n\n";

    int choice;
    cin >> choice;

    if (choice == 2) volunteerTab();
    else {
        cout << "You are registered!\n";
        waitEnter();
        volunteerTab();
    }
}

/* ===============================================
   MAIN (App starts at Security/Login)
=============================================== */

int main() {
    securityMenu();
    return 0;
}