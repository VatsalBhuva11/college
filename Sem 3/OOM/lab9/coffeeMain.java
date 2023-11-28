abstract class Beverage{
    String name;
    double sugar;
    double milk;
    abstract void prepare();
    public Beverage(double sugar, double milk){
        this.sugar = sugar;
        this.milk = milk;
    }
}

class Coffee extends Beverage{
    public Coffee(double sugar, double milk){
        super(sugar, milk);
        this.name = "Coffee";
    }
    public void prepare(){
        System.out.println("Preparing "+name);
    };
}

class Tea extends Beverage{
    public Tea(double sugar, double milk){
        super(sugar, milk);
        this.name = "Tea";
    }
    public void prepare(){
        System.out.println("Preparing "+name);
    };
}

class LemonTea extends Beverage{
    public LemonTea(double sugar, double milk){
        super(sugar, milk);
        this.name = "Lemon Tea";
    }
    public void prepare(){
        System.out.println("Preparing "+name);
    };
}


class CoffeeMachine{
    static void dispense(Beverage beverage){
        Class<?> bevClass = beverage.getClass();
        if (!bevClass.getName().equals("Coffee") && !bevClass.getName().equals("Tea") && !bevClass.getName().equals("LemonTea")){
            System.out.println("Beverage not available. Only coffee, tea, and lemon tea are available.");
        } else{
            beverage.prepare();
        }
    }
}

public class coffeeMain {
    public static void main(String args[]){
        Beverage c = new Coffee(100, 0.1);
        Beverage t = new Tea(50, 0.2);
        Beverage l = new LemonTea( 25, 0.5);
        CoffeeMachine.dispense(c);
        CoffeeMachine.dispense(t);
        CoffeeMachine.dispense(l);
    }
}
