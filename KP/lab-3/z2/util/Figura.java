package util;
import java.lang.Math;

public class Figura {
    public enum JedenParametr{
        KOLO, KWADRAT, PIECIOKAT, SZESCIOKAT;
        public double circumference(double x){
            switch(this){
                case KOLO:
                    return Math.PI*2.0*x;
                case KWADRAT:
                    return 4*x;
                case PIECIOKAT:
                    return 5*x;
                case SZESCIOKAT:
                    return 6*x;
                default:
                    return 0.0;
            }
        }

        public double area(double x){
            switch(this){
                case KOLO:
                    return Math.PI*Math.pow(x, 2.0);
                case KWADRAT:
                    return Math.pow(x,2.0);
                case PIECIOKAT:
                    return Math.pow(x,2.0)*1.72047740059;
                case SZESCIOKAT:
                    return Math.pow(x,2.0)*2.59807621135;
                default:
                    return 0.0;
            }
        }
    }

    public enum DwaParametry{
        PROSTOKAT,ROMB;
        public double circumference(double x, double y){
            switch(this){
                case PROSTOKAT:
                    return x+x+y+y;
                case ROMB:
                    return 4*x;
                default:
                    return 0.0;
            }
        }

        public double area(double x,double y){
            switch(this){
                case PROSTOKAT:
                    return x*y;
                case ROMB:
                    return Math.pow(x,2.0)*Math.sin(Math.toRadians(y));
                default:
                    return 0.0;
            }
        }
    }
}