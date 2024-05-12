public abstract class Galois {
    abstract public long order();
    protected long value;

    final public long get_value()
    {
        return value;
    }

    final public void set(long value)
    {
        this.value = value % order();
    }

    final public boolean equals(Galois other)
    {
        return this.compare(other) == 0;
    }

    final public long compare(Galois other)
    {
        return Long.compare(this.value, other.value);
    }

    final public void set(Galois other)
    {
        this.value = other.value;
    }

    static public Galois zero()
    {
        return null;
    };

    static public Galois one()
    {
        return null;
    };

    abstract public Galois add(Galois other);
    abstract public Galois sub(Galois other);
    abstract public Galois mul(Galois other);
    abstract public Galois div(Galois other);

    abstract public Galois inverse_add();
    abstract public Galois inverse_mul();

    final public String toString() {
        return Long.toString(value);
    }

    final protected long egcd(long a)
    {
        long b = order();

        long x = 1, y = 0;
        long x1 = 0, y1 = 1;

        while (b != 0) {
            final long q = a / b;

            final long x2 = x - q * x1;
            x = x1;
            x1 = x2;

            final long y2 = y - q * y1;
            y = y1;
            y1 = y2;

            final long temp = a - q * b;
            a = b;
            b = temp;
        }

        if (x < 0)
            x += order();

        return x;
    };
}