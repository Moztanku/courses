package lista;

/** Database handler.

 * @author most
 *  Użycie interfejsu pozwala na zapisywania do bazy danych w
   Klient niezależnie od implementacji metody save
 */
public interface DatabaseHandle {
  /** Save Faktura.

   * @param f faktura to save
   */
  public void save(Faktura f);
  
  /** Save Element.

   * @param e element
   */
  public void save(Element e);
  
  /** Save Towar.

   * @param t towar
   */
  public void save(Towar t);
}