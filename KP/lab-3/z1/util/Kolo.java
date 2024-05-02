package util;

public class Kolo implements Figura {
    public Kolo(double _radius){
        radius = _radius;
    };
    protected double radius;
    
    public double circumference(){
        return 2.0*Math.PI*radius;
    };
    public double area(){
        return Math.PI*Math.pow(radius, 2.0);
    };
}
