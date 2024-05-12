public class G1234567891 extends Galois {
    @Override
    public long order()
    {
        return 1234567891;
    }

    public G1234567891 (long value)
    {
        this.value = value % order();
    }

    public static G1234567891 create() {
        return new G1234567891(1);
    }

    @Override
    public Galois add(Galois other)
    {
        return new G1234567891(this.value + other.value);
    }

    @Override
    public Galois sub(Galois other)
    {
        G1234567891 inverse = (G1234567891) other.inverse_add();

        return new G1234567891(this.value + inverse.value);
    }

    @Override
    public Galois mul(Galois other)
    {
        return new G1234567891(this.value * other.value);
    }

    @Override
    public Galois div(Galois other)
    {
        G1234567891 inverse = (G1234567891) other.inverse_mul();

        return new G1234567891(this.value * inverse.value);
    }

    @Override
    public Galois inverse_add()
    {
        return new G1234567891(order() - this.value);
    }

    @Override
    public Galois inverse_mul()
    {
        return new G1234567891(egcd(this.value));
    }
}
