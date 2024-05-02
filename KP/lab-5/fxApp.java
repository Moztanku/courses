import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

/**
    * Main class responsible for running this program.
    * @author Jacek Zub
*/
public class fxApp extends Application{
    /**
     * Variable used to store workspace.
     */
    private fxPane workspace;

    /**
     * Function run at launch responsible for setting up the workspace and menu buttons.
     * @param mainStage Main application window.
     */
    @Override
    public void start(Stage mainStage){
        VBox mainBox = new VBox();  // Creating app's root Node.

        HBox menu = new HBox(); // Creating menu Node
        menu.setSpacing(5);
        menu.setStyle("-fx-background-color : #eee0ee;");
        menu.setPrefHeight(55); // Setting up menu

        workspace = new fxPane(mainStage);
        workspace.setStyle("-fx-background-color : #f0f0f0;");  // Setting up workspace 
        
        VBox.setVgrow(workspace, Priority.ALWAYS);  //  Making sure that workspace will adjust to window resizing
        mainBox.getChildren().addAll(menu,workspace);   //  Adding menu and workspace Nodes to mainBox (the root Node)

        menu.getChildren().addAll(
            new fxButton("RECTANGLE"),
            new fxButton("ELLIPSE"),
            new fxButton("TRIANGLE"),
            new fxButton("INFORMATION")
        );  //  Adding buttons to menu
        
        Scene scene = new Scene(mainBox,600,500);   // Setting up Scene

        mainStage.setTitle("Figury Gui");
        mainStage.setScene(scene);
        mainStage.show();   // Setting up window (Stage)
    }
    /**
     * Class used to create menu buttons
     */
    private class fxButton extends Button{
        /**
         * Constructor setting up Button functions and formatting.
         * @param str Button's text and function
         */
        public fxButton(String str){
            super(str); // Calling Button(str);

            setFont(new Font("Impact",26));
            setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
            HBox.setHgrow(this, Priority.ALWAYS);   // Setting up formatting
            if(str=="INFORMATION"){ // INFORMATION Button is a special case, handled differently.
                setOnAction(event -> {
                    Alert alert = new Alert(AlertType.INFORMATION);
                    alert.setTitle("Information Dialog");
                    alert.setHeaderText(
                        "\"Figury GUI\" by Jacek Zub, 2022\n"+
                        "How to use:"
                    );
                    alert.setContentText(
                        "Buttons:+\n"+
                        "    RECTANGLE - press and hold LMB to draw a rectangle\n"+
                        "    ELLIPSE - press and hold LMB to draw a ellipse\n"+
                        "    TRIANGLE - press and hold LMB to draw a triangle\n"+
                        "    INFORMATION - open this dialogue box\n"+
                        "Drawing Area:\n"+
                        "    LMB - drag shape around\n"+
                        "    RMB - change shape colour\n"+
                        "    MMB - rotate shape\n"+
                        "    Scroll - change shape scale"
                    );
                    alert.showAndWait();
                }); // On button press it'll show dialogue box with above text.
            }
            else{
                setOnAction(event -> workspace.setState(str));  // Standard case in which button will change workspace state to drawing either rectangle, ellipse or triangle
            }
        }
    }

    /**
     * The starting point
     * @param args console arguments
     */
    public static void main(String[] args) {
        launch(args);   // JavaFx does stuff here.
    }
}
