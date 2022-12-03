package eu.jpereira.trainings.designpatterns.behavioral.command.model.command;

import eu.jpereira.trainings.designpatterns.behavioral.command.model.command.results.DBServerInstanceResult;
import eu.jpereira.trainings.designpatterns.behavioral.command.model.exceptions.CouldNotConnectException;

public interface Command {
    public void execute() throws CouldNotConnectException;

    @SuppressWarnings("rawtypes")
    public DBServerInstanceResult getResult();
}
