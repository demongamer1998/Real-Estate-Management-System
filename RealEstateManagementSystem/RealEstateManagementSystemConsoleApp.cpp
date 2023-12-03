#include <iostream>
#include <windows.h>
#include <limits>
#include <conio.h> // For _getch() and _putch() functions (Windows specific)
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> // Include this for stringstream
#include <algorithm>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <unistd.h>
#include <iomanip>
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

void loginCountdown(int seconds) {
    time_t start_time = time(NULL);

    while (difftime(time(NULL), start_time) < seconds) {
    	Color::setTextColor(Color::White);
        cout << "Redirecting to your account in ";
        Color::setTextColor(Color::BrightGreen);
		cout << fixed << setprecision(0) << seconds - difftime(time(NULL), start_time) ;
		Color::setTextColor(Color::White);
		cout << " seconds" << endl;
        sleep(1); // Waits for 1 second
        system("cls");
    }
}

void logoutCountdown(int seconds) {
    time_t start_time = time(NULL);

    while (difftime(time(NULL), start_time) < seconds) {
    	Color::setTextColor(Color::White);
        cout << "Redirecting to main in " ;
        Color::setTextColor(Color::BrightGreen);
		cout << fixed << setprecision(0) << seconds - difftime(time(NULL), start_time) ;
		Color::setTextColor(Color::White);
		cout << " seconds" << endl;
        sleep(1); // Waits for 1 second
        system("cls");
    }
}

void countdown(int seconds) {
    time_t start_time = time(NULL);
    while (difftime(time(NULL), start_time) < seconds) {
        sleep(1); // Waits for 1 second
        system("cls");
    }
}

//Generate PropertyID
string generatePropertyId() {
    srand(static_cast<unsigned int>(time(NULL))); // Seed the random number generator
    const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Alphanumeric characters

    string propertyId;
    propertyId.reserve(6);

    for (int i = 0; i < 6; ++i) {
        propertyId += charset[rand() % charset.length()];
    }

    return propertyId;
}

class RealEstateProperty {
private:
	string propertyId;
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

    bool hasSpaces(const string &str) {
        for (size_t i = 0; i < str.length(); ++i) {
            if (isspace(static_cast<unsigned char>(str[i]))) {
                return true;
            }
        }
        return false;
    }
    
	void showAllProperty() {
	    ifstream input("globalProperty.txt");
	    string propertyId, propertyType, propertyAddress;
	    int bedrooms, bathrooms;
	    double price;
	    bool isAvailable;
	
	    if (!input.is_open()||input.peek() == ifstream::traits_type::eof()) {
	    	Color::setTextColor(Color::BrightRed);
	        cout << "\n    NO RECORDS AVAILABLE YET" << endl << endl;
	        Color::setTextColor(Color::BrightYellow);
	        cout << "---------------------------------" << endl;
	        return;
	    }
	
	    while (input >> propertyId >> propertyType >> propertyAddress >> bedrooms >> bathrooms >> price >> isAvailable) {
	        // Display property details here as needed
	        Color::setTextColor(Color::BrightRed);
	        cout << "PROPERTY'S DETAILS"<<endl;
	        Color::setTextColor(Color::Yellow);
	        cout << "Property ";
	        Color::setTextColor(Color::BrightGreen);
			cout << "ID: " ;
			Color::setTextColor(Color::BrightCyan);
			cout << propertyId << endl;
			Color::setTextColor(Color::Yellow);
	        cout << "Property ";
	        Color::setTextColor(Color::BrightGreen);
			cout << "Type: " ;
			Color::setTextColor(Color::BrightCyan);
			cout << propertyType << endl;
			Color::setTextColor(Color::Yellow);
	        cout << "Property ";
	        Color::setTextColor(Color::BrightGreen);
			cout << "Address: " ;
			Color::setTextColor(Color::BrightCyan);
			cout<< propertyAddress << endl;
			Color::setTextColor(Color::Yellow);
	        cout << "No: of ";
	        Color::setTextColor(Color::BrightGreen);
			cout << "Bedrooms: " ;
			Color::setTextColor(Color::BrightCyan);
			cout<< bedrooms << endl;
			Color::setTextColor(Color::Yellow);
	        cout << "No: of ";
	        Color::setTextColor(Color::BrightGreen);
			cout << "Bathrooms: " ;
			Color::setTextColor(Color::BrightCyan);
			cout<< bathrooms << endl;
			Color::setTextColor(Color::Yellow);
	        cout <<fixed<<setprecision(2)<< "Price: ";
	        Color::setTextColor(Color::BrightGreen);
			cout << "PHP " ;
			Color::setTextColor(Color::BrightCyan);
			cout<< price << endl;
			Color::setTextColor(Color::Yellow);
	        cout << "Available: " ;
	        Color::setTextColor(isAvailable ? Color::BrightCyan : Color::BrightRed);
			cout<< (isAvailable ? "Yes" : "No") << endl;
			Color::setTextColor(Color::BrightYellow);
	        cout << "---------------------------------" << endl;
	    }
	
	    input.close();
	}
        
