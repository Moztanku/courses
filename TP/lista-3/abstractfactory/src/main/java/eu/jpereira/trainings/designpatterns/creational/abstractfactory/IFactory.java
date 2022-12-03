package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

public interface IFactory {
    public ReportBody createReportBody();
    public ReportFooter createReportFooter();
    public ReportHeader createReportHeader();
}
