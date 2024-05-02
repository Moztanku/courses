public class podzielniki {
    public static int div(int n){
        if(n<=1) return 0;
        int x = n/2;
        while(n%x!=0){
            x--;
        }
        return x;
    };
    public static void main(String[] args) {
        int n=0;
        for(int i=0; i<args.length; i++){
            try { n=Integer.parseInt(args[i]);
                System.out.println(div(n)); }
            catch (NumberFormatException ex) {
                System.out.println(args[i] + " nie jest liczba calkowita");
                
            };
            
        }
    };
}
