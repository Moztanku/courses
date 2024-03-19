public class GF1234577 {
    public static final Integer order = 1234577;

    public GF1234577() {
        m_value = 0;
    }

    public GF1234577(Integer m_value) {
        this.m_value = m_value % order;
    }

    public boolean equals(GF1234577 other) {
        return m_value.equals(other.m_value);
    }

    public int compare(GF1234577 other) {
        return m_value.compareTo(other.m_value);
    }

    public void set(GF1234577 other) {
        m_value = other.m_value;
    }

    public GF1234577 add(GF1234577 other) {
        return new GF1234577((m_value + other.m_value) % order);
    }

    public GF1234577 sub(GF1234577 other) {
        GF1234577 inverse = other.inverse_add();
        return add(inverse);
    }

    public GF1234577 mul(GF1234577 other) {
        return new GF1234577((m_value * other.m_value) % order);
    }

    public GF1234577 div(GF1234577 other) {
        GF1234577 inverse = other.inverse_mul();
        return mul(inverse);
    }

    public GF1234577 inverse_add() {
        return new GF1234577(order - m_value);
    }

    public GF1234577 inverse_mul() {
        return new GF1234577(egcd(m_value));
    }

    public String toString() {
        return m_value.toString();
    }

    private Integer m_value;

    private static Integer egcd(Integer a) {
        Integer b = order;

        Integer x = 1, y = 0;
        Integer x1 = 0, y1 = 1;

        while (b != 0) {
            final Integer q = a / b;

            final Integer x2 = x - q * x1;
            x = x1;
            x1 = x2;

            final Integer y2 = y - q * y1;
            y = y1;
            y1 = y2;

            final Integer temp = a - q * b;
            a = b;
            b = temp;
        }

        if (x < 0)
            x += order;

        return x;
    };
}