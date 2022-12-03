package lista;

import java.util.Arrays;
import java.util.Scanner;

/** Starting point.

 * @author most
 *
 */
public class Main {
  /** Entry point.

   * @param args console arguments
   */
  public static void main(String[] args) {
    SqlDatabaseHandle db = new SqlDatabaseHandle();
    
    Klient klient = new Klient();
    Scanner in = new Scanner(System.in);
    
    String str = "";
    while (!str.equals("q")) {
      System.out.println("c - create invoice, s - show invoices, q - quit");
      str = in.nextLine();
      
      if (str.equals("c")) {
        klient.stworzFakture(
            generujFakture(in, db)
        );
      } else if (str.equals("s")) {
        System.out.print(
            wypiszFaktury(klient)
        );
      }
    }
    in.close();
    db.close();
  }
  
  private static Faktura generujFakture(Scanner input, DatabaseHandle db) {
    Element[] el = new Element[0];
    String str = "";
    while (!str.equals("q")) {
      System.out.println("a - add item, q - create invoice");
      str = input.nextLine();
      
      if (str.equals("a")) {
        System.out.print("Choose name for item: ");
        final String name = input.nextLine();

        System.out.print("Choose quantity for item: ");
        final int quantity = input.nextInt();
        input.nextLine();
        
        System.out.print("Choose price for item: ");
        int price = input.nextInt();
        input.nextLine();
        
        Element[] temp = Arrays.copyOf(el, el.length + 1);
        temp[el.length] = new Element(new Towar(name, quantity), price);
        el = temp;
      }
    }
    final Faktura faktura = new Faktura(liczbaFaktur++, el);
    db.save(faktura);
    return faktura;
  }
  
  private static String wypiszFaktury(Klient klient) {
    StringBuilder result = new StringBuilder();
    
    for (Faktura faktura : klient.getFaktury()) {
      result.append("#################\n"
                    + faktura.wypiszFakture()
                    + "#################\n"
      );
    }
    
    return result.toString();
  }
  
  private static int liczbaFaktur = 0;
}
