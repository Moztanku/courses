package jacek;

import java.util.Date;

class Worker extends Person {
	private int workerId;
	private double salary;
	private Date employment;
	
	public Worker(int age, String fn, String ln, int id, double salary) {
		this(age, fn, ln, id, salary, new Date());
	}
	public Worker(int age, String fn, String ln,int id,double salary,Date empl) {
		super(age,fn,ln);
		setSalary(salary);
		workerId = id;
		employment = empl;
	}
	public void setSalary(double s) {
		salary = s;
	}
	public int getId() {
		return workerId;
	}
	public void printInfo() {
		System.out.println("Pracownik: "+getName());
		System.out.println("Id: "+getId());
		System.out.println("Wiek: "+getAge());
		System.out.println("Wyplata: "+salary);
		System.out.println("Data zatrudnienia: "+employment.toString());
	}
}
