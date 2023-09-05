import java.util.Scanner;

abstract class Animal{
    String name;
    int age;
    abstract void speak();
    void eat(){
        System.out.println("The animal is eating.");
    }
}

class Lion extends Animal{
    public Lion(String name, int age){
        this.name = name;
        this.age = age;
    }

    @Override
    public void speak(){
        System.out.println("The lion "+name+" is "+age+", and it is roaring!");
    }
}

class Dolphin extends Animal{
    public Dolphin(String name, int age){
        this.name = name;
        this.age = age;
    }

    @Override
    public void speak(){
        System.out.println("The dolphin "+name+" is "+age+", and it says Ee-ee!");
    }
}

public class iit2022004_p3 {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter lion's name: ");
        String lionName = sc.nextLine();
        System.out.println("Enter lion's age: ");
        int lionAge = sc.nextInt();
        sc.nextLine();

        Lion l = new Lion(lionName, lionAge);
        l.speak();
        l.eat();

        System.out.println("Enter dolphins's name: ");
        String dolphinName = sc.nextLine();
        System.out.println("Enter dolphins's age: ");
        int dolphinAge = sc.nextInt();
        sc.nextLine();

        Dolphin d = new Dolphin(dolphinName, dolphinAge);
        d.speak();
        d.eat();

        sc.close();
    }
    
}
