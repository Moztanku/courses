package eu.jpereira.trainings.designpatterns.behavioral.chain.fakes;

import java.io.IOException;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

import eu.jpereira.trainings.designpatterns.behavioral.chain.filter.AbstractFilter;

public class FakeFormatFillter extends AbstractFilter {

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        
            chain.doFilter(request, response);
            response.getOutputStream().print(" :Formated");
    }
    
}
