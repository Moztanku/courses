package util;

public class Szesciokat implements Figura {
    public Szesciokat(double _bok){
        bok = _bok;
    };
    protected double bok;
    public double circumference(){
        return 6.0*bok;
    };
    public double area(){
        return 1.5*Math.pow(bok, 2.0)*Math.sqrt(3);
    };
}

// h = b sqrt(3) / 2
// T = a^2 sqrt(3) / 4
// P = 3/2