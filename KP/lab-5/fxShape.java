import javafx.scene.paint.Color;
import javafx.scene.shape.Shape;

public interface fxShape{
    
    /**
     * Sets anchor used to resize shape when creating it
     */
    public void setAnchor(double x,double y);
    /**
     * Checks if shape is hit with mouse
     */
    public boolean ishit(double x,double y);
    public void resize(double x,double y);
    public void move(double x,double y);
    public void scale(double x);
    public void rotate(double x);


    public void setColor(Color color);
    public Color getColor();
    /**
     * Returns this object
     * @return this object
     */
    public Shape getShape();
}