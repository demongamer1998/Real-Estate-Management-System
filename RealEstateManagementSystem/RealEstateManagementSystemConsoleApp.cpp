#include <iostream>
#include <windows.h>
#include <limits>
#include <conio.h> // For _getch() and _putch() functions (Windows specific)
#include<istream>
#include<fstream>
#include <string>
#include <vector>
#include <sstream> // Include this for stringstream
#include <algorithm>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void userLogin();
void adminLogin();
int main();

using namespace std;

int stringToInt(const string& str) {
    int result = 0;
    stringstream ss(str);
    ss >> result;
    return result;
}

string maskedInput() {
    string pass;
    char ch;
    while ((ch = _getch()) != '\r') { // \r is the Enter key
        if (ch == '\b') { // \b is the Backspace key
            if (pass.length() > 0) {
                pass.erase(pass.length() - 1); // Erase the last character
                cout << "\b \b"; // Erase the last character visually
            }
        } else {
            pass.push_back(ch);
            cout << '*'; // Print '*' instead of the actual character
        }
    }
    cout << endl;
    return pass;
}

class Color {
public:
    enum ConsoleColor {
        Black = 0,
        Blue = FOREGROUND_BLUE,
        Green = FOREGROUND_GREEN,
        Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
        Red = FOREGROUND_RED,
        Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
        Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
        White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        Gray = FOREGROUND_INTENSITY,
        BrightBlue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        BrightGreen = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        BrightCyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        BrightRed = FOREGROUND_RED | FOREGROUND_INTENSITY,
        BrightMagenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        BrightYellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        BrightWhite = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    };

    static void setTextColor(ConsoleColor color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    }
};

class RealEstateProperty {
private:
	int propertyId;
    string propertyType;
    string propertyAddress;
    int bedrooms;
    int bathrooms;
    double price;
    bool is_available;

public:
    // Constructor
    RealEstateProperty(string type, string addr, int beds, int baths, double pr) :
        propertyType(type), propertyAddress(addr), bedrooms(beds), bathrooms(baths), price(pr), is_available(true) {}

    // Method to display property information
    void displayPropertyInfo() {
    	cout << "Property Id: " << propertyId << endl;
        cout << "Property Type: " << propertyType << endl;
        cout << "Address: " << propertyAddress << endl;
        cout << "Bedrooms: " << bedrooms << endl;
        cout << "Bathrooms: " << bathrooms << endl;
        cout << "Price: " << price << endl;
        cout << "Availability: " << (is_available ? "Available" : "Not Available") << endl;
    }

    // Method to mark property as sold
    void markAsSold() {
        is_available = false;
        cout << "Property marked as sold." << endl;
    }

    // Method to update the property's price
    void updatePrice(double newPrice) {
        price = newPrice;
        cout << "Price updated to: " << price << endl;
    }
    
    int getPropertyId() const {return propertyId;}
    string getPropertyType() const {return propertyType;}
    string getPropertyAddress() const {return propertyAddress;}
    int getBedrooms() const {return bedrooms;}
    int getBathrooms() const {return bathrooms;}
    double getPrice() const {return price;}
    bool isAvailable() const {return is_available;} ;
};

class UserProfile {
private:
    int id;
    string username;
    string password;
    bool is_logged_in;

public:
    UserProfile(int user_id, string uname, string pwd)
        : id(user_id), username(uname), password(pwd), is_logged_in(false) {}



	 void login(const string& entered_username, const string& entered_password) {
	    ifstream input("userDatabase.txt");
	
	    if (!input.is_open()) {
	        // Handle unable to open the file
	        return;
	    }
	
	    string line;
	    
	    while (getline(input, line)) {
	        stringstream ss(line);
	        int id; // Declare id variable to store the integer ID
	        string username, password;
	        
	        ss >> id >> username >> password; // Read id, username, and password
	        
	        if (username == entered_username && password == entered_password) {
	            is_logged_in = true;
	            this->id = id; // Assign the id to the class member
	            this->username = username;
	            Color::setTextColor(Color::BrightGreen);
	            cout << "Login successful!" << endl; // If username and password exist
	            Color::setTextColor(Color::White);
	            return;
	        } else {
	            is_logged_in = false;
	        }
	    }
	    input.close();
	}
    
