class A {
    static int a;
    static {
        a = 5;
        System.out.println("First");
    }
}

class B extends A {
    static {
        System.out.println("Second");
    }
}

class C extends B {
    static {
        System.out.println("Third");
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println(A.a);
        A.a += 1;
        System.out.println(A.a);
        A a = new A();
        System.out.println(a.a);
    }
}