/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tutorialgui;

import View.GUI.MainWindow;
import Controller.Controller;
import View.GUI2.MainWindow_v2;
import model.Model;
import View.View;

/**
 *
 * @author Profe
 */
public class TutorialGUI {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Model model = new Model();
        View view = MainWindow.getInstance();
//        View view = MainWindow_v2.getInstance();
        Controller controller = Controller.getInstance();
        controller.setModelView (model,view);
        controller.start();
    }
    
}
