/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package View;

import java.util.ArrayList;

/**
 *
 * @author Profe
 */
public interface View {
    public void updateView();
    public void showView();
    public String getAppName();
    // Dialogs
    public ArrayList<String> getNames();
    // Messages
    public boolean confirmExitMessage();   
}
