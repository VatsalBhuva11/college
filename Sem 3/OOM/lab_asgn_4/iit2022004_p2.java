import java.util.Scanner;

interface BankAccount{
    void deposit(double amount);
    void withdraw(double amount);
    void viewBalance();
}


class SavingsAccount implements BankAccount{
    double balance, interest;
    public SavingsAccount(double balance, double interest){
        this.balance = balance;
        this.interest = interest;
    }

    public int enoughBalance(double balance){
        if (balance < 0) return -1;
        return 1;
    }

    @Override
    public void deposit(double amount){
        balance += amount;
        System.out.println("Successfully deposited "+amount+" in the account");
        System.out.println();
    }

    @Override
    public void withdraw(double amount){
        if (enoughBalance(balance-amount) == 1){
            balance -= amount;
            System.out.println("Successfully withdrew "+amount+" from the account");
        } else {
            System.out.println("Insufficient balance.");
        }
        System.out.println();
    }

    public void calculateInterest(Scanner sc){
        System.out.println("Enter number of years: ");
        int years = sc.nextInt();
        double interestAmount = (interest*years/100)*balance;
        balance += interestAmount;
        System.out.println("Added interest of "+interestAmount+" to account.");
        System.out.println();
    }

    @Override
    public void viewBalance(){
        System.out.println("Current balance: "+balance);
        System.out.println();
    }
}

class CheckingAccount implements BankAccount{
    double fee, balance;
    public CheckingAccount(double balance, double fee){
        this.fee = fee;
        this.balance = balance;
    }

    public int enoughBalance(double balance){
        if (balance < 0) return -1;
        return 1;
    }

    @Override
    public void deposit(double amount){
        balance += amount;
        System.out.println("Successfully deposited "+amount+" in the account");
        System.out.println();
    }

    @Override
    public void withdraw(double amount){
        if (enoughBalance(balance-amount) == 1){
            balance -= amount;
            System.out.println("Successfully withdrew "+amount+" from the account");
        } else {
            System.out.println("Insufficient balance.");
        }
        System.out.println();
    }

    public void deductFee(Scanner sc){
        System.out.println("Enter number of months: ");
        int months = sc.nextInt();
        double deducted = fee*months;
        if (enoughBalance(balance-deducted) == 1){
            balance -= deducted;
            System.out.println("Deducted fee of "+deducted+" from account.");
        } else {
            System.out.println("Insufficient amount in account.");
        }
        System.out.println();
    }

    @Override
    public void viewBalance(){
        System.out.println("Current balance: "+balance);
        System.out.println();
    }
}

public class iit2022004_p2 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter balance of savings account: ");
        double balance = sc.nextDouble();
        System.out.println("Enter interest rate of savings account: ");
        double interest = sc.nextDouble();

        SavingsAccount savAcc = new SavingsAccount(balance, interest);

        savAcc.deposit(5000);
        savAcc.viewBalance();
        savAcc.withdraw(2500);
        savAcc.viewBalance();
        savAcc.calculateInterest(sc);
        savAcc.viewBalance();

        System.out.println("Enter balance of checking account: ");
        balance = sc.nextDouble();
        System.out.println("Enter fee: ");
        double fee = sc.nextDouble();

        CheckingAccount checkAcc = new CheckingAccount(balance, fee);

        checkAcc.deposit(5000);
        checkAcc.viewBalance();
        checkAcc.withdraw(2500);
        checkAcc.viewBalance();
        checkAcc.deductFee(sc);
        checkAcc.viewBalance();

        sc.close();
    }
}
