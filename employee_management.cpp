#include <iostream>
#include <vector>
using namespace std;

// ===== Base Employee Class =====
class Employee {
protected:
    string name;
    int id;
    double baseSalary;
public:
    Employee(string n, int i, double salary) : name(n), id(i), baseSalary(salary) {}
    virtual void showDetails() = 0;
    virtual double calculatePay() = 0;
    virtual void performanceReview() = 0;
    virtual ~Employee() {}
};

// ===== Manager Class =====
class Manager : public Employee {
public:
    Manager(string n, int i, double salary) : Employee(n, i, salary) {}

    void showDetails() override {
        cout << "Manager: " << name << " | ID: " << id << " | Salary: Rs." << calculatePay() << endl;
    }

    double calculatePay() override {
        return baseSalary + 10000;
    }

    void performanceReview() override {
        cout << "Manager " << name << ": Excellent leadership & project delivery.\n";
    }
};

// ===== Staff Class =====
class Staff : public Employee {
public:
    Staff(string n, int i, double salary) : Employee(n, i, salary) {}

    void showDetails() override {
        cout << "Staff: " << name << " | ID: " << id << " | Salary: Rs." << calculatePay() << endl;
    }

    double calculatePay() override {
        return baseSalary;
    }

    void performanceReview() override {
        cout << "Staff " << name << ": Good team player and punctual.\n";
    }
};

// ===== Part-Time Employee Class =====
class PartTimeEmployee : public Employee {
private:
    int hoursWorked;
    double hourlyRate;
public:
    PartTimeEmployee(string n, int i, int hours, double rate)
        : Employee(n, i, 0), hoursWorked(hours), hourlyRate(rate) {}

    void showDetails() override {
        cout << "Part-Time: " << name << " | ID: " << id << " | Salary: Rs." << calculatePay() << endl;
    }

    double calculatePay() override {
        return hoursWorked * hourlyRate;
    }

    void performanceReview() override {
        cout << "Part-Time " << name << ": Works well with flexible hours.\n";
    }
};

// ===== HR System =====
class HRSystem {
private:
    vector<Employee*> employees;
public:
    void addEmployee(Employee* e) {
        employees.push_back(e);
    }

    void showAllEmployees() {
        cout << "\n--- Employee Records ---\n";
        for (auto e : employees) {
            e->showDetails();
            e->performanceReview();
            cout << endl;
        }
    }

    ~HRSystem() {
        for (auto e : employees) {
            delete e;
        }
    }
};

// ===== Main Function =====
int main() {
    HRSystem hr;
    int n;
    cout << "Enter number of employees to add: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int type;
        cout << "\nChoose employee type:\n";
        cout << "1. Manager\n2. Staff\n3. Part-Time\n";
        cout << "Enter choice (1-3): ";
        cin >> type;

        string name;
        int id;
        double salary, rate;
        int hours;

        cout << "Enter name: ";
        cin >> name;
        cout << "Enter ID: ";
        cin >> id;

        if (type == 1) {
            cout << "Enter base salary: ";
            cin >> salary;
            hr.addEmployee(new Manager(name, id, salary));
        }
        else if (type == 2) {
            cout << "Enter base salary: ";
            cin >> salary;
            hr.addEmployee(new Staff(name, id, salary));
        }
        else if (type == 3) {
            cout << "Enter hours worked: ";
            cin >> hours;
            cout << "Enter hourly rate: ";
            cin >> rate;
            hr.addEmployee(new PartTimeEmployee(name, id, hours, rate));
        }
        else {
            cout << "Invalid choice. Skipping...\n";
        }
    }

    hr.showAllEmployees();
    return 0;
}
