#include <iostream>
#include <iomanip>

const int ROWS = 8;
const int SEATS_PER_ROW = 5;
const int TOTAL_SEATS = ROWS * SEATS_PER_ROW;

char layout[ROWS][SEATS_PER_ROW]; // Array to store theater layout
int sales[TOTAL_SEATS] = {0}; // Array to store sales information for each seat

// Function to initialize the theater layout (all seats available)
void initializeLayout() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < SEATS_PER_ROW; ++j) {
            layout[i][j] = 'O'; // 'O' indicates available seat
        }
    }
}

// Function to display the theater layout
void displayLayout() {
    std::cout << "##############################\n";
    for (int i = 0; i < ROWS; ++i) {
        std::cout << "   ";
        for (int j = 0; j < SEATS_PER_ROW; ++j) {
            if (layout[i][j] == 'O') {
                std::cout << static_cast<char>('A' + j); // Print letter for available seats
            } else {
                std::cout << layout[i][j]; // Print 'X' for occupied seats
            }
            if (j < SEATS_PER_ROW - 1)
                std::cout << "     ";
        }
        std::cout << "\n";
    }
    std::cout << "##############################\n";
}

// Function to get row number, seat letter, and membership type from the user
void getRowSeatAndMembership(int& row, char& seat, char& membership) {
    std::cout << "      Enter the row number: ";
    std::cin >> row;
    if (row == -1)
        return;
    std::cout << "      Enter the seat letter: ";
    std::cin >> seat;
    seat = toupper(seat); // Convert to uppercase
    std::cout << "      Choose your membership:\n";
    std::cout << "      0. Not a member.\n";
    std::cout << "      1. Silver.\n";
    std::cout << "      2. Gold.\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 0:
            membership = 'N'; // Not a member
            break;
        case 1:
            membership = 'S'; // Silver member
            break;
        case 2:
            membership = 'G'; // Gold member
            break;
        default:
            break;
    }
}

// Function to update sales information based on membership type
void updateSales(char membership, int index) {
    switch (membership) {
        case 'G':
            sales[index] += 22; // Gold member price
            break;
        case 'S':
            sales[index] += 20; // Silver member price
            break;
        case 'N':
            sales[index] += 18; // Non-member price
            break;
        default:
            break;
    }
}

// Function to display the sales report
void displaySalesReport() {
    int totalSales = 0;
    int soldSeats = 0;
    for (int i = 0; i < TOTAL_SEATS; ++i) {
        if (sales[i] > 0) {
            totalSales += sales[i];
            soldSeats++;
        }
    }
    double occupancyPercentage = (static_cast<double>(soldSeats) / TOTAL_SEATS) * 100;
    std::cout << "Number of seats sold: " << soldSeats << "\n";
    std::cout << "Percentage occupied: ";
    if (soldSeats > 0)
        std::cout << std::fixed << std::setprecision(2) << occupancyPercentage << "%\n";
    else
        std::cout << "0%\n";
    std::cout << "Total Sales: $" << totalSales << "\n";
}

int main() {
    initializeLayout(); // Initialize theater layout
    int row;
    char seat, membership;

    while (true) {
        displayLayout(); // Display theater layout
        getRowSeatAndMembership(row, seat, membership); // Get user input for row, seat, and membership
        if (row == -1)
            break;
        int rowIndex = row - 1;
        int seatIndex = seat - 'A';
        if (rowIndex < 0 || rowIndex >= ROWS || seatIndex < 0 || seatIndex >= SEATS_PER_ROW) {
            std::cout << "Invalid row or seat! Please try again.\n";
            continue;
        }
        if (layout[rowIndex][seatIndex] == 'X') {
            std::cout << "The selected seat is not available.\n";
            continue;
        }
        layout[rowIndex][seatIndex] = 'X'; // Mark seat as taken
        updateSales(membership, rowIndex * SEATS_PER_ROW + seatIndex); // Update sales information
    }

    displaySalesReport(); // Display sales report

    return 0;
}