    void showProfile(){
    	Color::setTextColor(Color::BrightCyan);
    	cout<<"USER PROFILE"<<endl;
    	Color::setTextColor(Color::Yellow);
    	cout<<"ID: ";
    	Color::setTextColor(Color::Cyan);
    	cout<<getId()<<endl;
    	Color::setTextColor(Color::Yellow);
    	cout<<"USERNAME: ";
    	Color::setTextColor(Color::Cyan);
    	cout<<getUsername()<<endl;
	}

    void logout() {
        is_logged_in = false;
        Color::setTextColor(Color::BrightGreen);
        cout << "Logged out successfully." << endl;
    }

    // Accessors (getters)
    int getId() const { return id; }
    string getUsername() const { return username; }
    bool isLoggedIn() const { return is_logged_in; }
};

class AdminProfile {
private:
    int id;
    string username;
    string password;
    bool is_logged_in;

public:
    AdminProfile(int user_id, string uname, string pwd)
        : id(user_id), username(uname), password(pwd), is_logged_in(false) {}

	 void login(const string& entered_username, const string& entered_password) {
	    ifstream input("adminDatabase.txt");
	
	    if (!input.is_open()) {
	        // Handle unable to open the file
	        return;
	    }
	
	    string line;
	    
	    while (getline(input, line)) {
	        stringstream ss(line);
	        int id; // Declare id variable to store the integer ID
	        string username, password;
	        
	        ss >> id >> username >> password; // Read id, username, and password
	        
	        if (username == entered_username && password == entered_password) {
	            is_logged_in = true;
	            this->id = id; // Assign the id to the class member
	            this->username = username;
	            Color::setTextColor(Color::BrightGreen);
	            cout << "Login successful!" << endl; // If username and password exist
	            Color::setTextColor(Color::White); 
	            return;
	        } else {
	            is_logged_in = false;
	        }
	    }
	    input.close();
	}
	
    void showProfile(){
    	Color::setTextColor(Color::BrightCyan);
    	cout<<"ADMIN PROFILE"<<endl;
    	Color::setTextColor(Color::Yellow);
    	cout<<"ID: ";
    	Color::setTextColor(Color::Cyan);
    	cout<<getId()<<endl;
    	Color::setTextColor(Color::Yellow);
    	cout<<"USERNAME: ";
    	Color::setTextColor(Color::Cyan);
    	cout<<getUsername()<<endl;
	}
    
    void logout() {
        is_logged_in = false;
        Color::setTextColor(Color::BrightGreen);
        cout << "Logged out successfully." << endl;
    }

    // Accessors (getters)
    int getId() const { return id; }
    string getUsername() const { return username; }
    bool isLoggedIn() const { return is_logged_in; }
};

// Function to generate a random 6-digit number
int generateRandom6DigitNumber() {
    srand(static_cast<unsigned int>(time(NULL))); // Seed the random number generator
    return rand() % 900000 + 100000; // Generate a random number in the range 100000 to 999999
}