	//CreateProperty Constructor
	void createProperty(){
			string propertyType, propertyAddress; 
			int bedrooms, bathrooms; 
			double price;
	        Color::setTextColor(Color::BrightCyan);
	        cout << "CREATE PROPERTY TO SELL" << endl;
	        Color::setTextColor(Color::Red);
			cout << "NOTE: ";
			Color::setTextColor(Color::Yellow);
			cout << "NO ";
			Color::setTextColor(Color::BrightGreen);
			cout << "SPACES ";
			Color::setTextColor(Color::Blue);
			cout << "REQUIRED" << endl;
	        Color::setTextColor(Color::Yellow);
	        cout << "Enter ";
	        Color::setTextColor(Color::BrightGreen);
	        cout << "Property Type";
	        Color::setTextColor(Color::Yellow);
	        cout << ": ";
	        Color::setTextColor(Color::White);
	        cin >> propertyType;
			cin.ignore(50,'\n');
			
	        Color::setTextColor(Color::Yellow);
	        cout << "Enter ";
	        Color::setTextColor(Color::BrightGreen);
	        cout << "Property Address";
	        Color::setTextColor(Color::Yellow);
	        cout << ": ";
	        Color::setTextColor(Color::White);
	        cin >> propertyAddress;
	        cin.ignore(50,'\n');
	        
	        Color::setTextColor(Color::Yellow);
	        cout << "Enter ";
	        Color::setTextColor(Color::BrightGreen);
	        cout << "Property Beds";
	        Color::setTextColor(Color::Yellow);
	        cout << ": ";
	        Color::setTextColor(Color::White);
	        cin >> bedrooms;
	        cin.ignore(50,'\n');
	        
	        Color::setTextColor(Color::Yellow);
	        cout << "Enter ";
	        Color::setTextColor(Color::BrightGreen);
	        cout << "Property Bathrooms";
	        Color::setTextColor(Color::Yellow);
	        cout << ": ";
	        Color::setTextColor(Color::White);
	        cin >> bathrooms;
	        cin.ignore(50,'\n');
	        
	        Color::setTextColor(Color::Yellow);
	        cout << "Enter ";
	        Color::setTextColor(Color::BrightGreen);
	        cout << "Property Price";
	        Color::setTextColor(Color::Yellow);
	        cout << ": ";
	        Color::setTextColor(Color::White);
	        cin >> price;
	        cin.ignore(50,'\n');
	
	        string newId = generatePropertyUniqueID(); // Generate a unique ID
	
	        ofstream createProperty("globalProperty.txt", ios::app);
	        createProperty << newId << " " << propertyType << " " << propertyAddress << " " << bedrooms << " " << bathrooms << " " << price << " " << is_available << endl;
	        createProperty.close();
		
		    system("cls");
		    Color::setTextColor(Color::BrightGreen);
		    cout << "Property has been created and post successfully." << endl;
		    Color::setTextColor(Color::White);
		    
	}
	
	
    void updateProperty() {
        ifstream inputFile("globalProperty.txt");
        ofstream tempFile("tempProperty.txt");

        string propertyIdToUpdate;
        system("cls");
        Color::setTextColor(Color::Cyan);
        cout << "UPDATE PROPERTY" << endl;
        Color::setTextColor(Color::Yellow);
        cout << "Enter Property ID: ";
        Color::setTextColor(Color::White);
        while (!(cin >> propertyIdToUpdate)) {
            Color::setTextColor(Color::Yellow);
            cout << "Enter Property ID: ";
            Color::setTextColor(Color::White);
        }

        if (!inputFile.is_open() || !tempFile.is_open()) {
            cout << "Unable to open the property database." << endl;
            return;
        }

        bool propertyFound = false;
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string id;
            ss >> id;

            if (id == propertyIdToUpdate) {
                propertyFound = true;

                // Read old property details
                ss >> propertyType >> propertyAddress >> bedrooms >> bathrooms >> price >> is_available;

                bool updated = false; // Flag to track if any update was made

                while (true) {
                    int choice;
				    system("cls");
				    Color::setTextColor(Color::Cyan);
				    cout << "UPDATE PROPERTY" << endl;
		            Color::setTextColor(Color::White);
		            cout << "Property ";
		            Color::setTextColor(Color::BrightGreen);
					cout << "found. " << endl;
		            Color::setTextColor(Color::White);
					cout << "What would you like to ";
					Color::setTextColor(Color::Red);
					cout << "update?" << endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "1";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Property Type" << endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "2";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Property Address" << endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "3";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Number of Bedrooms" << endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "4";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Number of Bathrooms" << endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "5";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Price" << endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "6";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Exit" << endl;
					Color::setTextColor(Color::Yellow);
		            cout << "Enter your choice: ";
		            Color::setTextColor(Color::White);
                    cin >> choice;

                    if (choice == 6) {
	                	Color::setTextColor(Color::BrightGreen);
	                    cout << "Exiting update mode." << endl;
                        break;
                    }

                    switch (choice) {
                        case 1:
							{
								system("cls");
								string newPropertyType;
								Color::setTextColor(Color::Cyan);
								cout << "UPDATE PROPERTY" << endl;
						        Color::setTextColor(Color::Red);
								cout << "NOTE: ";
								Color::setTextColor(Color::Yellow);
								cout << "NO ";
								Color::setTextColor(Color::BrightGreen);
								cout << "SPACES ";
								Color::setTextColor(Color::Blue);
								cout << "REQUIRED" << endl;
	
							    do {
									Color::setTextColor(Color::Yellow);
									cout << "Enter updated Property Type: ";
									Color::setTextColor(Color::BrightYellow);
							        cin.ignore(); // Clear the input buffer
							        getline(cin, newPropertyType);
							
							        if (hasSpaces(newPropertyType)) {
							        	system("cls");
							        	Color::setTextColor(Color::Blue);
							            cout << "Spaces ";
							            Color::setTextColor(Color::White);
										cout << "are ";
										Color::setTextColor(Color::Red);
										cout << "not ";
										Color::setTextColor(Color::BrightGreen);
										cout << "allowed. ";
										Color::setTextColor(Color::White);
										cout << "Please enter the ";
										Color::setTextColor(Color::Yellow);
										cout << "Property ";
										Color::setTextColor(Color::BrightGreen);
										cout << "Type ";
										Color::setTextColor(Color::Red);
										cout << "without ";
										Color::setTextColor(Color::BrightCyan);
										cout << "spaces." << endl;
										Color::setTextColor(Color::Cyan);
										cout << "UPDATE PROPERTY" << endl;
								        Color::setTextColor(Color::Red);
										cout << "NOTE: ";
										Color::setTextColor(Color::Yellow);
										cout << "NO ";
										Color::setTextColor(Color::BrightGreen);
										cout << "SPACES ";
										Color::setTextColor(Color::Blue);
										cout << "REQUIRED" << endl;
							        }
							    } while (hasSpaces(newPropertyType));
								
						        if (newPropertyType == propertyType) {
						        	Color::setTextColor(Color::White);
						            cout << "No change in Property ";
						            Color::setTextColor(Color::BrightGreen);
									cout << "Type." << endl;
						        } else {
						            propertyType = newPropertyType;
						            updated = true;
						        }
								
							}
                            break;
                        case 2:
							{
								system("cls");
								string newPropertyAddress;
								Color::setTextColor(Color::Cyan);
								cout << "UPDATE PROPERTY" << endl;
						        Color::setTextColor(Color::Red);
								cout << "NOTE: ";
								Color::setTextColor(Color::Yellow);
								cout << "NO ";
								Color::setTextColor(Color::BrightGreen);
								cout << "SPACES ";
								Color::setTextColor(Color::Blue);
								cout << "REQUIRED" << endl;
	
							    do {
									Color::setTextColor(Color::Yellow);
									cout << "Enter updated Property Address: ";
									Color::setTextColor(Color::BrightYellow);
							        cin.ignore(); // Clear the input buffer
							        getline(cin, newPropertyAddress);
							
							        if (hasSpaces(newPropertyAddress)) {
							        	system("cls");
							        	Color::setTextColor(Color::Blue);
							            cout << "Spaces ";
							            Color::setTextColor(Color::White);
										cout << "are ";
										Color::setTextColor(Color::Red);
										cout << "not ";
										Color::setTextColor(Color::BrightGreen);
										cout << "allowed. ";
										Color::setTextColor(Color::White);
										cout << "Please enter the ";
										Color::setTextColor(Color::Yellow);
										cout << "Property ";
										Color::setTextColor(Color::BrightGreen);
										cout <<"Type ";
										Color::setTextColor(Color::Red);
										cout << "without ";
										Color::setTextColor(Color::BrightCyan);
										cout << "spaces." << endl;
										Color::setTextColor(Color::Cyan);
										cout << "UPDATE PROPERTY" << endl;
								        Color::setTextColor(Color::Red);
										cout << "NOTE: ";
										Color::setTextColor(Color::Yellow);
										cout << "NO ";
										Color::setTextColor(Color::BrightGreen);
										cout << "SPACES ";
										Color::setTextColor(Color::Blue);
										cout << "REQUIRED" << endl;
							        }
							    } while (hasSpaces(newPropertyAddress));
								
						        if (newPropertyAddress == propertyAddress) {
						        	Color::setTextColor(Color::White);
						            cout << "No change in Property ";
						            Color::setTextColor(Color::BrightGreen);
									cout << "Address." << endl;
						        } else {
						            propertyAddress = newPropertyAddress;
						            updated = true;
						        }
							}
                            break;
                        case 3:
							{
			                	system("cls");
			                	int newBedrooms;
							    Color::setTextColor(Color::Cyan);
							    cout << "UPDATE PROPERTY" << endl;
						        Color::setTextColor(Color::Red);
								cout << "NOTE: ";
								Color::setTextColor(Color::Yellow);
								cout << "NO ";
								Color::setTextColor(Color::BrightGreen);
								cout << "SPACES ";
								Color::setTextColor(Color::Blue);
								cout << "REQUIRED" << endl;
			                	Color::setTextColor(Color::Yellow);
			                    cout << "Enter updated Number of Bedrooms: ";
			                    Color::setTextColor(Color::BrightYellow);
			                    while(!(cin >> newBedrooms)){
			                	Color::setTextColor(Color::Yellow);
			                    cout << "Enter updated Number of Bedrooms: ";
			                    Color::setTextColor(Color::BrightYellow);
			                	}
						        if (newBedrooms == bedrooms) {
						        	Color::setTextColor(Color::White);
						            cout << "No change in Property ";
						            Color::setTextColor(Color::BrightGreen);
									cout << "Bedrooms." << endl;
						        } else {
						            bedrooms = newBedrooms;
						            updated = true;
						        }	
							}
                            break;
                        case 4:
							{
			                	system("cls");
			                	int newBathrooms;
							    Color::setTextColor(Color::Cyan);
							    cout << "UPDATE PROPERTY" << endl;
						        Color::setTextColor(Color::Red);
								cout << "NOTE: ";
								Color::setTextColor(Color::Yellow);
								cout << "NO ";
								Color::setTextColor(Color::BrightGreen);
								cout << "SPACES ";
								Color::setTextColor(Color::Blue);
								cout << "REQUIRED" << endl;
			                	Color::setTextColor(Color::Yellow);
			                    cout << "Enter updated Number of Bathrooms: ";
			                    Color::setTextColor(Color::BrightYellow);
			                    while(!(cin >> newBathrooms)){
				                	Color::setTextColor(Color::Yellow);
				                    cout << "Enter updated Number of Bathrooms: ";
				                    Color::setTextColor(Color::BrightYellow);
			                	}
						        if (newBathrooms == bathrooms) {
						        	Color::setTextColor(Color::White);
						            cout << "No change in Property ";
						            Color::setTextColor(Color::BrightGreen);
									cout << "Bathrooms." << endl;
						        } else {
						            bathrooms = newBathrooms;
						            updated = true;
						        }	
							}
                            break;
                        case 5:
							{
			                	system("cls");
			                	double newPrice;
							    Color::setTextColor(Color::Cyan);
							    cout << "UPDATE PROPERTY" << endl;
						        Color::setTextColor(Color::Red);
								cout << "NOTE: ";
								Color::setTextColor(Color::Yellow);
								cout << "NO ";
								Color::setTextColor(Color::BrightGreen);
								cout << "SPACES ";
								Color::setTextColor(Color::Blue);
								cout << "REQUIRED" << endl;
			                	Color::setTextColor(Color::Yellow);
			                    cout << "Enter updated Price: ";
			                    Color::setTextColor(Color::BrightYellow);
			                    while(!(cin >> newPrice)){
			                	Color::setTextColor(Color::Yellow);
			                    cout << "Enter updated Price: ";
			                    Color::setTextColor(Color::BrightYellow);
			                	}
						        if (newPrice == price) {
						        	Color::setTextColor(Color::White);
						            cout << "No change in Property ";
						            Color::setTextColor(Color::BrightGreen);
									cout << "Price." << endl;
						        } else {
						            price = newPrice;
						            updated = true;
						        }
							}
                            break;
                        default:
				            Color::setTextColor(Color::Red);
				            cout << "Invalid choice. ";
				            Color::setTextColor(Color::White);
							cout << "Please enter your choice between ";
				            Color::setTextColor(Color::BrightCyan);
				            cout << "[";
				            Color::setTextColor(Color::BrightGreen);
							cout << "1";
							Color::setTextColor(Color::BrightCyan);
							cout << "] ";
				            Color::setTextColor(Color::Yellow);
				            cout << "to ";
				            Color::setTextColor(Color::BrightCyan);
				            cout << "[";
				            Color::setTextColor(Color::BrightGreen);
							cout << "6";
							Color::setTextColor(Color::BrightCyan);
							cout << "] ";
				            Color::setTextColor(Color::White);
							cout << "only.\n";
                            continue; // Repeat the loop for a valid choice
                    }
                }

                // Write the updated or unchanged data to the temp file
                if (updated) {
                    tempFile << propertyIdToUpdate << " " << propertyType << " " << propertyAddress << " " << bedrooms << " "
                             << bathrooms << " " << price << " " << is_available << endl;
	                system("cls");
	                Color::setTextColor(Color::White);
	                cout << "Property with ";
	                Color::setTextColor(Color::Red);
					cout << "ID " ;
					Color::setTextColor(Color::BrightCyan);
					cout << "[";
					Color::setTextColor(Color::BrightGreen);
					cout << propertyIdToUpdate ;
					Color::setTextColor(Color::BrightCyan);
					cout << "]";
					Color::setTextColor(Color::White);
					cout << " has been updated ";
					Color::setTextColor(Color::BrightGreen);
					cout << "successfully." << endl;
					Color::setTextColor(Color::White);
                } else {
                    // If no changes were made, write the existing line to the temp file
	            	system("cls");
	            	Color::setTextColor(Color::White);
	                cout << "No ";
	                Color::setTextColor(Color::BrightGreen);
					cout << "changes ";
					Color::setTextColor(Color::Red);
					cout << "detected";
					Color::setTextColor(Color::White);
					cout << ".";
					Color::setTextColor(Color::BrightGreen);
					cout << " Update ";
					Color::setTextColor(Color::Red);
					cout << "canceled";
					Color::setTextColor(Color::White);
					cout << "." << endl;
                    tempFile << line << endl;
                }
            } else {
                tempFile << line << endl; // Write the existing line to the temp file
            }
        }

