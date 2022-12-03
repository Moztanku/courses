package eu.jpereira.trainings.designpatterns.structural.decorator.channel.decorator;

import static org.junit.Assert.*;

import org.junit.Test;

import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannel;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannelBuilder;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannelProperties;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannelPropertyKey;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.TwitterChannel;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.spy.TestSpySocialChannel;

public class ChainCensorDecoratorTest extends AbstractSocialChanneldDecoratorTest {
    @Test
	public void testChainTwoDecorators() {
		// Create the builder
		SocialChannelBuilder builder = createTestSpySocialChannelBuilder();

		// create a spy social channel
		SocialChannelProperties props = new SocialChannelProperties().putProperty(SocialChannelPropertyKey.NAME, TestSpySocialChannel.NAME);

		// Chain decorators
		SocialChannel channel = builder.
				with(new WordCensor("message")).
				with(new URLAppender("http://jpereira.eu")).
				getDecoratedChannel(props);

		channel.deliverMessage("this is a message");
		// Spy channel. Should get the one created before
		TestSpySocialChannel spyChannel = (TestSpySocialChannel) builder.buildChannel(props);
		assertEquals("this is a *** http://jpereira.eu", spyChannel.lastMessagePublished());
	}

	@Test
	public void testChainTwoDecoratorsWithoutBuilder() {
		
		SocialChannel channel = new TestSpySocialChannel();
		
		SocialChannelDecorator wordCensorChannel = new WordCensor("String");
        wordCensorChannel.setDecoratedSocialChannel(channel);
		
		//Now create a truncator
		SocialChannel messageTruncatorChannel = new MessageTruncator(10, wordCensorChannel);
		
		messageTruncatorChannel.deliverMessage("String String");
		// Spy channel. Should get the one created before
		TestSpySocialChannel spy = (TestSpySocialChannel)channel;
		assertEquals("*** ...", spy.lastMessagePublished());
	}

	@Test
	public void testThreeCensorDecorators() {
		// Create the builder
		SocialChannelBuilder builder = createTestSpySocialChannelBuilder();

		// create a spy social channel
		SocialChannelProperties props = new SocialChannelProperties().putProperty(SocialChannelPropertyKey.NAME, TestSpySocialChannel.NAME);

		// Chain decorators
		SocialChannel channel = builder.with(new WordCensor("secret")).with(new WordCensor("code")).with(new WordCensor("visual studio")).getDecoratedChannel(props);

		channel.deliverMessage("It's not a secret that a visual studio code is the best ide.");
		// Spy channel. Should get the one created before
		TestSpySocialChannel spyChannel = (TestSpySocialChannel) builder.buildChannel(props);
		assertEquals("It's not a *** that a *** *** is the best ide.", spyChannel.lastMessagePublished());
	}  
}