// Function to check if the generated USERID already exists in the database
bool userIdExistsInDatabase(int idToCheck) {
    ifstream input("userDatabase.txt");
    int id;

    while (input >> id) {
        if (id == idToCheck) {
            input.close();
            return true; // ID exists in the database
        }
        // Skip the rest of the line
        input.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    input.close();
    return false; // ID doesn't exist in the database
}

// Function to generate a unique 6-digit ID not present in the user database
int generateUserUniqueID() {
    ifstream input("userDatabase.txt");
    int maxID = 0;
    int id;

    while (input >> id) {
        if (id > maxID) {
            maxID = id;
        }
        // Skip the rest of the line
        input.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    input.close();

    int newID;
    do {
        newID = generateRandom6DigitNumber();
    } while (userIdExistsInDatabase(newID));

    return newID;
}

bool checkUserUsernameExists(const string& enteredUsername) {
    ifstream input("userDatabase.txt");
    string line;
    
	if(!input.is_open()){
		system("cls");
		Color::setTextColor(Color::BrightRed);
		cout<<"Cannot connect to database...";
	}

    while (getline(input, line)) {
        vector<string> tokens;
        stringstream ss(line);
        string token;

        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 2 && tokens[1] == enteredUsername) {
            input.close();
            return true;
        }
    }

    input.close();
    return false;
}

void registerUser() {
    string enteredUsername, enteredPassword, confirmPassword;
    bool exist = false;

    do {
        Color::setTextColor(Color::BrightCyan);
        cout << "USER REGISTRATION FORM" << endl;
        Color::setTextColor(Color::Yellow);
        cout << "Enter ";
        Color::setTextColor(Color::BrightGreen);
        cout << "Username";
        Color::setTextColor(Color::Yellow);
        cout << ": ";
        Color::setTextColor(Color::White);
        cin >> enteredUsername;

        Color::setTextColor(Color::Yellow);
        cout << "Enter ";
        Color::setTextColor(Color::BrightGreen);
        cout << "Password";
        Color::setTextColor(Color::Yellow);
        cout << ": ";
        Color::setTextColor(Color::White);
        enteredPassword = maskedInput();

        Color::setTextColor(Color::Yellow);
        cout << "Confirm ";
        Color::setTextColor(Color::BrightGreen);
        cout << "Password";
        Color::setTextColor(Color::Yellow);
        cout << ": ";
        Color::setTextColor(Color::White);
        confirmPassword = maskedInput();

        exist = checkUserUsernameExists(enteredUsername);

        if (confirmPassword != enteredPassword) {
            system("cls");
            Color::setTextColor(Color::Red);
            cout << "Passwords do not match.\n";
        } else if (exist) {
            system("cls");
            Color::setTextColor(Color::Red);
            cout << "Username is already taken." << endl;
        }
    } while (confirmPassword != enteredPassword || exist);

    int newId = generateUserUniqueID(); // Generate a unique ID

    ofstream reg("userDatabase.txt", ios::app);
    reg << newId << " " << enteredUsername << " " << confirmPassword << " " << "0" << endl;
    reg.close();

    system("cls");
    Color::setTextColor(Color::BrightGreen);
    cout << "User registered successfully!" << endl;
    Color::setTextColor(Color::White);
    main();
}


void userLogin() {
    string username="", password="";
    int id = 0; // Initialize ID here
    int counter = 0; // Counter to track login attempts
    
    Color::setTextColor(Color::BrightCyan);
    cout << "USER LOGIN PAGE" << endl;
    Color::setTextColor(Color::Yellow);
    cout << "Username: ";
    Color::setTextColor(Color::White);
    cin >> username;
    Color::setTextColor(Color::Yellow);
    cout << "Password: ";
    Color::setTextColor(Color::White);
    password = maskedInput();

    UserProfile user(id, username, password);
    system("cls");
    
    while (counter < 3) {
        user.login(username, password);
        if (user.isLoggedIn()) {
            user.showProfile(); // If logged in successfully, break out of the loop
            Color::setTextColor(Color::Green);
            cout<<"[";
            Color::setTextColor(Color::Red);
			cout<<"1";
			Color::setTextColor(Color::Green);
			cout<<"] Show All Availabe Property"<<endl;
            cout<<"[";
            Color::setTextColor(Color::Red);
			cout<<"2";
			Color::setTextColor(Color::Green);
			cout<<"] Search Property"<<endl;
            cout<<"[";
            Color::setTextColor(Color::Red);
			cout<<"3";
			Color::setTextColor(Color::Green);
			cout<<"] Buy A Property"<<endl;
            cout<<"[";
            Color::setTextColor(Color::Red);
			cout<<"4";
			Color::setTextColor(Color::Green);
			cout<<"] Edit Account"<<endl;
            cout<<"[";
            Color::setTextColor(Color::Red);
			cout<<"5";
			Color::setTextColor(Color::Green);
			cout<<"] Logout"<<endl;
            Color::setTextColor(Color::White);
            int option;
            Color::setTextColor(Color::Yellow);
            cout<<"Enter your choice: ";
            Color::setTextColor(Color::White);
            cin.ignore(50,'\n');
            while(!(cin>>option)||option<1||option>5){
            		system("cls");
			        Color::setTextColor(Color::Red);
			        cout << "Invalid choice. Please enter your choice between ";
			        Color::setTextColor(Color::BrightGreen);
			        cout<<"[1] ";
			        Color::setTextColor(Color::Yellow);
			        cout<<"to ";
			        Color::setTextColor(Color::BrightGreen);
			        cout<<"[5]:\n";
			        user.showProfile();
			        Color::setTextColor(Color::Green);
		            cout<<"[";
		            Color::setTextColor(Color::Red);
					cout<<"1";
					Color::setTextColor(Color::Green);
					cout<<"] Show All Availabe Property"<<endl;
		            cout<<"[";
		            Color::setTextColor(Color::Red);
					cout<<"2";
					Color::setTextColor(Color::Green);
					cout<<"] Search Property"<<endl;
		            cout<<"[";
		            Color::setTextColor(Color::Red);
					cout<<"3";
					Color::setTextColor(Color::Green);
					cout<<"] Buy A Property"<<endl;
		            cout<<"[";
		            Color::setTextColor(Color::Red);
					cout<<"4";
					Color::setTextColor(Color::Green);
					cout<<"] Edit Account"<<endl;
		            cout<<"[";
		            Color::setTextColor(Color::Red);
					cout<<"5";
					Color::setTextColor(Color::Green);
					cout<<"] Logout"<<endl;
		            Color::setTextColor(Color::White);
			        Color::setTextColor(Color::Yellow);
			         cin.ignore(50,'\n');
			        cout<<"Enter your choice: ";
			        Color::setTextColor(Color::White);
			}
            
            switch(option){
            	
			}
            
            break;
        } else {
            counter++;
            Color::setTextColor(Color::Red);
            cout << "Incorrect password. Login failed. ";
            Color::setTextColor(Color::White);
            cout << "Please try again." << endl;
            Color::setTextColor(Color::BrightGreen);
            cout << "Login attempt [" << counter << "]" << endl;
            if (counter < 3) {
                // Allow re-entry of credentials for remaining attempts
                Color::setTextColor(Color::Yellow);
                cout << "Username: ";
                Color::setTextColor(Color::White);
                cin >> username;
                Color::setTextColor(Color::Yellow);
                cout << "Password: ";
                Color::setTextColor(Color::White);
                password = maskedInput();
                system("cls");
            }
        }
    }

    if (counter == 3 && !user.isLoggedIn()) {
        system("cls");
        Color::setTextColor(Color::Red);
        cout << "Reached maximum login attempts.";
        Color::setTextColor(Color::White);
        cout<<"Please create an account to ";
        Color::setTextColor(Color::BrightGreen);
        cout<<"login";
        Color::setTextColor(Color::White);
        cout<<"."<<endl;
        main(); // Redirect to main menu
    }
    
    
}

// Function to check if the generated USERID already exists in the database
bool adminIdExistsInDatabase(int idToCheck) {
    ifstream input("adminDatabase.txt");
    int id;

    while (input >> id) {
        if (id == idToCheck) {
            input.close();
            return true; // ID exists in the database
        }
        // Skip the rest of the line
        input.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    input.close();
    return false; // ID doesn't exist in the database
}

// Function to generate a unique 6-digit ID not present in the user database
int generateAdminUniqueID() {
    ifstream input("adminDatabase.txt");
    int maxID = 0;
    int id;

    while (input >> id) {
        if (id > maxID) {
            maxID = id;
        }
        // Skip the rest of the line
        input.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    input.close();

    int newID;
    do {
        newID = generateRandom6DigitNumber();
    } while (adminIdExistsInDatabase(newID));

    return newID;
}

bool checkAdminUsernameExists(const string& enteredUsername) {
    ifstream input("adminDatabase.txt");
    string line;

    while (getline(input, line)) {
        vector<string> tokens;
        stringstream ss(line);
        string token;

        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 2 && tokens[1] == enteredUsername) {
            input.close();
            return true;
        }
    }

    input.close();
    return false;
}

void registerAdmin() {
    string enteredUsername, enteredPassword, confirmPassword;
    bool exist = false;

    do {
        Color::setTextColor(Color::BrightCyan);
        cout << "ADMIN REGISTRATION FORM" << endl;
        Color::setTextColor(Color::Yellow);
        cout << "Enter ";
        Color::setTextColor(Color::BrightGreen);
        cout << "Username";
        Color::setTextColor(Color::Yellow);
        cout << ": ";
        Color::setTextColor(Color::White);
        cin >> enteredUsername;

        Color::setTextColor(Color::Yellow);
        cout << "Enter ";
        Color::setTextColor(Color::BrightGreen);
        cout << "Password";
        Color::setTextColor(Color::Yellow);
        cout << ": ";
        Color::setTextColor(Color::White);
        enteredPassword = maskedInput();

        Color::setTextColor(Color::Yellow);
        cout << "Confirm ";
        Color::setTextColor(Color::BrightGreen);
        cout << "Password";
        Color::setTextColor(Color::Yellow);
        cout << ": ";
        Color::setTextColor(Color::White);
        confirmPassword = maskedInput();

        exist = checkAdminUsernameExists(enteredUsername);

        if (confirmPassword != enteredPassword) {
            system("cls");
            Color::setTextColor(Color::Red);
            cout << "Passwords do not match.\n";
        } else if (exist) {
            system("cls");
            Color::setTextColor(Color::Red);
            cout << "Username is already taken." << endl;
        }
    } while (confirmPassword != enteredPassword || exist);

    int newId = generateAdminUniqueID(); // Generate a unique ID

    ofstream reg("adminDatabase.txt", ios::app);
    reg << newId << " " << enteredUsername << " " << confirmPassword << " " << "0" << endl;
    reg.close();

    system("cls");
    Color::setTextColor(Color::BrightGreen);
    cout << "User registered successfully!" << endl;
    Color::setTextColor(Color::White);
    main();
}


void adminLogin() {
    string username, password;
    int id = 0; // Initialize ID here
    int counter = 0; // Counter to track login attempts
    
    Color::setTextColor(Color::BrightCyan);
    cout << "ADMIN LOGIN PAGE" << endl;
    Color::setTextColor(Color::Yellow);
    cout << "Username: ";
    Color::setTextColor(Color::White);
    cin >> username;
    Color::setTextColor(Color::Yellow);
    cout << "Password: ";
    Color::setTextColor(Color::White);
    password = maskedInput();

    AdminProfile admin(id, username, password);
    system("cls");
    
    while (counter < 3) {
        admin.login(username, password);
        if (admin.isLoggedIn()) {
        	admin.showProfile(); // If logged in successfully, break out of the loop
            break;
        } else {
            counter++;
            Color::setTextColor(Color::Red);
            cout << "Incorrect password. Login failed. ";
            Color::setTextColor(Color::White);
            cout << "Please try again." << endl;
            Color::setTextColor(Color::BrightGreen);
            cout << "Login attempt [" << counter << "]" << endl;
            if (counter < 3) {
                // Allow re-entry of credentials for remaining attempts
                Color::setTextColor(Color::Yellow);
                cout << "Username: ";
                Color::setTextColor(Color::White);
                cin >> username;
                Color::setTextColor(Color::Yellow);
                cout << "Password: ";
                Color::setTextColor(Color::White);
                password = maskedInput();
				AdminProfile admin(id, username, password);
                system("cls");
            }
        }
    }

    if (counter == 3 && !admin.isLoggedIn()) {
        system("cls");
        Color::setTextColor(Color::Red);
        cout << "Reached maximum login attempts.";
        Color::setTextColor(Color::White);
        cout<<"Please create an account to ";
        Color::setTextColor(Color::BrightGreen);
        cout<<"login";
        Color::setTextColor(Color::White);
        cout<<"."<<endl;
        main(); // Redirect to main menu
    }
    
}

int main(){
	
	int choice;
    
    Color::setTextColor(Color::BrightCyan);
	cout << "REAL ESTATE MANAGEMENT SYSTEM" << endl;
	Color::setTextColor(Color::Green);
	cout << "[";
	Color::setTextColor(Color::Red);
	cout<<"1";
	Color::setTextColor(Color::Green);
	cout<<"] Login As Admin" << endl;
	cout << "[";
	Color::setTextColor(Color::Red);
	cout<<"2";
	Color::setTextColor(Color::Green);
	cout<<"] Login As User" << endl;
	cout << "[";
	Color::setTextColor(Color::Red);
	cout<<"3";
	Color::setTextColor(Color::Green);
	cout<<"] Register As User" << endl;
	cout << "[";
	Color::setTextColor(Color::Red);
	cout<<"4";
	Color::setTextColor(Color::Green);
	cout<<"] Exit" << endl;
	
    Color::setTextColor(Color::Yellow);
	cout << "Enter your choice: ";
	// Set white text
	Color::setTextColor(Color::White);
    while (!(cin >> choice) || choice < 1 || choice > 4) {
        system("cls");
        Color::setTextColor(Color::Red);;
        cout << "Invalid choice. Please enter your choice between ";
        Color::setTextColor(Color::BrightGreen);;
        cout<<"[1] ";
        Color::setTextColor(Color::Yellow);;
        cout<<"to ";
        Color::setTextColor(Color::BrightGreen);;
        cout<<"[4]:\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        main();
    }
    
    switch (choice) {
        case 1:
        	system("cls");
        	adminLogin();
            break;
        case 2:
        	system("cls");
        	userLogin();
            break;
         case 3:
			system("cls");
            registerUser();
            break;
        case 4:
            cout << "Exiting the program." << endl;
            return 0;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
	}
	return 0;
}

