/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.ArrayList;

/**
 *
 * @author Profe
 */
public class PersonToUI {
    private String name;
    private ArrayList<BankCheckToUI> bankChecks;
    private int total;

    PersonToUI(Person p) {
        name = p.getName();
        total = p.getTotal();
        bankChecks = new ArrayList<>();
        for (BankCheck c : p.getBankChecks()) {
            bankChecks.add(c.getUIversion());
        }
    }
    
    public String getName() {
        return name;
    }
    
    public int getTotal () {
        return total;
    }
    
    public ArrayList<BankCheckToUI> getBankChecks () {
        return bankChecks;
    }
}
