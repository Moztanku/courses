import java.util.Random;

import javafx.event.EventHandler;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.Shape;

/**
 * Class implementing rectangle shape
 */
public class fxRectangle extends Rectangle implements fxShape{
    private double anchorX;
    private double anchorY;
    private Color color;

    /**
     * Initializing rectangle
     * @param x y coordinate
     * @param y x coordinate
     * @param w width
     * @param h height
     */
    public fxRectangle(double x,double y,double w,double h){
        super(x,y,w,h);
        anchorX = x;
        anchorY = y;

        Random random = new Random();
        color = new Color(random.nextDouble(1), random.nextDouble(1), random.nextDouble(1), 1.0);
        setFill(color);
        setOnMousePressed(new fxMouseEventHandler());
        setOnMouseDragged(new fxMouseEventHandler());
        setOnScroll(new fxScrollEventHandler());
    };
    
    public void setAnchor(double x,double y){
        anchorX = x;
        anchorY = y;
    }
    public boolean ishit(double x,double y){
        return getBoundsInLocal().contains(x,y);
    }
    public void resize(double x,double y){
        if(x<anchorX){
            setX(x);
            setWidth(anchorX-x);
        }else{
            setX(anchorX);
            setWidth(x-anchorX);
        }
        if(y<anchorY){
            setY(y);
            setHeight(anchorY-y);
        }else{
            setY(anchorY);
            setHeight(y-anchorY);
        }
    }
    public void move(double x,double y){
        //System.out.println(getX()-(x-(anchorX-getX()))+getY()-(y-(anchorY-getY())));
        setX(x-(anchorX-getX()));
        setY(y-(anchorY-getY()));
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
                    rotate((event.getSceneY()-anchorY)*0.1);
                    setAnchor(event.getSceneX(),event.getSceneY());
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


