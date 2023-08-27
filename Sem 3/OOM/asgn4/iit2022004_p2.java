import java.util.Scanner;

class Vehicle{
    String fuelType;

    public void printFuelType(){
        System.out.println("The fuel type is "+fuelType);
    }
}

class Car extends Vehicle{
    int numDoors;
    String carModel;

    public Car(Scanner sc){

        System.out.println("Enter model of car: ");
        this.carModel = sc.nextLine();
        System.out.println("Enter number of doors: ");
        this.numDoors = sc.nextInt();

    }

    public void displayAttributes(){
        System.out.println();
        System.out.println("Number of doors: "+numDoors);
        System.out.println("Car model: "+carModel);
        System.out.println();
    }

}

class Motorcycle extends Vehicle{
    String hasSideCar;

    public Motorcycle(Scanner s){

        System.out.println("Does the motorcycle have a sidecar? (yes/no) : ");
        this.hasSideCar = s.nextLine();
        this.hasSideCar = this.hasSideCar.toLowerCase();

    }

    public void displayAttributes(){
        System.out.println();
        if (hasSideCar.equals("yes")){
            System.out.println("The motorcycle has a sidecar.");
        } else {
            System.out.println("The motorcycle has no sidecar.");
        }
        System.out.println();
    }
}

public class iit2022004_p2 {
    
    public static void main(String args[]){

        Scanner scanner = new Scanner(System.in);

        Motorcycle m = new Motorcycle(scanner);
        m.displayAttributes();
        
        
        Car c = new Car(scanner);
        c.displayAttributes();

    }

}
