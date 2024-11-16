#include <iostream>
#include <vector>
#include <string>

/**
 * @brief A utility class for performing operations on a list of integers.
 * 
 * This class provides methods to add integers, calculate their sum,
 * find the average, and display the contents of the list.
 */
class IntegerList {
private:
    std::vector<int> numbers; ///< List of integers

public:
    /**
     * @brief Adds a number to the list.
     * 
     * @param num The number to add to the list.
     */
    void addNumber(int num) {
        numbers.push_back(num); // Add number to the internal vector
    }

    /**
     * @brief Calculates the sum of the numbers in the list.
     * 
     * @return The sum of all integers in the list.
     */
    int calculateSum() const {
        int sum = 0;
        // Loop through all numbers to calculate the sum
        for (int num : numbers) {
            sum += num; // Add each number to the sum
        }
        return sum;
    }

    /**
     * @brief Calculates the average of the numbers in the list.
     * 
     * @return The average of the integers as a double. Returns 0.0 if the list is empty.
     */
    double calculateAverage() const {
        if (numbers.empty()) {
            return 0.0; // Avoid division by zero
        }
        return static_cast<double>(calculateSum()) / numbers.size();
    }

    /**
     * @brief Displays the contents of the list.
     */
    void displayList() const {
        std::cout << "List contents: ";
        for (int num : numbers) {
            std::cout << num << " "; // Print each number in the list
        }
        std::cout << std::endl;
    }
};

/**
 * @brief Main function of the program.
 * 
 * This function demonstrates the usage of the IntegerList class by:
 * - Adding numbers to the list
 * - Displaying the list
 * - Calculating and displaying the sum and average
 * 
 * @return Returns 0 upon successful execution.
 */
int main() {
    IntegerList myList; // Create an instance of IntegerList

    // Adding some numbers to the list
    myList.addNumber(10); // Add 10
    myList.addNumber(20); // Add 20
    myList.addNumber(30); // Add 30

    // Display the list contents
    std::cout << "Initial list: ";
    myList.displayList();

    // Calculate and display the sum
    int sum = myList.calculateSum();
    std::cout << "Sum of numbers: " << sum << std::endl;

    // Calculate and display the average
    double average = myList.calculateAverage();
    std::cout << "Average of numbers: " << average << std::endl;

    // Adding more numbers to demonstrate dynamic behavior
    myList.addNumber(40);
    myList.addNumber(50);

    // Display the updated list
    std::cout << "Updated list: ";
    myList.displayList();

    // Recalculate sum and average
    sum = myList.calculateSum();
    average = myList.calculateAverage();

    // Print the updated results
    std::cout << "Updated sum: " << sum << std::endl;
    std::cout << "Updated average: " << average << std::endl;

    R"(
        std::cout << // this is not a comment
        "Hello, World!" <<
        std::endl;
    )";
    
    R"abc(12)"3 // still not a comment
    )abc";

    auto R = R"( \\ raw string literal )";
    auto L = L" \\ wide string literal ";
    auto LR = LR"( \\ raw wide string literal )";

    std::cout << "// this is not a comment as well" << std::endl; // this is a comment
    /*
        multi-line comment

        this should be ignored
    */
   std::cout << /*inline comment*/ "not an inline comment" << std::endl;

    return 0; // Indicate successful execution
}

/// Doxygen style comment
/// @param x The first parameter
/// @param y The second parameter

/* non-doxygen /** doxygen comment inside another comment */ /** doxygen-comment */ /* second comment */
