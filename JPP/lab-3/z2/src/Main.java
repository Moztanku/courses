public class Main {
    public static void main(String[] args) {
        try {
            UserTest.testOperations();
        } catch (AssertionError e) {
            System.out.println(e.getMessage());
            return;
        }

        System.out.println("All tests passed!");
    }
}