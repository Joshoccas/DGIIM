/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author Profe
 */
public class ModelToUI {
    private PersonToUI current;
    
    public ModelToUI (Model m) {
        current = m.getCurrent().getUIversion();
    }
    
    public PersonToUI getCurrent () {
        return current;
    }
}
