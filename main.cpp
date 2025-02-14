#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <map>
#include <stdexcept>

class Employee {
public:
    std::string name;
    std::string email;

    Employee(std::string name, std::string email)
        : name(name), email(email) {
    }
};

class FileHandler {
public:
    static std::vector<Employee> readEmployees(const std::string& filePath) {
        std::vector<Employee> employees;
        std::ifstream file(filePath);
        std::string line;
        // Skip the header
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, email;
            std::getline(ss, name, ',');
            std::getline(ss, email, ',');
            employees.push_back(Employee(name, email));
        }
        file.close();
        return employees;
    }

    static std::map<std::string, std::string> readPreviousAssignments(const std::string& filePath) {
        std::map<std::string, std::string> previousAssignments;
        std::ifstream file(filePath);
        std::string line;
        // Skip the header
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string employeeEmail, secretChildEmail;
            std::getline(ss, employeeEmail, ',');
            std::getline(ss, secretChildEmail, ',');
            previousAssignments[employeeEmail] = secretChildEmail;
        }
        file.close();
        return previousAssignments;
    }

    static void writeAssignments(const std::string& filePath, const std::vector<Employee>& employees,
        const std::map<std::string, std::string>& assignments) {
        std::ofstream file(filePath);
        file << "Employee_Name,Employee_EmailID,Secret_Child_Name,Secret_Child_EmailID\n";
        for (const auto& employee : employees) {
            file << employee.name << "," << employee.email << ",";
            auto secretChildEmail = assignments.at(employee.email);
            file << secretChildEmail << "," << secretChildEmail << "\n";
        }
        file.close();
    }
};

class SecretSantaGame {
public:
    SecretSantaGame(std::vector<Employee>& employees, std::map<std::string, std::string>& previousAssignments)
        : employees(employees), previousAssignments(previousAssignments) {
    }

    std::map<std::string, std::string> assignSecretSanta() {
        std::map<std::string, std::string> secretSantaAssignments;
        std::vector<Employee> availableEmployees = employees;

        // Randomly shuffle employees
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(availableEmployees.begin(), availableEmployees.end(), g);

        for (auto& employee : employees) {
            // Find a valid secret child
            for (size_t i = 0; i < availableEmployees.size(); ++i) {
                Employee& secretChild = availableEmployees[i];
                if (secretChild.email != employee.email && previousAssignments[employee.email] != secretChild.email) {
                    secretSantaAssignments[employee.email] = secretChild.email;
                    availableEmployees.erase(availableEmployees.begin() + i);
                    break;
                }
            }
        }
        return secretSantaAssignments;
    }

private:
    std::vector<Employee>& employees;
    std::map<std::string, std::string>& previousAssignments;
};

class SecretSantaApp {
public:
    SecretSantaApp(const std::string& employeeFile, const std::string& previousAssignmentFile, const std::string& outputFile)
        : employeeFile(employeeFile), previousAssignmentFile(previousAssignmentFile), outputFile(outputFile) {
    }

    void run() {
        try {
            // Read employee details
            std::vector<Employee> employees = FileHandler::readEmployees(employeeFile);
            // Read previous assignments
            std::map<std::string, std::string> previousAssignments = FileHandler::readPreviousAssignments(previousAssignmentFile);
            // Create SecretSantaGame instance
            SecretSantaGame game(employees, previousAssignments);
            // Assign Secret Santa
            std::map<std::string, std::string> secretSantaAssignments = game.assignSecretSanta();
            // Write the assignments to the output CSV file
            FileHandler::writeAssignments(outputFile, employees, secretSantaAssignments);
            std::cout << "Secret Santa assignments have been successfully generated!" << std::endl;
        }
        catch (const std::exception& ex) {
            std::cerr << "An error occurred: " << ex.what() << std::endl;
        }
    }

private:
    std::string employeeFile;
    std::string previousAssignmentFile;
    std::string outputFile;
};

int main() {
    std::string employeeFile = "employee.csv";
    std::string previousAssignmentFile = "previousExample.csv";
    std::string outputFile = "secret_santa_assignments.csv";

    SecretSantaApp app(employeeFile, previousAssignmentFile, outputFile);
    app.run();

    return 0;
}
