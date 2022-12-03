package eu.jpereira.trainings.designpatterns.creational.builder.builder;

import eu.jpereira.trainings.designpatterns.creational.builder.HTMLReportBody;
import eu.jpereira.trainings.designpatterns.creational.builder.model.ReportBody;

public class HTMLReportBuilder implements IReportBuilder{
    HTMLReportBody report;
    private String name;
    private String phone;
    private String items;

    @Override
    public void addItem(String name, int quantity, double price) {
        this.items += "<item><name>"+name+"</name>";
        this.items += "<quantity>"+String.valueOf(quantity)+"</quantity>";
        this.items += "<price>"+String.valueOf(price)+"</price></item>";
    }

    @Override
    public void reset() {
        this.report = new HTMLReportBody();
        this.name = "";
        this.phone = "";
        this.items = "";
    }

    @Override
    public void setCustomerName(String s) {
        this.name = s;
    }

    @Override
    public void setCustomerPhone(String s) {
        this.phone = s;
    }

    @Override
    public void buildReport() {
        this.report.putContent("<span class=\"customerName\">"+this.name+"</span>");
        this.report.putContent("<span class=\"customerPhone\">"+this.phone+"</span>");
        this.report.putContent("<items>"+this.items+"</items>");
    }

    @Override
    public ReportBody returnReportBody() {
        return this.report;
    }
}
