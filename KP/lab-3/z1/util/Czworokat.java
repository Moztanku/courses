package util;

public abstract class Czworokat implements Figura {
    public Czworokat(double _b1,double _b2,double _b3,double _b4,double _kat){
        b1 = _b1;
        b2 = _b2;
        b3 = _b3;
        b4 = _b4;
        kat = 2.0*_kat;
    };
    protected double b1,b2,b3,b4,kat;

    public double circumference(){
        return b1+b2+b3+b4;
    }
    public double area(){ 
        final double s = circumference()/2.0;
        return Math.sqrt((s-b1)*(s-b2)*(s-b3)*(s-b4)-b1*b2*b3*b4*(Math.pow(Math.cos(Math.toRadians(kat)/2),2.0)));
    };
}
