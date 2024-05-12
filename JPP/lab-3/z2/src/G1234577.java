public class G1234577 extends Galois {
    @Override
    public long order()
    {
        return 1234577;
    }

    public G1234577 (long value)
    {
        this.value = value % order();
    }

    public static G1234577 create() {
        return new G1234577(1);
    }

    @Override
    public Galois add(Galois other)
    {
        return new G1234577(this.value + other.value);
    }

    @Override
    public Galois sub(Galois other)
    {
        G1234577 inverse = (G1234577) other.inverse_add();

        return new G1234577(this.value + inverse.value);
    }

    @Override
    public Galois mul(Galois other)
    {
        return new G1234577(this.value * other.value);
    }

    @Override
    public Galois div(Galois other)
    {
        G1234577 inverse = (G1234577) other.inverse_mul();

        return new G1234577(this.value * inverse.value);
    }

    @Override
    public Galois inverse_add()
    {
        return new G1234577(order() - this.value);
    }

    @Override
    public Galois inverse_mul()
    {
        return new G1234577(egcd(this.value));
    }
}
