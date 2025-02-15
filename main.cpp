#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <unordered_set>
#include <random>

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

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open employee file: " << filePath << std::endl;
            throw std::runtime_error("File opening failed");
        }

        std::string line;
        // Skip the header
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, email;

            // Check if the line contains two columns (name, email)
            if (!std::getline(ss, name, ',') || !std::getline(ss, email, ',')) {
                std::cerr << "Error: Invalid format in employee file on line: " << line << std::endl;
                continue;  // Skip the invalid line and continue with the next line
            }
            employees.push_back(Employee(name, email));
            std::cout << "Loaded employee: " << name << " (" << email << ")" << std::endl;
        }
        file.close();
        return employees;
    }

    static std::map<std::string, std::string> readPreviousAssignments(const std::string& filePath) {
        std::map<std::string, std::string> previousAssignments;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open previous assignment file: " << filePath << std::endl;
            throw std::runtime_error("File opening failed");
        }

        std::string line;
        // Skip the header
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string employeeEmail, secretChildEmail;

            // Check if the line contains two columns (employeeEmail, secretChildEmail)
            if (!std::getline(ss, employeeEmail, ',') || !std::getline(ss, secretChildEmail, ',')) {
                std::cerr << "Error: Invalid format in previous assignments file on line: " << line << std::endl;
                continue;  // Skip the invalid line and continue with the next line
            }
            previousAssignments[employeeEmail] = secretChildEmail;
            std::cout << "Loaded previous assignment: " << employeeEmail << " -> " << secretChildEmail << std::endl;
        }
        file.close();
        return previousAssignments;
    }

    static void writeAssignments(const std::string& filePath, const std::vector<Employee>& employees,
        const std::map<std::string, std::string>& assignments) {

        std::ofstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open output file for writing: " << filePath << std::endl;
            throw std::runtime_error("File opening failed");
        }

        file << "Employee_Name,Employee_EmailID,Secret_Child_Name,Secret_Child_EmailID\n";
        for (const auto& employee : employees) {
            try {
                auto secretChildEmail = assignments.at(employee.email);
                file << employee.name << "," << employee.email << "," << secretChildEmail << "," << secretChildEmail << "\n";
                std::cout << "Assigned " << employee.name << " to " << secretChildEmail << std::endl;
            }
            catch (const std::out_of_range&) {
                std::cerr << "Error: Missing assignment for employee " << employee.email << std::endl;
            }
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
        std::unordered_set<std::string> assignedEmployees;

        // Randomly shuffle employees
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(employees.begin(), employees.end(), g);

        for (auto& employee : employees) {
            bool assigned = false;
            for (auto& secretChild : employees) {
                // Skip if the secret child is already assigned or is the same employee
                if (secretChild.email != employee.email &&
                    previousAssignments[employee.email] != secretChild.email &&
                    assignedEmployees.find(secretChild.email) == assignedEmployees.end()) {

                    secretSantaAssignments[employee.email] = secretChild.email;
                    assignedEmployees.insert(secretChild.email);
                    std::cout << employee.name << " is assigned to " << secretChild.name << std::endl;
                    assigned = true;
                    break;
                }
            }
            if (!assigned) {
                std::cerr << "Warning: Could not assign a valid Secret Child for " << employee.name << std::endl;
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
            std::cout << "Starting Secret Santa Assignment..." << std::endl;

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

    std::cout << "Starting Secret Santa program..." << std::endl;
    SecretSantaApp app(employeeFile, previousAssignmentFile, outputFile);
    app.run();
    std::cout << "Secret Santa program finished." << std::endl;

    return 0;
}
