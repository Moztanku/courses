import util.LiczbyPierwsze;
public class Test {
    public static void main(String[] args) {
        int x; int y;
        try{
            x=Integer.parseInt(args[0]);
            if(x<0)
                throw new NumberFormatException();
        }
        catch(NumberFormatException ex){
            System.out.println(args[0]+" - Nieprawidlowy zakres.");
            return;
        };
        LiczbyPierwsze lp = new LiczbyPierwsze(x);

        for(int i=1; i<args.length; i++)
        try{
            x = Integer.parseInt(args[i]);
            y = lp.liczba(x);
            if(y==-1)
                System.out.println(args[i]+" - liczba spoza zakresu");
            else
                System.out.println(args[i]+" - "+y);
        }
        catch(NumberFormatException ex){
            System.out.println(args[i]+" - nieprawidlowa dana");
        };
    };
}
