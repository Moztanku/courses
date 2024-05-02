import util.Figura;
import util.Kolo;
import util.Czworokat;
import util.Kwadrat;
import util.Pieciokat;
import util.Prostokat;
import util.Romb;
import util.Szesciokat;

import java.util.Vector;

public class Test {
    public static void main(String[] args) {
        String figury = args[0];
        int index = 1;
        try{
            for(char c : figury.toCharArray()){
                switch(c){
                    case 'c':{
                        double[] parametry = {1.0,1.0,1.0,1.0,90.0};
                        for(int i=0; i<parametry.length; i++)
                            try{
                                double temp = Double.parseDouble(args[index++]);
                                if(temp<=0.0)
                                    throw new NumberFormatException("");
                                parametry[i] = temp;
                            }catch(NumberFormatException ex){
                                System.out.println("Wprowadzono nie prawidlowy parametr: "+args[index-1]+", Przyjeto: "+parametry[i]);
                            }
                        if(parametry[0]==parametry[1] && parametry[1]==parametry[2] && parametry[2]==parametry[3]){
                            if(parametry[4]==90.0){
                                Figura figura = new Kwadrat(parametry[0]);
                                System.out.println("Obwod: "+figura.circumference()+", Pole: "+figura.area());
                            }
                            else if(parametry[4]>0 && parametry[4]<360){
                                //ROMB
                                Figura figura = new Romb(parametry[0],parametry[4]);
                                System.out.println("Obwod: "+figura.circumference()+", Pole: "+figura.area());
                            }
                            else{
                                //ZŁY KĄT
                                System.out.println("Podano zly kat");
                            }
                        }else if(parametry[0]==parametry[1] && parametry[2]==parametry[3] && parametry[4]==90.0){
                            //PROSTOKĄT
                            Figura figura = new Prostokat(parametry[0],parametry[1]);
                            System.out.println("Obwod: "+figura.circumference()+", Pole: "+figura.area());
                        }else{
                            System.out.println("Nieodpowiedia figura.");
                        }
                        break;
                    }
                    case 'p':{
                        double parametry = 1.0;
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp<=0.0)
                                throw new NumberFormatException("");
                            parametry = temp;
                        }catch(NumberFormatException ex){
                            System.out.println("Wprowadzono nie prawidlowy parametr: "+args[index-1]+", Przyjeto: "+parametry);
                        }

                        // PIECIOKAT
                        Figura figura = new Pieciokat(parametry);
                        System.out.println("Obwod: "+figura.circumference()+", Pole: "+figura.area());
                        break;
                    }
                    case 's':{
                        double parametry = 1.0;
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp<=0.0)
                                throw new NumberFormatException("");
                            parametry = temp;
                        }catch(NumberFormatException ex){
                            System.out.println("Wprowadzono nie prawidlowy parametr.");
                        }

                        // SZESCIOKAT
                        Figura figura = new Szesciokat(parametry);
                        System.out.println("Obwod: "+figura.circumference()+", Pole: "+figura.area());
                        break;
                    }
                    case 'o':{
                        double parametry = 1.0;
                        try{
                            double temp = Double.parseDouble(args[index++]);
                            if(temp<=0.0)
                                throw new NumberFormatException("");
                            parametry = temp;
                        }catch(NumberFormatException ex){
                            System.out.println("Wprowadzono nie prawidlowy parametr.");
                        }

                        // KOLO
                        Figura figura = new Kolo(parametry);
                        System.out.println("Obwod: "+figura.circumference()+", Pole: "+figura.area());
                        break;
                    }
                    default:{
                        System.out.println("Wprowadzono nie prawidlowy parametr.");
                        break;
                    }
                }
            }
        }
        catch(ArrayIndexOutOfBoundsException ex){
            System.out.println("Wprowadzono za malo parametrow.");
        }
    }
}

// o - koło
// c - czworokat
// p - pieciokat
// s - szesciokat
// r - romb /
// t - prostokat /
// k -kwadrat /
//
