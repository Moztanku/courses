package util;

public class Pieciokat implements Figura {
    public Pieciokat(double _bok){
        bok = _bok;
    };
    protected double bok;
    public double circumference(){
        return 5.0*bok;
    };
    public double area(){
        return 0.25*Math.sqrt(5*(5+2*Math.sqrt(5)))*Math.pow(bok, 2.0);
    };
}

//  72o 36o 54o  
//  1/2*h*1/2b * 10
// 
