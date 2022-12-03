package eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty;

import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.CodeMismatchException;
import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.IncorrectDoorCodeException;
import eu.jpereira.trainings.designpatterns.structural.adapter.model.Door;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotChangeCodeForUnlockedDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotChangeStateOfLockedDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotUnlockDoorException;

public class ThirdPartyDoorAdapter extends ThirdPartyDoor implements Door {
    private ThirdPartyDoor door = new ThirdPartyDoor();

    @Override
    public void open(String code) throws IncorrectDoorCodeException {
        try{
            this.door.unlock(code);
        } catch(CannotUnlockDoorException exception){
            throw new IncorrectDoorCodeException();
        }
        try{
            this.door.setState(DoorState.OPEN);
        } catch(CannotChangeStateOfLockedDoor exception){
            exception.printStackTrace();
        }
    }

    @Override
    public void close() {
        try{
            this.door.setState(DoorState.CLOSED);
        } catch(CannotChangeStateOfLockedDoor exception){
            exception.printStackTrace();
        }
    }

    @Override
    public boolean isOpen() {
        return this.door.getState().equals(DoorState.OPEN);
    }

    @Override
    public void changeCode(String oldCode, String newCode, String newCodeConfirmation)
            throws IncorrectDoorCodeException, CodeMismatchException {
        if(!newCode.equals(newCodeConfirmation)){
            throw new CodeMismatchException();
        }
        try{
            this.door.unlock(oldCode);
        } catch(CannotUnlockDoorException exception){
            throw new IncorrectDoorCodeException();
        }
        try{
            this.door.setNewLockCode(newCode);
        } catch(CannotChangeCodeForUnlockedDoor exception){
            exception.printStackTrace();
        }
        
    }

    @Override
    public boolean testCode(String code) {
        LockStatus initialLockStatus = this.door.getLockStatus();
        try{
            this.door.unlock(code);
            if(initialLockStatus.equals(LockStatus.LOCKED)){
                this.door.lock();
            }
        } catch(CannotUnlockDoorException exception){
            return false;
        }
        return true;
    }

}
