# 🔐 Login & Registration System

A console-based **Login & Registration System** developed in **C++** .

The project demonstrates user registration, login authentication, duplicate username prevention, file-based data storage, password hashing with randomly generated salts, input validation, and a colorful command-line interface.

---

## ✨ Features

* 👤 **User Registration**

  * Create a new account using a username and password.
  * Supports usernames containing spaces.

* 🔑 **User Login**

  * Authenticate users using their username and password.
  * Passwords are re-hashed using the stored salt before comparison.

* 🛡️ **Salted Password Hashing**

  * Passwords are **never stored as plain text**.
  * A randomly generated salt is combined with the password before hashing.
  * Users with the same password receive different stored hash values because their salts are different.

* 🚫 **Duplicate Username Prevention**

  * Prevents registration with an existing username.

* ✅ **Input Validation**

  * Username and password cannot be empty.
  * Username cannot contain commas.
  * Password must contain at least **6 characters**.
  * Invalid menu inputs are handled safely.

* 💾 **File-Based Data Storage**

  * User information is stored locally in `user.txt`.
  * Registered users remain available after restarting the program.

* 🎨 **Colorful Console Interface**

  * Green messages for successful operations.
  * Red messages for errors.
  * Cyan headings and yellow menu display.

* 🔄 **Interactive Menu**

  * Register
  * Login
  * Exit

---

## 🛠️ Technologies Used

| Technology     | Purpose                |
| -------------- | ---------------------- |
| **C++**      | Programming language   |
| `<fstream>`    | File input/output      |
| `<functional>` | `hash`            |
| `<random>`     | Random salt generation |
| `<string>`     | String handling        |
| `<sstream>`    | Hash value conversion  |
| `<iostream>`   | Console input/output   |
| `<limits>`     | Input validation       |

---

## 🔐 How Password Security Works

The system does **not** save the user's original password.

Instead, it generates a random salt and combines it with the password:

```text
Salt + Password
       ↓
     Hash
       ↓
Stored Password Hash
```

For example:

```text
Username: Trisha
Password: mypassword
Salt:     a7f31c92
Hash:     [generated hash value]
```

The database stores:

```text
username,salt,passwordHash
```

During login, the entered password is combined with the user's stored salt and hashed again. The newly generated hash is then compared with the stored hash.

### ⚠️ Security Note

This project uses C++ `hash` for educational purposes.

`hash` is **not a cryptographic password-hashing algorithm** and should not be used for storing passwords in a real-world production application.

For production systems, password-hashing algorithms such as **Argon2**, **bcrypt**, or **PBKDF2** should be used.

---

## 📸 Project Demo

Add a screenshot of the program output here:

```md
![Login & Registration System Screenshot](screenshot.png)
```

Example program flow:

```text
+-----------------------------------+
|   LOGIN & REGISTRATION SYSTEM     |
+-----------------------------------+
  1. Register
  2. Login
  3. Exit
>
```

### Registration

```text
=== USER REGISTRATION ===
Username: Trisha Barua
Password: ********

[SUCCESS] Registration completed! Now you can log in.
```

### Login

```text
=== USER LOGIN ===
Username: Trisha Barua
Password: ********

[SUCCESS] Login successful! Welcome, Trisha Barua!
```

---

## 🚀 How to Run

### Prerequisites

Make sure you have a C++ compiler installed.

Recommended:

* **GCC / MinGW**
* **VS Code** with a C++ compiler
* Windows, Linux, or macOS

---

### 1. Clone the Repository

```bash
git clone https://github.com/TrishaBarua308/CodeAlpha_Login_-_Registration-system.git
```

Then enter the project directory:

```bash
cd CodeAlpha_Login_-_Registration-system
```

---

### 2. Compile the Program

Using GCC / MinGW:

```bash
g++ task2.cpp -o app
```

On Windows, you can also use:

```bash
g++ task2.cpp -o app.exe
```

---

### 3. Run the Application

#### Windows

```bash
app.exe
```

#### Linux / macOS

```bash
./app
```

---

## 📁 Project Structure

```text
CodeAlpha_Login_-_Registration-system/
│
├── task2.cpp
├── user.txt
└── README.md
```

### File Description

| File        | Description                                                    |
| ----------- | -------------------------------------------------------------- |
| `task2.cpp` | Main C++ source code                                           |
| `user.txt`  | Local file used to store usernames, salts, and password hashes |
| `README.md` | Project documentation                                          |


---

## 🧠 Concepts Demonstrated

This project demonstrates several important C++ and software development concepts:

* Functions
* Structures (`struct`)
* Namespaces
* File handling
* String manipulation
* Input validation
* Loops and conditional statements
* Random number generation
* Hashing
* Salted password storage
* Error handling
* Console-based UI
* Persistent local data storage

---

## 🎯 Project Objective

The main objective of this project is to build a simple authentication system while practicing:

1. C++ programming fundamentals
2. File handling
3. User input validation
4. Authentication logic
5. Password hashing concepts
6. Basic security practices
7. Clean console-based application design

---

## 👩‍💻 Author

**Trisha Barua**

* GitHub: [@TrishaBarua308](https://github.com/TrishaBarua308)
* Internship: **CodeAlpha C++ Programming Internship**
* Project: **Login & Registration System**

---

## ⭐ Acknowledgement

This project was developed as part of the **CodeAlpha C++ Programming Internship** to gain practical experience in C++ programming and software development.

---

⭐ **If you find this project useful, feel free to star the repository!**
