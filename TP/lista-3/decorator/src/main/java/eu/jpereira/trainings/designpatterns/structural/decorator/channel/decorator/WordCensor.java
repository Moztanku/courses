package eu.jpereira.trainings.designpatterns.structural.decorator.channel.decorator;

public class WordCensor extends SocialChannelDecorator{
    private String censoredString = "";

    public WordCensor(String string){
        this.censoredString = string;
    }

    @Override
    public void deliverMessage(String message) {
        if(message.contains(censoredString)){
            message = message.replace(censoredString, "***");
        }
        delegate.deliverMessage(message);
    }
}
