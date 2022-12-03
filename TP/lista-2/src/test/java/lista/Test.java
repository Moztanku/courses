package lista;

import static org.junit.jupiter.api.Assertions.assertEquals;

/** Test class.

 * @author most
 *
 */
class Test {
  public Test() {
  }
  
  @org.junit.jupiter.api.Test
  void test() {
    Towar t = new Towar("nazwa_towaru", 350);
    assertEquals(t.cena, 350);
    assertEquals(t.nazwa, "nazwa_towaru");
    
    Element e = new Element(t, 30);
    assertEquals(e.nazwaTowaru(), "nazwa_towaru");
    assertEquals(e.obliczElement(), 350 * 30);
    
    Element[] tab = new Element[1];
    tab[0] = e;
    Faktura f = new Faktura(1, tab);
    assertEquals(f.obliczKwote(), 350 * 30);
    assertEquals(
        f.wypiszFakture(), 
        "ID: 1\nCalosc: " + f.obliczKwote() + "\nnazwa_towaru - " + 350 * 30 + "\n"
    );
  }
}
