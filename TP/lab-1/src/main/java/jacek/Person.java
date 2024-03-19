package jacek;

abstract class Person {
	private int age;
	private String firstName;
	private String lastName;
	
	
	public Person(int a, String fn, String ln) {
		age = a;
		firstName = fn;
		lastName = ln;
	}
	public String getName() {
		return firstName + ' ' + lastName;
	}
	public int getAge() {
		return age;
	}
	public abstract int getId();
	public abstract void printInfo();
}
