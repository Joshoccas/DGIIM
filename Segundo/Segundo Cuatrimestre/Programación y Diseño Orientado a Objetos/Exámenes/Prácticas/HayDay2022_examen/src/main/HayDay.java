/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package main;

import controlador.Controlador;
import java.util.ArrayList;
import modelo.Cultivo;
import modelo.Parcela;
import modelo.Soja;
import modelo.Trigo;
import vista.VistaPrincipal;



/**
 *
 * @author Profe
 */
public class HayDay {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // ----
        // EXAMEN
                
           
        // a) Cree 2 parcelas nuevas 
       Parcela p1 = new Parcela();
       Parcela p2 =  new Parcela();
       ArrayList<Parcela> parcelas = new ArrayList<>();
       parcelas.add(p1);
       parcelas.add(p2);
       
        // b) Cree y 3 cultivos disponibles (2 trigos; 1 soja)
        ArrayList<Cultivo> cultivosDisponibles = new ArrayList<>();
        cultivosDisponibles.add(new Trigo());
        cultivosDisponibles.add(new Trigo());
        cultivosDisponibles.add(new Soja());
        cultivosDisponibles.get(0).setRiego(20);
        
        System.out.println(cultivosDisponibles.get(0).getRiego());
        
        // c) Cree la vista e inica el controlador
        VistaPrincipal vista = new VistaPrincipal();
        // llamar a start()
        Controlador.instancia.start(vista, parcelas, cultivosDisponibles);
        // FIN DE EXAMEN
        // ----
    }
    
}
