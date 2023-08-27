import java.util.Scanner;

public class Main{
  int x = 4;

  public Main(){
    x = 5;
  }
  public static void main(String[] args){
    Main obj1 = new Main();
    Second obj2 = new Second();
    System.out.println(obj1.x);
    System.out.println(obj2.y);

    Scanner inp = new Scanner(System.in);
    String name = inp.nextLine();
    System.out.println(name);

  }
}