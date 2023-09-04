class Spacecraft{
    String name;
    double fuelCapacity;
    public Spacecraft(String name, double fuelCapacity){
        this.name = name;
        this.fuelCapacity = fuelCapacity;
    }
    //getter method for spacecraft attributes.
    public void getAttributes(){
        System.out.println("Name of Spacecraft: "+name);
        System.out.println("Fuel Capacity of Spacecraft: "+fuelCapacity);
        System.out.println("======================================================");
    }
}

class Spaceship extends Spacecraft{
    int crewSize;
    public Spaceship(String name, double fuelCapacity, int crewSize){
        super(name, fuelCapacity);
        this.crewSize = crewSize;
    }
    //getter method for crewSize
    public void getCrewSize(){
        System.out.println("Crew size of Spaceship: "+crewSize);
        System.out.println("======================================================");
    }
}

class Starship extends Spaceship{
    double warpSpeed;
    public Starship(String name, double fuelCapacity, int crewSize, double warpSpeed){
        super(name, fuelCapacity, crewSize);
        this.warpSpeed = warpSpeed;
    }
    public void getWarpSpeed(){
        System.out.println("Warp speed of starship: "+warpSpeed);
        System.out.println("======================================================");
    }
}

public class iit2022004_p4 {
    public static void main(String args[]){
        Starship s1 = new Starship("Chandrayaan 4", 10000, 7, 7654321);
        s1.getAttributes();
        s1.getCrewSize();
        s1.getWarpSpeed();
    }
}
