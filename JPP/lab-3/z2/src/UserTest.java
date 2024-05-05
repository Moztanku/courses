public class UserTest {
    public static void testOperations() {
    }

    private static void assertEquals(GF1234577 expected, GF1234577 actual) {
        if (!expected.equals(actual)) {
            throw new AssertionError("Expected " + expected + ", but got " + actual);
        }
    }
}