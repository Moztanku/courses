int phi(long int n){
/*    int x=n-1;
    for(int i=1; i<n; i++){
        if(gcd(i,n)!=1){
            x--;
        }
    }
    return x;
*/
     int x=n;
     for(int i=2; i*i<=n;i++){
         if(n%i==0){
             while(n%i==0){
                 n=n/i;
             }
             x-=(x/i);
         }
     }
     if(n>1){
        x-=x/n;
     }
     return x;
};
