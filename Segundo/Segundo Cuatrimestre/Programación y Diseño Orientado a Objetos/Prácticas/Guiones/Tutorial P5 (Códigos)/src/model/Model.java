/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author Profe
 */
public class Model {
    private ArrayList<Person> people;
    private Person current;
    private int indexCurrent;
    private AppState state;
    private final int MINTOSPEND;
    
    private final Random r = new Random();
    
    public Model() {
      people = new ArrayList<>();
      current = null;
      indexCurrent = -1;
      state = AppState.NOTINIT;
      MINTOSPEND = 1000;
    }
    
    Person getCurrent() {
        return current;
    }
    
    public void init (ArrayList<String> names) {
        for (String n : names) {
            people.add (new Person (n));
        }
        indexCurrent = r.nextInt (people.size());
        current = people.get(indexCurrent);
        updateState();
    }

    public void next () {
        indexCurrent = (indexCurrent+1) % people.size();
        current = people.get(indexCurrent);
        updateState();
    }
    
    private void updateState() {
        if (current.getTotal() < MINTOSPEND)
            state = AppState.PERSONCANNOTSPEND;
        else
            state = AppState.PERSONCANSPEND;
    }
    
    public AppState getAppState () {
        return state;
    }
    
    public void getAnotherBankCheck () {
        current.getAnotherBankCheck();
        updateState();
    }
    
    public void spendBankCheck (int i) {
        if (state == AppState.PERSONCANSPEND)
            current.spendBankCheck(i);
        updateState();
    }
    
    public int getTotal () {
        return current.getTotal();
    }

    public ModelToUI getUIversion() {
        return new ModelToUI(this);
    }
    
}
