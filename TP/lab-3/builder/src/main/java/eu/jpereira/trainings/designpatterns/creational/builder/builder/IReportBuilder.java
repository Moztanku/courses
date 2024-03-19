package eu.jpereira.trainings.designpatterns.creational.builder.builder;

import eu.jpereira.trainings.designpatterns.creational.builder.model.ReportBody;

public interface IReportBuilder {
    void reset();
    void setCustomerName(String s);
    void setCustomerPhone(String s);
    void addItem(String name, int quantity, double price);
    void buildReport();
    ReportBody returnReportBody();
}
