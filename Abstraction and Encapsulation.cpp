#include <iostream>
#include <vector>
#include <string>
#include <limits> // For numeric_limits

class Employee {
protected:
    int id;
    std::string name;
    double salary;

public:
    Employee(int id, std::string name) : id(id), name(name) {}
    virtual void calculateSalary() = 0; // Pure virtual function
    virtual void display() const = 0;
    int getId() const { return id; }
};

class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee(int id, std::string name, double salary) 
        : Employee(id, name), salary(salary) {}

    void calculateSalary() override {
        // Salary is fixed for full-time employees
    }

    void display() const override {
        std::cout << "Employee: " << name << " (ID: " << id << ")\n";
        std::cout << "Fixed Monthly Salary: $" << salary << "\n";
    }

private:
    double salary;
};

class PartTimeEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;

public:
    PartTimeEmployee(int id, std::string name, double hourlyRate, int hoursWorked)
        : Employee(id, name), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}

    void calculateSalary() override {
        salary = hourlyRate * hoursWorked;
    }

    void display() const override {
        std::cout << "Employee: " << name << " (ID: " << id << ")\n";
        std::cout << "Hourly Wage: $" << hourlyRate << "\n";
        std::cout << "Hours Worked: " << hoursWorked << "\n";
        std::cout << "Total Salary: $" << salary << "\n";
    }
};

class ContractualEmployee : public Employee {
private:
    double paymentPerProject;
    int projectsCompleted;

public:
    ContractualEmployee(int id, std::string name, double paymentPerProject, int projectsCompleted)
        : Employee(id, name), paymentPerProject(paymentPerProject), projectsCompleted(projectsCompleted) {}

    void calculateSalary() override {
        salary = paymentPerProject * projectsCompleted;
    }

    void display() const override {
        std::cout << "Employee: " << name << " (ID: " << id << ")\n";
        std::cout << "Contract Payment Per Project: $" << paymentPerProject << "\n";
        std::cout << "Projects Completed: " << projectsCompleted << "\n";
        std::cout << "Total Salary: $" << salary << "\n";
    }
};

class PayrollSystem {
private:
    std::vector<Employee*> employees;

public:
    bool isDuplicateId(int id) {
        for (const auto& emp : employees) {
            if (emp->getId() == id) {
                return true;
            }
        }
        return false;
    }

    void addEmployee(Employee* emp) {
        employees.push_back(emp);
    }

    void displayPayrollReport() const {
        std::cout << "--- Employee Payroll Report ---\n";
        for (const auto& emp : employees) {
            emp->display();
            std::cout << "\n";
        }
    }

    ~PayrollSystem() {
        for (auto& emp : employees) {
            delete emp;
        }
    }
};

// Function to validate numeric input
template <typename T>
T getValidInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard extra input
            break;
        }
    }
    return value;
}

int main() {
    PayrollSystem payroll;
    int choice;
    do {
        std::cout << "Menu\n";
        std::cout << "1 - Full-time Employee\n";
        std::cout << "2 - Part-time Employee\n";
        std::cout << "3 - Contractual Employee\n";
        std::cout << "4 - Display Payroll Report\n";
        std::cout << "5 - Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            continue;
        }

        int id;
        std::string name;
        double salary, hourlyRate, paymentPerProject;
        int hoursWorked, projectsCompleted;

        switch (choice) {
            case 1: {
                id = getValidInput<int>("Enter ID: ");
                if (payroll.isDuplicateId(id)) {
                    std::cout << "Duplicate ID! Please enter a different ID.\n";
                    break;
                }
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                salary = getValidInput<double>("Enter Salary: ");
                payroll.addEmployee(new FullTimeEmployee(id, name, salary));
                break;
            }
            case 2: {
                id = getValidInput<int>("Enter ID: ");
                if (payroll.isDuplicateId(id)) {
                    std::cout << "Duplicate ID! Please enter a different ID.\n";
                    break;
                }
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                hourlyRate = getValidInput<double>("Enter Hourly Rate: ");
                hoursWorked = getValidInput<int>("Enter Hours Worked: ");
                payroll.addEmployee(new PartTimeEmployee(id, name, hourlyRate, hoursWorked));
                break;
            }
            case 3: {
                id = getValidInput<int>("Enter ID: ");
                if (payroll.isDuplicateId(id)) {
                    std::cout << "Duplicate ID! Please enter a different ID.\n";
                    break;
                }
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                paymentPerProject = getValidInput<double>("Enter Payment Per Project: ");
                projectsCompleted = getValidInput<int>("Enter Projects Completed: ");
                payroll.addEmployee(new ContractualEmployee(id, name, paymentPerProject, projectsCompleted));
                break;
            }
            case 4: {
                payroll.displayPayrollReport();
                break;
            }
            case 5: {
                std::cout << "Exiting...\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            }
        }
    } while (choice != 5);

    return 0;
}