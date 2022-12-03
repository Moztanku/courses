package jacek;

class Client extends Person {
	private int clientId;
	private String postalCode;
	private String city;
	private String street;
	private String apartament;
	
	public Client(int _age, String _fn, String _ln, int _id, String _pc, String _city, String _street, String _apartament) {
		super(_age, _fn, _ln);
		clientId = _id;
		setAdress(_pc, _city, _street, _apartament);
	}
	public void setAdress(String pc, String c, String s, String a) {
		postalCode = pc;
		city = c;
		street = s;
		apartament = a;
	}
	public int getId() {
		return clientId;
	}
	public void printInfo() {
		System.out.println("Klient: "+getName());
		System.out.println("Id: "+getId());
		System.out.println("Wiek: "+getAge());
		System.out.println("Adres: "+city+" "+postalCode+", ul. "+street+" "+apartament);
	}
}
