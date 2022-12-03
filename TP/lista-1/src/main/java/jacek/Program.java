package jacek;

public class Program {
  public static void main(String[] args) {
    Client cl = new Client(36, "Robert", "Smith", 1, "44700", "Lodz", "Grochowa", "32/6");
    cl.printInfo();

    Worker wo = new Worker(26, "Arnold", "Schwarzenegger", 1, 33000.0);
    wo.printInfo();
  }
}
