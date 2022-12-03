package lista;

import java.util.Arrays;

/** Klient class.

 * @author most
 *  Ta klasa widzi tylko klasę Faktura, wszystkie klasy mają minimalna funkcjonalność
 *  np. wypisywanie do konsoli dzieje się dopiero w klasie main
 */
public class Klient {
  private transient Faktura[] faktury;
  
  public Klient() {
    faktury = new Faktura[0];
  }
  
  public Faktura[] getFaktury() {
    return faktury;
  }
  
  /** Dodaje fakture.

   * @param faktura faktura do dodania
   */
  public void stworzFakture(Faktura faktura) {
    Faktura[] temp = Arrays.copyOf(faktury, faktury.length+1)
    temp[faktury.length] = faktura;
    faktury = temp;
  }
}
