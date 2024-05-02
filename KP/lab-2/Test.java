import src.WierszTrojkatPascala;

public class Test {
      public static void main(String[] args) {
        WierszTrojkatPascala obj;
        try{
            int x=Integer.parseInt(args[0]);
            if(x<0)
                throw new NumberFormatException();
            obj = new WierszTrojkatPascala(x);
        }
        catch(NumberFormatException ex){
            System.out.println(args[0]+" - Nieprawidlowy zakres.");
            return;
        }
        for(int i=1; i<args.length; i++)
            try{
                int x = Integer.parseInt(args[i]);
                int y = obj.Wspolczynnik(x);
                if(x<0 || y==-1)
                    throw new NumberFormatException();
                System.out.println(args[i]+" - "+obj.Wspolczynnik(x));
            }
            catch(NumberFormatException ex){
                System.out.println(args[i]+" - Nieprawidlowa dana.");
            }
      };
};
