import util.Figura;

import java.util.Vector;

public class Test {
    public static void main(String[] args) {
        char[] figureStr = args[0].toCharArray();
        int index = 1;
        try{
            for(char c : figureStr){
                switch(c){
                    case 'o':{
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp<0)
                                throw new NumberFormatException();
                                System.out.println(
                                    "Kolo, pole: "+
                                    Figura.JedenParametr.KOLO.area(temp)+", Obwod: "+
                                    Figura.JedenParametr.KOLO.circumference(temp));
                        }catch(NumberFormatException ex){
                            System.out.println(args[index-1]+" - Nieprawidlowa wartosc.");
                        }
                    }
                        break;
                    case 'p':{
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp<0)
                                throw new NumberFormatException();
                                System.out.println(
                                    "Kolo, pole: "+
                                    Figura.JedenParametr.PIECIOKAT.area(temp)+", Obwod: "+
                                    Figura.JedenParametr.PIECIOKAT.circumference(temp));
                        }catch(NumberFormatException ex){
                            System.out.println(args[index-1]+" - Nieprawidlowa wartosc.");
                        }
                    }
                        break;
                    case 's':{
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp<0)
                                throw new NumberFormatException();
                                System.out.println(
                                    "Kolo, pole: "+
                                    Figura.JedenParametr.SZESCIOKAT.area(temp)+", Obwod: "+
                                    Figura.JedenParametr.SZESCIOKAT.circumference(temp));
                        }catch(NumberFormatException ex){
                            System.out.println(args[index-1]+" - Nieprawidlowa wartosc.");
                        }
                    }
                        break;
                    case 'r':{
                        double tab[] = {1.0,180.0};
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp < 0)
                                throw new NullPointerException();
                            tab[0] = temp;
                        }
                        catch(NumberFormatException ex){
                            System.out.println(args[index-1]+" - Nieprawidlowa wartosc.");
                        }
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp < 0 || temp > 360)
                                throw new NullPointerException();
                            tab[1] = temp;
                        }
                        catch(NumberFormatException ex){
                            System.out.println(args[index-1]+" - Nieprawidlowa wartosc.");
                        }
                        System.out.println(
                            "Kolo, pole: "+
                            Figura.DwaParametry.ROMB.area(tab[0],tab[1])+", Obwod: "+
                            Figura.DwaParametry.ROMB.circumference(tab[0],tab[1]));
                    }
                        break;
                    case 't':{
                        double tab[] = {1.0,1.0};
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp < 0)
                                throw new NullPointerException();
                            tab[0] = temp;
                        }
                        catch(NumberFormatException ex){
                            System.out.println(args[index-1]+" - Nieprawidlowa wartosc.");
                        }
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp < 0)
                                throw new NullPointerException();
                            tab[1] = temp;
                        }
                        catch(NumberFormatException ex){
                            System.out.println(args[index-1]+" - Nieprawidlowa wartosc.");
                        }
                        System.out.println(
                            "Kolo, pole: "+
                            Figura.DwaParametry.PROSTOKAT.area(tab[0],tab[1])+", Obwod: "+
                            Figura.DwaParametry.PROSTOKAT.circumference(tab[0],tab[1]));
                    }
                        break;
                    case 'k':{
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp<0)
                                throw new NumberFormatException();
                                System.out.println(
                                    "Kolo, pole: "+
                                    Figura.JedenParametr.KWADRAT.area(temp)+", Obwod: "+
                                    Figura.JedenParametr.KWADRAT.circumference(temp));
                        }catch(NumberFormatException ex){
                            System.out.println(args[index-1]+" - Nieprawidlowa wartosc.");
                        }
                    }
                        break;
                    default:{
                        System.out.println(c+" - Nieprawidlowy parametr.");
                    }
                        break;
                }
            }
        }catch(ArrayIndexOutOfBoundsException ex){
            System.out.println(" Wprowadzono za malo parametrow.");
        }
        }
}

// o - koło
// c - czworokat
// p - pieciokat
// s - szesciokat
// r - romb
// t - prostokat
// k -kwadrat
//
