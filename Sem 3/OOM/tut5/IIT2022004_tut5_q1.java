/*We can use interface instead of classes to use multiple inheritance in java. Then we use the keyword 'implements' on the sub-class.*/
interface Animal {
    void speak();
}
interface Dog {
    void bark();
}
class PuppyDog implements Animal, Dog {
    public void speak() {
        System.out.println("PuppyDog speaks");
    }
    public void bark() {
        System.out.println("PuppyDog barks");
    }
}
public class Tutq1 {
    public static void main(String[] args) {
        PuppyDog puppy = new PuppyDog();
        puppy.speak();
        puppy.bark();
    }
}
