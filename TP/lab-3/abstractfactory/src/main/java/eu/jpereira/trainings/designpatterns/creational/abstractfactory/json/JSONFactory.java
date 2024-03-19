package eu.jpereira.trainings.designpatterns.creational.abstractfactory.json;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.IFactory;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportFooter;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportHeader;

public class JSONFactory implements IFactory {

    @Override
    public ReportBody createReportBody() {// TODO Auto-generated method stub
        return new JSONReportBody();
    }

    @Override
    public ReportFooter createReportFooter() {
        return new JSONReportFooter();
    }

    @Override
    public ReportHeader createReportHeader() {
        return new JSONReportHeader();
    }
    
}