        inputFile.close();
        tempFile.close();

        if (propertyFound) {
            remove("globalProperty.txt");
            rename("tempProperty.txt", "globalProperty.txt");
        } else {
            remove("tempProperty.txt");
            system("cls");
            Color::setTextColor(Color::White);
            cout << "Property with ";
            Color::setTextColor(Color::Yellow);
			cout << "ID " ;
			Color::setTextColor(Color::BrightCyan);
			cout << "[" ;
			Color::setTextColor(Color::BrightGreen);
			cout << propertyIdToUpdate ;
			Color::setTextColor(Color::BrightCyan);
			cout << "]" ;
			Color::setTextColor(Color::White);
			cout << " not ";
			Color::setTextColor(Color::Red);
			cout << "found." << endl;
        }
    }
	
	
	
	//DeleteProperty Constructor
	void deleteProperty() {
	    ifstream inputFile("globalProperty.txt");
	    ofstream tempFile("tempProperty.txt");
	    string propertyIdToDelete;
	    
	    Color::setTextColor(Color::Cyan);
	    cout << "DELETE PROPERTY" << endl;
	    Color::setTextColor(Color::Yellow);
	    cout << "Enter Property ID: ";
	    Color::setTextColor(Color::White);
	    while(!(cin>>propertyIdToDelete)){
	    	Color::setTextColor(Color::Yellow);
	    	cout << "Enter Property ID: ";
	    	Color::setTextColor(Color::White);
		}
	
	    if (!inputFile.is_open() || !tempFile.is_open()) {
	        cout << "Unable to open the property database." << endl;
	        return;
	    }
	
	    bool propertyFound = false;
	    string line;
	    while (getline(inputFile, line)) {
	        stringstream ss(line);
	        string id;
	        ss >> id;
	
	        if (id == propertyIdToDelete) {
	            propertyFound = true;
	            continue; // Skip writing this line to temp file
	        }
	
	        tempFile << line << endl;
	    }
	
	    inputFile.close();
	    tempFile.close();
	
	    if (propertyFound) {
	        remove("globalProperty.txt");
	        rename("tempProperty.txt", "globalProperty.txt");
	        system("cls");
		    Color::setTextColor(Color::White);
	        cout << "Property with ";
	        Color::setTextColor(Color::Red);
			cout << "ID " ;
			Color::setTextColor(Color::BrightCyan);
			cout << "[";
			Color::setTextColor(Color::BrightGreen);
			cout << propertyIdToDelete ;
			Color::setTextColor(Color::BrightCyan);
			cout << "]";
			Color::setTextColor(Color::White);
			cout << " has been ";
			Color::setTextColor(Color::Red);
			cout << "deleted ";
			Color::setTextColor(Color::BrightGreen);
			cout << "successfully." << endl;
			Color::setTextColor(Color::White);
	    } else {
	    	system("cls");
	        remove("tempProperty.txt");
	        Color::setTextColor(Color::White);
	        cout << "Property with ";
	        Color::setTextColor(Color::Yellow);
			cout << "ID ";
			Color::setTextColor(Color::BrightCyan);
			cout << "[";
			Color::setTextColor(Color::BrightGreen);
			cout << propertyIdToDelete ;
			Color::setTextColor(Color::BrightCyan);
			cout << "]";
			Color::setTextColor(Color::White);
			cout << " not ";
			Color::setTextColor(Color::Red);
			cout << "found." << endl;
			Color::setTextColor(Color::White);
	    }
	}
	
	//Checks Generated PropertyID	
	bool checkPropertyIdExists(const string& enteredIdToCheck) {
	    ifstream input("globalProperty.txt");
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
	
	        if (tokens.size() >= 1 && tokens[1] == enteredIdToCheck) {
	            input.close();
	            return true;
	        }
	    }
	
	    input.close();
	    return false;
	}


    // Function to generate a unique 6-digit ID not present in the user database
    string generatePropertyUniqueID() {
        ifstream input("globalProperty.txt");
        string maxID = "";
        string id;

        while (input >> id) {
            if (id > maxID) {
                maxID = id;
            }
            // Skip the rest of the line
            input.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        input.close();

        string newID;
        do {
            newID = generatePropertyId();
        } while (checkPropertyIdExists(newID));

        return newID;
    }
    
    string getPropertyId() const {return propertyId;}
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
	            this->password = password;
	            Color::setTextColor(Color::BrightGreen);
	            cout << "LoggedIn successfully." << endl; // If username and password exist
	            Color::setTextColor(Color::White);
	            countdown(1);
	            loginCountdown(3);
	            system("cls");
	            return;
	        } else {
	            is_logged_in = false;
	        }
	    }
	    input.close();
	}
	
	int userOption(int id, string username, string password){
		int option;
		UserProfile user(id, username, password);
		    while (true) {
		        Color::setTextColor(Color::Yellow);
		        cout << "Enter your choice: ";
		        Color::setTextColor(Color::White);
		
		        if (!(cin >> option) || option < 1 || option > 5) {
		            cin.clear(); // Clear error flags
		            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
		            system("cls");
		            Color::setTextColor(Color::Red);
		            cout << "Invalid choice. ";
		            Color::setTextColor(Color::White);
					cout << "Please enter your choice between ";
		            Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightGreen);
					cout << "1";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
		            Color::setTextColor(Color::Yellow);
		            cout << "to ";
		            Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightGreen);
					cout << "5";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::White);
					cout << "only.\n";
		            user.showProfile(); // If logged in successfully, show user profile
		            // Display menu options
		            Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "1";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Show All Availabe Property //Coming soon"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "2";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Search Property //Coming soon"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "3";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Buy A Property //Coming soon"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "4";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Edit Account //Coming soon"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "5";;
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Logout"<<endl;
		            Color::setTextColor(Color::White);
		            Color::setTextColor(Color::Yellow);;
		            // Display other menu options similarly
		            Color::setTextColor(Color::White);
		            continue; // Restart the loop
		        }
		
		        // Clear any additional characters in the input buffer
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		        // Valid input, break the loop
		        break;
		    }
		return option;
	}
    
    void showProfile(){
    	Color::setTextColor(Color::Cyan);
    	cout<<"USER PROFILE"<<endl;
    	Color::setTextColor(Color::Yellow);
    	cout<<"ID: ";
    	Color::setTextColor(Color::BrightYellow);
    	cout<<getId()<<endl;
    	Color::setTextColor(Color::Yellow);
    	cout<<"USERNAME: ";
    	Color::setTextColor(Color::BrightYellow);
    	cout<<getUsername()<<endl;
	}

    void logout() {
        is_logged_in = false;
        Color::setTextColor(Color::BrightGreen);
        cout << "Logged out successfully." << endl;
        countdown(1);
        logoutCountdown(3);
        system("cls");
    }

    // Accessors (getters)
    int getId() const { return id; }
    string getPassword() const {return password;} 
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
	            cout << "LoggedIn successfully." << endl; // If username and password exist
	            Color::setTextColor(Color::White);
		        countdown(1);
		        loginCountdown(3);
		        system("cls");
	            Color::setTextColor(Color::White); 
	            return;
	        } else {
	            is_logged_in = false;
	        }
	    }
	    input.close();
	}
	
    void showProfile(){
    	Color::setTextColor(Color::Cyan);
    	cout<<"ADMIN PROFILE"<<endl;
    	Color::setTextColor(Color::Yellow);
    	cout<<"ID: ";
    	Color::setTextColor(Color::BrightYellow);
    	cout<<getId()<<endl;
    	Color::setTextColor(Color::Yellow);
    	cout<<"USERNAME: ";
    	Color::setTextColor(Color::BrightYellow);
    	cout<<getUsername()<<endl;
	}
	
	int adminOption(int id, string username, string password){
		int option;
		AdminProfile admin(id, username, password);
		    while (true) {
		        Color::setTextColor(Color::Yellow);
		        cout << "Enter your choice: ";
		        Color::setTextColor(Color::White);
		
		        if (!(cin >> option) || option < 1 || option > 6) {
		            cin.clear(); // Clear error flags
		            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
		            system("cls");
		            Color::setTextColor(Color::Red);
		            cout << "Invalid choice. ";
		            Color::setTextColor(Color::White);
					cout << "Please enter your choice between ";
		            Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightGreen);
					cout << "1";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
		            Color::setTextColor(Color::Yellow);
		            cout << "to ";
		            Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightGreen);
					cout << "6";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
		            Color::setTextColor(Color::White);
					cout << "only.\n";
		            admin.showProfile(); // If logged in successfully, show user profile
		            // Display menu options
		            Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "1";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Sell A Property"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "2";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Delete A Property"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "3";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout<< "Update A Property"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "4";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Edit Accounts //Coming soon"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "5";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Show All Property"<<endl;
					Color::setTextColor(Color::BrightCyan);
		            cout << "[";
		            Color::setTextColor(Color::BrightRed);
					cout << "6";
					Color::setTextColor(Color::BrightCyan);
					cout << "] ";
					Color::setTextColor(Color::BrightGreen);
					cout << "Logout"<<endl;
		            Color::setTextColor(Color::White);
		            Color::setTextColor(Color::Yellow);
		            // Display other menu options similarly
		            Color::setTextColor(Color::White);
		            continue; // Restart the loop
		        }
		
		        // Clear any additional characters in the input buffer
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		        // Valid input, break the loop
		        break;
		    }
		return option;
	}
    
    void logout() {
        is_logged_in = false;
        Color::setTextColor(Color::BrightGreen);
        cout << "Logged out successfully." << endl;
        countdown(1);
        logoutCountdown(3);
    }

    // Accessors (getters)
    int getId() const { return id; }
    string getUsername() const { return username; }
    string getPassword() const {return password;} 
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
    
    Color::setTextColor(Color::Cyan);
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
        	bool exitRequested = false;
			while(!exitRequested){
	            user.showProfile(); // If logged in successfully, break out of the loop
	            Color::setTextColor(Color::BrightCyan);
	            cout << "[";
	            Color::setTextColor(Color::BrightRed);
				cout << "1";
				Color::setTextColor(Color::BrightCyan);
				cout << "] ";
				Color::setTextColor(Color::BrightGreen);
				cout << "Show All Availabe Property"<<endl;
				Color::setTextColor(Color::BrightCyan);
	            cout << "[";
	            Color::setTextColor(Color::BrightRed);
				cout << "2";
				Color::setTextColor(Color::BrightCyan);
				cout << "] ";
				Color::setTextColor(Color::BrightGreen);
				cout << "Search Property"<<endl;
				Color::setTextColor(Color::BrightCyan);
	            cout << "[";
	            Color::setTextColor(Color::BrightRed);
				cout << "3";
				Color::setTextColor(Color::BrightCyan);
				cout << "] ";
				Color::setTextColor(Color::BrightGreen);
				cout << "Buy A Property"<<endl;
				Color::setTextColor(Color::BrightCyan);
	            cout << "[";
	            Color::setTextColor(Color::BrightRed);
				cout << "4";
				Color::setTextColor(Color::BrightCyan);
				cout << "] ";
				Color::setTextColor(Color::BrightGreen);
				cout << "Edit Account"<<endl;
				Color::setTextColor(Color::BrightCyan);
	            cout << "[";
	            Color::setTextColor(Color::BrightRed);
				cout << "5";;
				Color::setTextColor(Color::BrightCyan);
				cout << "] ";
				Color::setTextColor(Color::BrightGreen);
				cout << "Logout"<<endl;
	            Color::setTextColor(Color::White);
	            Color::setTextColor(Color::Yellow);
	            int option = user.userOption(user.getId(), user.getUsername(), user.getPassword());
	            
	            switch(option){
	            	case 1:
						{
		            		system("cls");
		            		Color::setTextColor(Color::White);
		            		cout<<"Show All Availabe Property is ";
		            		Color::setTextColor(Color::Red);
							cout << "*";
							Color::setTextColor(Color::BrightGreen);
							cout << "Coming Soon";
							Color::setTextColor(Color::Yellow);
							cout << "!";
							Color::setTextColor(Color::Red);
							cout << "*"<<endl;
							Color::setTextColor(Color::White);
						}
	            		break;
	            	case 2:
						{
		            		system("cls");
		            		cout<<"Search Property is ";
		            		Color::setTextColor(Color::Red);
							cout << "*";
							Color::setTextColor(Color::BrightGreen);
							cout << "Coming Soon";
							Color::setTextColor(Color::Yellow);
							cout << "!";
							Color::setTextColor(Color::Red);
							cout << "*"<<endl;
							Color::setTextColor(Color::White);
						}
	            		break;
	            	case 3:
	            		{
		            		system("cls");
		            		cout<<"Buy A Property is ";
		            		Color::setTextColor(Color::Red);
							cout << "*";
							Color::setTextColor(Color::BrightGreen);
							cout << "Coming Soon";
							Color::setTextColor(Color::Yellow);
							cout << "!";
							Color::setTextColor(Color::Red);
							cout << "*"<<endl;
							Color::setTextColor(Color::White);
						}
	            		break;
	            	case 4:
	            		{
	            		system("cls");
	            		cout<<"Edit Account is ";
	            		Color::setTextColor(Color::Red);
						cout << "*";
						Color::setTextColor(Color::BrightGreen);
						cout << "Coming Soon";
						Color::setTextColor(Color::Yellow);
						cout << "!";
						Color::setTextColor(Color::Red);
						cout << "*"<<endl;
						Color::setTextColor(Color::White);
						}
	            		break;
	            	case 5:
	            		exitRequested = true;
	            		system("cls");
	            		user.logout();
	            		main();
	            		break;
	        		default:
	        			break;
				}
			}
            break;
        } else {
            counter++;
            Color::setTextColor(Color::Red);
            cout << "Incorrect password. ";
            Color::setTextColor(Color::BrightGreen);
			cout << "Login ";
			Color::setTextColor(Color::Red);
			cout << "failed. ";
            Color::setTextColor(Color::White);
            cout << "Please try again." << endl;
            Color::setTextColor(Color::BrightGreen);
            cout << "Login ";
            Color::setTextColor(Color::Red);
			cout << "attempt ";
			Color::setTextColor(Color::BrightCyan);
			cout << "[" ;
			Color::setTextColor(Color::BrightGreen);
			cout << counter ;
			Color::setTextColor(Color::BrightCyan);
			cout << "]" << endl;
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
        cout << "Reached maximum ";
        Color::setTextColor(Color::BrightGreen);
		cout << "login ";
		Color::setTextColor(Color::Red);
		cout << "attempts.";
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
    
    Color::setTextColor(Color::Cyan);
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
        	bool exitRequested = false;
        	while(!exitRequested){
        	admin.showProfile(); // If logged in successfully, break out of the loop
            Color::setTextColor(Color::BrightCyan);
            cout << "[";
            Color::setTextColor(Color::BrightRed);
			cout << "1";
			Color::setTextColor(Color::BrightCyan);
			cout << "] ";
			Color::setTextColor(Color::BrightGreen);
			cout << "Sell A Property"<<endl;
			Color::setTextColor(Color::BrightCyan);
            cout << "[";
            Color::setTextColor(Color::BrightRed);
			cout << "2";
			Color::setTextColor(Color::BrightCyan);
			cout << "] ";
			Color::setTextColor(Color::BrightGreen);
			cout << "Delete A Property"<<endl;
			Color::setTextColor(Color::BrightCyan);
            cout << "[";
            Color::setTextColor(Color::BrightRed);
			cout << "3";
			Color::setTextColor(Color::BrightCyan);
			cout << "] ";
			Color::setTextColor(Color::BrightGreen);
			cout<< "Update A Property"<<endl;
			Color::setTextColor(Color::BrightCyan);
            cout << "[";
            Color::setTextColor(Color::BrightRed);
			cout << "4";
			Color::setTextColor(Color::BrightCyan);
			cout << "] ";
			Color::setTextColor(Color::BrightGreen);
			cout << "Edit Accounts"<<endl;
			Color::setTextColor(Color::BrightCyan);
            cout << "[";
            Color::setTextColor(Color::BrightRed);
			cout << "5";
			Color::setTextColor(Color::BrightCyan);
			cout << "] ";
			Color::setTextColor(Color::BrightGreen);
			cout << "Show All Property"<<endl;
			Color::setTextColor(Color::BrightCyan);
            cout << "[";
            Color::setTextColor(Color::BrightRed);
			cout << "6";
			Color::setTextColor(Color::BrightCyan);
			cout << "] ";
			Color::setTextColor(Color::BrightGreen);
			cout << "Logout"<<endl;
            Color::setTextColor(Color::White);
            Color::setTextColor(Color::Yellow);
            int option = admin.adminOption(admin.getId(), admin.getUsername(), admin.getPassword());

	            switch(option){
	            	case 1:
						{
							system("cls");
							string propertyType, propertyAddress ; 
							int bedrooms, bathrooms; 
							double price;
							
							RealEstateProperty property(propertyType, propertyAddress, bedrooms, bathrooms, price);
							property.createProperty();
							countdown(1);
					        loginCountdown(3);
						}	
	            		break;
	            	case 2:
	            		{
							system("cls");
							string propertyType, propertyAddress ; 
							int bedrooms, bathrooms; 
							double price;
							
							RealEstateProperty property(propertyType, propertyAddress, bedrooms, bathrooms, price);
							property.deleteProperty();
							countdown(1);
					        loginCountdown(3);
						}
	            		
	            		break;
	            	case 3:
	            		{
							string propertyType, propertyAddress ; 
							int bedrooms, bathrooms; 
							double price;
							
							RealEstateProperty property(propertyType, propertyAddress, bedrooms, bathrooms, price);
							property.updateProperty();
							countdown(1);
					        loginCountdown(3);	
						}
	            		break;
	            	case 4:
	            		{
		            		system("cls");
		            		Color::setTextColor(Color::White);
		            		cout << "Edit Account is";
		            		Color::setTextColor(Color::Red);
							cout << "*";
							Color::setTextColor(Color::BrightGreen);
							cout << "Coming Soon";
							Color::setTextColor(Color::Yellow);
							cout << "!";
							Color::setTextColor(Color::Red);
							cout << "*"<<endl;
							Color::setTextColor(Color::White);
						}
	            		break;
	            	case 5:
	            		{
							system("cls");
							string propertyType, propertyAddress ; 
							int bedrooms, bathrooms; 
							double price;
							RealEstateProperty property(propertyType, propertyAddress, bedrooms, bathrooms, price);
							Color::setTextColor(Color::Cyan);
        					cout << "PROPERTY'S MARKET PLACE"<<endl;
        					Color::setTextColor(Color::BrightYellow);
	        				cout << "---------------------------------" << endl;
	            			property.showAllProperty();
							cout << endl;
						}
	            		break;
	            	case 6:
	            		exitRequested = true;
	            		system("cls");
	            		admin.logout();
	            		main();
	            		break;
	        		default:
	        			break;
				}
			}
            break;
        } else {
            counter++;
            Color::setTextColor(Color::Red);
            cout << "Incorrect password. ";
            Color::setTextColor(Color::BrightGreen);
			cout << "Login ";
			Color::setTextColor(Color::Red);
			cout << "failed. ";
            Color::setTextColor(Color::White);
            cout << "Please try again." << endl;
            Color::setTextColor(Color::BrightGreen);
            cout << "Login ";
            Color::setTextColor(Color::Red);
			cout << "attempt ";
			Color::setTextColor(Color::BrightCyan);
			cout << "[";
			Color::setTextColor(Color::BrightGreen);
			cout << counter;
			Color::setTextColor(Color::BrightCyan);
			cout << "]" << endl;
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
        cout << "Reached maximum ";
        Color::setTextColor(Color::BrightGreen);
		cout << "login ";
		Color::setTextColor(Color::Red);
		cout << "attempts.";
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
    
    Color::setTextColor(Color::Red);
	cout << "REAL ";
	Color::setTextColor(Color::Yellow);
	cout <<"ESTATE ";
	Color::setTextColor(Color::Green);
	cout <<"MANAGEMENT ";
	Color::setTextColor(Color::Blue);
	cout <<"SYSTEM" << endl;
	Color::setTextColor(Color::BrightCyan);
	cout << "[";
	Color::setTextColor(Color::BrightRed);
	cout <<"1";
	Color::setTextColor(Color::BrightCyan);
	cout <<"] ";
	Color::setTextColor(Color::BrightGreen);
	cout <<"Login As Admin" << endl;
	Color::setTextColor(Color::BrightCyan);
	cout << "[";
	Color::setTextColor(Color::BrightRed);
	cout <<"2";
	Color::setTextColor(Color::BrightCyan);
	cout <<"] ";
	Color::setTextColor(Color::BrightGreen);
	cout <<"Login As User" << endl;
	Color::setTextColor(Color::BrightCyan);
	cout << "[";
	Color::setTextColor(Color::BrightRed);
	cout <<"3";
	Color::setTextColor(Color::BrightCyan);
	cout <<"] ";
	Color::setTextColor(Color::BrightGreen);
	cout <<"Register As User" << endl;
	Color::setTextColor(Color::BrightCyan);
	cout << "[";
	Color::setTextColor(Color::BrightRed);
	cout <<"4";
	Color::setTextColor(Color::BrightCyan);
	cout <<"] ";
	Color::setTextColor(Color::BrightGreen);
	cout <<"Exit" << endl;
	
    Color::setTextColor(Color::Yellow);
	cout << "Enter your choice: ";
	// Set white text
	Color::setTextColor(Color::White);
    while (!(cin >> choice) || choice < 1 || choice > 4) {
        system("cls");
        Color::setTextColor(Color::Red);
        cout << "Invalid choice. ";
        Color::setTextColor(Color::White);
		cout <<"Please enter your choice between ";
        Color::setTextColor(Color::BrightGreen);
        cout<<"[1] ";
        Color::setTextColor(Color::Yellow);
        cout<<"to ";
        Color::setTextColor(Color::BrightGreen);
        cout<<"[4]";
        Color::setTextColor(Color::White);
		cout <<" only.\n";
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
            system(0);
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
	}
	return 0;
}

