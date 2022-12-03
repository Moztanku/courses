package lista;

import java.util.Arrays;

/** Faktura class.

 * @author most
 *  Ta klasa widzi tylko klasę Element i jest niezależna od implementacji jej funkcji.
 */
public class Faktura {
  private transient int numer;
  private transient Element[] elementy;
  /** Constructor

   * @param nr numer
   * @param el elements
   */
  public Faktura(int nr, Element[] el) {
    numer = nr;
    if (el == null) {
      elementy = new Element[0];
    } else {
      elementy = Arrays.copyOf(el, el.length);
    }
  }
  /** Oblicza kwote.

   * @return int
   */
  public int obliczKwote() {
    int temp = 0;
    for (Element element : elementy) {
      temp += element.obliczElement();
    }
    return temp;
  }
  
  public int getNumer() {
    return numer;
  }
  
  /** Zwraca treść faktury.

   * @return string
   */
  public String wypiszFakture() {
    StringBuilder result = new StringBuilder();
    result.append("ID: " + numer);
    result.append(System.getProperty("line.separator"));
    result.append("Calosc: " + obliczKwote());
    result.append(System.getProperty("line.separator"));
    for (Element element : elementy) {
      result.append(
          element.nazwaTowaru() + " - " + element.obliczElement()
      );
      result.append(System.getProperty("line.separator"));
    }
    return result.toString();
  }
}
