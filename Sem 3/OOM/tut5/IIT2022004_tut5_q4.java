class Animal{
    public void announce(){
        System.out.println("I am an animal!");
    }
}
class Dog extends Animal{
    public void announce(){
        System.out.println("I am a dog!");
    }
}
class PuppyDog extends Dog{
}
public class IIT2022004_tut5_q4{
    public static void main(String[] args){
        PuppyDog puppy=new PuppyDog();
        puppy.announce();
    }
}
