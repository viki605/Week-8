#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

// ===== Named Constants =====
const int MIN_QUANTITY = 1;
const double MIN_PRICE = 1.0;
const int BEGINNER_QUANTITY = 5;
const double MAX_BEGINNER_SPENDING = 20.0;
const int ADVANCED_QUANTITY = 10;
const int MAX_SOUVENIRS = 50;
const int MAX_FILE_IGNORE = 1000;

// ===== Enum for souvenir type =====
enum SouvenirType { Keychain = 1, Magnet, Postcard, Other };

// ===== Struct =====
struct Souvenir {
    string name;
    SouvenirType type;
    int quantity;
    double price;
    double totalCost;
};

// ===== Function Prototypes (Helpers) =====
void showBanner();
void setColor(int colorCode);
string getStringInput(const string& prompt);
int getIntInput(const string& prompt, int min);
double getDoubleInput(const string& prompt, double min);
string getSouvenirTypeName(SouvenirType type);

// ===== SouvenirTracker Class =====
class SouvenirTracker {
private:
    Souvenir souvenirs[MAX_SOUVENIRS];
    int souvenirCount;

public:
    SouvenirTracker() { souvenirCount = 0; }

    // Collect a souvenir from the user
    Souvenir collectSouvenir() {
        Souvenir s;
        s.name = getStringInput("Enter the name of the souvenir: ");

        int typeInput = getIntInput("Enter type (1=Keychain, 2=Magnet, 3=Postcard, 4=Other): ", 1);
        s.type = static_cast<SouvenirType>(typeInput);

        s.quantity = getIntInput("Enter the quantity you bought: ", MIN_QUANTITY);
        s.price = getDoubleInput("Enter the price per item (USD): ", MIN_PRICE);
        s.totalCost = s.quantity * s.price;

        return s;
    }

    // Display one souvenir
    void displaySouvenir(const Souvenir& s) {
        setColor(11);
        cout << "\n===================== Souvenir Summary =====================\n";
        cout << left << setw(20) << "Name"
            << setw(15) << "Type"
            << right << setw(15) << "Quantity"
            << right << setw(15) << "Price ($)"
            << right << setw(15) << "Total ($)" << endl;
        cout << "------------------------------------------------------------\n";

        cout << left << setw(20) << s.name
            << setw(15) << getSouvenirTypeName(s.type)
            << right << setw(15) << s.quantity
            << right << setw(15) << fixed << setprecision(2) << s.price
            << right << setw(15) << fixed << setprecision(2) << s.totalCost
            << endl;
    }

    // Save a souvenir to file
    void saveToFile(const Souvenir& s) {
        ofstream report("report.txt", ios::app);
        if (report.is_open()) {
            report << left << setw(20) << s.name
                << setw(15) << getSouvenirTypeName(s.type)
                << right << setw(15) << s.quantity
                << right << setw(15) << fixed << setprecision(2) << s.price
                << right << setw(15) << fixed << setprecision(2) << s.totalCost
                << endl;
            report.close();
        }
    }

    // Add souvenirs (menu option 1)
    void addSouvenirs() {
        setColor(11);
        int numToAdd = getIntInput("How many souvenirs do you want to add? ", 1);

        for (int i = 0; i < numToAdd; i++) {
            if (souvenirCount < MAX_SOUVENIRS) {
                cout << "\nSouvenir " << souvenirCount + 1 << ":\n";
                Souvenir s = collectSouvenir();
                souvenirs[souvenirCount] = s;
                souvenirCount++;

                displaySouvenir(s);
                saveToFile(s);
            }
            else {
                cout << "Array is full! Cannot add more.\n";
                break;
            }
        }
    }

    // View report from file (menu option 2)
    void viewReport() {
        setColor(11);
        cout << "\n================= Souvenir Report (File) ====================\n";
        cout << left << setw(20) << "Souvenir Name"
            << setw(15) << "Type"
            << right << setw(15) << "Quantity"
            << right << setw(15) << "Price ($)"
            << right << setw(15) << "Total ($)" << endl;
        cout << "------------------------------------------------------------\n";

        ifstream file("report.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        else {
            cout << "Report file not found.\n";
        }
        cout << "------------------------------------------------------------\n";
    }

