/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import static modelo.Vaca.PRECIO;

/**
 *
 * @author Profe
 */
public class Gallina extends Animal{
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    public static final String ICONO = "/img/gallina.png";
    public static final String ICONO32 = "/img/gallina32.png";
    public static final int MAX_PRODUCCION = 1;
    public static final int PRECIO = 5;
    public static final int PIENSO = 1;
    
    
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------
    public Gallina(){
        super(TipoAnimal.GALLINA, MAX_PRODUCCION, PIENSO, PRECIO);
    }
    
    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------


    
}
