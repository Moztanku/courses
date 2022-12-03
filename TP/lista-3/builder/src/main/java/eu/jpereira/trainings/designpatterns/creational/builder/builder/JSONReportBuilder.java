package eu.jpereira.trainings.designpatterns.creational.builder.builder;

import eu.jpereira.trainings.designpatterns.creational.builder.json.JSONReportBody;
import eu.jpereira.trainings.designpatterns.creational.builder.model.ReportBody;

public class JSONReportBuilder implements IReportBuilder {
    JSONReportBody report;
    private String name;
    private String phone;
    private String items;

    public JSONReportBuilder(){
        this.reset();
    }

    @Override
    public void addItem(String name, int quantity, double price) {
        if(this.items.length() > 0)
            this.items += ",";
        this.items += "{name:\""+name+"\"";
        this.items += ",quantity:"+String.valueOf(quantity);
        this.items += ",price:"+String.valueOf(price)+"}";
    }

    @Override
    public void reset() {
        this.report = new JSONReportBody();
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
        this.report.addContent("sale:{customer:{");
        this.report.addContent("name:\""+this.name+"\"");
        this.report.addContent(",phone:\""+this.phone+"\"");
        this.report.addContent("},items:["+this.items+"]}");
    }

    @Override
    public ReportBody returnReportBody() {
        return this.report;
    }
}
