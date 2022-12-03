package eu.jpereira.trainings.designpatterns.creational.builder.builder;

import eu.jpereira.trainings.designpatterns.creational.builder.model.ReportBody;
import eu.jpereira.trainings.designpatterns.creational.builder.xml.XMLReportBody;

public class XMLReportBuilder implements IReportBuilder{
    private XMLReportBody report;
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
        this.report = new XMLReportBody();
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
        this.report.putContent("<sale><customer>");
        this.report.putContent("<name>"+this.name+"</name>");
        this.report.putContent("<phone>"+this.phone+"</phone>");
        this.report.putContent("</customer>");
        this.report.putContent("<items>"+this.items+"</items>");
        this.report.putContent("</sale>");
    }

    @Override
    public ReportBody returnReportBody() {
        return this.report;
    }
}