    // Summary of all souvenirs in array (menu option 3)
    void processArray() {
        if (souvenirCount == 0) {
            cout << "No souvenirs stored yet.\n";
            return;
        }

        double grandTotal = 0;
        double highest = souvenirs[0].totalCost;
        double lowest = souvenirs[0].totalCost;

        int i = 0;
        while (i < souvenirCount) { // WHILE LOOP
            grandTotal += souvenirs[i].totalCost;
            if (souvenirs[i].totalCost > highest) highest = souvenirs[i].totalCost;
            if (souvenirs[i].totalCost < lowest) lowest = souvenirs[i].totalCost;
            i++;
        }

        double average = grandTotal / souvenirCount;

        cout << "\n============= Array Summary of Souvenirs =============\n";
        cout << "Total souvenirs logged: " << souvenirCount << endl;
        cout << "Grand total spent: $" << fixed << setprecision(2) << grandTotal << endl;
        cout << "Average cost per souvenir entry: $" << fixed << setprecision(2) << average << endl;
        cout << "Most expensive entry: $" << fixed << setprecision(2) << highest << endl;
        cout << "Least expensive entry: $" << fixed << setprecision(2) << lowest << endl;
        cout << "======================================================\n";
    }

    // Recommend level (menu option 4)
    void recommendLevel() {
        int quantity = getIntInput("Enter the total souvenirs collected today: ", 0);
        double spent = getDoubleInput("Enter total money spent: ", 0);

        if (quantity >= BEGINNER_QUANTITY && spent <= MAX_BEGINNER_SPENDING)
            cout << "You are a beginner collector. Keep exploring!\n";
        else if (quantity >= ADVANCED_QUANTITY || spent > MAX_BEGINNER_SPENDING * 2.5)
            cout << "You are an advanced collector!\n";
        else
            cout << "You are an intermediate collector.\n";
    }
};

// ===== Main Function =====
int main() {
    SouvenirTracker tracker;
    showBanner();

    int choice;
    char continueMenu;

    do {
        setColor(3);
        cout << "\nMenu:\n";
        cout << "1 - Add a souvenir\n";
        cout << "2 - View saved souvenir report (file)\n";
        cout << "3 - Summary of all souvenirs (array)\n";
        cout << "4 - Recommend collecting level\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: tracker.addSouvenirs(); break;
        case 2: tracker.viewReport(); break;
        case 3: tracker.processArray(); break;
        case 4: tracker.recommendLevel(); break;
        default:
            setColor(12);
            cout << "Invalid menu choice.\n";
        }

        cout << "\nReturn to menu? (y/n): ";
        cin >> continueMenu;
        cin.ignore();
    } while (continueMenu == 'y' || continueMenu == 'Y');

    cout << "\nThank you for using Viktorija's Souvenir Tracker!\n";
    return 0;
}

// ===== Helper Functions =====
void showBanner() {
    setColor(10);
    cout << "==================================================\n";
    cout << "     Welcome to Viktorija's Souvenir Tracker\n";
    cout << "==================================================\n\n";
    setColor(7);
}

void setColor(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

string getStringInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) cout << "Input cannot be empty.\n";
    } while (input.empty());
    return input;
}

int getIntInput(const string& prompt, int min) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value >= min) break;
        cout << "Invalid input. Must be at least " << min << ".\n";
        cin.clear();
        cin.ignore(MAX_FILE_IGNORE, '\n');
    }
    cin.ignore();
    return value;
}

double getDoubleInput(const string& prompt, double min) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value >= min) break;
        cout << "Invalid input. Must be at least " << min << ".\n";
        cin.clear();
        cin.ignore(MAX_FILE_IGNORE, '\n');
    }
    cin.ignore();
    return value;
}

string getSouvenirTypeName(SouvenirType type) {
    switch (type) {
    case Keychain: return "Keychain";
    case Magnet: return "Magnet";
    case Postcard: return "Postcard";
    default: return "Unknown";
    }
}
