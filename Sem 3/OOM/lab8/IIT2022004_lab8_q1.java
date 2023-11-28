class Vehicle{
    public void start_engine(){
        System.out.println("Engine started!");
    }
}

class Car extends Vehicle{
    public void start_engine(){
        System.out.println("Car Engine started!");
    }
}

class IIT2022004_lab8_q1{
    public static void main(String args[]){
        Vehicle v = new Vehicle();
        Car c = new Car();

        System.out.println("start_engine() on Vehicle object:");
        v.start_engine();
        System.out.println("\nstart_engine() on Car object:");
        c.start_engine();
    }
}