import java.util.Vector;

import javafx.event.EventHandler;
import javafx.scene.control.ColorPicker;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.stage.Popup;
import javafx.stage.Stage;

/**
 * Class that sets up area used for drawing different shapes.
 */
public class fxPane extends Pane{
    /**
     * Vector storing all shapes on this Node.
     */
    Vector<fxShape> shapes = new Vector<fxShape>();
    /**
     * Variable used to determine which shape should be drawn.
     * @see fxMouseEventHandler
     */
    private String currentState = "IDLE";
    /**
     * Reference to app's window used to display popup window.
     * @see pop
     */
    private Stage stageRef;
    /**
     * Popup window used to display colorPicker.
     */
    fxPopup pop = new fxPopup();

    /**
     * Constructor setting up drawing area.
     * @param _stage Application window.
     */
    public fxPane(Stage _stage){
        super();
        stageRef = _stage;
        fxMouseEventHandler handler = new fxMouseEventHandler();
        setOnMousePressed(handler);
        setOnMouseDragged(handler);
        setOnMouseReleased(handler);
    }
    /**
     * Method setting this objects state.
     * @param str Should be either "TRIANGLE","RECTANGLE","ELLIPSE" or "IDLE".
     */
    public void setState(String str){
        currentState = str;
    }    
    /**
     * Class used for changing shapes colour.
     */
    private class fxPopup extends Popup{
        private ColorPicker cp;
        /**
         * Reference to a shape you've clicked onto.
         */
        private fxShape refShape;

        public fxPopup(){
            super();    // Calling Popup()
            setAutoFix(true);
            setAutoHide(true);  // Popup will close after picking colour or, clicking elswhere.

            cp = new ColorPicker();
            cp.setOnAction(event -> refShape.setColor(cp.getValue()));  // ColorPicker will change refrenced shape color.
            getContent().add(cp);   // Adding ColorPicker to this object.
        }
        /**
         * Showing ColorPicker on x,y coordinates
         */
        public void showCP(double x,double y){
            setX(x+stageRef.getX());
            setY(y+stageRef.getY());
            show(stageRef);
        };
        public void setRefShape(fxShape x){ // Selfexplanatory
            refShape = x;
        }
        public ColorPicker getCP(){ // Get ColorPicker
            return cp;
        };
    }
    /**
     * Event handler for fxPane
     */
    private class fxMouseEventHandler implements EventHandler<MouseEvent>{
        /**
         * Reference to a shape being drawn currently.
         */
        private fxShape shapeRef;

        /**
         * Handles drawing of a new shape and changing colour of existing ones.
         * @param event Mouse event.
         */
        @Override
        public void handle(MouseEvent event) {
            switch(currentState){   // Checks which shape should be drawn
                case "RECTANGLE":
                    if(event.getEventType() == MouseEvent.MOUSE_PRESSED){
                        shapeRef = new fxRectangle(event.getX(), event.getY(), 0, 0);
                        getChildren().add(shapeRef.getShape()); // On mouse pressed the shape is created and added to this Node's children
                    }else if(event.getEventType() == MouseEvent.MOUSE_DRAGGED){
                        shapeRef.resize(event.getX(), event.getY());    // On mouse dragged the shape is resized by mouse cursor
                    }else if(event.getEventType() == MouseEvent.MOUSE_RELEASED){
                        shapes.add(shapeRef);
                        currentState = "IDLE";  // On mouse release drawing is complete
                    }
                    break;
                case "ELLIPSE":
                    if(event.getEventType() == MouseEvent.MOUSE_PRESSED){
                        shapeRef = new fxEllipse(event.getX(), event.getY(), 0, 0);
                        getChildren().add(shapeRef.getShape()); // On mouse pressed the shape is created and added to this Node's children
                    }else if(event.getEventType() == MouseEvent.MOUSE_DRAGGED){
                        shapeRef.resize(event.getX(), event.getY());    // On mouse dragged the shape is resized by mouse cursor
                    }else if(event.getEventType() == MouseEvent.MOUSE_RELEASED){
                        shapes.add(shapeRef);
                        currentState = "IDLE";  // On mouse release drawing is complete
                    }
                    break;
                case "TRIANGLE":
                    if(event.getEventType() == MouseEvent.MOUSE_PRESSED){
                        shapeRef = new fxTriangle(event.getX(), event.getY(),event.getX(),event.getY());
                        getChildren().add(shapeRef.getShape()); // On mouse pressed the shape is created and added to this Node's children
                    }else if(event.getEventType() == MouseEvent.MOUSE_DRAGGED){
                        shapeRef.resize(event.getX(), event.getY());    // On mouse dragged the shape is resized by mouse cursor
                    }else if(event.getEventType() == MouseEvent.MOUSE_RELEASED){
                        shapes.add(shapeRef);
                        currentState = "IDLE";  // On mouse release drawing is complete
                    }
                    break;
                case "IDLE":
                    if(event.getEventType() == MouseEvent.MOUSE_PRESSED && event.getButton() == MouseButton.SECONDARY){
                        for(fxShape x : shapes){
                            if(x.ishit(event.getX(), event.getY())){
                                pop.getCP().setValue(x.getColor());
                                pop.setRefShape(x);
                                pop.showCP(event.getSceneX(),event.getSceneY());    // Shows ColorPicker if state is "IDLE" and RMB is pressed
                            }
                        }  
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
