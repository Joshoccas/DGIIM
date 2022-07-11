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
public class BankCheckToUI {
    private int amount;

    BankCheckToUI(BankCheck c) {
        amount = c.getAmount();
    }
    
    public int getAmount () {
        return amount;
    }
    
}
