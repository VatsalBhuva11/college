import java.util.Scanner;

class Bicycle{
    int gear;
    double speed;

    public Bicycle(int gear, double speed){
        this.gear = gear;
        this.speed = speed;
    }

    public void incrementGear(){
        gear++;
    }
    public void decrementGear(){
        gear--;
    }
    public void incrementSpeed(){
        speed++;
    }
    public void decrementSpeed(){
        speed--;
    }

    public void showAttributes(){
        System.out.println();
        System.out.println("Gear: " + gear);
        System.out.println("Speed: " + speed);
    }

}

class mountainBike extends Bicycle{
    double seatHeight;

    public mountainBike(int gear, double speed, double seatHeight){
        super(gear, speed);
        this.seatHeight = seatHeight;
    }

    public void updateSeatHeight(){
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter new seat height: ");
        sc.nextLine();

        sc.close();
    }

    public void showAttributes(){
        super.showAttributes(); //super keyword used to call attribute/method of parent class
        System.out.println("Seat height: "+seatHeight);
        System.out.println();
    }

}

public class iit2022004_p1 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter current gear number: ");
        int gear = sc.nextInt();
        System.out.print("Enter current speed: ");
        double speed = sc.nextDouble();
        System.out.print("Enter seat height: ");
        int height = sc.nextInt();
        mountainBike bike = new mountainBike(gear, speed, height);
        bike.showAttributes();

        bike.decrementGear();
        bike.incrementSpeed();

        bike.showAttributes();

        sc.close();
    }
}
