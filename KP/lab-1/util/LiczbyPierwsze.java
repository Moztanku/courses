package util;
import java.lang.Math;
public class LiczbyPierwsze {
    public LiczbyPierwsze(int n){
        for(int i=2; i<=n; i++)
            if(isPrime(i)){
                append(i);
            };
    };
    public int liczba(int m){
        if(m<0 || m>tab.length)
            return -1;
        else
            return tab[m];
    };

    private int tab[] = {};

    private boolean isPrime(int x){
        for(int i=2; i<=Math.sqrt(x); i++)
            if(x%i==0)
                return false;
        return true;
    };

    private void append(int x){
        int length = this.tab.length;
        int temp[] = new int[length+1];
        for(int i=0; i<length; i++)
            temp[i]=this.tab[i];
        temp[length] = x;
        this.tab = temp;
    };
}
