# Team46_MobileAppSecurityUI
C++ Security Module + UI integration for mobile app project

- **Security & Password Module** (user registration, login, password reset)  
- **UI Module** (quiz, book recommendations, volunteer events)  
- Fully integrated so that users must login/register before accessing the main app.

---

## Project Files

- `src/main.cpp` : Main program, including quiz, book, and volunteer UI integrated with login.  
- `src/Security.cpp` : Security module implementation.  
- `src/Security.h` : Security module declarations.  
- `users.txt` : Stores usernames and passwords (empty initially).  
- `README.md` : This file with project instructions.  

---

## Features

### Security
- Register new users  
- Login with credentials  
- Reset password  

### Quiz
- Three sample quiz questions  
- Records user answers  
- Shows suggested publications  

### Book Recommendations
- List of books  
- View details  
- Simulate purchase  

### Volunteer Events
- List of events  
- View details  
- Register for events  

---

## How to Run

1. Open project in **CLion**.  
2. Make sure `users.txt` is in the same folder as `main.cpp`.  
3. Build and run the project.  
4. Users will first see the **login menu**:  
   - Register a new user  
   - Login  
   - Reset password  
5. After login, the app shows **quiz → books → volunteer menus**.  

---

## Collaboration Notes

- **Security module** (`Security.cpp` / `Security.h`) → handled by Tanishka  
- **UI / Integration** (`main.cpp`) → handled by teammate  
- Always test locally before uploading to GitHub  
- Download the latest version from GitHub before making changes  

---

## Example Usage

```cpp
#include "Security.h"
#include <iostream>
using namespace std;

int main() {
    if (RegisterUser("testuser", "1234")) cout << "Registered successfully\n";
    if (LoginUser("testuser", "1234")) cout << "Login successful\n";
    if (ResetUserPassword("testuser", "4321")) cout << "Password reset successful\n";
    return 0;
}

