package lista;

/** Element class.

 * @author most
 *
 */
public class Element {
  public Element(Towar t, int i) {
    towar = t;
    ilosc = i;
  }
  
  public int obliczElement() {
    return towar.cena * ilosc;
  }
  
  public String nazwaTowaru() {
    return towar.nazwa;
  }
  
  /** Ilosc towaru.
   * 
   */
  private transient int ilosc;
  /** Typ towaru.
   * 
   */
  private transient Towar towar;
}
