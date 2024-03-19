package eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.IFactory;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportFooter;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportHeader;

public class XMLFactory implements IFactory{

    @Override
    public ReportBody createReportBody() {
        return new XMLReportBody();
    }

    @Override
    public ReportFooter createReportFooter() {
        return new XMLReportFooter();
    }

    @Override
    public ReportHeader createReportHeader() {
        return new XMLReportHeader();
    }
    
}