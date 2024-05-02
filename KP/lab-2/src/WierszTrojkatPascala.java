package src;

public class WierszTrojkatPascala {
    public WierszTrojkatPascala(int n){
        PascalArr = new int[n+1];
        for(int i=0; i<=(n+1)/2; i++){
            PascalArr[i]=PascalArr[n-i]=SymbolNewtona(n,i);
        }
    };
    public int Wspolczynnik(int m){
        if(m<0 || m>PascalArr.length)
            return -1;
        return PascalArr[m];
    }
    private int SymbolNewtona(int n, int k){
        int x = 1;
        for(int i=1; i<=k; i++){
            x*=(n-k+i);
            x/=i;
        }
        return x;
    }
    private int PascalArr[];
};

// Maksymalny numer wiersza możliwy do policzenia to 33