package lista;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/** Class that handles saving to mysql server.

 * @author most
 *
 */
public class SqlDatabaseHandle implements DatabaseHandle {
  private transient Connection connection;
  
  /** Creates connection to mysql database.
   * 
   */
  public SqlDatabaseHandle() {
    String connectionUrl = "jdbc:mysql://localhost:3306/przyklad";
    String username = "superuser";
    String password = "kamisama123";
    
    try {
      Class.forName("com.mysql.jdbc.Driver");
      connection = DriverManager.getConnection(connectionUrl, username, password);
    } catch (SQLException e) {
      e.printStackTrace();
      System.out.print("Couldn't connect to the database.\n");
    } catch (ClassNotFoundException e) {
      e.printStackTrace();
      System.out.print("Couldn't find com.mysql.jdbc.Driver.\n");
    }
  }

  @Override
  public void save(Faktura f) {
    String query = "INSERT INTO faktury (numer) VALUES (" + f.getNumer() + ");";
    try {
      connection.createStatement().executeUpdate(query);
    } catch (SQLException e) {
      System.out.println("Couldn't execute query: " + query);
    }
  }

  @Override
  public void save(Element e) {
    //
  }

  @Override
  public void save(Towar t) {
    //
  }
  
  /** Closing connection with mysql server.
   * 
   */
  public void close() {
    try {
      connection.close();
    } catch (SQLException e) {
      e.printStackTrace();
    }
  }
}