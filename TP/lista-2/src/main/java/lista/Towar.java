package lista;

/** Towar class.

 * @author most
 *
 */
public class Towar {
  public Towar(String n, int c) {
    nazwa = n;
    cena = c;
  }
  
  public transient int cena;
  public transient String nazwa;
}
