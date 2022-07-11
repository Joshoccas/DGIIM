/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.Random;

/**
 *
 * @author Profe
 */
class BankCheck {
    
    static private final int MAX = 1000;
    private final Random r;
    
    private int amount = 0;

    BankCheck () {
        r = new Random();
        amount = r.nextInt(MAX)+1;
    }
    
    int getAmount() {
        return amount;
    }
    
    BankCheckToUI getUIversion() {
        return new BankCheckToUI (this);
    }
}
