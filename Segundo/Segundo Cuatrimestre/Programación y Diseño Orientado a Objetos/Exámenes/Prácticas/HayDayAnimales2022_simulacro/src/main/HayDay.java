/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package main;

import controlador.Controlador;
import java.util.ArrayList;
import java.util.Arrays;
import modelo.ProductoAnimal;
import modelo.Animal;
import modelo.Gallina;
import modelo.Leche;
import modelo.Huevo;
import modelo.Vaca;
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
        // a) Cree 1 lista de animales con 2 gallinas y 1 vaca 
        ArrayList<Animal> parcelas = new ArrayList<>(Arrays.asList(new Gallina(),
            new Gallina(),
            new Vaca()
        ));
        // b) y 3 productos de animales disponibles (2 huevos; 1 leche)
        ArrayList<ProductoAnimal> productosDisponibles = new ArrayList<>(Arrays.asList(new Huevo(),
            new Huevo(),
            new Leche()
        ));
        
       
        // c) Inicia la vista y controlador
        VistaPrincipal vista = new VistaPrincipal();
        Controlador.instancia.start(vista, parcelas, productosDisponibles);
    }
    
}
