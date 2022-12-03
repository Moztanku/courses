package eu.jpereira.trainings.designpatterns.structural.facade;

import eu.jpereira.trainings.designpatterns.structural.facade.model.Book;
import eu.jpereira.trainings.designpatterns.structural.facade.model.Customer;
import eu.jpereira.trainings.designpatterns.structural.facade.model.DispatchReceipt;
import eu.jpereira.trainings.designpatterns.structural.facade.model.Order;
import eu.jpereira.trainings.designpatterns.structural.facade.service.BookDBService;
import eu.jpereira.trainings.designpatterns.structural.facade.service.CustomerDBService;
import eu.jpereira.trainings.designpatterns.structural.facade.service.CustomerNotificationService;
import eu.jpereira.trainings.designpatterns.structural.facade.service.OrderingService;
import eu.jpereira.trainings.designpatterns.structural.facade.service.WharehouseService;

public class DefaultBookstoreFacade implements BookstoreFacade {
    BookDBService bookDBService;
    CustomerDBService customerDBService;
    CustomerNotificationService customerNotificationService;
    OrderingService orderingService;
    WharehouseService wharehouseService;

    @Override
    public void placeOrder(String customerId, String isbn) {
        Order order = orderingService.createOrder(
            customerDBService.findCustomerById(customerId),
            bookDBService.findBookByISBN(isbn)
        );
        customerNotificationService.notifyClient(
            wharehouseService.dispatch(order)
        );
    }
    
    public void setBookDBService(BookDBService bookDBService) {
        this.bookDBService = bookDBService;
    }
    public void setCustomerDBService(CustomerDBService customerDBService) {
        this.customerDBService = customerDBService;
    }
    public void setCustomerNotificationService(CustomerNotificationService customerNotificationService) {
        this.customerNotificationService = customerNotificationService;
    }
    public void setOrderingService(OrderingService orderingService) {
        this.orderingService = orderingService;
    }
    public void setWharehouseService(WharehouseService wharehouseService) {
        this.wharehouseService = wharehouseService;
    }
}
