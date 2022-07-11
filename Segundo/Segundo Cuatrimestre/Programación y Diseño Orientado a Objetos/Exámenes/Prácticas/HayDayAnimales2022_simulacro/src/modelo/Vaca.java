/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

/**
 *
 * @author Profe
 */
public class Vaca extends Animal{
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    public static final String ICONO = "/img/vaca.png";
    public static final String ICONO32 = "/img/vaca32.png";
    public static final int MAX_PRODUCCION = 2;
    public static final int PRECIO = 10;
    public static final int PIENSO = 2;
    
    
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------
    public Vaca(){
        super(TipoAnimal.VACA, MAX_PRODUCCION, PIENSO, PRECIO);
    }
    
    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------
    
}
