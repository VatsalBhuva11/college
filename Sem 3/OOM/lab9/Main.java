class Animal {
    void eat() {
        System.out.println("Animals Eat");
    }
}

class herbivores extends Animal {
    void eat() {
        System.out.println("Herbivores Eat Plants");
    }
}

class omnivores extends Animal {
    void eat() {
        System.out.println("Omnivores Eat Plants and meat");
    }
}

class carnivores extends Animal {
    void eat() {
        System.out.println("Carnivores Eat meat");
    }
}

class Main {
    public static void main(String args[])
    {
        Animal a = new Animal();
        Animal herbi = new herbivores();
        Animal omni = new omnivores();
        Animal carni = new carnivores();

        a.eat();
        herbi.eat();
        omni.eat();
        carni.eat();
    }
}