//IIT2022004 question 1

import java.util.Scanner;

class Salaried{
    final int weeklyFixed = 6000;
    float getSalary(){
        return weeklyFixed;
    }
}

class Hourly {
    final int salaryPerHour = 100;
    final int overTimeSalaryPerHour = 500;
    float getSalary(int numberOfHours) {
        return salaryPerHour*numberOfHours + (numberOfHours>40 ? (salaryPerHour + overTimeSalaryPerHour)*(numberOfHours - 40) : 0);
    }
}

class Commission {
    final float percentage = 20;
    float getSalary(int sales) {
        return sales*(percentage/100);
    }
}

class Salaried_Commission {
    final int weeklyFixed = 6000;
    final float percentage = 10;

    float getSalary(int sales) {
        return weeklyFixed + sales*(percentage/100);
    }
}

class Employee {
    String employeeType = "";

    public Employee(String employeeType) {
        this.employeeType = employeeType;
    }

    float findSalary() {
        Scanner sc = new Scanner(System.in);
        float finalSalary = 0;
        switch (employeeType.toLowerCase()) {
            case "salaried":
                Salaried salariedEmployee = new Salaried();
                finalSalary =  salariedEmployee.getSalary();
                break;
            case "hourly":
                Hourly hourlyEmployee = new Hourly();
                System.out.print("Enter Working Hours: ");
                finalSalary =  hourlyEmployee.getSalary(sc.nextInt());
                break;

            case "commission":
                Commission commissionEmployee = new Commission();
                System.out.print("Enter sales: ");
                finalSalary = Math.round(commissionEmployee.getSalary(sc.nextInt()));
                break;
            
            case "salaried-commission":
                Salaried_Commission salariedCommissionEmployee = new Salaried_Commission();
                System.out.print("Enter sales: ");
                finalSalary = Math.round(salariedCommissionEmployee.getSalary(sc.nextInt()));
                break;

            default:
                System.err.println("Invalid Type");
                break;
        }
        sc.close();
        return finalSalary;
    }
}

public class Payroll{
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter employee type: ");
        String employeeType = sc.nextLine();

        Employee emp = new Employee(employeeType);
        System.out.println("Salary is: " + emp.findSalary());

        sc.close();
    }
}