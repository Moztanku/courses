import java.util.Random;

import javafx.event.EventHandler;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.Ellipse;
import javafx.scene.shape.Shape;

/**
 * Class implementing ellipse shape
 */
public class fxEllipse extends Ellipse implements fxShape{
    private double anchorX;
    private double anchorY;
    private Color color;

    /**
     * Initializing ellipse
     * @param x y coordinate
     * @param y x coordinate
     * @param w width
     * @param h height
     */
    public fxEllipse(double x,double y,double w,double h){
        super(x,y,w,h);
        anchorX = x;
        anchorY = y;

        Random random = new Random();
        color = new Color(random.nextDouble(1), random.nextDouble(1), random.nextDouble(1), 1.0);
        setFill(color);
        setOnMousePressed(new fxMouseEventHandler());
        setOnMouseDragged(new fxMouseEventHandler());
        setOnScroll(new fxScrollEventHandler());
    }
    /**
     * Sets anchor used to resize shape during initialization
     */
    public void setAnchor(double x,double y){
        anchorX = x;
        anchorY = y;
    }
    /**
     * Checks if shape is hit with mouse
     */
    public boolean ishit(double x,double y){
        return getBoundsInLocal().contains(x,y);
    }
    public void resize(double x,double y){
        setRadiusX(Math.abs(anchorX-x));
        setRadiusY(Math.abs(anchorY-y));
    }
    public void move(double x,double y){
        setCenterX(getCenterX()+(x-anchorX));
        setCenterY(getCenterY()+(y-anchorY));
    }
    public void scale(double x){
        if(getScaleX()<0)
            setVisible(false);
        setScaleX(getScaleX()+x);
        setScaleY(getScaleY()+x);
    }
    public void rotate(double x){
        setRotate(getRotate()+x);
    }

    public void setColor(Color _color){
        color = _color;
        setFill(color);
    }
    public Color getColor(){
        return color;
    }
    /**
     * Returns this object
     */
    public Shape getShape(){
        return this;
    }
    /**
     * Handles mouse events
     */
    private class fxMouseEventHandler implements EventHandler<MouseEvent>{
        @Override
        public void handle(MouseEvent event) {
        if(event.getEventType() == MouseEvent.MOUSE_PRESSED){
            if(event.getButton() == MouseButton.PRIMARY){
                setAnchor(event.getSceneX(),event.getSceneY());
            }
            if(event.getButton() == MouseButton.MIDDLE){
                setAnchor(event.getSceneX(),event.getSceneY());
            }
        }
        if(event.getEventType() == MouseEvent.MOUSE_DRAGGED){
            if(event.getButton() == MouseButton.PRIMARY){
                move(event.getSceneX(),event.getSceneY());
                setAnchor(event.getSceneX(),event.getSceneY());
            }
            if(event.getButton() == MouseButton.MIDDLE){
                rotate((event.getSceneY()-anchorY)*0.004);
            }
        }
            
        }
    }
    private class fxScrollEventHandler implements EventHandler<ScrollEvent>{
        @Override
        public void handle(ScrollEvent event) {
            System.out.println("SCROLL: "+event.getDeltaY());
            scale(event.getDeltaY()*0.0004);
        }
    }
}
