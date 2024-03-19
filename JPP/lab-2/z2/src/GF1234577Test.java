public class GF1234577Test {
    public static void testOperations() {
        GF1234577 a = new GF1234577(10);
        GF1234577 b = new GF1234577(20);

        // Test addition
        GF1234577 sum = a.add(b);
        assertEquals(new GF1234577(30), sum);

        // Test subtraction
        GF1234577 diff = a.sub(b);
        assertEquals(new GF1234577(1234567), diff); // 10 - 20 mod 1234577

        // Test multiplication
        GF1234577 product = a.mul(b);
        assertEquals(new GF1234577(200), product);

        // Test division
        GF1234577 quotient = a.div(b);
        assertEquals(new GF1234577(617289), quotient); // 10 / 20 mod 1234577
    }

    private static void assertEquals(GF1234577 expected, GF1234577 actual) {
        if (!expected.equals(actual)) {
            throw new AssertionError("Expected " + expected + ", but got " + actual);
        }
    }
}