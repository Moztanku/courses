using GF = Galois.Field<Galois.Order1234577>;

public class FieldTests
{
    
    public static void testOperations() {
        GF a = new GF(10);
        GF b = new GF(20);

        assertEquals(new GF(30), a + b);
        assertEquals(new GF(1234567), a - b);

        assertEquals(new GF(200), a * b);
        assertEquals(new GF(2), b / a);
    }

    private static void assertEquals(GF expected, GF actual) {
        if (!expected.Equals(actual)) {
            throw new System.Exception($"Expected {expected} but got {actual}");
        }
    }
}